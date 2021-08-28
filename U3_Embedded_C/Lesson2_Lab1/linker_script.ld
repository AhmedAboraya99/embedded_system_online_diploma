ENTRY(reset)

MEMORY
{
	Mem (rwx) : ORIGIN = 0x00000000, LENGTH = 64M 	/* reserving read write execution memory */
}

SECTIONS
{
	. = 0x010000;
	.startup . :
	{
		startup.o(.text) /*put text in startup.o in startup section*/
	}> Mem 				 /* put VMA and LMA in Mem*/
	.text :
	{
		*(.text) *(.rodata)
	}> Mem
	.data :
	{
		*(.data)
	}> Mem
	.bss :
	{
		*(.bss)  *(.COMMON)
	}> Mem
	. = . + 0x1000; /* 4KB of stack Memory */
	Stack_top = . ; /* make top of stack  = 0x00011000  */
}