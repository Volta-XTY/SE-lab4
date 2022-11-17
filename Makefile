BUILD_DIR = ./build
INC_DIR = src/include
OBJ_DIR = $(BUILD_DIR)/obj
BINARY_NAME = judge

CC = g++
LD = g++
INCLUDES = $(addprefix -I, $(INC_DIR))
CFLAGS = -O2 -Wall -Werror -ggdb -std=c++17 $(INCLUDES)

SRCS = $(shell find src/ -name "*.cc")
OBJS = $(SRCS:src/%.cc=$(OBJ_DIR)/%.o)
$(OBJ_DIR)/%.o: src/%.cc
	@echo + CXX $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(BINARY_NAME): $(OBJS)
	@echo + LD $@
	@$(LD) -O2 -o $@ $^


.PHONY: bin run

bin: $(BUILD_DIR)/$(BINARY_NAME)

run: bin
	@cd $(BUILD_DIR) && ./$(BINARY_NAME)
