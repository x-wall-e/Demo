PROJECT := demo

DIR_DRIVERS   += ../Drivers/sys/
DIR_DRIVERS   += ../Drivers/delay/
DIR_DRIVERS   += ../Drivers/timer/
DIR_DRIVERS   += ../Drivers/pwm/
DIR_DRIVERS   += ../Drivers/nvic/
DIR_DRIVERS   += ../Drivers/exti/
DIR_DRIVERS   += ../Drivers/debug_usart1/

DIR_MODULES   += ../Modules/led/
DIR_MODULES   += ../Modules/mpu6050/
DIR_MODULES   += ../Modules/mpu6050/eMPL/
DIR_MODULES   += ../Modules/encoder/
DIR_MODULES   += ../Modules/motor/
DIR_MODULES   += ../Modules/segger/

DIR_ALGORITHM += ../Algorithm/control/

DIR_INCLUDE   += -I../Libraries/CMSIS/ \
                 -I../Libraries/FWLib/inc/ \
                 $(addprefix -I, $(DIR_DRIVERS)) \
                 $(addprefix -I, $(DIR_MODULES)) \
                 $(addprefix -I, $(DIR_ALGORITHM)) \
                 -I../User/ \

SRC_C   += $(wildcard ../Libraries/CMSIS/*.c)
SRC_C   += $(wildcard ../Libraries/FWLib/src/*.c)
SRC_C   += $(wildcard $(addsuffix *.c, $(DIR_DRIVERS)))
SRC_C   += $(wildcard $(addsuffix *.c, $(DIR_MODULES)))
SRC_C   += $(wildcard $(addsuffix *.c, $(DIR_ALGORITHM)))
SRC_C   += $(wildcard ../User/*.c)

SRC_ASM := ../Libraries/CMSIS/startup/gcc/startup_stm32f10x_md.s

OBJS    := $(filter %.o, $(SRC_ASM:.s=.o)) $(filter %.o, $(SRC_C:.c=.o))

LINK_SCRIPT := ../Libraries/LinkScript/stm32f10x_flash.lds

CC_PREFIX := arm-none-eabi-

CC        := $(CC_PREFIX)gcc
CXX       := $(CC_PREFIX)g++
CP        := $(CC_PREFIX)objcopy
GDB       := $(CC_PREFIX)gdb
SIZE      := $(CC_PREFIX)size
AS        := $(CC) -x assembler-with-cpp
HEX       := $(CP) -O ihex
BIN       := $(CP) -O binary -S

DDEFS += -DSTM32F10X_MD
DDEFS += -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER

DEFS  := $(DDEFS) -DRUN_FROM_FLASH=1

MCU   := cortex-m3

OPT   += -Os
OPT   += -fsingle-precision-constant
OPT   += -fno-common
OPT   += -ffunction-sections
OPT   += -fdata-sections

#SPECS := --specs=rdimon.specs -u _printf_float
#For use printf
SPECS := --specs=nosys.specs -u _printf_float -specs=nano.specs


FLAGS_MCU := -mcpu=$(MCU)
FLAGS_AS  := $(SPECS) $(FLAGS_MCU) $(OPT) -c -g -gdwarf-2 -mthumb
FLAGS_C   := $(SPECS) $(FLAGS_MCU) $(OPT) -c -g -gdwarf-2 -mthumb \
             -fomit-frame-pointer -Wall -fverbose-asm $(DEFS)
FLAGS_CXX := $(SPECS) $(FLAGS_MCU) $(OPT) -c -g -gdwarf-2 -mthumb \
             -fomit-frame-pointer -Wall -fverbose-asm -fno-exceptions \
             -fno-rtti -fno-threadsafe-statics -fvisibility=hidden -std=c++11 \
             $(DEFS)
FLAGS_LD  := $(SPECS) $(FLAGS_MCU) $(OPT) -lm -g -gdwarf-2 -mthumb \
             -nostartfiles -Xlinker --gc-sections -T$(LINK_SCRIPT) \
             -Wl,-Map=$(PROJECT).map,--cref,--no-warn-mismatch 

TYPE_BURN  := openocd_swd_flash
TYPE_DEBUG := openocd_swd_debug
TYPE_ERASE := openocd_swd_erase

###############################################################################

.PHONY: all burn debug erase clean

all: $(OBJS) $(PROJECT).elf $(PROJECT).hex $(PROJECT).bin
	$(SIZE) $(PROJECT).elf

%.o: %.c
	$(CC) $(FLAGS_C) $(DIR_INCLUDE) $< -o $@

%.o: %.s
	$(AS) $(FLAGS_AS) $< -o $@

%.elf: $(OBJS)
	$(CC) $(OBJS) $(FLAGS_LD) -o $@

%.hex: %.elf
	$(HEX) $< $@

%.bin: %.elf
	$(BIN) $< $@

###############################################################################

burn:  $(TYPE_BURN)
debug: $(TYPE_DEBUG)
erase: $(TYPE_ERASE)

openocd_swd_flash: $(PROJECT).bin
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f1x.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $(PROJECT).bin 0x08000000" -c "sleep 100" -c "verify_image $(PROJECT).bin 0x08000000" -c "sleep 100" -c "reset run" -c shutdown

openocd_swd_debug: $(PROJECT).bin
	xterm -e openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f1x.cfg -c "init" -c "halt" -c "reset halt" &
	$(GDB) --eval-command="target extended-remote localhost:3333" $(PROJECT).elf

openocd_swd_erase:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f1x.cfg  -c "init" -c "reset halt" -c "sleep 100" -c "stm32f1x mass_erase 0" -c "sleep 100" -c shutdown

###############################################################################

clean:
	-rm -rf $(OBJS)
	-rm -rf $(PROJECT).elf
	-rm -rf $(PROJECT).map
	-rm -rf $(PROJECT).hex
	-rm -rf $(PROJECT).bin
