CFLAGS = -Wall -std=c11
ARFLAGS = -rcs
#LDFLAGS =
#CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

INC = -I.
LIBINSC = -L.
SZJLIB = szjlib.a

SZJLIB_DIR = ./szjlib
EXAMPLES_DIR = ./examples
BIN_DIR = .
OBJS_DIR = ./objs

DIRS = $(OBJS_DIR)
SZJLIB_SRC = $(wildcard $(SZJLIB_DIR)/*.c)
SZJLIB_OBJS = $(patsubst %.c, %.o, $(SZJLIB_SRC))

EXAMPLES_SRC = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLES = $(patsubst %.c, %.out, $(notdir $(EXAMPLES_SRC)))

BINS := $(addprefix $(BINS_DIR)/, $(BINS))

all:$(EXAMPLES) $(SZJLIB)

$(EXAMPLES):$(SZJLIB) $(EXAMPLES_SRC)
	$(CC) $(INC) $(CFLAGS) $(EXAMPLES_DIR)/$@.c $< -o $@

$(SZJLIB):$(SZJLIB_OBJS)
	@echo "# create lib file"
	$(AR) $(ARFLAGS) $@ $?

%.o:%.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

.PHONY: clean info debug

info:
	@echo "***********************"
	@echo "* SRC:      "$(SZJLIB_SRC)
	@echo "* LIB:      "$(SZJLIB)
	@echo "* EXAMPLES: "$(EXAMPLES)
	@echo "***********************"

clean:
	rm -rf $(EXAMPLES) $(SZJLIB) $(SZJLIB_DIR)/*.o
