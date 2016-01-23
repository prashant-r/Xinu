################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../net/arp.c \
../net/arp_dump.c \
../net/dhcp.c \
../net/dhcp_dump.c \
../net/dot2ip.c \
../net/hexdump.c \
../net/icmp.c \
../net/ip.c \
../net/net.c \
../net/netstart.c \
../net/pdump.c \
../net/pxe.c \
../net/tftp.c \
../net/udp.c 

OBJS += \
./net/arp.o \
./net/arp_dump.o \
./net/dhcp.o \
./net/dhcp_dump.o \
./net/dot2ip.o \
./net/hexdump.o \
./net/icmp.o \
./net/ip.o \
./net/net.o \
./net/netstart.o \
./net/pdump.o \
./net/pxe.o \
./net/tftp.o \
./net/udp.o 

C_DEPS += \
./net/arp.d \
./net/arp_dump.d \
./net/dhcp.d \
./net/dhcp_dump.d \
./net/dot2ip.d \
./net/hexdump.d \
./net/icmp.d \
./net/ip.d \
./net/net.d \
./net/netstart.d \
./net/pdump.d \
./net/pxe.d \
./net/tftp.d \
./net/udp.d 


# Each subdirectory must supply rules for building sources it contributes
net/%.o: ../net/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


