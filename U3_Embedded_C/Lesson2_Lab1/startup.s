.global reset

@reset section 
reset:
		ldr sp, =Stack_top  @ set stack pointer to top of stack of main
		bl main 		     @ jump to main function to execute its commands

exit: 	
		b exit 	   @ infinite loop if program finish the execution of main