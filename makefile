# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Directories
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/main.c $(LIB_DIR)/parsing.c

# Object files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = rover_control

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the executable
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rule to check if the code is implemented correctly
check: $(TARGET)
	./$(TARGET) # Add any specific test commands if needed

.PHONY: all clean check
