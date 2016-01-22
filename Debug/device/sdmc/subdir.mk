################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/sdmc/sdmcclose.c \
../device/sdmc/sdmccmd.c \
../device/sdmc/sdmcinit.c \
../device/sdmc/sdmcinterrupt.c \
../device/sdmc/sdmcopen.c \
../device/sdmc/sdmcread.c \
../device/sdmc/sdmcwrite.c 

S_UPPER_SRCS += \
../device/sdmc/sdmcdispatch.S 

OBJS += \
./device/sdmc/sdmcclose.o \
./device/sdmc/sdmccmd.o \
./device/sdmc/sdmcdispatch.o \
./device/sdmc/sdmcinit.o \
./device/sdmc/sdmcinterrupt.o \
./device/sdmc/sdmcopen.o \
./device/sdmc/sdmcread.o \
./device/sdmc/sdmcwrite.o 

C_DEPS += \
./device/sdmc/sdmcclose.d \
./device/sdmc/sdmccmd.d \
./device/sdmc/sdmcinit.d \
./device/sdmc/sdmcinterrupt.d \
./device/sdmc/sdmcopen.d \
./device/sdmc/sdmcread.d \
./device/sdmc/sdmcwrite.d 


# Each subdirectory must supply rules for building sources it contributes
device/sdmc/%.o: ../device/sdmc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

device/sdmc/%.o: ../device/sdmc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


