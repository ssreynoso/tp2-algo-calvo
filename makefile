CC = g++
CXXFLAGS = -std=c++98 -O0 -g3 -Wall -Werror -I./include
CXXFLAGS2 = -std=c++98 -O0 -g3 -Wall -I./include
LDFLAGS =
VALGRINDFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2

APPNAME = tesorobinario
SRCDIR = src
OBJDIR = obj
INCLUDEDIR = src/include
EXT = .cpp

SRC = $(wildcard $(SRCDIR)/*$(EXT))
# OBJ = $(patsubst $(SRCDIR)/%$(EXT),$(OBJDIR)/%.o,$(SRC))
OBJ = $(patsubst $(SRCDIR)/%$(EXT),$(OBJDIR)/%.o,$(SRC)) $(OBJDIR)/EasyBMP.o
DEP = $(OBJ:.o=.d)

all: $(APPNAME)

run: $(APPNAME)
	./$(APPNAME)

valgrind: $(APPNAME)
	valgrind $(VALGRINDFLAGS) ./$(APPNAME)

$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.d: $(SRCDIR)/%$(EXT)
	@$(CC) $(CXXFLAGS) -MMD -MP -MT $(@:.d=.o) -o $@ $<

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -I$(INCLUDEDIR) -o $@ -c $<

$(OBJDIR)/EasyBMP.o: $(INCLUDEDIR)/libreria/EasyBMP_1.06/EasyBMP.cpp
	$(CC) $(CXXFLAGS2) -I$(INCLUDEDIR) -o $@ -c $<

.PHONY: clean cleandep valgrind

clean:
	rm -f $(OBJ) $(APPNAME)

cleandep:
	rm -f $(DEP)

cleandepw:
	rm -f $(DEP)

cleanw:
	rm -f $(OBJ) $(APPNAME)