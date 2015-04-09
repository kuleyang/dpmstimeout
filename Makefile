DESTDIR=
PREFIX=/usr
CC=gcc

dpmstimeout: dpmstimeout.c
	$(CC) -o dpmstimeout dpmstimeout.c -lXext -lX11

.PHONY:
install: dpmstimeout dpmslock
	install -Dm 755 dpmstimeout ${DESTDIR}${PREFIX}/bin/dpmstimeout
	install -Dm 755 dpmslock ${DESTDIR}${PREFIX}/bin/dpmslock
