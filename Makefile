# Compiler/linker options
CC = g++
CFLAGS = -c -Wno-unused -Wno-unused-macros -g
LDFLAGS = -l argp
V = @

# Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Files
SRC = parsecli.cpp \
			hexdiff.cpp
EXE = hexdiff
SRC_FILES = $(SRC:%.cpp=$(SRC_DIR)/%.cpp)
OBJ_FILES = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
EXE_FILES = $(EXE:%=$(BIN_DIR)/%)

# Phony
.PHONY: build clean

# Make

$(EXE_FILES): $(OBJ_FILES)
	$(V)$(CC) $(LDFLAGS) -o $@ $^
	@echo Build successful!

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo + $<
	$(V)mkdir -p $(@D)
	$(V)$(CC) $(CFLAGS) -o $@ $<

build: $(EXE_FILES)

clean:
	rm -Rf $(OBJ_DIR) $(EXE)
