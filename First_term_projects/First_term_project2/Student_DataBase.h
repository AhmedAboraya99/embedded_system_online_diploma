#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "typedef.h"


//APIs
void AddStudent_File(FIFO_Buff_t* Student_FIFO);
void AddStudent_Manual(FIFO_Buff_t* Student_FIFO);
int Check_Roll(FIFO_Buff_t* Student_FIFO,int Selected_ID);
void FindS_byRoll(FIFO_Buff_t* Student_FIFO,int Selected_ID);
void FindS_byFName(FIFO_Buff_t* Student_FIFO);
void FindS_byCourse(FIFO_Buff_t* Student_FIFO);
void Total_Students(FIFO_Buff_t* Student_FIFO);
void Delete_Student(FIFO_Buff_t* Student_FIFO,SData* StudentBuffer);
void Update_Student(FIFO_Buff_t* Student_FIFO);
void View_Students(FIFO_Buff_t* Student_FIFO);

#endif
