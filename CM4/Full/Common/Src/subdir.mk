################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Src/shared.c \
/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c 

C_DEPS += \
./Common/Src/shared.d \
./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.d 

OBJS += \
./Common/Src/shared.o \
./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.o 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/shared.o: /home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Src/shared.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DARM_MATH_CM4 -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Application/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Core/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Middlewares/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Peripheral/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Utilities/Fonts" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Utilities/lcd" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/Common" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/ft6x06" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/is42s32800j" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/otm8009a" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/mt25tl01g" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/wm8994" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/STM32H747I-Discovery" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/STM32H7xx_HAL_Driver" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/App" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/target" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/target/generated" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/fonts/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/gui_generated/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/images/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/texts/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/videos/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/gui/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Middlewares/ST/touchgfx/framework/include" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/ARM/DSP/Inc -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../../Middlewares/Third_Party/FreeRTOS/Source/include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.o: /home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DARM_MATH_CM4 -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Application/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Core/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Middlewares/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Peripheral/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Utilities/Fonts" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Utilities/lcd" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Common/Inc" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/Common" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/ft6x06" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/is42s32800j" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/otm8009a" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/mt25tl01g" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/Components/wm8994" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/BSP/STM32H747I-Discovery" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Drivers/STM32H7xx_HAL_Driver" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/App" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/target" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/target/generated" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/fonts/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/gui_generated/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/images/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/texts/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/generated/videos/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/TouchGFX/gui/include" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/CM4/Middlewares/ST/touchgfx/framework/include" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/ARM/DSP/Inc -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/zhonx/Documents/Workspace_Cube_SSS/SSS_MOD-747DISCO/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../../Middlewares/Third_Party/FreeRTOS/Source/include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src

clean-Common-2f-Src:
	-$(RM) ./Common/Src/shared.d ./Common/Src/shared.o ./Common/Src/shared.su ./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.d ./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.o ./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.su

.PHONY: clean-Common-2f-Src

