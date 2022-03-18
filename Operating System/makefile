CC = gcc
TARGET = 22_shell

CSRC = $(TARGET).c

COBJ = $(CSRC:.c=.o)

OPT = 2
CDEFS =
DEBUG = gdb3

CFLAGS = $(CDEFS) -O$(OPT) -I. -g$(DEBUG) -Wunused-result
LDFLAGS = -lm -lpthread

all: $(TARGET).out

$(TARGET).out: $(COBJ)
	@echo "linking ..."
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(COBJ):%.o: %.c
	@echo "compiling $< ..."
	$(CC) -c $(CFLAGS) $<

clean:
	@echo "deleting files"
	rm -f $(TARGET).out $(COBJ)

.PHONY: all clean



