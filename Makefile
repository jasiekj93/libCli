# ------------------------------------------------
# @author Adrian Szczepanski
# @date 23-07-2021
# ------------------------------------------------

# Target
TARGET = libCli
PLATFORM = ARM

ifeq ($(PLATFORM), Win32)
TARGET := $(TARGET)Win32
endif

# debug
DEBUG = 1
OPT = -O0

# external libraries
EXTERNAL_NAMES = \
CppUTest \

# directories
BUILD_ROOT = build
BUILD_DIR = build/$(TARGET)
LIB_DIR = lib

# toolchain
ifeq ($(PLATFORM), Win32)
PREFIX = 
else
PREFIX = arm-none-eabi-
endif

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
$(wildcard libCli/*.cpp) \
$(wildcard libCli/Utils/*.cpp) \
$(wildcard libCli/Template/*.cpp) \
$(wildcard libCli/Model/*.cpp) \
$(wildcard libCli/Internal/*.cpp) \
$(wildcard libCli/Internal/IO/*.cpp) \
$(wildcard libCli/Internal/IO/Container/*.cpp) \

# includes
CXX_INCLUDES =  \
-I. \

# gcc flags
CXXFLAGS = $(MCU) $(CXX_DEFS) $(CXX_INCLUDES) $(OPT) -std=c++17 -Wall  

ifneq ($(PLATFORM), Win32)
CXXFLAGS += -fdata-sections -ffunction-sections -ffreestanding -fno-exceptions -fno-rtti
endif

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

.PHONY: all externals library winLibrary tests print clean

# build all
all: externals library winLibrary tests

externals: 
	@echo Making external libraries
	@for library in $(EXTERNAL_NAMES); do \
		$(MAKE) -C external/$$library ; \
	done

library: $(LIB_DIR)/$(TARGET).a

winLibrary:
	$(MAKE) -C . library PLATFORM=Win32

tests:
	$(MAKE) -C tests

print-%  : ; @echo $* = $($*)

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
	mkdir $@

# clean up
rebuild:
	rm -rf $(BUILD_ROOT)
	$(MAKE) -C .

# clean up
clean:
	rm -rf $(BUILD_DIR)
  
# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)