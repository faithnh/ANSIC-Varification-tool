################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ProgramSlicing/DeclarationPSI.c \
../ProgramSlicing/ExpressionStatementPSI.c \
../ProgramSlicing/ForStatementPSI.c \
../ProgramSlicing/FunctionPSI.c \
../ProgramSlicing/IfStatementPSI.c \
../ProgramSlicing/JumpStatementPSI.c \
../ProgramSlicing/LabeledStatementPSI.c \
../ProgramSlicing/ProgramSlicing.c \
../ProgramSlicing/ProgramSlicingInformation.c \
../ProgramSlicing/ReturnStatementPSI.c \
../ProgramSlicing/SwitchStatementPSI.c \
../ProgramSlicing/WhileStatementPSI.c 

OBJS += \
./ProgramSlicing/DeclarationPSI.o \
./ProgramSlicing/ExpressionStatementPSI.o \
./ProgramSlicing/ForStatementPSI.o \
./ProgramSlicing/FunctionPSI.o \
./ProgramSlicing/IfStatementPSI.o \
./ProgramSlicing/JumpStatementPSI.o \
./ProgramSlicing/LabeledStatementPSI.o \
./ProgramSlicing/ProgramSlicing.o \
./ProgramSlicing/ProgramSlicingInformation.o \
./ProgramSlicing/ReturnStatementPSI.o \
./ProgramSlicing/SwitchStatementPSI.o \
./ProgramSlicing/WhileStatementPSI.o 

C_DEPS += \
./ProgramSlicing/DeclarationPSI.d \
./ProgramSlicing/ExpressionStatementPSI.d \
./ProgramSlicing/ForStatementPSI.d \
./ProgramSlicing/FunctionPSI.d \
./ProgramSlicing/IfStatementPSI.d \
./ProgramSlicing/JumpStatementPSI.d \
./ProgramSlicing/LabeledStatementPSI.d \
./ProgramSlicing/ProgramSlicing.d \
./ProgramSlicing/ProgramSlicingInformation.d \
./ProgramSlicing/ReturnStatementPSI.d \
./ProgramSlicing/SwitchStatementPSI.d \
./ProgramSlicing/WhileStatementPSI.d 


# Each subdirectory must supply rules for building sources it contributes
ProgramSlicing/%.o: ../ProgramSlicing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


