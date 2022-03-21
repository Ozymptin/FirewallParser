SRC_FILES := $(wildcard src/*.c)
HDR_FILES := $(wildcard src/*.h)
BUILD_DIR := build

BUILD := mkdir -p ./$(BUILD_DIR)

LIBS=-lnetfilter_log
CC=gcc
CFLAGS=-Wall -Wextra -O1 -Wno-unused
CDFLAGS=-g3 -Og

.PHONY: fwp debug run rund clean

fwp: $(SRC_FILES) $(HDR_FILES)
	$(BUILD)
	$(CC) $(CFLAGS) $(LIBS) $(SRC_FILES) -o $(BUILD_DIR)/fwp

debug: $(SRC_FILES) $(HDR_FILES)
	$(BUILD)
	$(CC) $(CFLAGS) $(CDFLAGS) $(LIBS) $(SRC_FILES) -o $(BUILD_DIR)/fwpd

run: fwp
	./$(BUILD_DIR)/fwp

rund: debug
	./$(BUILD_DIR)/fwpd

clean:
	rm -rf ./$(BUILD_DIR)
