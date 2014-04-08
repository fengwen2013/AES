IDIR = .
CC = gcc
CFLAGS = -I$(IDIR) -g -Wall
_DEPS = hw6.h
DEPS = $(pathsubst %, $(IDIR)/%, $(_DEPS))

OBJ = hw6.o decrypt.o encrypt.o tablecheck.o util.o modprod.o keyexpand.o inverse.o

hw6: $(OBJ)
	$(CC) $^ -o $@

./%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o hw6
