# Specific part of the Makefile
EXEC=exec

# Begin generic part of the Makefile
CC = gcc
CFLAGS = -Werror -Wextra -Wall -pedantic
LDFLAGS =

OBJ = couche1.o\
			couche2.o\
			couche3.o\
			couche4.o\
			couche5.o

SRCDIR = src
BINDIR = bin
OBJDIR = obj
DISKSDIR = disk

RAID5DIR = Raid5

ifeq ($(DEBUG),yes)
	CFLAG += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(EXEC)

$(EXEC): $(OBJ) main.o
	$(CC) -o $@ $^ $(LDFLAGS)
	mv *.o $(OBJDIR)/
	mv $(EXEC) $(BINDIR)/

%.o: $(SRCDIR)/$(RAID5DIR)/%.c
		$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

main.o: $(SRCDIR)/main.c
		$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

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
