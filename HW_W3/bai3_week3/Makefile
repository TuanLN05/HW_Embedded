.RECIPEPREFIX := >


# ============================================================
# PROJECT
# ============================================================

TARGET := $(notdir $(CURDIR))


# ============================================================
# STM32F103C8T6 COMMON
# ============================================================

STM32_DIR := $(HOME)/stm32f103

STARTUP := $(STM32_DIR)/startup_stm32f103xb.s
LINKER  := $(STM32_DIR)/STM32F103C8Tx_FLASH.ld

CLOCK_C := $(STM32_DIR)/clock.c
CLOCK_H := $(STM32_DIR)/clock.h


# ============================================================
# STM32CubeF1 / CMSIS
# ============================================================

STM32CUBE := $(HOME)/STM32CubeF1

CMSIS_CORE := $(STM32CUBE)/Drivers/CMSIS/Include

CMSIS_DEVICE := $(STM32CUBE)/Drivers/CMSIS/Device/ST/STM32F1xx/Include


# ============================================================
# TOOLCHAIN
# ============================================================

CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size


# ============================================================
# CPU
# ============================================================

CPU := -mcpu=cortex-m3 \
       -mthumb


# ============================================================
# DEFINES
# ============================================================

DEFINES := \
-DSTM32F103xB


# ============================================================
# INCLUDE PATH
# ============================================================

INCLUDES := \
-I$(CMSIS_CORE) \
-I$(CMSIS_DEVICE) \
-I$(STM32_DIR) \
-I.


# ============================================================
# COMPILER FLAGS
# ============================================================

CFLAGS := $(CPU) \
          $(DEFINES) \
          $(INCLUDES) \
          -std=c11 \
          -Wall \
          -Wextra \
          -O0 \
          -g3 \
          -ffreestanding \
          -fno-builtin \
          -ffunction-sections \
          -fdata-sections \
          -MMD \
          -MP


# ============================================================
# LINKER FLAGS
# ============================================================

LDFLAGS := $(CPU) \
           -T$(LINKER) \
           -nostdlib \
           -Wl,--gc-sections \
           -Wl,-Map=$(TARGET).map


# ============================================================
# SOURCE
# ============================================================

C_SRC := $(wildcard *.c)

C_OBJ := $(C_SRC:.c=.o)

OBJ := $(C_OBJ) clock.o startup.o

DEP := $(C_OBJ:.o=.d) clock.d


# ============================================================
# DEFAULT
# ============================================================

all: $(TARGET).bin


# ============================================================
# COMPILE PROJECT .C
# ============================================================

%.o: %.c
>$(CC) $(CFLAGS) -c $< -o $@


# ============================================================
# COMPILE CLOCK.C
# ============================================================

clock.o: $(CLOCK_C) $(CLOCK_H)
>$(CC) $(CFLAGS) -c $(CLOCK_C) -o $@


# ============================================================
# COMPILE STARTUP
# ============================================================

startup.o: $(STARTUP)
>$(CC) $(CPU) -c $< -o $@


# ============================================================
# LINK ELF
# ============================================================

$(TARGET).elf: $(OBJ)
>$(CC) $(OBJ) $(LDFLAGS) -o $@
>$(SIZE) $@


# ============================================================
# ELF -> BIN
# ============================================================

$(TARGET).bin: $(TARGET).elf
>$(OBJCOPY) -O binary $< $@


# ============================================================
# ST-LINK
# ============================================================

probe-stlink:
>st-info --probe


flash-stlink: $(TARGET).bin
>st-flash --reset write $(TARGET).bin 0x08000000


erase-stlink:
>st-flash erase


reset-stlink:
>st-flash reset


# ============================================================
# ST-LINK CONNECT UNDER RESET
# ============================================================

flash-stlink-reset: $(TARGET).bin
>st-flash --connect-under-reset --reset write $(TARGET).bin 0x08000000


erase-stlink-reset:
>st-flash --connect-under-reset erase


# ============================================================
# DAPLINK / CMSIS-DAP
# ============================================================

OPENOCD_INTERFACE := interface/cmsis-dap.cfg
OPENOCD_TARGET    := target/stm32f1x.cfg
OPENOCD_SPEED     := 1000


# ============================================================
# DAPLINK PROBE
# ============================================================

probe-daplink:
>openocd \
-f $(OPENOCD_INTERFACE) \
-f $(OPENOCD_TARGET) \
-c "adapter speed $(OPENOCD_SPEED); init; targets; shutdown"


# ============================================================
# DAPLINK FLASH
# ============================================================

