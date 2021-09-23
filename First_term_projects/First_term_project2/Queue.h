#ifndef _QUEUE_H
#define _QUEUE_H
#include "typedef.h"


//Queue APIs
Buffer_Status FIFO_init (FIFO_Buff_t* P_Buff,SData* Buff_item,element_type Buff_length);
void FIFO_enqueue (FIFO_Buff_t* P_Buff);
Buffer_Status Buff_valid (FIFO_Buff_t* P_Buff);
void print_FIFO(SData* CurrentStudent);

#endif
