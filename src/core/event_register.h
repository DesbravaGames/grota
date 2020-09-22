#ifndef GROTA_EVENT_REGISTER_H
#define GROTA_EVENT_REGISTER_H
#include <stdbool.h>

typedef struct {
	int *events;
	int event_count;
	int capacity;
} EventRegister;

EventRegister register_alloc(int capacity);

bool register_event(EventRegister *reg,int event);
void register_reset(EventRegister *reg);
bool register_has_event(EventRegister *reg,int event);
 
void register_free(EventRegister *reg);

bool array_contains(int* arr,unsigned int arr_size,int value);
bool array_add_once(int* arr,unsigned int arr_size,int value);
bool array_add(int* arr,unsigned int arr_size,int value);
bool array_remove(int* arr,unsigned int arr_size,int value);
void array_clear(int* arr,unsigned int arr_size);

#endif
