################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ObjRecog/controlOR.cpp \
../src/ObjRecog/imageDB.cpp \
../src/ObjRecog/visualWords.cpp 

OBJS += \
./src/ObjRecog/controlOR.o \
./src/ObjRecog/imageDB.o \
./src/ObjRecog/visualWords.o 

CPP_DEPS += \
./src/ObjRecog/controlOR.d \
./src/ObjRecog/imageDB.d \
./src/ObjRecog/visualWords.d 


# Each subdirectory must supply rules for building sources it contributes
src/ObjRecog/%.o: ../src/ObjRecog/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


