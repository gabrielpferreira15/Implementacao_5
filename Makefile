CC = gcc-16
CFLAGS = -Wall -Wextra -std=gnu17

TARGET = station
OBJ = main.o station.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

main.o: main.c station.h
	$(CC) $(CFLAGS) -c main.c

station.o: station.c station.h
	$(CC) $(CFLAGS) -c station.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: run clean