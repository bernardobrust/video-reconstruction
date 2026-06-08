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

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CFLAGS := $(C_STD)
CFLAGS += $(addprefix -I,$(INC_DIRS))
CFLAGS += -MMD -MP

EXTERNAL_LIBS := -lX11

WARN_FLAGS    := -Wall -Wextra -Werror
DBG_FLAGS     := -ggdb -O0 -fsanitize=address
RELEASE_FLAGS := -Ofast -flto -march=native -DNDEBUG

LDFLAGS :=

ifeq ($(filter $(MODE),debug test),$(MODE))
    CFLAGS  += $(WARN_FLAGS) $(DBG_FLAGS)
    LDFLAGS += -fsanitize=address
else
    CFLAGS += $(RELEASE_FLAGS)
endif

BIN := $(BUILD_DIR)/$(TARGET)/$(TARGET)

$(BIN): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(EXTERNAL_LIBS)

$(BUILD_DIR)/%.o: %
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean test

test: $(BIN)
	./$(BIN)

clean:
	rm -rf build

-include $(DEPS)