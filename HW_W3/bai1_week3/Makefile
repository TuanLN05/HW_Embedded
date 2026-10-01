TARGET  = bai01
BUILD   = build

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CFLAGS  = -mcpu=cortex-m3 -mthumb -Os -g -Wall -Wextra \
          -ffunction-sections -fdata-sections -Iinc -MMD -MP
LDFLAGS = -mcpu=cortex-m3 -mthumb -T linker.ld -nostartfiles \
          --specs=nano.specs --specs=nosys.specs \
          -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,$(BUILD)/%.o,$(SRCS))

all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS) linker.ld
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD)/%.bin: $(BUILD)/%.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD):
	mkdir -p $(BUILD)

flash: $(BUILD)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
	        -c "program $< verify reset exit"

serial:
	picocom -b 9600 /dev/ttyUSB0

clean:
	rm -rf $(BUILD)

-include $(OBJS:.o=.d)
.PHONY: all flash serial clean
