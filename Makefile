CXX = clang++

SRC_DIR := src
BUILD_DIR := build
BINARY := main
TARGET := $(BINARY)
LIBS_FOLDER := libs

INCLUDE_FLAGS := -I$(LIBS_FOLDER) -I$(LIBS_FOLDER)/glad/include/

CXXFLAGS := -std=c++20 -I$(SRC_DIR) $(INCLUDE_FLAGS) -Wall -Wextra -MMD -MP -O0 -g
CXXLIBS :=

PKG_DEPS := sdl3
PKG_CFLAGS := $(shell pkg-config --cflags $(PKG_DEPS))
PKG_LIBS := $(shell pkg-config --libs $(PKG_DEPS))

LIBS_SRC := $(wildcard $(LIBS_FOLDER)/glad/*.c)
LIBS_OBJS := $(patsubst $(LIBS_FOLDER)/glad/%.c,$(BUILD_DIR)/%.o,$(LIBS_SRC))

CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))

C_SRCS := $(wildcard $(SRC_DIR)/*.c)
C_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))
OBJS := $(CPP_OBJS) $(C_OBJS) $(LIBS_OBJS)
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

run: all
	./$(BINARY)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $^ -o $@ $(CXXLIBS) $(PKG_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PKG_CFLAGS) -c $< -o $@

# Libs specific
$(BUILD_DIR)/%.o: $(LIBS_FOLDER)/glad/%.c | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PKG_CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
