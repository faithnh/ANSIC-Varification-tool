################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ANSICInformation/ANSIC_CODE.c \
../ANSICInformation/AST.c \
../ANSICInformation/DivitionDeclarator.c \
../ANSICInformation/DivitionInformation.c \
../ANSICInformation/ForInformation.c \
../ANSICInformation/FreeMemInfo.c \
../ANSICInformation/FunctionInformation.c \
../ANSICInformation/LogicalExpression.c \
../ANSICInformation/MallocNumber.c \
../ANSICInformation/MemallocInfo.c \
../ANSICInformation/PointerArrayControl.c \
../ANSICInformation/PreProcess.c \
../ANSICInformation/Return_Info.c \
../ANSICInformation/SubEffectCheck.c \
../ANSICInformation/Synbol.c \
../ANSICInformation/VariableOfStatement.c \
../ANSICInformation/Varidate_statement.c \
../ANSICInformation/WriteVelificationStatement.c \
../ANSICInformation/lex.yy.c \
../ANSICInformation/y.tab.c 

OBJS += \
./ANSICInformation/ANSIC_CODE.o \
./ANSICInformation/AST.o \
./ANSICInformation/DivitionDeclarator.o \
./ANSICInformation/DivitionInformation.o \
./ANSICInformation/ForInformation.o \
./ANSICInformation/FreeMemInfo.o \
./ANSICInformation/FunctionInformation.o \
./ANSICInformation/LogicalExpression.o \
./ANSICInformation/MallocNumber.o \
./ANSICInformation/MemallocInfo.o \
./ANSICInformation/PointerArrayControl.o \
./ANSICInformation/PreProcess.o \
./ANSICInformation/Return_Info.o \
./ANSICInformation/SubEffectCheck.o \
./ANSICInformation/Synbol.o \
./ANSICInformation/VariableOfStatement.o \
./ANSICInformation/Varidate_statement.o \
./ANSICInformation/WriteVelificationStatement.o \
./ANSICInformation/lex.yy.o \
./ANSICInformation/y.tab.o 

C_DEPS += \
./ANSICInformation/ANSIC_CODE.d \
./ANSICInformation/AST.d \
./ANSICInformation/DivitionDeclarator.d \
./ANSICInformation/DivitionInformation.d \
./ANSICInformation/ForInformation.d \
./ANSICInformation/FreeMemInfo.d \
./ANSICInformation/FunctionInformation.d \
./ANSICInformation/LogicalExpression.d \
./ANSICInformation/MallocNumber.d \
./ANSICInformation/MemallocInfo.d \
./ANSICInformation/PointerArrayControl.d \
./ANSICInformation/PreProcess.d \
./ANSICInformation/Return_Info.d \
./ANSICInformation/SubEffectCheck.d \
./ANSICInformation/Synbol.d \
./ANSICInformation/VariableOfStatement.d \
./ANSICInformation/Varidate_statement.d \
./ANSICInformation/WriteVelificationStatement.d \
./ANSICInformation/lex.yy.d \
./ANSICInformation/y.tab.d 


# Each subdirectory must supply rules for building sources it contributes
ANSICInformation/%.o: ../ANSICInformation/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


