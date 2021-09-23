#include "typedef.h"
#include "Queue.h"
#include "Student_DataBase.h"

SData StudentBuffer[FIFO_Buff_length];
FIFO_Buff_t Student_FIFO;
int main()
{
	FIFO_init (&Student_FIFO,StudentBuffer,FIFO_Buff_length);
	int Selected_ID = 0;
	char temp_text[40];
	DPRINTF("\n welcome to the Student Management System");
	while(1)
	 {
		DPRINTF("\n =================");
		DPRINTF("\n  Choose on of the following Options \n");
		DPRINTF("\n 1: Add Student Details Manually");
		DPRINTF("\n 2: Add Student Details from Text File");
		DPRINTF("\n 3: Find Student Data by Roll Number ");
		DPRINTF("\n 4: Find Student Data by First Name ");
		DPRINTF("\n 5: Find Student Data by Course ID ");
		DPRINTF("\n 6: Find Total Number of Students");
		DPRINTF("\n 7: Delete Student Data by Roll Number");
		DPRINTF("\n 8: Update Student Data by Roll Number");
		DPRINTF("\n 9: Show All information ");
		DPRINTF("\n 10: Exit ");
		DPRINTF("\n Enter Option Number: ");
		gets(temp_text);
		DPRINTF("\n =================\n");
	switch(atoi(temp_text))
	  {
		case 1:
			AddStudent_Manual(&Student_FIFO);
		  	break ;
		case 2:
			AddStudent_File(&Student_FIFO);
		  	break ;
		case 3:
			FindS_byRoll(&Student_FIFO,Selected_ID);
		  	break ;
		case 4:
		 	FindS_byFName(&Student_FIFO);
		  break;
		case 5:
			FindS_byCourse(&Student_FIFO);
			break ;	
		case 6:
			Total_Students(&Student_FIFO);
		  	break;
		case 7:
			Delete_Student(&Student_FIFO,StudentBuffer);
		 	break;
		case 8:
			Update_Student(&Student_FIFO);
			break;
		case 9:
			View_Students(&Student_FIFO);
			break;
		case 10 :
			exit(1);
		default:
		  DPRINTF("\n Wrong option ");
		  break ;
	  }
	}
}
