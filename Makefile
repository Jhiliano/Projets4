# Specific part of the Makefile
EXEC=exec

# Begin generic part of the Makefile
CC=gcc
CFLAGS=-std=c99 -Werror -Wextra -Wall -ansi -pedantic
LDFLAGS=

SRCDIR = src
BINDIR = bin
OBJDIR = obj
DISKSDIR = disk

RAID5DIR = raid5

ifeq ($(DEBUG),yes)
	CFLAG += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	mv *.o $(OBJDIR)/
	mv $(EXEC) $(BINDIR)/

%.o: $(SRCDIR)/$(RAID5DIR)/%.c
		$(CC) -o $@ -c $< $(SYS) $(INC)

.PHONY: clean mrproper doc

doc: stack.h main.c
	@doxygen doc/doxyfile

clean:
	rm -f *.o
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*

mrproper: clean
	@rm -rf $(EXEC)
# End generic part of the makefile

# Specific file dependencies
