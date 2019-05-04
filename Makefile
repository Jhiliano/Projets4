# Specific part of the Makefile
EXEC = Exec
CREATEDISK = createdisk

ARGS =
# Begin generic part of the Makefile
CC = gcc
CFLAGS = -Wextra -Wall -pedantic
LDFLAGS =

SRC = couche1.c\
			couche2.c\
			couche3.c\
			couche4.c\
			couche5.c
OBJ = $(SRC:.c=.o)
HEAD = $(SRC:.c=.h)

TEST = testunitaire
CMDT1 = cmd_test1
CMDT2 = cmd_test2
CMDDI = cmd_dump_inode
CMDDR = cmd_dump_raid

SRCDIR = src
BINDIR = bin
OBJDIR = obj
HEADIR = headers
DISKSDIR = disk
CREATEDISKDIR = genDisk
TESTDIR = tests



RAID5DIR = Raid5

ifeq ($(DEBUG),yes)
	CFLAG += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(EXEC) $(TEST) $(CMDT1) $(CMDT2) $(CMDDI) $(CMDDR)

$(EXEC): $(OBJ) main.o
	@echo "Création de l'executabe "$@
	@$(CC) -o $(addprefix $(BINDIR)/,$@) $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)

$(TEST): $(OBJ) $(addsuffix .o,$(TEST))
	@echo "Creation de l'executable "$@
	@$(CC) -o $(addprefix $(TESTDIR)/$(BINDIR)/,$@) $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)

$(CMDT1): $(OBJ) $(addsuffix .o,$(CMDT1))
	@echo "Creation de l'executable "$@
	@$(CC) -o $(addprefix $(TESTDIR)/$(BINDIR)/,$@) $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)

$(CMDT2): $(OBJ) $(addsuffix .o,$(CMDT2))
	@echo "Creation de l'executable "$@
	@$(CC) -o $(addprefix $(TESTDIR)/$(BINDIR)/,$@) $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)

$(CMDDI): $(OBJ) $(addsuffix .o,$(CMDDI))
	@echo "Creation de l'executable "$@
	@$(CC) -o $(addprefix $(TESTDIR)/$(BINDIR)/,$@) $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)

$(CMDDR): $(OBJ) $(addsuffix .o,$(CMDDR))
	@echo "Creation de l'executable "$@
	@$(CC) -o $(addprefix $(TESTDIR)/$(BINDIR)/,$@) $(addprefix $(OBJDIR)/,$^) $(LDFLAGS)

run:
	./$(BINDIR)/$(EXEC) $(ARGS)

run_TU: $(CREATEDISK)
		./$(TESTDIR)/$(BINDIR)/$(TEST)

run_T1:
	./$(TESTDIR)/$(BINDIR)/$(CMDT1)

run_T2:
	./$(TESTDIR)/$(BINDIR)/$(CMDT2)

run_DI:
	./$(TESTDIR)/$(BINDIR)/$(CMDDI) disk

run_DR:
	./$(TESTDIR)/$(BINDIR)/$(CMDDR) disk



%.o: $(SRCDIR)/$(RAID5DIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $(addprefix $(OBJDIR)/,$@) -c $< $(CFLAGS) $(LDFLAGS)

%.o: $(SRCDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $(addprefix $(OBJDIR)/,$@) -c $< $(CFLAGS) $(LDFLAGS)

%.o: $(TESTDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $(addprefix $(OBJDIR)/,$@) -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: clean mrproper doc

doc:
	@echo "Creation de la documentation"
	@doxygen doc/doxyfile

$(CREATEDISK): $(SRCDIR)/$(CREATEDISKDIR)/$(addsuffix .c,$(CREATEDISK))
	@echo "Création de l'executable de generation du disque"
	@$(CC) -o $(BINDIR)/$@ $^
	@echo "Création de 4 disk de 50*1024 octets"

	@./bin/$@ $(DISKSDIR) 4 51200

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "Fichiers intermédiaires supprimés"

mrproper: clean
	@rm -f $(BINDIR)/*
	@rm -f $(TESTDIR)/$(BINDIR)/*
	@rm -f $(EXEC) $(CREATEDISK)
	@echo "Executable supprimé"
# End generic part of the makefile

# Specific file dependencies
main.o: $(addprefix $(HEADIR)/$(RAID5DIR)/,$(HEAD))
couche2.o: $(HEADIR)/$(RAID5DIR)/couche2.h
couche3.o: $(HEADIR)/$(RAID5DIR)/couche3.h
couche4.o: $(HEADIR)/$(RAID5DIR)/couche4.h
couche5.o: $(HEADIR)/$(RAID5DIR)/couche5.h
