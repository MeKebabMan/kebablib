# variables
Src := src
Bin := bin
CC := clang
Testfile := test.c
Target := $(Bin)/test.out

# Lib

CompileLib := false
LibTarget := $(Bin)/kebablib
LibExtension := so
LibCflags := -march=native -O3 -DNDEBUG -DKEBAB_ABORT

headers := -Iinclude
cflags := -march=native -O3 -Wall -Wextra -fsanitize=address,undefined -g3 -ggdb -fstack-protector-strong -DKEBAB_DEBUG -DKEBAB_ABORT
  
# files

Srcs = $(wildcard $(Src)/*.c)
Objs = $(patsubst $(Src)/%.c, $(Bin)/%.obj, $(Srcs))
TestTarget = $(Bin)/test.obj

ifeq ($(CompileLib),true)
All: $(LibTarget)
else
All: $(Target)
endif

# Creating object files

ifeq ($(CompileLib),true)
$(Bin)/%.obj: $(Src)/%.c
	@mkdir -p $(dir $@)

	$(CC) -c -fPIC $< -o $@ $(LibCflags) -lm $(headers)
else
$(Bin)/%.obj: $(Src)/%.c
	@mkdir -p $(dir $@)

	$(CC) -c $< -o $@ $(cflags) -lm $(headers)
endif

# Compile the test file as well
$(TestTarget): $(Testfile)
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(cflags) $(headers)

# Linking 

$(Target): $(Objs) $(TestTarget)
	$(CC) $^ -o $@ $(cflags) $(headers)

ifeq ($(CompileLib),true)
$(LibTarget): $(Objs)
	$(CC) -shared $^ -o $@.$(LibExtension) $(LibCflags) $(headers)
endif

# Phony rules

ifeq ($(CompileLib),true)
clean:
	rm -f $(LibTarget) $(Objs)
else
clean:
	rm -f $(Target) $(TestTarget) $(Objs)
endif	

.PHONY: clean