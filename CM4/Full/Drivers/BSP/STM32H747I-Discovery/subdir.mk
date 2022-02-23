################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_audio.c \
../Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_bus.c \
../Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_qspi.c \
../Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_sdram.c \
../Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_audio.o \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_bus.o \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_qspi.o \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_sdram.o \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_audio.d \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_bus.d \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_qspi.d \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_sdram.d \
./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H747I-Discovery/%.o: ../Drivers/BSP/STM32H747I-Discovery/%.c Drivers/BSP/STM32H747I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DDEBUG -DARM_MATH_CM4 -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -D__FPU_PRESENT -c -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Application/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Core/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Middlewares/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Peripheral/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Utilities/Fonts" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Utilities/lcd" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Common/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/Common" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/ft6x06" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/is42s32800j" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/otm8009a" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/mt25tl01g" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/wm8994" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/STM32H747I-Discovery" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/STM32H7xx_HAL_Driver" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/App" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/target" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/target/generated" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/fonts/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/gui_generated/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/images/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/texts/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/videos/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/gui/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Middlewares/ST/touchgfx/framework/include" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/ARM/DSP/Inc -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../../Middlewares/Third_Party/FreeRTOS/Source/include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H747I-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32H747I-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_audio.d ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_audio.o ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_bus.d ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_bus.o ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_qspi.d ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_qspi.o ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_sdram.d ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_sdram.o ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_ts.d ./Drivers/BSP/STM32H747I-Discovery/stm32h747i_discovery_ts.o

.PHONY: clean-Drivers-2f-BSP-2f-STM32H747I-2d-Discovery

