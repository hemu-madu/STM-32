################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bme280.c \
../Core/Src/diskio.c \
../Core/Src/ff.c \
../Core/Src/ffsystem.c \
../Core/Src/ffunicode.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/logger.c \
../Core/Src/main.c \
../Core/Src/rcc.c \
../Core/Src/rtc.c \
../Core/Src/sdcard.c \
../Core/Src/spi.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/uart.c 

OBJS += \
./Core/Src/bme280.o \
./Core/Src/diskio.o \
./Core/Src/ff.o \
./Core/Src/ffsystem.o \
./Core/Src/ffunicode.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/logger.o \
./Core/Src/main.o \
./Core/Src/rcc.o \
./Core/Src/rtc.o \
./Core/Src/sdcard.o \
./Core/Src/spi.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/uart.o 

C_DEPS += \
./Core/Src/bme280.d \
./Core/Src/diskio.d \
./Core/Src/ff.d \
./Core/Src/ffsystem.d \
./Core/Src/ffunicode.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/logger.d \
./Core/Src/main.d \
./Core/Src/rcc.d \
./Core/Src/rtc.d \
./Core/Src/sdcard.d \
./Core/Src/spi.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L476xx -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bme280.cyclo ./Core/Src/bme280.d ./Core/Src/bme280.o ./Core/Src/bme280.su ./Core/Src/diskio.cyclo ./Core/Src/diskio.d ./Core/Src/diskio.o ./Core/Src/diskio.su ./Core/Src/ff.cyclo ./Core/Src/ff.d ./Core/Src/ff.o ./Core/Src/ff.su ./Core/Src/ffsystem.cyclo ./Core/Src/ffsystem.d ./Core/Src/ffsystem.o ./Core/Src/ffsystem.su ./Core/Src/ffunicode.cyclo ./Core/Src/ffunicode.d ./Core/Src/ffunicode.o ./Core/Src/ffunicode.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/logger.cyclo ./Core/Src/logger.d ./Core/Src/logger.o ./Core/Src/logger.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rcc.cyclo ./Core/Src/rcc.d ./Core/Src/rcc.o ./Core/Src/rcc.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/sdcard.cyclo ./Core/Src/sdcard.d ./Core/Src/sdcard.o ./Core/Src/sdcard.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/uart.cyclo ./Core/Src/uart.d ./Core/Src/uart.o ./Core/Src/uart.su

.PHONY: clean-Core-2f-Src

