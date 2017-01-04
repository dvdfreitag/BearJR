INCLUDE_DIRS := \
-I../../include \
-I../../CMSIS/include

SRCS := \
../../hanlders.c \
./benchmark.c \
./printf.c

OBJS := \
./handlers.o \
./benchmark.o \
./printf.o

DEPS := \
./handlers.d \
./benchmark.d \
./printf.d

TARGET := benchmark.elf
MAP := benchmark.map
LSS := benchmark.lss

LINKER_SCRIPT := ../../samd20e18.ld

CC := arm-none-eabi-gcc
OBJDUMP := arm-none-eabi-objdump
SIZE := arm-none-eabi-size
PARSER := ../../../utilities/size_parser

BUILTIN := -mthumb -ffreestanding -fno-builtin

OPTIMIZE := -Os
OPTIMIZE_SECTIONS := -ffunction-sections -fdata-sections
CPU := cortex-m0plus
DEFINES := -D__SAMD20E18__ -DDONT_USE_CMSIS_INIT

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

FLASH := 262144
SRAM := 32768

%.o: %.c
	@$(CC) -x c -mthumb $(BUILTIN) $(DEFINES) $(INCLUDE_DIRS) $(OPTIMIZE) $(OPTIMIZE_SECTIONS) -mlong-calls -g3 -Wall -mcpu=$(CPU) -c -std=gnu99 $(DEPFLAGS) -o "$@" "$<"
	@echo [CC] $@
	@$(POSTCOMPILE)

$(TARGET): $(OBJS)
	@$(CC) -o $(TARGET) $(OBJS) $(BUILTIN) -Wl,-Map="$(MAP)" -Wl,--start-group -Wl,--end-group -Wl,--gc-sections -mcpu=$(CPU) -T$(LINKER_SCRIPT)
	@echo [LD] $@
	@$(OBJDUMP) -h -S $(TARGET) > $(LSS)
	@$(SIZE) $(TARGET)
	@$(SIZE) $(TARGET) | $(PARSER) -f $(FLASH) -s $(SRAM)

handlers.o: ../../handlers.c
	@$(CC) -x c -mthumb $(BUILTIN) $(DEFINES) $(INCLUDE_DIRS) $(OPTIMIZE) $(OPTIMIZE_SECTIONS) -mlong-calls -g3 -Wall -mcpu=$(CPU) -c -std=gnu99 $(DEPFLAGS) -o "$@" "$<"
	@echo [CC] $@
	@$(POSTCOMPILE)

disassemble:
	@$(OBJDUMP) -h -S $(TARGET) > $(LSS)

size:
	@$(SIZE) $(TARGET)
	@$(SIZE) $(TARGET) | $(PARSER) -f $(FLASH) -s $(SRAM)

.PHONY: program
program:
	openocd -f /usr/share/openocd/scripts/board/atmel_samd20_xplained_pro.cfg -c "program $(TARGET) verify reset exit"

.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET) $(DEPDIR) $(MAP) $(LSS)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
