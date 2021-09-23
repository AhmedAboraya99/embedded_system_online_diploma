#include "typedef.h"
#include "Student_DataBase.h"
#include "Queue.h"

#include <string.h>

element_type i ;

SData* pNewStudent;
SData* pCurrentStudent;

void AddStudent_Manual(FIFO_Buff_t* Student_FIFO){

	//if the list is not exist
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] DataBase not exist \n");
		return;
	}
	if (Buffer_valid(Student_FIFO)==FIFO_full){
		DPRINTF("[ERROR] Student Database is Full \n");
		return;
	}

	if(Buffer_valid(Student_FIFO)==FIFO_no_error||Buffer_valid(Student_FIFO)==FIFO_empty)	//if the list is valid
	{
		DPRINTF("--------------------------------------------\n");
		DPRINTF("Add Student Details \n");
		FIFO_enqueue(Student_FIFO);
	}
}
int Check_Roll(FIFO_Buff_t* Student_FIFO,int Selected_ID){
	pCurrentStudent = Student_FIFO->base;
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] Database not exist  \n");
		return 0;
	}
	//if the list is valid
	if(Buffer_valid(Student_FIFO)==FIFO_no_error||Buffer_valid(Student_FIFO)==FIFO_empty)
	{
		for(i=0;i<Student_FIFO->count;i++)   // loop to get the Roll number
		{
			if(pCurrentStudent->Roll==Selected_ID){
				return 1;
			}
			pCurrentStudent++;
		}
		return 0;
	}
	return 0;
}
void FindS_byRoll(FIFO_Buff_t* Student_FIFO,int Selected_Roll){
	pCurrentStudent = (SData*)Student_FIFO->base;
	DPRINTF("Enter student roll number  \n");
	scanf("%d",&Selected_Roll);
	if (Buffer_valid(Student_FIFO)==FIFO_empty){
			DPRINTF("[ERROR] Database is empty \n");
			return;
		}
	if(Check_Roll(Student_FIFO,Selected_Roll)==1){
		print_FIFO(pCurrentStudent);
	}
	else
		DPRINTF("[ERROR] Roll Number is Not Found\n");// loop finished and roll not found

}
void FindS_byFName(FIFO_Buff_t* Student_FIFO){
	int flag= 0;
	char temp_text[50];
	pCurrentStudent = (SData*)Student_FIFO->base;
	DPRINTF("Enter student First Name  \n");
	gets(temp_text);
	//if the list is not exist or empty
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] Database not exist  \n");
		return;
	}
	if (Buffer_valid(Student_FIFO)==FIFO_empty){
		DPRINTF("[ERROR] Database is empty \n");
		return;
	}
	if(Buffer_valid(Student_FIFO)==FIFO_no_error)	//if the list is valid
	{
		for(i=0;i<Student_FIFO->count;i++)   // loop to get the First Name of Students
		{
			if(strcmpi(pCurrentStudent->FirstName,temp_text)==0){
				print_FIFO(pCurrentStudent);
				flag = 1;
			}
			pCurrentStudent++;
		}
	}
	if(flag==0){
		DPRINTF("[ERROR] No First Name Matched this Name\n");// loop finished and Name not found
	}
}
void FindS_byCourse(FIFO_Buff_t* Student_FIFO){
	pCurrentStudent = (SData*)Student_FIFO->base;
	char temp_text[50];
	int i,n,temp_CID,flag = 0;
	DPRINTF("Enter Course ID \n");
	gets(temp_text);
	temp_CID=atoi(temp_text);
	//if the list is not exist or empty
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] Database not exist  \n");
		return;
	}
	if (Buffer_valid(Student_FIFO)==FIFO_empty){
		DPRINTF("[ERROR] Database is empty \n");
		return;
	}
	if(Buffer_valid(Student_FIFO)==FIFO_no_error)	//if the list is valid
	{
		for(i=0;i<Student_FIFO->count;i++)   // loop to get registered student in this Course ID
		{
			for(n=1;n<=5;n++){
				if(pCurrentStudent->Course_ID[n]==temp_CID){
					print_FIFO(pCurrentStudent);
					flag = 1;
				}
			}
			pCurrentStudent++;
	  }
	}  
		if(flag==0){
			DPRINTF("[ERROR] No Student signed this Course\n");// loop finished and no student found
		}
}

