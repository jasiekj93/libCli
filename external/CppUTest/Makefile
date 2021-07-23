# ------------------------------------------------
# @author Adrian Szczepanski
# @date 23-07-2021
# ------------------------------------------------

# Target
TARGET = libCppUTest
#PLATFORM = CortexM7
PLATFORM = Win32

ifeq (PLATFORM, Win32)
TARGET += Win32
endif

# debug
DEBUG = 1
OPT = -Og

# directories
BUILD_DIR = build/$(TARGET)
LIB_DIR = lib/$(PLATFORM)

# toolchain
ifeq ($(PLATFORM), Win32)
PREFIX = 
else
PREFIX = arm-none-eabi-
endif

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
AR = $(PREFIX)ar
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# mcu definition
ifeq ($(PLATFORM), Win32)
MCU = -m32
else
CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
endif 

# sources 
CXX_SOURCES =  \
$(wildcard CppUTest/*.cpp) \

# includes
CXX_INCLUDES =  \
-Iinclude \

#defines
ifeq ($(PLATFORM), Win32)
USE_STD_LIB = 1
else
USE_STD_LIB = 0
endif

CXX_DEFS = \
-DCPPUTEST_USE_STD_CPP_LIB=$(USE_STD_LIB)

# gcc flags
CXXFLAGS = $(MCU) $(CXX_DEFS) $(CXX_INCLUDES) $(OPT) -std=c++17 -Wall 

ifneq ($(PLATFORM), Win32)
CXXFLAGS += -fdata-sections -ffunction-sections -ffreestanding -fno-exceptions -nostdlib
endif

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

.PHONY: all print clean

# build all
all: $(LIB_DIR)/$(TARGET).a

print-%: ; @echo $* = $($*)

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

# list of C++ objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

# build C++ objects
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

# build library
$(LIB_DIR)/$(TARGET).a: $(OBJECTS) Makefile | $(LIB_DIR)
	@echo Creating library $@
	@$(AR) rcs $@ $(OBJECTS) 

# create directories
$(BUILD_DIR):
	mkdir -p $@		

$(LIB_DIR):
	mkdir -p $@

# clean up
clean:
	rm -rf $(BUILD_DIR)
  
# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)