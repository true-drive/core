CC := gcc
CFLAGS := -Wall -Wextra -g
SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/truedrive

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: clean $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) ./test/**/*.bmp ./test/**/*.bin ./test/**/output*

run: $(TARGET)
	$(TARGET) $(MAKECMDGOALS)
