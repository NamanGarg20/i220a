TARGET = bits-to-ints

CC = gcc

OFILES = \
  main.o \
  bits-to-ints.o \
  errors.o

CFLAGS = -g -Wall -std=c11

$(TARGET): 	$(OFILES)
		$(CC) $(OFILES) $(LDFLAGS) -o $@

.phony:		clean

clean:
		rm -f *~ $(OFILES) $(TARGET) 


bits-to-ints.o: bits-to-ints.c errors.h bits-to-ints.h 

