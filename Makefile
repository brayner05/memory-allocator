# Compiler and tools
CC = gcc
AS = as

# Compiler and linker flags
CFLAGS = -Wall -g
LDFLAGS = -z noexecstack

# Source files and object files
SRC_DIR = src
OBJ_DIR = out

C_SRC = $(wildcard $(SRC_DIR)/*.c)
ASM_SRC = $(wildcard $(SRC_DIR)/*.asm)

C_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRC))
ASM_OBJ = $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(ASM_SRC))
OBJ = $(C_OBJ) $(ASM_OBJ)

# Target executable
TARGET = out/a.out

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile C source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble assembly source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	$(AS) $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)

run:
	./out/a.out

# Phony targets
.PHONY: all clean
