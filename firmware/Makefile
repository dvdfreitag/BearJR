# Include directories
INCLUDE_DIRS := \
-I./include \
-I./CMSIS/include

SRCS := \
./hanlders.c \
./main.c

OBJS := \
./handlers.o \
./main.o

DEPS := \
./handlers.d \
./main.d

MAKEDEP := ./makedep.mk

TARGET := BearJR.elf
MAP := BearJR.map
LSS := BearJR.lss

LINKER_SCRIPT := samd20e18.ld

CC := arm-none-eabi-gcc
OBJDUMP := arm-none-eabi-objdump
SIZE := arm-none-eabi-size
PARSER := ../utilities/size_parser

OPTIMIZE := -Os
OPTIMIZE_SECTIONS := -ffunction-sections -fdata-sections
CPU := cortex-m0plus

FLASH := 262144
SRAM := 32768

%.o: %.c
	$(CC) -x c -mthumb -D__SAMD20E18__ -DDONT_USE_CMSIS_INIT $(INCLUDE_DIRS) $(OPTIMIZE) $(OPTIMIZE_SECTIONS) -mlong-calls -g3 -Wall -mcpu=$(CPU) -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -o "$@" "$<"

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

$(TARGET): $(OBJS) $(MAKEDEP) $(LINKER_SCRIPT)
	$(CC) -o $(TARGET) $(OBJS) -mthumb -nostartfiles -nodefaultlibs -nostdlib -Wl,-Map="$(MAP)" -Wl,--start-group -Wl,--end-group -Wl,--gc-sections -mcpu=$(CPU) -T$(LINKER_SCRIPT)
	$(OBJDUMP) -h -S $(TARGET) > $(LSS)
	$(SIZE) $(TARGET)
	$(SIZE) $(TARGET) | $(PARSER) -f $(FLASH) -s $(SRAM)

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET) $(DEPS) $(MAP) $(LSS)
