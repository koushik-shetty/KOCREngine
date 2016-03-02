#create by Koushik Shetty

#compiler used
CC = g++-4.9

OBJS = ImageAcquition.o ImageHeader.o

SRC = ImageAcquition.cpp ImageHeader.cpp

#output directory
BINDIR = bin/

#object directory
OBJDIR = objs/

#outputname
TARGET = vt.exe

#flags for compilation
CFLAGS = -W -Wall -Wextra -pedantic -std=c++11

#flasgs for assembly
OFLAGS = -O3

$(TARGET) : $(OBJDIR)$(OBJS)
	CC $(OFLAGS) $(OBJDIR)$(OBJS) -o $(TARGET) 

build: $(TARGET)

clean: 
	@rm -rf $(BINDIR)

all: 
	clean
	build