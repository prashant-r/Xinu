################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/lfs/lfdballoc.c \
../device/lfs/lfdbfree.c \
../device/lfs/lfflush.c \
../device/lfs/lfgetmode.c \
../device/lfs/lfiballoc.c \
../device/lfs/lfibclear.c \
../device/lfs/lfibget.c \
../device/lfs/lfibput.c \
../device/lfs/lflclose.c \
../device/lfs/lflcontrol.c \
../device/lfs/lflgetc.c \
../device/lfs/lflinit.c \
../device/lfs/lflputc.c \
../device/lfs/lflread.c \
../device/lfs/lflseek.c \
../device/lfs/lflwrite.c \
../device/lfs/lfsckfmt.c \
../device/lfs/lfscreate.c \
../device/lfs/lfsetup.c \
../device/lfs/lfsinit.c \
../device/lfs/lfsopen.c \
../device/lfs/lftruncate.c 

OBJS += \
./device/lfs/lfdballoc.o \
./device/lfs/lfdbfree.o \
./device/lfs/lfflush.o \
./device/lfs/lfgetmode.o \
./device/lfs/lfiballoc.o \
./device/lfs/lfibclear.o \
./device/lfs/lfibget.o \
./device/lfs/lfibput.o \
./device/lfs/lflclose.o \
./device/lfs/lflcontrol.o \
./device/lfs/lflgetc.o \
./device/lfs/lflinit.o \
./device/lfs/lflputc.o \
./device/lfs/lflread.o \
./device/lfs/lflseek.o \
./device/lfs/lflwrite.o \
./device/lfs/lfsckfmt.o \
./device/lfs/lfscreate.o \
./device/lfs/lfsetup.o \
./device/lfs/lfsinit.o \
./device/lfs/lfsopen.o \
./device/lfs/lftruncate.o 

C_DEPS += \
./device/lfs/lfdballoc.d \
./device/lfs/lfdbfree.d \
./device/lfs/lfflush.d \
./device/lfs/lfgetmode.d \
./device/lfs/lfiballoc.d \
./device/lfs/lfibclear.d \
./device/lfs/lfibget.d \
./device/lfs/lfibput.d \
./device/lfs/lflclose.d \
./device/lfs/lflcontrol.d \
./device/lfs/lflgetc.d \
./device/lfs/lflinit.d \
./device/lfs/lflputc.d \
./device/lfs/lflread.d \
./device/lfs/lflseek.d \
./device/lfs/lflwrite.d \
./device/lfs/lfsckfmt.d \
./device/lfs/lfscreate.d \
./device/lfs/lfsetup.d \
./device/lfs/lfsinit.d \
./device/lfs/lfsopen.d \
./device/lfs/lftruncate.d 


# Each subdirectory must supply rules for building sources it contributes
device/lfs/%.o: ../device/lfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


