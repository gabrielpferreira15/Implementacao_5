#ifndef SYNC_CAR_H
#define SYNC_CAR_H

typedef struct{
}station;

void station_init();

void station_load_car(station *station, int count);

void station_wait_for_car(station *station);

void station_on_board(station *station);

#endif