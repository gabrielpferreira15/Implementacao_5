CC = gcc-16
CFLAGS = -Wall -Wextra -std=gnu17

TARGET = sync_car
OBJ = main.o sync_car.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

main.o: main.c sync_car.h
	$(CC) $(CFLAGS) -c main.c

sync_car.o: sync_car.c sync_car.h
	$(CC) $(CFLAGS) -c sync_car.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: run clean