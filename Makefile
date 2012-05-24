# binclock makefile
# 2012-05-23 16:51
# by Ian D Brunton <iandbrunton at gmail dot com>

APPNAME=binclock
VERSION=1.1
CC=gcc
CFLAGS=-c -g -Wall -DVERSION=\"$(VERSION)\" -DAPPNAME=\"$(APPNAME)\"
#LDFLAGS=-Wl
SRC=main.c
OBJ=$(SRC:.c=.o)

all: $(APPNAME)

$(APPNAME): $(OBJ)
	$(CC) $(LDFLAGS) -Wl,--start-group $(OBJ) -Wl,--end-group -o $@

.c.o:
	$(CC) $(CFLAGS)  $< -o $@

clean:
	rm -rf *.o $(APPNAME)
