AS = as
CC = g++
LD = g++

ASFLAGS =  -g
CFLAGS = -std=c++20 -Wall -g
LDFLAGS = -g

TARGET = pvz_asm

BUILD_DIR = build
SRC_DIR = src

ASM_SRC = $(SRC_DIR)/asm/main.s
CPP_SRC = $(SRC_DIR)/main.cpp

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/asm.o

.PHONY: all clean

all: $(TARGET) $(BUILD_DIR) 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/asm.o: $(ASM_SRC) $(BUILD_DIR) 
	$(AS) $(ASFLAGS) -o $(BUILD_DIR)/asm.o $(ASM_SRC)

$(BUILD_DIR)/main.o: $(CPP_SRC) $(BUILD_DIR) 
	$(CC) $(CFLAGS) -c $(CPP_SRC) -o $(BUILD_DIR)/main.o 
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(BUILD_DIR)
