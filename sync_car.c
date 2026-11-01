#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sync_car.h"

void station_init(struct station *station){
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->trem_chegou, NULL);
    pthread_cond_init(&station->todos_embarcaram, NULL);
    station->passageiros_esperando = 0;
    station->assentos_livres = 0;
    station->passageiros_embarcando = 0;
}

void station_load_car(struct station *station, int count) {
    station->assentos_livres = count;

    pthread_cond_broadcast(&station->trem_chegou);

    while (station->assentos_livres > 0 && (station->passageiros_esperando > 0 || station->passageiros_embarcando > 0)) {
        pthread_cond_wait(&station->todos_embarcaram, &station->lock);
    }

    station->assentos_livres = 0;
}

void station_wait_for_car(struct station *station){

}

void station_on_board(struct station *station){
    
}