void Total_Students(FIFO_Buff_t* Student_FIFO){
	// check the list of students
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] Database not exist  \n");
		return;
	}
	if (Buffer_valid(Student_FIFO)==FIFO_empty){
		DPRINTF("[ERROR] Database is empty \n");
		return;
	}
	DPRINTF("--------------------------------------------\n");
	DPRINTF("[INFO] the total number of students is : %d\n",Student_FIFO->count);
	DPRINTF("[INFO] you can add up to %d students \n",Student_FIFO->length);
	DPRINTF("[INFO] you can add more about %d students \n",Student_FIFO->length-Student_FIFO->count);
	DPRINTF("--------------------------------------------\n");
}

void Delete_Student(FIFO_Buff_t* Student_FIFO,SData* StudentBuffer){
	pCurrentStudent = (SData*)Student_FIFO->base;
	char temp_text[50];
	int Selected,flag=0;
	int x,index = 0;
	DPRINTF("\n Enter Student Roll to be Deleted: ");
	gets(temp_text);
	Selected = atoi(temp_text);
	for(i=0;i<Student_FIFO->count;i++)   // loop to get the Roll Number of student
	{
		if(pCurrentStudent->Roll==Selected)
		{	flag = 1;
			print_FIFO(pCurrentStudent);
			DPRINTF("Delete Student 1-Yes 2-No \n");
			DPRINTF("--------------------------------------------\n");
			gets(temp_text);
			Selected=atoi(temp_text);
			if(Selected==1){
				for(x=index;x<Student_FIFO->count;x++)
				{
					StudentBuffer[x]=StudentBuffer[x+1];
				}
				DPRINTF("--------------------------------------------\n");
				DPRINTF("Student Deleted successfully\n");
				DPRINTF("--------------------------------------------\n");
				Student_FIFO->head--;
				Student_FIFO->count--;
				return;
			}
			else if(Selected==2)
			{
				DPRINTF("--------------------------------------------\n");
				DPRINTF("--------Process Canceled-------\n");
				return;
			}
			else
			{
			DPRINTF("--------------------------------------------\n");
			DPRINTF("[ERROR] Wrong Choice---\n ---Uncompleted Process---\n");
			return;
			}
		}
		pCurrentStudent++;
		index++;
	}
	if(flag==0)
		DPRINTF("[ERROR] Roll Number is Not Found\n");// loop finished and roll not found;
}
void Update_Student(FIFO_Buff_t* Student_FIFO){
	pCurrentStudent = (SData*)Student_FIFO->base;
	char temp_text[50];
	int Selected,temp_CID;
	int i;
	DPRINTF("\n Enter Student Roll to be Updated: ");
	gets(temp_text);
	Selected = atoi(temp_text);

	if(Check_Roll(Student_FIFO,Selected)==1)
	{
		print_FIFO(pCurrentStudent);
		DPRINTF("--------------------------------------------\n");
		DPRINTF("Enter Data Number to be Updated\n");
		DPRINTF("1- First Name\n");
		DPRINTF("2- Last Name \n");
		DPRINTF("3- GPA\n");
		DPRINTF("4- Courses \n");
		DPRINTF("--------------------------------------------\n");
		gets(temp_text);
		Selected=atoi(temp_text);
		switch(Selected)
		{
			case 1:
				DPRINTF("Enter New first Name\n");
				gets(pCurrentStudent->FirstName);
				break;
			case 2 :
			{
				DPRINTF("Enter New Last Name\n");
				gets(pCurrentStudent->LastName);
				break;
			}
			case 3 :
			{
				DPRINTF("Enter New GPA \n");
				gets(temp_text);
				pCurrentStudent->GPA=atof(temp_text);
				break;
			}
			case 4 :
			{
				DPRINTF("Enter the course id of each course\n");
				for(i=1;i<=5;i++)
				{
					DPRINTF("Course %d ID :\n",i);
					gets(temp_text);
					temp_CID=atoi(temp_text);
					pCurrentStudent->Course_ID[i]=temp_CID;

				}
				break;
			}
			default :
			{
				DPRINTF("[ERROR] wrong choice \n");
				return;
			}
		}
		// print Student Information after update
		DPRINTF("--------------------------------------------\n");
		DPRINTF("information updated successfully \n");
		DPRINTF("Student information after update \n");
		DPRINTF("--------------------------------------------\n");
		print_FIFO(pCurrentStudent);
	}
	else
		DPRINTF("[ERROR] Roll Number is Not Found\n");// loop finished and roll not found;
}

