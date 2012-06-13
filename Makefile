#===============================================================================
#
#     Filename: Makefile
#  Description:
#
#        Usage: make              (generate executable                       )
#               make clean        (remove objects, executable, prerequisites )
#               make test         (clean, make all, run                      )
##==============================================================================

CC=g++
CFLAGS=-g -Wall -ansi
EXECUTABLES=mazebot

all: $(EXECUTABLES)

.SUFFIXES: .cpp .o

.cc.o:
	$(CC) $(CFLAGS) -c *.cpp

mazebot: client.o
	$(CC) $(CFLAGS) -o mazebot  client.o


clean:
	rm -f *.obj *core *.exe  *.stackdump *.o

run:
	./mazebot.exe

sout:
	./mazebot > s.out

test: clean all run


