nrlteams: nrld/rabbitohs.h nrld/eels.h nrld/roosters.h nrld/seaeagles.h nrld/bulldogs.h \
	nrld/broncos.h nrld/warriors.h nrld/panthers.h nrld/storm.h nrld/raiders.h nrld/sharks.h \
	 nrld/dragons.h nrld/tigers.h nrld/knights.h nrld/titans.h nrld/cowboys.h

nrl: singnrl.c nrl.c nrl.h spi.h gpio-mmap.h nrlteams 
	gcc -o nrl singnrl.c -lrt -DIMX 
	sudo chown root:root nrl
	sudo chmod 6711 nrl

aflteams: afld/blues.h afld/cats.h afld/eagles.h afld/hawks.h afld/lions.h afld/saints.h \
	afld/swans.h afld/bombers.h afld/crows.h afld/giants.h afld/kangaroos.h afld/magpies.h \
	afld/suns.h afld/tigers.h afld/demons.h afld/power.h

afl: singafl.c afl.c afl.h spi.h gpio-mmap.h aflteams 
	gcc -o afl singafl.c -lrt -DIMX
	sudo chown root:root afl
	sudo chmod 6711 afl


