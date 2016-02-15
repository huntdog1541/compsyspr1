CC = gcc
CFLAGS = -c -Wall
THREAD = -lpthread

TARGET = client
MAIN = TCPclient

$(TARGET): $(MAIN).o
	$(CC) -o $(TARGET) $(MAIN).o $(THREAD)

$(MAIN).o: $(MAIN).c $(MAIN).h
	$(CC) $(CFLAGS) $(MAIN).c $(MAIN).h

.PHONY : clean

clean :
			-rm -f *.o *.gch Parser* src/*.gch
