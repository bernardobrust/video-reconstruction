# We could use c2y for the most modern, but c11 has everything we need and is standard
CC 	  := gcc
C_STD := --std=c11

MODE   ?= debug
TARGET ?=

VALID_TARGETS := inspector reconstructor

ifeq ($(filter clean,$(MAKECMDGOALS)),)
    ifeq ($(filter $(TARGET),$(VALID_TARGETS)),)
        $(error TARGET must be one of: $(VALID_TARGETS))
    endif
endif

# Easier testing command
ifeq ($(MAKECMDGOALS),test)
    MODE := test
endif

BUILD_DIR := build/$(MODE)
LIB_DIR   := lib

INC_DIRS := $(shell find $(TARGET) -type d) $(LIB_DIR)

ifeq ($(MODE),test)
    SRCS := $(shell find $(TARGET) -name '*.c' ! -name 'main.c')
else
    SRCS := $(shell find $(TARGET) -name '*.c' ! -name '*.test.c')
endif

FLAGS := $(C_STD)
FLAGS += $(addprefix -I,$(INC_DIRS))
FLAGS += -MMD -MP

WARN_FLAGS    := -Wall -Wextra -Werror
DBG_FLAGS     := -ggdb -O0 -fsanitize=address
RELEASE_FLAGS := -Ofast -flto -march=native -DNDEBUG

LD_FLAGS :=

ifeq ($(filter $(MODE),debug test),$(MODE))
    FLAGS += $(WARN_FLAGS) $(DBG_FLAGS)
    LD_FLAGS += -fsanitize=address
else
    FLAGS += $(RELEASE_FLAGS)
endif

BIN := $(BUILD_DIR)/$(TARGET)/$(TARGET)

$(BIN): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean test

test: $(BIN)
	./$(BIN)

clean:
	rm -rf build

-include $(DEPS)