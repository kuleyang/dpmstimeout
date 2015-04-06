DESTDIR=
PREFIX=/usr
CC=gcc

dpmstimeout: dpmstimeout.c
	$(CC) -o dpmstimeout dpmstimeout.c -lXext -lX11

install: dpmstimeout
	install -Dm 755 dpmstimeout ${DESTDIR}${PREFIX}/bin/dpmstimeout
