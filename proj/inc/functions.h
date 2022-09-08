#pragma once
#include<udp.h>
//function declarations
//to manage client
void* UA_Client(void *);
//to manage server
void* UA_Server(void *);
//mutex
static pthread_mutex_t x;
