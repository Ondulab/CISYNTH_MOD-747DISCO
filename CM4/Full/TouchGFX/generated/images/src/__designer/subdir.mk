################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button_pressed.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_active.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_inactive.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_normal.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_pressed.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Indicators_Slider_Round_nob.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_back.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_fill.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Indicators_Slider3_Vertical_Round_nob.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_back.cpp \
../TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_fill.cpp 

OBJS += \
./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button_pressed.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_active.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_inactive.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_normal.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_pressed.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Indicators_Slider_Round_nob.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_back.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_fill.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Indicators_Slider3_Vertical_Round_nob.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_back.o \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_fill.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button_pressed.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_active.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_inactive.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_normal.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_pressed.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Indicators_Slider_Round_nob.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_back.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_fill.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Indicators_Slider3_Vertical_Round_nob.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_back.d \
./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_fill.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/__designer/%.o: ../TouchGFX/generated/images/src/__designer/%.cpp TouchGFX/generated/images/src/__designer/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DDEBUG -DARM_MATH_CM4 -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -D__FPU_PRESENT -c -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Application/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Core/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Middlewares/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Peripheral/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Utilities/Fonts" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Utilities/lcd" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/Common" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/ft6x06" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/is42s32800j" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/otm8009a" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/mt25tl01g" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/STM32H747I-Discovery" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/STM32H7xx_HAL_Driver" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/App" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/target" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/target/generated" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/fonts/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/gui_generated/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/images/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/texts/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/videos/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/gui/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Middlewares/ST/touchgfx/framework/include" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/ARM/DSP/Inc -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../../Middlewares/Third_Party/FreeRTOS/Source/include -Ofast -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-__designer

clean-TouchGFX-2f-generated-2f-images-2f-src-2f-__designer:
	-$(RM) ./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button.d ./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button.o ./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button_pressed.d ./TouchGFX/generated/images/src/__designer/image_Dark_Buttons_Square_icon_button_pressed.o ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_active.d ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_active.o ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_inactive.d ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_inactive.o ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_normal.d ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_normal.o ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_pressed.d ./TouchGFX/generated/images/src/__designer/image_Dark_Check_buttons_Check_mark_pressed.o ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Indicators_Slider_Round_nob.d ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Indicators_Slider_Round_nob.o ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_back.d ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_back.o ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_fill.d ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Horizontal_Large_Slider_Round_fill.o ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Indicators_Slider3_Vertical_Round_nob.d ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Indicators_Slider3_Vertical_Round_nob.o ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_back.d ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_back.o ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_fill.d ./TouchGFX/generated/images/src/__designer/image_Dark_Slider_Vertical_Small_Slider3_Vertical_Round_fill.o

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-__designer

