BUILD_DIR = ./build
INC_DIR = src/include
SRC_DIR = ./src
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

ZIP = lab4-201220088-夏天钰.zip
ZIP_DIR= ./lab4-201220088-夏天钰

REPORT_DIR = ./writeup
REPORT_SRC = $(shell find $(REPORT_DIR) -name "*.tex")
REPORT_SRC_REL = $(shell cd $(REPORT_DIR) && find . -name "*.tex")
REPORT = $(REPORT_SRC:$(REPORT_DIR)/%.tex=$(REPORT_DIR)/%.pdf)

CODE_DIR = $(ZIP_DIR)/lab4-code

$(REPORT): $(REPORT_SRC)
	@cd $(REPORT_DIR) && xelatex $(REPORT_SRC_REL)

$(ZIP_DIR): $(REPORT) run
	mkdir -p $(ZIP_DIR)
	mkdir -p $(CODE_DIR)
	cp $(REPORT) $(ZIP_DIR)
	cp -r $(SRC_DIR) $(OUTPUT) $(CODE_DIR)

$(ZIP): $(ZIP_DIR)
	rm -f $(ZIP)
	zip -r $(ZIP) $(ZIP_DIR)
	rm -rf $(ZIP_DIR)


.PHONY: bin run submit

bin: $(BUILD_DIR)/$(BINARY_NAME)

run: bin
	@cd $(BUILD_DIR) && ./$(BINARY_NAME)

OUTPUT = $(shell find $(BUILD_DIR)/ -name "*.csv")

submit: $(ZIP)
