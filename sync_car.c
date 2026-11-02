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
    pthread_mutex_lock(&station->lock);

    if (count == 0 || station->passageiros_esperando == 0) {
        pthread_mutex_unlock(&station->lock);
        return; 
    }

    station->assentos_livres = count;
    pthread_cond_broadcast(&station->trem_chegou);

    while (station->assentos_livres > 0 && (station->passageiros_esperando > 0 || station->passageiros_embarcando > 0)) {
        pthread_cond_wait(&station->todos_embarcaram, &station->lock);
    }

    station->assentos_livres = 0;
    pthread_mutex_unlock(&station->lock);
}

void station_wait_for_car(struct station *station) { 
    pthread_mutex_lock(&station->lock);

    station->passageiros_esperando++;

    while (station->assentos_livres == 0) {
        pthread_cond_wait(&station->trem_chegou, &station->lock);
    }

    station->passageiros_esperando--;
    station->assentos_livres--;
    station->passageiros_embarcando++;

    pthread_mutex_unlock(&station->lock);
}

void station_on_board(struct station *station) {
    pthread_mutex_lock(&station->lock);

    station->passageiros_embarcando--;

    if (station->assentos_livres == 0 || station->passageiros_embarcando == 0) {
        pthread_cond_signal(&station->todos_embarcaram);
    }

    pthread_mutex_unlock(&station->lock);
}