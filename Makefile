CC = gcc
CFLAGS = -Wall -Wextra -std=gnu17 -pthread

TARGET = sync_car
OBJ = sync_car-runner.o sync_car.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

sync_car-runner_2.o: sync_car-runner.c sync_car.h
	$(CC) $(CFLAGS) -c sync_car-runner.c

sync_car.o: sync_car.c sync_car.h
	$(CC) $(CFLAGS) -c sync_car.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: run clean