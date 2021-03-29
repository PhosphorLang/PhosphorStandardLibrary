SOURCE_DIRECTORY := src
OBJECT_DIRECTORY := obj
BINARY_DIRECTORY := bin

GCC_FLAGS := -nostdinc \
			 -fno-stack-protector \
			 -fdata-sections \
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
RESULT_FILE := $(BINARY_DIRECTORY)/standardLibrary.a

C_SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.c)
C_OBJECTS := $(patsubst $(C_SOURCE_FILES), $(OBJECT_FILES), $(C_SOURCES))

ASM_SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.asm)
ASM_OBJECTS := $(patsubst $(ASM_SOURCE_FILES), $(OBJECT_FILES), $(ASM_SOURCES))

.PRECIOUS: $(OBJECT_FILES)
.PRECIOUS: $(RESULT_FILE)

.PHONY: all
all: prepare $(RESULT_FILE)
	@echo "Make completed."

$(RESULT_FILE): $(C_OBJECTS) $(ASM_OBJECTS)
#	# Compile object files into static library:
	ar $(AR_FLAGS) $(RESULT_FILE) $(C_OBJECTS) $(ASM_OBJECTS)

.PHONY: prepare
prepare:
	mkdir -p "$(OBJECT_DIRECTORY)"
	mkdir -p "$(BINARY_DIRECTORY)"

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIRECTORY)/*.o
	rm -rf $(RESULT_FILE)

# C sources to C objects:
$(OBJECT_FILES): $(C_SOURCE_FILES)
#	# Compile C to objects:
	gcc $(GCC_FLAGS) -c "$<" -o "$@"

# NASM Assembly to objects:
$(OBJECT_FILES): $(ASM_SOURCE_FILES)
	nasm $(NASM_FLAGS) -f $(NASM_FORMAT) -o "$@" "$<"
