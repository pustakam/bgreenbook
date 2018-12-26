# Modified from https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
#INC_DIRS ?= ./include
INC_DIRS ?= 

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
#$(info SRCS = $(SRCS))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -Wpedantic -g $(shell pkg-config --cflags gtest)
LDFLAGS := $(shell pkg-config --libs gtest)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

