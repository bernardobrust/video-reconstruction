# We could use c2y for the most modern, but c11 has everything we need and is standard
CC 	  := gcc
C_STD := --std=c11

MODE   ?= debug
TARGET ?= null

# Easier testing command
ifeq ($(MAKECMDGOALS),test)
    MODE := test
endif

BUILD_DIR := build/$(MODE)

RECONSTRUCTOR_DIR := reconstructor
INSPECTOR_DIR     := inspector
SRCS_DIR          := $(RECONSTRUCTOR_DIR) $(INSPECTOR_DIR)
LIB_DIR           := lib

ifeq ($(MODE), test)
    INC_DIRS_INSPECTOR := $(shell find $(INSPECTOR_DIR) -type d) $(LIB_DIR)
    SRCS_INSPECTOR     := $(shell find $(INSPECTOR_DIR) -name '*.c' ! -name 'main.c')

    INC_DIRS_RECONSTRUCTOR := $(shell find $(RECONSTRUCTOR_DIR) -type d) $(LIB_DIR)
    SRCS_RECONSTRUCTOR     := $(shell find $(RECONSTRUCTOR_DIR) -name '*.c' ! -name 'main.c')
else
    INC_DIRS_INSPECTOR := $(shell find $(INSPECTOR_DIR) -type d) $(LIB_DIR)
    SRCS_INSPECTOR     := $(shell find $(INSPECTOR_DIR) -name '*.c' ! -name '*.test.c')

    INC_DIRS_RECONSTRUCTOR := $(shell find $(RECONSTRUCTOR_DIR) -type d) $(LIB_DIR)
    SRCS_RECONSTRUCTOR     := $(shell find $(RECONSTRUCTOR_DIR) -name '*.c' ! -name '*.test.c')
endif

OBJS_INSPECTOR := $(SRCS_INSPECTOR:%=$(BUILD_DIR)/%.o)
DEPS_INSPECTOR := $(OBJS_INSPECTOR:.o=.d)

OBJS_RECONSTRUCTOR := $(SRCS_RECONSTRUCTOR:%=$(BUILD_DIR)/%.o)
DEPS_RECONSTRUCTOR := $(OBJS_RECONSTRUCTOR:.o=.d)

ifeq ($(TARGET),inspector)
    OBJS      := $(OBJS_INSPECTOR)
    DEPS      := $(DEPS_INSPECTOR)
    INC_FLAGS := $(addprefix -I,$(INC_DIRS_INSPECTOR))

else ifeq ($(TARGET),reconstructor)
    OBJS      := $(OBJS_RECONSTRUCTOR)
    DEPS      := $(DEPS_RECONSTRUCTOR)
    INC_FLAGS := $(addprefix -I,$(INC_DIRS_RECONSTRUCTOR))

else
	ifneq ($(MAKECMDGOALS),clean)
        $(error TARGET must be inspector, reconstructor, or both)
	endif
endif

C_COMMON     	:= $(INC_FLAGS) -MMD -MP
C_WARN_FLAGS    := -Wall -Wextra -Werror
C_DBG_FLAGS     := -ggdb -O0 -fsanitize=address
C_RELEASE_FLAGS := -Ofast -flto -march=native -DNDEBUG

LD_FLAGS :=

ifeq ($(filter $(MODE),debug test),$(MODE))
    C_COMMON += $(C_WARN_FLAGS) $(C_DBG_FLAGS)
    LD_FLAGS += -fsanitize=address
else
    C_COMMON += $(C_RELEASE_FLAGS)
endif

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@/$(TARGET) $(LD_FLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(C_STD) $(C_COMMON) -c $< -o $@

.PHONY: clean test
clean:
	rm -rf build/

test: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)/$(TARGET)

-include $(DEPS)