flash-daplink: $(TARGET).bin
>openocd \
-f $(OPENOCD_INTERFACE) \
-f $(OPENOCD_TARGET) \
-c "adapter speed $(OPENOCD_SPEED); program $(TARGET).bin 0x08000000 verify reset exit"


# ============================================================
# DAPLINK ERASE
# ============================================================

erase-daplink:
>openocd \
-f $(OPENOCD_INTERFACE) \
-f $(OPENOCD_TARGET) \
-c "adapter speed $(OPENOCD_SPEED); init; reset halt; stm32f1x mass_erase 0; reset run; shutdown"


# ============================================================
# DAPLINK RESET
# ============================================================

reset-daplink:
>openocd \
-f $(OPENOCD_INTERFACE) \
-f $(OPENOCD_TARGET) \
-c "adapter speed $(OPENOCD_SPEED); init; reset run; shutdown"


# ============================================================
# CLEAN
# ============================================================

clean:
>rm -f *.o
>rm -f *.d
>rm -f *.elf
>rm -f *.bin
>rm -f *.map


# ============================================================
# REBUILD
# ============================================================

rebuild: clean all


# ============================================================
# INFO
# ============================================================

info:
>@echo ""
>@echo "=========================================="
>@echo " PROJECT INFORMATION"
>@echo "=========================================="
>@echo ""
>@echo "Target:"
>@echo "  $(TARGET)"
>@echo ""
>@echo "MCU:"
>@echo "  STM32F103C8T6"
>@echo ""
>@echo "System clock:"
>@echo "  72 MHz"
>@echo ""
>@echo "Project source:"
>@echo "  $(C_SRC)"
>@echo ""
>@echo "Clock source:"
>@echo "  $(CLOCK_C)"
>@echo ""
>@echo "Startup:"
>@echo "  $(STARTUP)"
>@echo ""
>@echo "Linker:"
>@echo "  $(LINKER)"
>@echo ""


# ============================================================
# CHECK
# ============================================================

check:
>@echo ""
>@echo "Checking ARM GCC..."
>@which arm-none-eabi-gcc
>@echo ""
>@echo "Checking ST-Link..."
>@which st-flash
>@echo ""
>@echo "Checking OpenOCD..."
>@which openocd
>@echo ""
>@echo "Checking CMSIS..."
>@test -f $(CMSIS_DEVICE)/stm32f1xx.h && echo "CMSIS OK" || echo "CMSIS NOT FOUND"
>@echo ""
>@echo "Checking clock.c..."
>@test -f $(CLOCK_C) && echo "clock.c OK" || echo "clock.c NOT FOUND"
>@echo ""
>@echo "Checking clock.h..."
>@test -f $(CLOCK_H) && echo "clock.h OK" || echo "clock.h NOT FOUND"
>@echo ""
>@echo "Checking Startup..."
>@test -f $(STARTUP) && echo "Startup OK" || echo "Startup NOT FOUND"
>@echo ""
>@echo "Checking Linker..."
>@test -f $(LINKER) && echo "Linker OK" || echo "Linker NOT FOUND"
>@echo ""


# ============================================================
# HELP
# ============================================================

help:
>@echo ""
>@echo "=========================================="
>@echo " STM32F103C8T6 - 72 MHz"
>@echo "=========================================="
>@echo ""
>@echo "BUILD:"
>@echo "  make"
>@echo "  make clean"
>@echo "  make rebuild"
>@echo ""
>@echo "ST-LINK:"
>@echo "  make probe-stlink"
>@echo "  make flash-stlink"
>@echo "  make erase-stlink"
>@echo "  make reset-stlink"
>@echo ""
>@echo "ST-LINK UNDER RESET:"
>@echo "  make flash-stlink-reset"
>@echo "  make erase-stlink-reset"
>@echo ""
>@echo "DAPLINK:"
>@echo "  make probe-daplink"
>@echo "  make flash-daplink"
>@echo "  make erase-daplink"
>@echo "  make reset-daplink"
>@echo ""
>@echo "OTHER:"
>@echo "  make check"
>@echo "  make info"
>@echo "  make help"
>@echo ""


# ============================================================
# DEPENDENCY
# ============================================================

-include $(DEP)


# ============================================================
# PHONY
# ============================================================

.PHONY: all \
        clean \
        rebuild \
        info \
        check \
        help \
        probe-stlink \
        flash-stlink \
        erase-stlink \
        reset-stlink \
        flash-stlink-reset \
        erase-stlink-reset \
        probe-daplink \
        flash-daplink \
        erase-daplink \
        reset-daplink

