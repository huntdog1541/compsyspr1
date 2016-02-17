CC = gcc
CFLAGS = -c -Wall
THREAD = -lpthread

TARGET = server
MAIN = main

$(TARGET): main.o
	$(CC) -o $(TARGET) main.o $(THREAD)

main.o: $(MAIN).c
	$(CC) $(CFLAGS) $(MAIN).c

.PHONY : clean

clean :
			-rm -f *.o *.gch Parser* src/*.gch
