CC=gcc
CFLAGS=-Wall -Wextra -std=c2x -pedantic -ggdb
INCLUDE=-Iinclude
SRC_DIR=src
BUILD_DIR=build

SOURCES=$(wildcard $(SRC_DIR)/*.c)
TARGET=$(BUILD_DIR)/game

$(TARGET): $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET) -lraylib

clean:
	rm -rf $(BUILD_DIR)
