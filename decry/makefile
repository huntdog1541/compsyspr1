CC = gcc
CFLAGS = -c -Wall
THREAD = -lpthread

TARGET = decry
MAIN = src/main
FILE = src/file
TRANS = src/translate

$(TARGET): main.o file.o translate.o
	$(CC) -o $(TARGET) main.o file.o translate.o

main.o: $(MAIN).c
	$(CC) $(CFLAGS) $(MAIN).c

file.o: $(FILE).c $(FILE).h
	$(CC) $(CFLAGS) $(FILE).c $(FILE).h

translate.o: $(TRANS).c $(TRANS).h
	$(CC) $(CFLAGS) $(TRANS).c $(TRANS).h

.PHONY : clean

clean :
			-rm -f *.o *.gch $(TARGET) src/*.gch
