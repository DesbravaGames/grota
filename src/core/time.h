#ifndef NK_TIME_H
#define NK_TIME_H

void time_init();
float time_elapsed();

long time_elapsed_millis();
long time_elapsed_micro();

float time_delta();
void time_update();
int time_fps();


#endif