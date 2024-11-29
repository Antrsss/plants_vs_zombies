AS = as
CC = g++
LD = g++

ASFLAGS =  -g
CFLAGS = -std=c++20 -Wall -g
LDFLAGS = -g

TARGET = pvz_asm

BUILD_DIR = build
SRC_DIR = src
LIBS_DIRS = -I./include/
LIBS = $(LIBS_DIRS) -lncursesw

ASM_SRC = $(SRC_DIR)/asm/main.s
CPP_SRC = $(SRC_DIR)/main.cpp 
HEADERS = $(SRC_DIR)/display.h $(SRC_DIR)/entities.h $(SRC_DIR)/config.h
DISPLAY_SRC = $(SRC_DIR)/display.cpp
ENTITIES_SRC = $(SRC_DIR)/entities.cpp
OBJS = $(BUILD_DIR)/display.o $(BUILD_DIR)/entities.o $(BUILD_DIR)/main.o $(BUILD_DIR)/step.o $(BUILD_DIR)/suns.o

.PHONY: all clean

all: $(TARGET) $(BUILD_DIR) 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(HEADERS) $(OBJS) $(LIBS)

$(BUILD_DIR)/step.o: $(ASM_SRC) $(BUILD_DIR) 
	$(AS) $(ASFLAGS) -o $(BUILD_DIR)/step.o $(SRC_DIR)/asm/main.s

$(BUILD_DIR)/suns.o: $(ASM_SRC) $(BUILD_DIR) 
	$(AS) $(ASFLAGS) -o $(BUILD_DIR)/suns.o $(SRC_DIR)/asm/generate_sun.s

$(BUILD_DIR)/main.o: $(CPP_SRC) $(BUILD_DIR) 
	$(CC) $(CFLAGS) -c $(CPP_SRC) -o $(BUILD_DIR)/main.o 

$(BUILD_DIR)/display.o: $(DISPLAY_SRC) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(DISPLAY_SRC) -o $(BUILD_DIR)/display.o

$(BUILD_DIR)/entities.o: $(ENTITIES_SRC) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(ENTITIES_SRC) -o $(BUILD_DIR)/entities.o

clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(BUILD_DIR)
