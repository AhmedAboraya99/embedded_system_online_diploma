#include "Student_DataBase.h"
int main()
{
	 char temp_text[40];
	 int index;
	 while(1)
	 {
		DPRINTF("\n =================");
		DPRINTF("\n  Choose on of the following Options \n");
		DPRINTF("\n 0: exit ");
		DPRINTF("\n 1: Add Student ");
		DPRINTF("\n 2: Delete Student ");
		DPRINTF("\n 3: View Students ");
		DPRINTF("\n 4: DeleteAll ");
		DPRINTF("\n 5: Student Data by index ");
		DPRINTF("\n 6: Get length of list ");
		DPRINTF("\n 7: Student Data by index from the end ");
		DPRINTF("\n 8: Reverse List of Students");
		DPRINTF("\n Enter Option Number: ");
		gets(temp_text);
		DPRINTF("\n =================");
	switch(atoi(temp_text))
	  {
		case 0 :
			exit(0);
		case 1:
		  AddStudent();
		  break ;
		case 2:
		  Delete_Student();
		  break ;
		case 3:
			View_Students();
		  break ;
		case 4:
		  DeleteAll();
		  break;
		case 5:
		  DPRINTF("\n index=");
		  scanf("%d",&index);
		  GetNth(index);
		  break ;
		case 6:
			DPRINTF("\n List length = %d",getCount());
		  break;
		case 7:
		  DPRINTF("\n index from end =");
		  scanf("%d",&index);
		  get_end_Nth(index);
		  break;
		case 8:
			getReverse();
			break;
		default:
		  DPRINTF("\n Wrong option ");
		  break ;
	  }
	}
}
