# Specific part of the Makefile
EXEC = Exec

# Begin generic part of the Makefile
CC = gcc
CFLAGS = -Werror -Wextra -Wall -pedantic
LDFLAGS =

SRC = couche1.c\
			couche2.c\
			couche3.c\
			couche4.c\
			couche5.c
OBJ = $(SRC:.c=.o)
HEAD = $(SRC:.c=.h)

SRCDIR = src
BINDIR = bin
OBJDIR = obj
HEADIR = headers
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
	@$(CC) -o $@ $^ $(LDFLAGS)
	@mv *.o $(OBJDIR)/
	@mv $(EXEC) $(BINDIR)/
	@echo "Création de l'executabe "$@

%.o: $(SRCDIR)/$(RAID5DIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
	
%.o: $(SRCDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: clean mrproper doc

doc: stack.h main.c
	@echo "Creation de la documentation"
	@doxygen doc/doxyfile


clean:
	@rm -f $(OBJDIR)/*.o
	@echo "Fichiers intermédiaires supprimés"

mrproper: clean
	@rm -f $(BINDIR)/*
	@echo "Executable supprimé"
# End generic part of the makefile

# Specific file dependencies
