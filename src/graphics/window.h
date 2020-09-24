#ifndef GROTA_WINDOW_H
#define GROTA_WINDOW_H
#include <stdbool.h>

bool window_init();
void window_update();
void window_destroy();
int window_width();
int window_height();


int input_pressing(int key);
int input_pressed(int key);
int input_released(int key);

#endif
