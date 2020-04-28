SOURCE_DIRECTORY := src
TEMPORY_DIRECTORY := tmp
OBJECT_DIRECTORY := obj
BINARY_DIRECTORY := bin

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

AR_FLAGS := crs

C_SOURCE_FILES := $(SOURCE_DIRECTORY)/%.c
ASM_SOURCE_FILES := $(SOURCE_DIRECTORY)/%.asm
OBJECT_FILES := $(OBJECT_DIRECTORY)/%.o
ASSEMBLY_FILES := $(TEMPORY_DIRECTORY)/%.s
RESULT_FILE := $(BINARY_DIRECTORY)/standardLibrary.a

C_SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.c)
C_ASSEMBLIES := $(patsubst $(C_SOURCE_FILES), $(ASSEMBLY_FILES), $(C_SOURCES))
C_OBJECTS := $(patsubst $(ASSEMBLY_FILES), $(OBJECT_FILES), $(C_ASSEMBLIES))

ASM_SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.asm)
ASM_OBJECTS := $(patsubst $(ASM_SOURCE_FILES), $(OBJECT_FILES), $(ASM_SOURCES))

.PRECIOUS: $(OBJECT_FILES)
.PRECIOUS: $(ASSEMBLY_FILES)
.PRECIOUS: $(RESULT_FILE)

.PHONY: all
all: $(RESULT_FILE)

$(RESULT_FILE): $(C_OBJECTS) $(ASM_OBJECTS)
#	# Compile object files into static library:
	ar $(AR_FLAGS) $(RESULT_FILE) $(C_OBJECTS) $(ASM_OBJECTS)

.PHONY: clean
clean:
	rm -rf $(TEMPORY_DIRECTORY)/*.s
	rm -rf $(OBJECT_DIRECTORY)/*.o
	rm -rf $(RESULT_FILE)

# C sources to C Assembly:
$(ASSEMBLY_FILES): $(C_SOURCE_FILES)
#	# Compile C to Assembly:
	gcc $(GCC_FLAGS) -S "$<" -o "$@"
#	# Remove the last line from the Assembly, which contains an unwanted section:
	sed -i '$$d' "$@"

# C Assembly to C objects:
$(OBJECT_FILES): $(ASSEMBLY_FILES)
	as -o "$@" "$<"

# NASM Assembly to objects:
$(OBJECT_FILES): $(ASM_SOURCE_FILES)
	nasm $(NASM_FLAGS) -f $(NASM_FORMAT) -o "$@" "$<"
