[![Build](https://github.com/PhosphorLang/PhosphorStandardLibrary/workflows/Build/badge.svg)](https://github.com/PhosphorLang/PhosphorStandardLibrary/actions)

# **The Phosphor Standard Library**

The standard library for the Phosphor programming language.

## **External Dependencies**

You need the following present on your system to compile the standard library:

- [NASM](https://nasm.us/) >= 2.13
- [gcc](https://gcc.gnu.org/) >= 8.3
- [GNU ar](https://www.gnu.org/software/binutils/) >= 2.30

## **Compilation**

To compile the standard library you only need to run the build script with the target as parameter:

```bash
./build.sh <target>
```

For example Linux on Amd64:

```bash
./build.sh linuxAmd64
```

You can get an overview over all possible targets with help:

```bash
./build.sh --help
```

After that, the standard library file `standardLibrary.a` can be found in the `bin` folder.
