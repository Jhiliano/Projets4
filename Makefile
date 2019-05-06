# Specific part of the Makefile
EXEC = Exec
CREATEDISK = createdisk

ARGS =
# Begin generic part of the Makefile
CC = gcc
CFLAGS = -Wextra -Wall -pedantic
LDFLAGS =

SRC5 = couche1_5.c\
			couche2_5.c\
			couche3_5.c\
			couche4_5.c\
			couche5_5.c
OBJ5 = $(SRC5:.c=.o)
HEAD5 = $(SRC5:.c=.h)
SRC0 = couche1_0.c\
			couche2_0.c\
			couche3_0.c\
			couche4_0.c\
			couche5_0.c
OBJ0 = $(SRC0:.c=.o)
HEAD0 = $(SRC0:.c=.h)
SRC01 = couche1_01.c\
			couche2_01.c\
			couche3_01.c\
			couche4_01.c\
			couche5_01.c
OBJ01 = $(SRC01:.c=.o)
HEAD01 = $(SRC01:.c=.h)
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
RAID0DIR = Raid0
RAID01DIR = Raid01

ifeq ($(DEBUG),yes)
	CFLAG += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(BINDIR)/$(EXEC) $(TESTDIR)/$(BINDIR)/$(TEST) $(TESTDIR)/$(BINDIR)/$(CMDT1) $(TESTDIR)/$(BINDIR)/$(CMDT2) $(BINDIR)/$(CMDDI) $(BINDIR)/$(CMDDR) $(BINDIR)/$(CMDRR) $(BINDIR)/$(CMDDD)

$(BINDIR)/$(EXEC): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(OBJ0)) $(addprefix $(OBJDIR)/,$(OBJ01)) $(addprefix $(OBJDIR)/,$(MAIN))
	@echo "Création de l'executabe "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TESTDIR)/$(BINDIR)/$(TEST): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(TEST)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TESTDIR)/$(BINDIR)/$(CMDT1): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDT1)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TESTDIR)/$(BINDIR)/$(CMDT2): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDT2)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDDI): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDDI)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDDR): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDDR)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDRR): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDRR)))
	@echo "Creation de l'executable "$@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/$(CMDDD): $(addprefix $(OBJDIR)/,$(OBJ5)) $(addprefix $(OBJDIR)/,$(addsuffix .o,$(CMDDD)))
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
	./$(BINDIR)/$(CMDDI) disk/raid5

dump_raid:
	./$(BINDIR)/$(CMDDR) disk/raid5

repair_raid:
	./$(BINDIR)/$(CMDRR) disk/raid5 $(ARGS)

defrag_raid:
	./$(BINDIR)/$(CMDDD) disk/raid5





$(OBJDIR)/%.o: $(SRCDIR)/$(RAID5DIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/$(RAID0DIR)/%.c
	@echo "Création de "$@
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/$(RAID01DIR)/%.c
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
	@./bin/$@ $(DISQUESDIR)/raid5 4 51200
	@./bin/$@ $(DISQUESDIR)/raid0 4 51200
	@./bin/$@ $(DISQUESDIR)/raid01/Grape1 4 51200
	@./bin/$@ $(DISQUESDIR)/raid01/Grape2 4 51200
clean:
	@rm -f $(OBJDIR)/*.o
	@echo "Fichiers intermédiaires supprimés"

cleandisk:
	@rm -f $(DISQUESDIR)/raid5/*
	@rm -f $(DISQUESDIR)/raid0/*
	@rm -f $(DISQUESDIR)/raid01/Grape1/*
	@rm -f $(DISQUESDIR)/raid01/Grape2/*
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
