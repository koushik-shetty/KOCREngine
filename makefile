#create by Koushik Shetty

#compiler used
CC = g++

OBJS = objs/ImageAcquition.o objs/Image.o objs/main.o

SRC = src/ImageAcquition.cpp src/Image.cpp src/main.cpp

#output directory
BINDIR = bin/

#object directory
OD = objs/

#outputname
TARGET = kocrengine.exe

#flags for compilation
CFLAGS = -std=c++14 -W -Wall -Wextra -pedantic 

#flasgs for assembly
OFLAGS = -O3



################################  Tasks  ##################################
.PHONY: def
def:
	@echo "############ KOCREngine build system commands ############"
	@echo clean :- clears the object and out dir
	@echo build :- builds the source if there are any changes
	@echo rebuild :- cleans the out dir and builds the source


$(TARGET) : obj
	mkdir -p $(BINDIR)
	$(CC) -DDEBUG $(CFLAGS) $(OBJS) -o $(BINDIR)$(TARGET) 

.PHONY: obj
obj:
	$(CC) -c -DDEBUG $(CFLAGS) $(OFLAGS) $(SRC)
	mkdir -p $(OD)
	mv *.o $(OD)

build: $(TARGET)

.PHONY: clean
clean: 
	@rm -rf $(BINDIR)/** $(BINDIR)/*.* $(OD)/** $(OD)/*.*

rebuild:
	clean
	build

all: 
	clean
	build