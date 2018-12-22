#PATH_TO_BIN = /local/sdk_elec/gcc-arm-none-eabi-5_2-2015q4/bin/


TARGET  = $(PATH_TO_BIN)arm-none-eabi-

CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)gcc -x assembler-with-cpp -c
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump

PROJECT_NAME = template

PROJECT_SRC = .
STM_SRC = _Libraries/STM32F4xx_HAL_Driver/Src/


vpath %.c $(PROJECT_SRC)
vpath %.c $(STM_SRC)


EXT_SRCS = stm32f4xx_hal.c
EXT_SRCS += stm32f4xx_hal_rcc.c
EXT_SRCS += stm32f4xx_hal_gpio.c
EXT_SRCS += stm32f4xx_hal_cortex.c
EXT_SRCS += stm32f4xx_hal_pcd.c
EXT_SRCS += stm32f4xx_hal_pcd_ex.c

EXT_SRCS += stm32f4xx_hal_uart.c
EXT_SRCS += stm32f4xx_hal_usart.c

EXT_SRCS += stm32f4xx_hal_dma.c

EXT_SRCS += stm32f4xx_hal_tim.c
EXT_SRCS += stm32f4xx_hal_tim_ex.c

EXT_SRCS += stm32f4xx_hal_adc.c
EXT_SRCS += stm32f4xx_hal_adc_ex.c

EXT_SRCS += stm32f4xx_hal_spi.c

EXT_SRCS += stm32f4xx_hal_i2c.c

SRCS = src/main.c

SRCS += Device/startup_stm32f411xe.s
SRCS += _Libraries/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.c

SRCS += src/stm32f4xx_hal_msp.c
SRCS += src/stm32f4xx_it.c
SRCS += src/system_stm32f4xx.c
SRCS += src/newlib_stubs.c
SRCS += src/SystemClock.c
SRCS += src/tickTimer.c
SRCS += src/captDistIR.c

SRCS += src/util.c

SRCS += src/motorCommand.c
SRCS += src/quadEncoder.c
SRCS += src/servoCommand.c


SRCS += src/pixyCam.c
SRCS += src/captDistUltrason.c
SRCS += src/screenLCD.c

SRCS += src/drv/drv_i2c.c
SRCS += src/drv/drv_uart.c
SRCS += src/drv/drv_spi.c
SRCS += src/drv/drv_gpio.c

FREE_RTOS_SRC = FreeRTOS/Source
SRCS += $(FREE_RTOS_SRC)/croutine.c $(FREE_RTOS_SRC)/list.c $(FREE_RTOS_SRC)/queue.c $(FREE_RTOS_SRC)/tasks.c 
SRCS += $(FREE_RTOS_SRC)/portable/GCC/ARM_CM4F/port.c
SRCS += $(FREE_RTOS_SRC)/portable/MemMang/heap_1.c
INC_DIRS += $(FREE_RTOS_SRC)/include/
INC_DIRS += $(FREE_RTOS_SRC)/portable/GCC/ARM_CM4F/


# List FreeRTOS resources
#FREE_RTOS_SRC = /FreeRTOS/Source
#FREE_RTOS_SRC_FILES = $(FREE_RTOS_SRC)/croutine.c $(FREE_RTOS_SRC)/list.c $(FREE_RTOS_SRC)/queue.c $(FREE_RTOS_SRC)/tasks.c $(FREE_RTOS_SRC)/croutine.c $(FREE_RTOS_SRC)/portable/GCC/ARM_CM4F/port.c
#FREE_RTOS_INC = $(FREE_RTOS_SRC)/include/
#FREE_RTOS_PORT_INC = $(FREE_RTOS_SRC)/portable/GCC/ARM_CM4F/



EXT_OBJ = $(EXT_SRCS:.c=.o)

INC_DIRS += inc/
INC_DIRS += src/drv/
INC_DIRS += _Libraries/STM32F4xx_HAL_Driver/Inc/
INC_DIRS += _Libraries/STM32F4xx_StdPeriph_Driver/Inc/
INC_DIRS += _Libraries/CMSIS/Device/ST/STM32F4xx/Include/
INC_DIRS += _Libraries/CMSIS/Include/
INC_DIRS += _Libraries/BSP/STM32F4xx-Nucleo/




INCLUDE = $(addprefix -I,$(INC_DIRS))

DEFS = -DSTM32F411xE

CFLAGS  = -ggdb -O0
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -Wl,--gc-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant

WFLAGS += -Wall -Wextra -Warray-bounds -Wno-unused-parameter

LFLAGS = -TDevice/gcc.ld -mfloat-abi=hard -lc -lgcc -lgcov -lm -Wl,-Map=$@.map



.PHONY: all
all: $(PROJECT_NAME)

.PHONY: $(PROJECT_NAME)
$(PROJECT_NAME): $(PROJECT_NAME).elf

$(PROJECT_NAME).elf: $(SRCS) $(EXT_OBJ)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(WFLAGS) $(LFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT_NAME).elf   $(PROJECT_NAME).hex
	$(OBJCOPY) -O binary $(PROJECT_NAME).elf $(PROJECT_NAME).bin

%.o: %.c
	$(CC) -c -o $@ $(INCLUDE) $(DEFS) $(CFLAGS) $^

clean:
	rm -f *.o $(PROJECT_NAME).elf $(PROJECT_NAME).hex $(PROJECT_NAME).bin $(PROJECT_NAME).map

	
	
