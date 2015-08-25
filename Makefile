DESTDIR=
PREFIX=/usr
CC=gcc

dpmstimeout: dpmstimeout.c
	$(CC) -o dpmstimeout dpmstimeout.c \
		-I/usr/X11R6/include \
		-L/usr/X11R6/lib \
		-lXext -lX11

.PHONY: clean
clean:
	rm dpmstimeout

.PHONY: install
install: dpmstimeout dpmslock
	install -Dm 755 dpmstimeout ${DESTDIR}${PREFIX}/bin/dpmstimeout
	install -Dm 755 dpmslock ${DESTDIR}${PREFIX}/bin/dpmslock
