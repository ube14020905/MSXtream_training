COMPILER=g++
INCLUDE=-Iinclude

BINDIR=bin
OBJ=student
BIN=$(BINDIR)/$(OBJ)
SRCDIR=src
SRC=$(SRCDIR)/*.cpp

all:
	$(COMPILER) -o $(BIN) $(SRC) $(INCLUDE)

run:
	./$(BIN)

remove:
	rm -f $(BIN)