void View_Students(FIFO_Buff_t* Student_FIFO)
{
	int count = 0 ;
	pCurrentStudent = (SData*)Student_FIFO->base;
	//check if list is exit and not empty
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] Database not exist  \n");
		return;
	}
	if (Buffer_valid(Student_FIFO)==FIFO_empty){
		DPRINTF("[ERROR] Database is empty \n");
		return;
	}
	for(i=0;i< Student_FIFO->count;i++)
	{
		DPRINTF("\n Record Number %d>", count+1);
		print_FIFO(pCurrentStudent);
		pCurrentStudent++;
		count++;
	}
}

void AddStudent_File(FIFO_Buff_t* Student_FIFO){

	char FName[50], LName[50];
	int RollNum, CID[5], n, FileCount=0, line =0;;
	float GPA;
	//if the list is not exist or full
	if(Buffer_valid(Student_FIFO)==FIFO_Null){
		DPRINTF("[ERROR] DataBase not exist \n");
		return;
	}
	if (Buffer_valid(Student_FIFO)==FIFO_full){
		DPRINTF("[ERROR] Student DataBase is Full \n");
		return;
	}

	FILE *SFile = fopen("Students.txt","r");
	if(SFile==NULL)
	{
		DPRINTF("------------------------------ \n");
		DPRINTF("[ERROR] File Not Found \n");
	}

	//if the list is valid or empty
	if(Buffer_valid(Student_FIFO)==FIFO_no_error ||Buffer_valid(Student_FIFO)==FIFO_empty)
	{

		DPRINTF("--------------------------------------------\n");
		DPRINTF("Add Students Details from File \n");
		// reading from file

		while( fscanf(SFile,"%d %s %s %f %d %d %d %d %d \n",
					 &RollNum,FName,LName,&GPA,&CID[0],&CID[1],&CID[2],&CID[3],&CID[4])!=EOF)
		{

			if(Buffer_valid(Student_FIFO)==FIFO_full)
			{
			DPRINTF("----------------------------\n");
			DPRINTF("[ERROR] Database is full\n");
			DPRINTF("[INFO] students added : %d\n",FileCount);
			DPRINTF("[INFO] remaining students due to size or errors are :%d\n",line-FileCount);
			return;
			}
			if(Check_Roll(Student_FIFO,RollNum)==1)
			{
				DPRINTF("[ERROR] IN line %d : Roll Number is already taken before \n",line);
				line++;
				continue; // Skip This Student
			}
			pNewStudent = Student_FIFO->head;
			pNewStudent->Roll=RollNum;
			strcpy(pNewStudent->FirstName,FName);
			strcpy(pNewStudent->LastName,LName);
			pNewStudent->GPA=GPA;
			for(n=0;n<5;n++)
			{
				pNewStudent->Course_ID[n]=CID[n];
			}
			print_FIFO(pNewStudent);
			Student_FIFO->count++;
			Student_FIFO->head++;
			line++;
			FileCount++;    // Store Successful records
			DPRINTF("\n");
		}
		DPRINTF("\nEnd of file.\n");

		// close connection
		fclose(SFile);
		DPRINTF("[INFO] students added : %d\n",FileCount);
		DPRINTF("[INFO] remaining students due to errors are :%d\n",line-FileCount);
	}
}


