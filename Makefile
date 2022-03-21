SRC_DIR := $(wildcard src/*.c)
BUILD_DIR := build

BUILD := mkdir -p ./$(BUILD_DIR)

LIBS=-lnetfilter_log
CC=gcc
CFLAGS=-Wall -Wextra -O1
CDFLAGS=-g3 -Og

.PHONY: fwp debug run rund clean

fwp: $(SRC_DIR)
	$(BUILD)
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR) -o $(BUILD_DIR)/fwp

debug: $(SRC_DIR)
	$(BUILD)
	$(CC) $(CFLAGS) $(CDFLAGS) $(LIBS) $(SRC_DIR) -o $(BUILD_DIR)/fwpd

run: fwp
	./$(BUILD_DIR)/fwp

rund: debug
	./$(BUILD_DIR)/fwpd

clean:
	rm -rf ./$(BUILD_DIR)
