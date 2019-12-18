# Author: jaspalsingh@cmail.carleton.ca
# Date: Dec 01 2019
# Version: 1.0

CC        = gcc
CFLAGS    = -Wall
rm        = rm -f
APP       = main

# CORE FILE DIRs
BINARY_DIR   = bin
BUILD_DIR    = build
INCLUDE_DIR  = include
SOURCE_DIR   = src

TEST_SOURCE  = test/src
TEST_INCLUDE = test/include

GSL_LIB      = lib/gsl/lib
GSL_INCLUDE  = lib/gsl/include


LFLAGS   = -L$(GSL_LIB) -lgsl -lgslcblas -lm

INC      := -I$(INCLUDE_DIR) -I$(GSL_INCLUDE) -I$(TEST_INCLUDE)
CORE_SRC := $(wildcard $(SOURCE_DIR)/*.c)
TEST_SRC := $(wildcard $(TEST_SOURCE)/*.c)
CORE_OBJ := $(CORE_SRC:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJ := $(TEST_SRC:$(TEST_SOURCE)/%.c=$(BUILD_DIR)/%.o)


$(BINARY_DIR)/$(APP): $(CORE_OBJ) $(TEST_OBJ)
	@mkdir -p $(BINARY_DIR)
	@$(CC) $(CORE_OBJ) $(TEST_OBJ) $(LFLAGS) -o $@
	@echo "Finished Linking ..."

$(CORE_OBJ): $(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Finished Compiling Module "$<" ..."

$(TEST_OBJ): $(BUILD_DIR)/%.o : $(TEST_SOURCE)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Finished Compiling Module  "$<" ..."

clean:
	@$(rm) $(CORE_OBJ) $(TEST_OBJ) $(BINARY_DIR)/$(APP)
	@echo "Finished Cleaning ..."