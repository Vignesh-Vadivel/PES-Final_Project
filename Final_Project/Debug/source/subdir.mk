################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/DAC.c \
../source/DMA.c \
../source/Final_Project.c \
../source/LEDs.c \
../source/i2c.c \
../source/mma8451.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/systick.c \
../source/timers.c 

C_DEPS += \
./source/DAC.d \
./source/DMA.d \
./source/Final_Project.d \
./source/LEDs.d \
./source/i2c.d \
./source/mma8451.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/systick.d \
./source/timers.d 

OBJS += \
./source/DAC.o \
./source/DMA.o \
./source/Final_Project.o \
./source/LEDs.o \
./source/i2c.o \
./source/mma8451.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/systick.o \
./source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project\board" -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project\source" -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project" -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project\drivers" -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project\CMSIS" -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project\utilities" -I"S:\MCUXpressoIDE_11.6.0_8187\Final_Project\startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/DAC.d ./source/DAC.o ./source/DMA.d ./source/DMA.o ./source/Final_Project.d ./source/Final_Project.o ./source/LEDs.d ./source/LEDs.o ./source/i2c.d ./source/i2c.o ./source/mma8451.d ./source/mma8451.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/systick.d ./source/systick.o ./source/timers.d ./source/timers.o

.PHONY: clean-source

