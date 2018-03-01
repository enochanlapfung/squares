CC:=g++
CXXFLAGS:= -O0 -g -std=c++11 -Wall -Wextra -Wshadow -pedantic -Weffc++ -Werror

BINARY_NAME = squares.exe

MAIN = main.cpp
SOURCES = squares.cpp
DEPS = $(SOURCES:%.cpp=%.h)
OBJDIR = obj
OBJ = 	$(SOURCES:%.cpp=$(OBJDIR)/%.obj) \
		$(MAIN:%.cpp=$(OBJDIR)/%.obj)

LIBDIR = ../lib
LIBSOURCES =
LIBDEPS = $(LIBSOURCES:%.cpp=%.h)
LIBOBJDIR = $(LIBDIR)/obj
LIBOBJ = $(LIBSOURCES:$(LIBDIR)/%.cpp=$(LIBOBJDIR)/%.obj)

CXXFLAGS += -I$(LIBDIR) \
			-I../

$(info OBJ:$(OBJ))
$(info DEPS:$(DEPS))
$(info LIBSOURCES:$(LIBSOURCES))
$(info LIBOBJDIR:$(LIBOBJDIR))
$(info LIBOBJ:$(LIBOBJ))

all: dirs $(LIBOBJ) $(OBJ)
	$(CC) $(OBJ) $(LIBOBJ) -o $(BINARY_NAME) $(CXXFLAGS)

$(OBJDIR)/%.obj: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(LIBOBJDIR)/%.obj: $(LIBDIR)/%.cpp $(LIBDEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

dirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(LIBOBJDIR)

clean:
	rm $(OBJDIR)/*.obj
	rm $(BINARY_NAME)
	rm $(LIBOBJDIR)/*.obj
	
.PHONY: clean dirs all
