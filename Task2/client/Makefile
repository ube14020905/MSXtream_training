COMPILER=g++
CPPFLAGS=-Wall -g

SRCDIR=src
LIB=-l:libubacipc.so.1.4.4
INCLUDE=-Iinclude
BINDIR=bin
OBJ=client
BIN=$(BINDIR)/$(OBJ)
SRC=$(SRCDIR)/*.cpp

all:
	$(COMPILER) $(CPPFLAGS) -o $(BIN) $(SRC) $(INCLUDE) $(LIB)

run:
	./$(BIN)

remove:
	rm -f $(BIN)
