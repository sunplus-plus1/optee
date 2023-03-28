CROSS_C = /home/haiq.tang/new/crossgcc/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
TEEC_EXPORT = ../../../optee_client/out/export/usr
CC      = $(CROSS_C)gcc
LD      = $(CROSS_C)ld
AR      ?= $(CROSS_C)ar
NM      ?= $(CROSS_C)nm
OBJCOPY ?= $(CROSS_C)objcopy
OBJDUMP ?= $(CROSS_C)objdump
READELF ?= $(CROSS_C)readelf

OBJS = main.o

CFLAGS += -Wall -I../ta/include -I$(TEEC_EXPORT)/include -I./include
#Add/link other required libraries here
LDFLAGS  = -L $(shell dirname `$(CC) -print-libgcc-file-name`) -lgcc


CFLAGS += -I$(TEEC_EXPORT)/include
LDADD += -lteec -L$(TEEC_EXPORT)/lib

BINARY = optee_example_random

.PHONY: all
all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $< $(LDADD)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BINARY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
