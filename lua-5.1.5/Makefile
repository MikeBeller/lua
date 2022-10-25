OBJS0= lapi.o lcode.o ldo.o ldump.o ldebug.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o 
OBJS= $(OBJS0) lua.o lauxlib.o lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o loadlib.o linit.o
OBJS2= $(OBJS0) luac.o print.o lauxlib.o

CFLAGS= -Wall -O2

T= lua

all:	lib mikedir

clean:
	rm -f $T $(OBJS) $(OBJS2) core core.* luac.out luac

diff:
	diff ORIG . | grep -v ^Only > DIFFS

lib: $(OBJS)
	ar rcs liblua.a $(OBJS)

mikedir: lib
	gcc -I. -o mikedir mikedir.c liblua.a -lm
