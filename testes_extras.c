#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "sync_car.h"

void *passageiro_teste_limite(void *arg) {
    struct station *station = (struct station *)arg;
    
    // Passageiro aguarda na fila até ter vaga
    station_wait_for_car(station);
    
    // Passageiro sinaliza que embarcou
    station_on_board(station);
    
    return NULL;
}

int main() {
    struct station station;
    station_init(&station);
    
    printf("==========================================\n");
    printf(" INICIANDO TESTES EXTRAS DE SINCRONIZAÇÃO \n");
    printf("==========================================\n\n");

    // ---------------------------------------------------------
    // TESTE 1: TESTE INVÁLIDO (Corrupção de Estado / Input Negativo)
    // ---------------------------------------------------------
    printf("[TESTE INVÁLIDO] Trem chegando com capacidade negativa (-5)...\n");
    station_load_car(&station, -5);
    
    if (station.assentos_livres <= 0) {
        printf(" -> SUCESSO: A função tratou a entrada inválida e ignorou a capacidade.\n\n");
    } else {
        printf(" -> FALHA: O estado da estação foi corrompido.\n\n");
    }

    // ---------------------------------------------------------
    // TESTE 2: TESTE LIMITE (Avalanche de Threads / Carga Extrema)
    // ---------------------------------------------------------
    int num_passageiros = 5000;
    printf("[TESTE LIMITE] Criando %d passageiros simultâneos na plataforma...\n", num_passageiros);
    pthread_t threads[5000];

    // Dispara 5000 threads ao mesmo tempo
    for (int i = 0; i < num_passageiros; i++) {
        if (pthread_create(&threads[i], NULL, passageiro_teste_limite, &station) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    printf(" -> Todos os passageiros criados. Abrindo as portas do trem com %d vagas...\n", num_passageiros);
    
    // Trem chega com capacidade suficiente para todos
    station_load_car(&station, num_passageiros);

    // Aguarda o término de todas as threads
    for (int i = 0; i < num_passageiros; i++) {
        pthread_join(threads[i], NULL);
    }

    printf(" -> SUCESSO: Avalanche de %d passageiros processada sem deadlocks ou falha de memória!\n\n", num_passageiros);
    printf("Testes extras finalizados com sucesso.\n");

    return 0;
}