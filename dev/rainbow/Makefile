#cliclr: cliclr.c spi.h gpio-mmap.h
#	gcc -o cliclr cliclr.c -DIMX -DPROTO
#	sudo chown root:root cliclr
#	sudo chmod 6711 cliclr

#rand: sing.c rand.c spi.h gpio-mmap.h
#	gcc -o rand sing.c -lrt -DIMX
#	chmod 6711 rand

#spectrum: singspec.c spectrum.c spi.h gpio-mmap.h
#	gcc -o spectrum singspec.c -lrt -DIMX
#	chmod 6711 spectrum

rainbow: singbow.c rainbow.c spi.h gpio-mmap.h
	gcc -o rainbow singbow.c -lrt -DIMX 
	sudo chown root:root rainbow
	sudo chmod 6711 rainbow

