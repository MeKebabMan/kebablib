src := src
bin := bin
cc := clang

# Test target

test_extension := out
test_target := ./$(bin)/testbinary.$(test_extension)
test_cflags := -march=native -O0 -DKEBAB_DEBUG -DKEBAB_ABORT -g3 -ggdb -fsanitize=address,undefined 

# Lib target

lib_extension = so
lib_target := ./$(bin)/kebablib.$(lib_extension)
lib_cflags := -march=native -O3 -DNDEBUG

target ?= test
cflags := $(test_cflags)

ifeq ($(target), test)
# ==== test ====
	src_files := $(wildcard $(src)/*.c) test.c
	target_file := $(test_target)
else ifeq ($(target), lib)
# ==== lib ====
	target_file := $(lib_target)
	src_files := $(wildcard $(src)/*.c)
	cflags := $(lib_cflags)
else ifeq ($(target), static)
# ==== static ====
	target_file := $(lib_target)
	src_files := $(wildcard $(src)/*.c)
	cflags := $(lib_cflags)
else
	$(error INVALID TARGET)
endif

object_files := $(patsubst %.c, $(bin)/%.obj, $(notdir $(src_files)))

# Compiling

vpath %.c $(src)

ifeq ($(target), lib)
# ==== lib ====
$(bin)/%.obj: %.c
	@mkdir -p $(dir $@)
	$(cc) -c -fPIE $< -o $@ $(cflags)  -Iinclude
# Linking
$(target_file): $(object_files)
	@mkdir -p $(dir $@)
	$(cc) -shared -fPIC $^ -o $@ $(cflags) -lm -Iinclude 
else ifeq ($(target), static)
# ==== static ====
$(bin)/%.obj: %.c
	@mkdir -p $(dir $@)
	$(cc) -c $< -o $@ $(cflags) -Iinclude
# Linking
$(target_file): $(object_files)
	@mkdir -p $(dir $@)
	ar rcs $@ $^
else ifeq ($(target), test)
# ==== test ====
$(bin)/%.obj: %.c
	@mkdir -p $(dir $@)
	$(cc) -c $< -o $@ $(cflags) -Iinclude
# Linking
$(target_file): $(object_files)
	@mkdir -p $(dir $@)
	$(cc) $^ -o $@ $(cflags) -lm -Iinclude
else
	$(error INVALID TARGET)
endif

# Phony rules

clean: ./bin/*
# I DONT TRUST A DAMN VARIABLE
	@rm -r $^

.PHONY: clean