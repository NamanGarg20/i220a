CFLAGS = -g -Wall -fPIC -std=c11

OBJS = \
  circ.o \
  rect.o

all:		libgeom.a  libgeom.so testgeom-static testgeom-dynamic 

libgeom.so:	$(OBJS) 
		$(CC) -shared $(OBJS) -o $@

libgeom.a:	$(OBJS)
		ar rcs $@ $(OBJS)

testgeom-static: testgeom.o
		$(CC)  -static testgeom.o -L. -libgeom -o $@

testgeom-dynamic: testgeom.o
		$(CC) testgeom.o -L. -libgeom -o $@

.PHONY:		clean
clean:
		rm -f *.o *.so *.a testgeom-*






