SOURCE_DIRECTORY := src
OBJECT_DIRECTORY := obj
TEMPORY_DIRECTORY := tmp

GCC_FLAGS := -fdata-sections \
             -ffunction-sections \
             -fno-builtin \
             -fno-asynchronous-unwind-tables \
             -fno-ident \
             -finhibit-size-directive \
             -masm=intel \
             -O1

NASM_FLAGS := -a

NASM_FORMAT := elf64

C_SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.c)
C_ASSEMBLIES := $(patsubst $(SOURCE_DIRECTORY)/%.c, $(TEMPORY_DIRECTORY)/%.s, $(C_SOURCES))
C_OBJECTS := $(patsubst $(TEMPORY_DIRECTORY)/%.s, $(OBJECT_DIRECTORY)/%.o, $(C_ASSEMBLIES))

ASM_SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.asm)
ASM_OBJECTS := $(patsubst $(SOURCE_DIRECTORY)/%.asm, $(OBJECT_DIRECTORY)/%.o, $(ASM_SOURCES))

.PHONY: all
all: $(C_OBJECTS) $(ASM_OBJECTS)

.PHONY: clean
clean:
	rm -rf $(TEMPORY_DIRECTORY)/*.s
	rm -rf $(OBJECT_DIRECTORY)/*.o

# C sources to C Assembly:
$(TEMPORY_DIRECTORY)/%.s: $(SOURCE_DIRECTORY)/%.c
#	Compile C to Assembly:
	gcc $(GCC_FLAGS) -S "$<" -o "$@"
#	Remove the last line from the Assembly, which contains an unwanted section:
	sed -i '$$d' "$@"

# C Assembly to C objects:
$(OBJECT_DIRECTORY)/%.o: $(TEMPORY_DIRECTORY)/%.s
	as -o "$@" "$<"

# NASM Assembly to objects:
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.asm
	nasm $(NASM_FLAGS) -f $(NASM_FORMAT) -o "$@" "$<"
