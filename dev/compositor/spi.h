#ifdef IMX
#include "gpio-mmap.h"
// GPIO 19 = SSP2_SS = Arduino SS
// GPIO 23 = Arduino "ACK/BUSY"

#define GPIO_ARDUINO_START      19
#define GPIO_ARDUINO_ACKBUSY    23

#endif

#include <linux/spi/spidev.h>

static const char *device = "/dev/spidev1.0";
static uint32_t speed = 1250000;
static uint8_t mode;
static uint8_t bits = 8;
static uint16_t delay;
static int spi_fd;

static void pabort(const char *s)
{
    perror(s);
    abort();
}

void spi_open()
{
#ifdef IMX
    gpio_map();
    GPIO_WRITE_PIN(GPIO_ARDUINO_START, 1);
    gpio_output(0, GPIO_ARDUINO_START);  //bank 0 bit 19 = GPIO10 = GPIO_ARDUINO_START
    gpio_input(0, GPIO_ARDUINO_ACKBUSY); //bank 0 bit 23 = GPIO23 = GPIO_ARDUINO_ACKBUSY
#endif

    int ret;

    spi_fd = open(device, O_RDWR);
    if (spi_fd < 0)
        pabort("can't open device");

    /*
     * spi mode
     */
    ret = ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
        pabort("can't set spi mode");

    ret = ioctl(spi_fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
        pabort("can't get spi mode");

    /*
     * bits per word
     */
    ret = ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't set bits per word");

    ret = ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't get bits per word");

    /*
     * max speed hz
     */
    ret = ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("can't set max speed hz");

    ret = ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("can't get max speed hz");

    printf("spi mode: %d\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed: %d Hz (%d KHz)\n", speed, speed / 1000);
}

void spi_close()
{
    close(spi_fd);
}

static void spi_send(uint8_t txbuf[], int buffsize)
{
//printf("spi_send\n");

#ifdef IMX
    if (GPIO_READ_PIN(GPIO_ARDUINO_ACKBUSY) == 0)
        return; // Arduino still busy

    GPIO_WRITE_PIN(GPIO_ARDUINO_START, 0); // START active

    uint8_t j = 0;
    while (GPIO_READ_PIN(GPIO_ARDUINO_ACKBUSY) == 1 && j++ < 255)
        ; // wait for Arduino ack

    if (GPIO_READ_PIN(GPIO_ARDUINO_ACKBUSY) == 1)
    {
        GPIO_WRITE_PIN(GPIO_ARDUINO_START, 1); // START inactive
        return;                                // Arduino not responding
    }
#endif

    int ret;
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)txbuf,
        .rx_buf = 0,
        .len = buffsize,
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bits,
    };

    //printf("buffsize %d\n", buffsize);
    ret = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
        perror("can't send spi message");

#ifdef IMX
    GPIO_WRITE_PIN(GPIO_ARDUINO_START, 1); // START inactive
#endif
}
