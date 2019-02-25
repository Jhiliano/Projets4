# Specific part of the Makefile
EXEC = Exec
CREATEDISK = createdisk
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
CREATEDISKDIR = genDisk



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
	@echo "Création de l'executabe "$@
	@$(CC) -o $@ $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)
	@mv $(EXEC) $(BINDIR)/


%.o: $(SRCDIR)/$(RAID5DIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
	@mv *.o $(OBJDIR)/

%.o: $(SRCDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
	@mv *.o $(OBJDIR)/

.PHONY: clean mrproper doc

doc:
	@echo "Creation de la documentation"
	@doxygen doc/doxyfile

$(CREATEDISK): $(SRCDIR)/$(CREATEDISKDIR)/$(addsuffix .c,$(CREATEDISK))
	@echo "Création de l'executable de generation du disque"
	@$(CC) -o $@ $^
	@mv $(CREATEDISK) $(BINDIR)/
	@./bin/$@ $(DISKSDIR) 4 51200

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "Fichiers intermédiaires supprimés"

mrproper: clean
	@rm -f $(BINDIR)/*
	@echo "Executable supprimé"
# End generic part of the makefile

# Specific file dependencies
main.o: $(addprefix $(HEADIR)/$(RAID5DIR)/,$(HEAD))
couche2.o: $(HEADIR)/$(RAID5DIR)/couche2.h
couche3.o: $(HEADIR)/$(RAID5DIR)/couche3.h
couche4.o: $(HEADIR)/$(RAID5DIR)/couche4.h
couche5.o: $(HEADIR)/$(RAID5DIR)/couche5.h
