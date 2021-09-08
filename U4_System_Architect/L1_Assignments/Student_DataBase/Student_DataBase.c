#include "Student_DataBase.h"
struct SStudent* gpFirstStudent = NULL ;

void Fill_SData (struct SStudent* NewStudent){
	char temp_text[50];

	DPRINTF("\n Enter Student ID: ");
	gets(temp_text);
	NewStudent->Student_Data.ID = atoi(temp_text);

	DPRINTF("\n Enter Student Full Name: ");
	gets(NewStudent->Student_Data.name);

	DPRINTF("\n Enter Student height: ");
	gets(temp_text);
	NewStudent->Student_Data.height = atof(temp_text);

}
void AddStudent(){
	struct SStudent* pLastStudent ;
	struct SStudent* pNewStudent ;

	if(gpFirstStudent==NULL)	//if the list is empty
	{
		//create first record
		pNewStudent = (struct SStudent*) malloc(sizeof(struct SStudent));
		//Assign gpFirstStudent pointer to this record
		gpFirstStudent = pNewStudent ;
	}
	else //if the list is not empty
	{
		//search for finding the last record
		pLastStudent = gpFirstStudent ;
		while(pLastStudent->pNextStudent)
			pLastStudent = pLastStudent->pNextStudent;
		//create New record after the last record and assign pNext pointer to it
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		pLastStudent -> pNextStudent = pNewStudent;
	}
	//fill new record data
	Fill_SData (pNewStudent);
	//set next record pointer to NULL
	pNewStudent->pNextStudent = NULL;
}

int Delete_Student(){
	char temp_text[50];
	int Selected_ID;

	DPRINTF("\n Enter Student ID to be Deleted: ");
	gets(temp_text);
	Selected_ID = atoi(temp_text);

	if(gpFirstStudent){
		struct SStudent* pPreviousStudent = NULL;
		struct SStudent* pSelectedStudent = gpFirstStudent;

		while(pSelectedStudent)
		{
			//compare recorded ID to Selected ID
			if (pSelectedStudent->Student_Data.ID == Selected_ID)
			{
				if(pPreviousStudent)
				{
					pPreviousStudent->pNextStudent = pSelectedStudent->pNextStudent;
				}
				else{
					gpFirstStudent = pSelectedStudent->pNextStudent;
				}
				free(pSelectedStudent); //delete "free up" the location of selected record
				DPRINTF("\n Student with ID = %d --removed successfully",Selected_ID);
				return 1; //we find it
			}
			//store & change previous and next record pointer
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->pNextStudent;
		}
	}
	DPRINTF("\n Cannot find student ID.");
	return 0; //we can't find it
}

void View_Students ()
{
	int count = 0 ;
	struct SStudent* pCurrentStudent = gpFirstStudent;;
	if (gpFirstStudent == NULL)
		DPRINTF("\n Empty list");
	while (pCurrentStudent)
	{
		DPRINTF("\n Record Number %d>", count+1);
		DPRINTF("\n Student ID: %d", pCurrentStudent->Student_Data.ID);
		DPRINTF("\n Student Name: %s", pCurrentStudent->Student_Data.name);
		DPRINTF("\n Height: %.2f\n", pCurrentStudent->Student_Data.height);
		pCurrentStudent = pCurrentStudent->pNextStudent;
		count++;
	}
}

void DeleteAll ()
  {
	struct SStudent* pCurrentStudent = gpFirstStudent;
	if (gpFirstStudent == NULL)
		DPRINTF("\n Empty list ");
	while (pCurrentStudent )
	{
		struct SStudent* pTempStudent = pCurrentStudent ;
		pCurrentStudent = pCurrentStudent ->pNextStudent ;
		free (pTempStudent);
	}
	gpFirstStudent = NULL ;
	DPRINTF("\n All Student List removed successfully ");
  }

void GetNth(int index)
{	int count = 0,found=0;
	struct SStudent* pStudent = gpFirstStudent;;
	if(gpFirstStudent==NULL)
		DPRINTF("\n Empty list ");

	while(pStudent)
	{
		if (count == index){
			DPRINTF("\n the Student at index %d: \n", index);
			DPRINTF("\n Student ID: %d", pStudent->Student_Data.ID);
			DPRINTF("\n Student Name: %s", pStudent->Student_Data.name);
			DPRINTF("\n Height: %.2f", pStudent->Student_Data.height);
			found = 1;
		}
		count++;
		pStudent = pStudent->pNextStudent;

	}
	if(found == 0){
		DPRINTF("\n index is not exist");
		found = 0;
	}
}
int getCount(){
	int count = 0;
	struct SStudent* pStudent = gpFirstStudent;
	if (gpFirstStudent == NULL){
		DPRINTF("\n Empty list ");
		return 0;
	}
	else {
	while(pStudent){
		count++ ;
		pStudent = pStudent->pNextStudent;
	}
	return count;
	}
}
void get_end_Nth(int n){
	int i = 0;
	struct SStudent* main_ptr = gpFirstStudent;
	struct SStudent* ref_ptr = main_ptr;
	if(gpFirstStudent==NULL){
		DPRINTF("\n Empty list ");
	}
	else if (n>getCount()){
		DPRINTF("\n index is not exist");
	}
	else{
		while(i<=n){
			ref_ptr = ref_ptr->pNextStudent;
			i++;
		}
		  while(ref_ptr->pNextStudent)
		  {
			ref_ptr=ref_ptr->pNextStudent;
			main_ptr=main_ptr->pNextStudent;
		  }
		  DPRINTF("\n Student at index %d from end > ID = %d , Name: %s ,height: %.2f",n
					,main_ptr->Student_Data.ID, main_ptr->Student_Data.name, main_ptr->Student_Data.height);
		}
	}

void getMiddle(){
	int count = 0;
	struct SStudent* pStudent = gpFirstStudent;
	struct SStudent* ref_ptr = pStudent->pNextStudent;
	if (gpFirstStudent == NULL){
		DPRINTF("\n Empty list ");
	}
	else {
		while(ref_ptr){
			count++ ;
			pStudent = pStudent->pNextStudent;
			ref_ptr=ref_ptr->pNextStudent->pNextStudent;
		}
		if(count%2 != 0){
			DPRINTF("\n Middle of list is > ID = %d , Name: %s ,height: %.2f",
					pStudent->Student_Data.ID, pStudent->Student_Data.name, pStudent->Student_Data.height);
		}
		else{
			pStudent = pStudent->pNextStudent;
			DPRINTF("\n Middle of list is > ID = %d , Name: %s ,height: %.2f",
					pStudent->Student_Data.ID, pStudent->Student_Data.name, pStudent->Student_Data.height);
		}
   }
}
void getReverse(){
	struct SStudent* current = gpFirstStudent;
	struct SStudent* next;
	struct SStudent* prev = NULL;
	if (gpFirstStudent == NULL){
			DPRINTF("\n Empty list ");
	}
	else{
	while(current != NULL)
	{
		next = current->pNextStudent;
		current->pNextStudent = prev;
		prev = current ;
		current = next ;
	}
	gpFirstStudent = prev;
	DPRINTF("\n list is reversed successfully");
	}
}
