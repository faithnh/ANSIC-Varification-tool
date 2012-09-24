################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CSTLString.c \
../Library/CharStringExtend.c \
../Library/FlagDatabase.c \
../Library/IdList.c \
../Library/PrintExtend.c \
../Library/Stack_int.c \
../Library/StoreInformation.c 

OBJS += \
./Library/CSTLString.o \
./Library/CharStringExtend.o \
./Library/FlagDatabase.o \
./Library/IdList.o \
./Library/PrintExtend.o \
./Library/Stack_int.o \
./Library/StoreInformation.o 

C_DEPS += \
./Library/CSTLString.d \
./Library/CharStringExtend.d \
./Library/FlagDatabase.d \
./Library/IdList.d \
./Library/PrintExtend.d \
./Library/Stack_int.d \
./Library/StoreInformation.d 


# Each subdirectory must supply rules for building sources it contributes
Library/%.o: ../Library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


