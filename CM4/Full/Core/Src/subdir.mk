################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/crc.c \
../Core/Src/dma.c \
../Core/Src/dma2d.c \
../Core/Src/dsihost.c \
../Core/Src/fmc.c \
../Core/Src/freertos.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/ltdc.c \
../Core/Src/main.c \
../Core/Src/quadspi.c \
../Core/Src/rng.c \
../Core/Src/sai.c \
../Core/Src/sdram.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_hal_timebase_tim.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/crc.o \
./Core/Src/dma.o \
./Core/Src/dma2d.o \
./Core/Src/dsihost.o \
./Core/Src/fmc.o \
./Core/Src/freertos.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/ltdc.o \
./Core/Src/main.o \
./Core/Src/quadspi.o \
./Core/Src/rng.o \
./Core/Src/sai.o \
./Core/Src/sdram.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_hal_timebase_tim.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/crc.d \
./Core/Src/dma.d \
./Core/Src/dma2d.d \
./Core/Src/dsihost.d \
./Core/Src/fmc.d \
./Core/Src/freertos.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/ltdc.d \
./Core/Src/main.d \
./Core/Src/quadspi.d \
./Core/Src/rng.d \
./Core/Src/sai.d \
./Core/Src/sdram.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_hal_timebase_tim.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DDEBUG -DARM_MATH_CM4 -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -D__FPU_PRESENT -c -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Application/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Core/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Middlewares/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Peripheral/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Utilities/Fonts" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Utilities/lcd" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Common/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/Common" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/ft6x06" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/is42s32800j" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/otm8009a" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/mt25tl01g" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/wm8994" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/STM32H747I-Discovery" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/STM32H7xx_HAL_Driver" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/App" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/target" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/target/generated" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/fonts/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/gui_generated/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/images/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/texts/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/videos/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/gui/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Middlewares/ST/touchgfx/framework/include" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/ARM/DSP/Inc -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../../Middlewares/Third_Party/FreeRTOS/Source/include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/crc.d ./Core/Src/crc.o ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma2d.d ./Core/Src/dma2d.o ./Core/Src/dsihost.d ./Core/Src/dsihost.o ./Core/Src/fmc.d ./Core/Src/fmc.o ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/ltdc.d ./Core/Src/ltdc.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/quadspi.d ./Core/Src/quadspi.o ./Core/Src/rng.d ./Core/Src/rng.o ./Core/Src/sai.d ./Core/Src/sai.o ./Core/Src/sdram.d ./Core/Src/sdram.o ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_timebase_tim.d ./Core/Src/stm32h7xx_hal_timebase_tim.o ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/usart.d ./Core/Src/usart.o

.PHONY: clean-Core-2f-Src

