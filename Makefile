CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CFLAGS = -Wall -std=c11
ARFLAGS = -rcs

INC = -I.
SZJLIB = szjlib.a
SZJLIB_DIR = ./szjlib
EXAMPLES_DIR = ./examples

SZJLIB_SRC = $(wildcard $(SZJLIB_DIR)/*.c)
SZJLIB_OBJS = $(patsubst %.c, %.o, $(SZJLIB_SRC))

EXAMPLES_SRC = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLES = $(patsubst %.c, %.out, $(notdir $(EXAMPLES_SRC)))

all:$(EXAMPLES) $(SZJLIB)

$(EXAMPLES):$(SZJLIB) $(EXAMPLES_SRC)
	$(CC) $(INC) $(CFLAGS) $(EXAMPLES_DIR)/$(basename $@).c $< -o $@

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
