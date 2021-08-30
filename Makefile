
# folder/files config
BUILD_DIR=build

SOURCES_C = \
		main.c \
		display.c

# create list of object based on C filenames
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_C:.c=.o)))
vpath %.c $(sort $(dir $(SOURCES_C)))

DEFINE_GLOBAL= -D_GNU_SOURCE

DEFINE_TEST= -DDBG_TEST
DBG_FLAG= -g

CFLAGS = -std=c11
CFLAGS+= $(DEFINE_GLOBAL)

CFLAGS_DBG = $(CFLAGS)
CFLAGS_DBG+= $(DEFINE_TEST)


.PHONY: clean

all: output_dbg Makefile
	@echo "Build Complete"

output_bin: $(OBJECTS)
	gcc $(CFLAGS) $< -o $@

output_dbg: $(OBJECTS)
	gcc $(CFLAGS_DBG) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@echo "Compiling $<..."
	gcc -c $(CFLAGS_DBG) $< -o $@

clean:
	rm -f output.* 2> /dev/null
	rm -f build/* 2> /dev/null
