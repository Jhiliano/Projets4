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
MAIN = main.o
TEST = testunitaire
CMDT1 = cmd_test1
CMDT2 = cmd_test2
CMDDI = cmd_dump_inode
CMDDR = cmd_dump_raid
CMDRR = cmd_repair_raid
CMDDD = cmd_defrag_raid

SRCDIR = src
BINDIR = bin
OBJDIR = obj
HEADIR = headers
DISQUESDIR = disk
CREATEDISKDIR = genDisk
TESTDIR = tests
UTILDIR = utilitaire



RAID5DIR = Raid5

ifeq ($(DEBUG),yes)
	CFLAG += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(BINDIR)/$(EXEC) $(TESTDIR)/$(BINDIR)/$(TEST) $(TESTDIR)/$(BINDIR)/$(CMDT1) $(TESTDIR)/$(BINDIR)/$(CMDT2) $(BINDIR)/$(CMDDI) $(BINDIR)/$(CMDDR) $(BINDIR)/$(CMDRR) $(BINDIR)/$(CMDDD)

$(BINDIR)/$(EXEC): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(MAIN))
	@echo "Création de l'executabe "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TESTDIR)/$(BINDIR)/$(TEST): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(TEST)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TESTDIR)/$(BINDIR)/$(CMDT1): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDT1)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TESTDIR)/$(BINDIR)/$(CMDT2): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDT2)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDDI): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDDI)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDDR): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDDR)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDRR): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDRR)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDDD): $(addprefix $(OBJDIR)/,$(OBJ)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDDD)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

run:
	./$(BINDIR)/$(EXEC) $(ARGS)

run_TU: $(CREATEDISK)
		./$(TESTDIR)/$(BINDIR)/$(TEST)

run_T1:
	./$(TESTDIR)/$(BINDIR)/$(CMDT1)

run_T2:
	./$(TESTDIR)/$(BINDIR)/$(CMDT2)

dump_inode:
	./$(BINDIR)/$(CMDDI) disk

dump_raid:
	./$(BINDIR)/$(CMDDR) disk

repair_raid:
	./$(BINDIR)/$(CMDRR) disk $(ARGS)

defrag_raid:
	./$(BINDIR)/$(CMDDD) disk





$(OBJDIR)/%.o: $(SRCDIR)/$(RAID5DIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/$(UTILDIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)


.PHONY: clean mrproper doc

doc:
	@echo "Creation de la documentation"
	@doxygen doc/doxyfile

$(CREATEDISK): $(SRCDIR)/$(CREATEDISKDIR)/$(addsuffix .c,$(CREATEDISK))
	@echo "Création de l'executable de generation du disque"
	@$(CC) -o $(BINDIR)/$@ $^
	@echo "Création de 4 disk de 50*1024 octets"
	@./bin/$@ $(DISQUESDIR) 4 51200

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "Fichiers intermédiaires supprimés"

cleandisk:
	@rm -f $(DISQUESDIR)/*
	@make $(CREATEDISK) > /dev/null
	@echo "Disques réinitialisés"

mrproper: clean cleandisk
	@rm -f $(BINDIR)/*
	@rm -f $(TESTDIR)/$(BINDIR)/*
	@echo "Executable supprimé"

# End generic part of the makefile

# Specific file dependencies
main.o: $(addprefix $(HEADIR)/$(RAID5DIR)/,$(HEAD))
couche2.o: $(HEADIR)/$(RAID5DIR)/couche2.h
couche3.o: $(HEADIR)/$(RAID5DIR)/couche3.h
couche4.o: $(HEADIR)/$(RAID5DIR)/couche4.h
couche5.o: $(HEADIR)/$(RAID5DIR)/couche5.h
