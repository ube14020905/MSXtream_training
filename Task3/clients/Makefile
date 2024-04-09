COMPILER=g++
CPPFLAGS=-Wall -g

SRCDIR=src
LIB=-l:libubacipc.so.1.4.4
INCLUDE=-Iinclude
BINDIR=bin
OBJ=client
BIN=$(BINDIR)/$(OBJ)
SRC=$(SRCDIR)/*.cpp

c1:
	$(COMPILER) $(CPPFLAGS) -o $(BIN)1 $(SRC) $(INCLUDE) $(LIB)
c2:
	$(COMPILER) $(CPPFLAGS) -o $(BIN)2 $(SRC) $(INCLUDE) $(LIB)
c3:
	$(COMPILER) $(CPPFLAGS) -o $(BIN)3 $(SRC) $(INCLUDE) $(LIB)
all:
	$(c1)
	$(c2)
	$(c3)

run:
	./$(BIN)

remove:
	rm -f $(BIN)
