# Compiler/linker options
CC = gcc
CFLAGS = -c -Wno-unused -Wno-unused-macros -g
LDFLAGS = 
V = @

# Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Files
SRC = hexdiff.c
EXE = hexdiff
SRC_FILES = $(SRC:%.c=$(SRC_DIR)/%.c)
OBJ_FILES = $(SRC:%.c=$(OBJ_DIR)/%.o)
EXE_FILES = $(EXE:%=$(BIN_DIR)/%)

# Phony
.PHONY: build clean

# Make

$(EXE_FILES): $(OBJ_FILES)
	$(V)$(CC) $(LDFLAGS) -o $@ $^
	@echo Build successful!

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo + $<
	$(V)mkdir -p $(@D)
	$(V)$(CC) $(CFLAGS) -o $@ $<

build: $(EXE_FILES)

clean:
	rm -Rf $(OBJ_DIR) $(EXE)
