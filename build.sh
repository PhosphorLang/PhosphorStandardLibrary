#!/bin/env bash

# Enable "strict mode":
set -euo pipefail

# Constant definitions:
readonly SOURCE_DIRECTORY="src"
readonly PLATFORM_SOURCE_DIRECTORY="$SOURCE_DIRECTORY/platform"
readonly OBJECT_DIRECTORY="obj"
readonly BINARY_DIRECTORY="bin"

# Parameters:
target="${1--h}"

# Functions:

function clean
{
    rm -rf "$OBJECT_DIRECTORY"
    rm -rf "$BINARY_DIRECTORY"

    echo "Cleaned up."
}

function targetLinuxAmd64
{
    targetSubdirectory="amd64/linux"

    prepare "$targetSubdirectory"

    sourceDirectory="$PLATFORM_SOURCE_DIRECTORY/$targetSubdirectory"

    objectFiles=()

    # Compile C files:
    for sourceFile in $sourceDirectory/*.c; do
        baseFileName=$(basename "$sourceFile" .c)
        outputFile="$OBJECT_DIRECTORY/$targetSubdirectory/$baseFileName.o"

        objectFiles+=("$outputFile")

        gcc \
            -nostdinc \
            -fno-stack-protector \
            -fdata-sections \
            -ffunction-sections \
            -fno-builtin \
            -fno-asynchronous-unwind-tables \
            -fno-ident \
            -finhibit-size-directive \
            -masm=intel \
            -O1 \
            -c "$sourceFile" -o "$outputFile"

    done

    # Compile Assembler files:
    for sourceFile in $sourceDirectory/*.asm; do
        baseFileName=$(basename "$sourceFile" .asm)
        outputFile="$OBJECT_DIRECTORY/$targetSubdirectory/$baseFileName.o"

        objectFiles+=("$outputFile")

        nasm -a -f elf64 -o "$outputFile" "$sourceFile"
    done

    targetFile="$BINARY_DIRECTORY/$targetSubdirectory/standardLibrary.a"

    # Pack the object files into the library:
    ar crs "$targetFile" ${objectFiles[@]}

    postBuild "linuxArm64"
}

function targetAvr
{
    targetSubdirectory="avr"

    prepare "$targetSubdirectory"

    sourceDirectory="$PLATFORM_SOURCE_DIRECTORY/$targetSubdirectory"

    objectFiles=()

    # Compile Assembler files:
    for sourceFile in $sourceDirectory/*.asm; do
        baseFileName=$(basename "$sourceFile" .asm)
        outputFile="$OBJECT_DIRECTORY/$targetSubdirectory/$baseFileName.o"

        objectFiles+=("$outputFile")

        avr-as \
            -mmcu=avr25 \
            --mlink-relax \
            -o "$outputFile" "$sourceFile"
    done

    targetFile="$BINARY_DIRECTORY/$targetSubdirectory/standardLibrary.a"

    # Pack the object files into the library:
    ar crs "$targetFile" ${objectFiles[@]}

    postBuild "avr"
}

function prepare
{
    targetSubdirectory="$1"

    mkdir -p "$OBJECT_DIRECTORY/$targetSubdirectory"
	mkdir -p "$BINARY_DIRECTORY/$targetSubdirectory"
}

function postBuild
{
    buildTarget=$1

    echo "Build completed for target $buildTarget."
}

# Target processing:
case $target in
    clean)
        clean
        ;;
    all)
        targetAvr
        targetLinuxAmd64
        ;;
    avr)
        targetAvr
        ;;
    linuxAmd64)
        targetLinuxAmd64
        ;;
    -h|--help|help|*)
        echo "Allowed targets: clean, all, avr, limuxAmd64"
        ;;
esac
