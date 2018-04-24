################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/src/animatedsprite.cpp \
../source/src/game.cpp \
../source/src/graphics.cpp \
../source/src/input.cpp \
../source/src/level.cpp \
../source/src/main.cpp \
../source/src/player.cpp \
../source/src/sprite.cpp \
../source/src/tile.cpp \
../source/src/tinyxml2.cpp 

OBJS += \
./source/src/animatedsprite.o \
./source/src/game.o \
./source/src/graphics.o \
./source/src/input.o \
./source/src/level.o \
./source/src/main.o \
./source/src/player.o \
./source/src/sprite.o \
./source/src/tile.o \
./source/src/tinyxml2.o 

CPP_DEPS += \
./source/src/animatedsprite.d \
./source/src/game.d \
./source/src/graphics.d \
./source/src/input.d \
./source/src/level.d \
./source/src/main.d \
./source/src/player.d \
./source/src/sprite.d \
./source/src/tile.d \
./source/src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
source/src/%.o: ../source/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/jezwin/eclipse-workspace/BlobWorld/source/headers" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


