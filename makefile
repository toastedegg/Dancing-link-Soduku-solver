IDIR =.
EDIR =.
CC=g++
CFLAGS=-g
CXX=g++
CXXFLAGS=-std=c++11 -g


ODIR=.
LDIR =.

LIBS=

_DEPS = DLXsudoku.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = DLXsudoku.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o:%.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

solver: $(OBJ) 
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)



.PHONY: clean

clean:
	rm -f $(ODIR)/*.o solver
