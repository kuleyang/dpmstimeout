CC=gcc
DESTDIR=/usr/local/bin

all: xtimeout

xtimeout: xtimeout.c
	$(CC) -o xtimeout xtimeout.c -lXext -lX11

install: xtimeout
	install -Dm 755 xtimeout $(DESTDIR)/xtimeout
