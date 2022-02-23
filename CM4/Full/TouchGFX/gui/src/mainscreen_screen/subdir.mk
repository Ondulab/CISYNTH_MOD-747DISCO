################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/mainscreen_screen/mainScreenPresenter.cpp \
../TouchGFX/gui/src/mainscreen_screen/mainScreenView.cpp 

OBJS += \
./TouchGFX/gui/src/mainscreen_screen/mainScreenPresenter.o \
./TouchGFX/gui/src/mainscreen_screen/mainScreenView.o 

CPP_DEPS += \
./TouchGFX/gui/src/mainscreen_screen/mainScreenPresenter.d \
./TouchGFX/gui/src/mainscreen_screen/mainScreenView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/mainscreen_screen/%.o: ../TouchGFX/gui/src/mainscreen_screen/%.cpp TouchGFX/gui/src/mainscreen_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DDEBUG -DARM_MATH_CM4 -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -D__FPU_PRESENT -c -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Application/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Core/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Middlewares/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Peripheral/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Utilities/Fonts" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Utilities/lcd" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Common/Inc" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/Common" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/ft6x06" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/is42s32800j" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/otm8009a" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/mt25tl01g" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/BSP/STM32H747I-Discovery" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Drivers/STM32H7xx_HAL_Driver" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/App" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/target" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/target/generated" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/fonts/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/gui_generated/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/images/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/texts/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/generated/videos/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/TouchGFX/gui/include" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/CM4/Middlewares/ST/touchgfx/framework/include" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/ARM/DSP/Inc -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/dev/STM32CubeIDE/workspace_1.8.0/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../../Middlewares/Third_Party/FreeRTOS/Source/include -Ofast -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-mainscreen_screen

clean-TouchGFX-2f-gui-2f-src-2f-mainscreen_screen:
	-$(RM) ./TouchGFX/gui/src/mainscreen_screen/mainScreenPresenter.d ./TouchGFX/gui/src/mainscreen_screen/mainScreenPresenter.o ./TouchGFX/gui/src/mainscreen_screen/mainScreenView.d ./TouchGFX/gui/src/mainscreen_screen/mainScreenView.o

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-mainscreen_screen

