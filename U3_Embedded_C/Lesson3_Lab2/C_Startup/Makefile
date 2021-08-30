#prepared by : Ahmed Aboraya
ARMTC=arm-none-eabi-
OFLAGS=	-mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC = $(wildcard *.c) #all C files
OBJ = $(SRC:.c=.o)	   #all object files which its source is C files
AS =  $(wildcard *.s) #all assembly files
ASOBJ = $(AS:.s=.o)   #all object files which its source is assembly files
Project_name =learn-in-depth_cortexM3

all: $(Project_name).hex
	@echo "==========Build is done=========="

%.o: %.s
	$(ARMTC)as.exe $(OFLAGS) $< -o $@ 

%.o: %.c
	$(ARMTC)gcc.exe $(OFLAGS) $(INCS) -c $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(ARMTC)ld.exe -T linker_script.ld -Map=map_file.map $(LIBS) $(OBJ) $(ASOBJ) -o $@

$(Project_name).hex: $(Project_name).elf
	$(ARMTC)objcopy.exe -O binary $< $@

clean_all:
	rm -rf *.o *~ *.elf *.hex
	@echo "Everything is clean"
	
clean:
	rm *.elf *.bin
	@echo "Remove Build files"