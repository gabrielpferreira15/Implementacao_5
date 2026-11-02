CC = gcc
CFLAGS = -Wall -Wextra -std=gnu17 -pthread

TARGET = sync_car
TARGET_EXTRAS = testes_extras

OBJ = sync_car-runner.o sync_car.o
OBJ_EXTRAS = testes_extras.o sync_car.o

# O comando padrao 'make' vai compilar ambos os projetos
all: $(TARGET) $(TARGET_EXTRAS)

# Compila o testador original do projeto
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compila o seu testador personalizado de casos limites
$(TARGET_EXTRAS): $(OBJ_EXTRAS)
	$(CC) $(CFLAGS) $(OBJ_EXTRAS) -o $(TARGET_EXTRAS)

# Regras de construcao dos arquivos objeto (.o)
sync_car-runner.o: sync_car-runner.c sync_car.h
	$(CC) $(CFLAGS) -c sync_car-runner.c

testes_extras.o: testes_extras.c sync_car.h
	$(CC) $(CFLAGS) -c testes_extras.c

sync_car.o: sync_car.c sync_car.h
	$(CC) $(CFLAGS) -c sync_car.c

# Comandos de execucao rapida
run: $(TARGET)
	./$(TARGET)

run-extras: $(TARGET_EXTRAS)
	./$(TARGET_EXTRAS)

clean:
	rm -f *.o $(TARGET) $(TARGET_EXTRAS)

.PHONY: all run run-extras clean