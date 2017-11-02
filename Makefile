CC=gcc
CFLAGS=-Wall -g


clean:
	rm -f bin/*

all:
	$(CC) $(CFLAGS) src/keyboard_backlight.c -o bin/keyboard_backlight
	$(CC) $(CFLAGS) src/monitor_backlight.c -o bin/monitor_backlight
