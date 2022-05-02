#!/bin/env bash

# Enable "strict mode":
set -euo pipefail

# Constant definitions:
readonly SOURCE_DIRECTORY="src"
readonly OBJECT_DIRECTORY="obj"
readonly BINARY_DIRECTORY="bin"
readonly PLATFORM_SOURCE_DIRECTORY="$SOURCE_DIRECTORY/platforms"

# Functions:

function clean
{
    rm -rf "$OBJECT_DIRECTORY"
    rm -rf "$BINARY_DIRECTORY"

    echo "Cleaned up."
}

function targetAmd64
{
    local targetName="amd64"
    local targetSubdirectory="amd64"

    prepare "$targetName" "$targetSubdirectory"

    local objectFiles=()

    local commandGcc=(
        'gcc'
        '-nostdinc'
        '-fno-stack-protector'
        '-fdata-sections'
        '-ffunction-sections'
        '-fno-builtin'
        '-fno-asynchronous-unwind-tables'
        '-fno-ident'
        '-finhibit-size-directive'
        '-masm=intel'
        '-O1'
        '-c'
        '-o'
    )

    # Common files
    compileSubdirectory "common" "c" objectFiles "${commandGcc[@]}"
    # Amd64 files
    compileSubdirectory "$targetSubdirectory" "c" objectFiles "${commandGcc[@]}"

    local commandNasm=(
        'nasm'
        '-a'
        '-f elf64'
        '-o'
    )

    # Common files
    compileSubdirectory "common" "asm" objectFiles "${commandNasm[@]}"
    # Amd64 files
    compileSubdirectory "$targetSubdirectory" "asm" objectFiles "${commandNasm[@]}"

    packLibrary "$targetName" "${objectFiles[@]}"
    copyHeaders "$targetName"
}

function targetLinuxAmd64
{
    local targetName="linuxAmd64"
    local targetSubdirectory="amd64/linux"

    prepare "$targetName" "$targetSubdirectory"

    local objectFiles=()

    local commandGcc=(
        'gcc'
        '-nostdinc'
        '-fno-stack-protector'
        '-fdata-sections'
        '-ffunction-sections'
        '-fno-builtin'
        '-fno-asynchronous-unwind-tables'
        '-fno-ident'
        '-finhibit-size-directive'
        '-masm=intel'
        '-O1'
        '-c'
        '-o'
    )

    # Common files
    compileSubdirectory "common" "c" objectFiles "${commandGcc[@]}"
    # Amd64 files
    compileSubdirectory "amd64" "c" objectFiles "${commandGcc[@]}"
    # Linux Amd64 files
    compileSubdirectory "$targetSubdirectory" "c" objectFiles "${commandGcc[@]}"

    local commandNasm=(
        'nasm'
        '-a'
        '-f elf64'
        '-o'
    )

    # Common files
    compileSubdirectory "common" "asm" objectFiles "${commandNasm[@]}"
    # Amd64 files
    compileSubdirectory "amd64" "asm" objectFiles "${commandNasm[@]}"
    # Linux Amd64 files
    compileSubdirectory "$targetSubdirectory" "asm" objectFiles "${commandNasm[@]}"

    packLibrary "$targetName" "${objectFiles[@]}"
    copyHeaders "$targetName"
}

function targetAvr
{
    local targetName="avr"
    local targetSubdirectory="avr"

    prepare "$targetName" "$targetSubdirectory"

    local objectFiles=()

    local command=(
        'avr-as'
        '-mmcu=avr25'
        '--mlink-relax'
        '-o'
    )

    # Common files
    compileSubdirectory "common" "asm" objectFiles "${command[@]}"
    # Avr files
    compileSubdirectory "$targetSubdirectory" "asm" objectFiles "${command[@]}"

    packLibrary "$targetName" "${objectFiles[@]}"
    copyHeaders "$targetName"
}

# Compile the contents of a subdirectory with the given compile command.
function compileSubdirectory
{
    local targetSubdirectory=$1
    local fileExtension=$2
    local -n outputFiles=$3
    shift 3
    local command=("${@}")

    local sourceDirectory="$PLATFORM_SOURCE_DIRECTORY/$targetSubdirectory"

    for sourceFile in $sourceDirectory/*.$fileExtension ; do
        # Check if this is really a file and otherwise skip the loop:
        if ! [ -f $sourceFile ]; then
            continue
        fi

        local baseFileName=$(basename "$sourceFile" .$fileExtension)
        local outputFile="$OBJECT_DIRECTORY/$targetSubdirectory/$baseFileName.o"

        outputFiles+=("$outputFile")

        "${command[@]}" "$outputFile" "$sourceFile"
    done
}

# Pack the given object files into a linkable library.
function packLibrary
{
    local targetName=$1
    shift 1
    local objectFiles=("${@}")

    local targetFile="$BINARY_DIRECTORY/$targetName/standardLibrary.a"

    ar crs "$targetFile" ${objectFiles[@]}
}

function prepare
{
    local targetName="$1"
    local targetSubdirectory="$2"

    mkdir -p "$OBJECT_DIRECTORY/common"
    mkdir -p "$OBJECT_DIRECTORY/$targetSubdirectory"
	mkdir -p "$BINARY_DIRECTORY/$targetName/headers"

    # TODO: Should we clean a target before compiling it again to prevent old files not being deleted?
}

function copyHeaders
{
    local targetName="$1"

    local sourceDirectory="$SOURCE_DIRECTORY/headers/$targetName/."

    # We must check if the directory exists because not all targets have header files:
    if [ -d "$sourceDirectory" ]; then
        # Copy the CONTENTS of the header directory (hence the trailing "/") to the target subdirectory in the bin folder:
        cp -R "$SOURCE_DIRECTORY/headers/$targetName/." "$BINARY_DIRECTORY/$targetName/headers"
    fi
}

function build
{
    local buildTarget=$1

    case $buildTarget in
        all)
            targetAvr
            targetAmd64
            targetLinuxAmd64
            ;;
        avr)
            targetAvr
            ;;
        amd64)
            targetAmd64
            ;;
        linuxAmd64)
            targetLinuxAmd64
            ;;
        stable)
            targetAmd64
            targetLinuxAmd64
            ;;
    esac

    echo "Build completed for target $buildTarget."
}

# Parameters (when no given, default to "stable"):
target="${1-stable}"

# Target processing:
case $target in
    clean)
        clean
        ;;
    all|avr|amd64|linuxAmd64|stable)
        build $target
        ;;
    -h|--help|help|*)
        echo "Allowed targets: clean, all, avr, amd64, limuxAmd64, stable"
        ;;
esac
