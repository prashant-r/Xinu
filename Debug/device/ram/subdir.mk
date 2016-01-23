################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/ram/ramclose.c \
../device/ram/raminit.c \
../device/ram/ramopen.c \
../device/ram/ramread.c \
../device/ram/ramwrite.c 

OBJS += \
./device/ram/ramclose.o \
./device/ram/raminit.o \
./device/ram/ramopen.o \
./device/ram/ramread.o \
./device/ram/ramwrite.o 

C_DEPS += \
./device/ram/ramclose.d \
./device/ram/raminit.d \
./device/ram/ramopen.d \
./device/ram/ramread.d \
./device/ram/ramwrite.d 


# Each subdirectory must supply rules for building sources it contributes
device/ram/%.o: ../device/ram/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


