################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/eth/colon2mac.c \
../device/eth/ethcontrol.c \
../device/eth/ethhandler.c \
../device/eth/ethinit.c \
../device/eth/ethmcast.c \
../device/eth/ethread.c \
../device/eth/ethwrite.c 

S_UPPER_SRCS += \
../device/eth/ethdispatch.S 

OBJS += \
./device/eth/colon2mac.o \
./device/eth/ethcontrol.o \
./device/eth/ethdispatch.o \
./device/eth/ethhandler.o \
./device/eth/ethinit.o \
./device/eth/ethmcast.o \
./device/eth/ethread.o \
./device/eth/ethwrite.o 

C_DEPS += \
./device/eth/colon2mac.d \
./device/eth/ethcontrol.d \
./device/eth/ethhandler.d \
./device/eth/ethinit.d \
./device/eth/ethmcast.d \
./device/eth/ethread.d \
./device/eth/ethwrite.d 


# Each subdirectory must supply rules for building sources it contributes
device/eth/%.o: ../device/eth/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

device/eth/%.o: ../device/eth/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


