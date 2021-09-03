#prepared by : Ahmed Aboraya
ARMTC=arm-none-eabi-
OFLAGS=	-mcpu=cortex-m4 -gdwarf-2 -g
INCS=-I .
LIBS=
SRC = $(wildcard *.c) #all C files
OBJ = $(SRC:.c=.o)	   #all object files which its source is C files
AS =  $(wildcard *.s) #all assembly files
ASOBJ = $(AS:.s=.o)   #all object files which its source is assembly files
Project_name =ToggleLED_cortexM4

all: $(Project_name).bin
	@echo "==========Build is done=========="

%.o: %.s
	$(ARMTC)as.exe $(OFLAGS) $< -o $@ 

%.o: %.c
	$(ARMTC)gcc.exe $(OFLAGS) $(INCS) -c $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(ARMTC)ld.exe -T linker_script.ld -Map=map_file.map $(LIBS) $(OBJ) $(ASOBJ) -o $@

	cp $(Project_name).elf  $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(ARMTC)objcopy.exe -O binary $< $@

clean_all:
	rm -rf *.o *~ *.elf *.bin
	@echo "Everything is clean"
	
clean:
	rm *.elf *.bin
	@echo "Remove Build files"