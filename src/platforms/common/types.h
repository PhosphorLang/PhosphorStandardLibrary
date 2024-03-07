#pragma once

/** 1 Byte signed integer */
typedef signed char Integer8;
/** 2 Byte signed integer */
typedef signed short Integer16;
/** 4 Byte signed integer */
typedef signed long Integer32;
/** 8 Byte signed integer */
typedef signed long long Integer64;

/** 1 Byte unsigned integer */
typedef unsigned char Cardinal8;
/** 2 Byte unsigned integer */
typedef unsigned short Cardinal16;
/** 4 Byte unsigned integer */
typedef unsigned long Cardinal32;
/** 8 Byte unsigned integer */
typedef unsigned long long Cardinal64;

/** 4 Byte floating point number */
typedef float Float32;
/** 8 Byte floating point number */
typedef double Float64;

/** 1 Byte Boolean */
typedef enum {
    false = (Integer8)0,
    true = (Integer8)-1,
} __attribute__((__packed__)) Boolean;

#define null 0

#if defined(__x86_64__) || defined(__x86_64) || defined(__LP64__) || defined(_LP64)

    /** Architecture (word size) dependent signed integer */
    typedef Integer64 Integer;
    /** Architecture (word size) dependent unsigned integer */
    typedef Cardinal64 Cardinal;
    /** Architecture (word size) dependent floating point number */
    typedef Float64 Float;

#elif defined(__AVR)

    /** Architecture (word size) dependent signed integer */
    typedef Integer64 Integer;
    /** Architecture (word size) dependent unsigned integer */
    typedef Cardinal64 Cardinal;
    /** Architecture (word size) dependent floating point number */
    typedef Float32 Float;

#else

    #error "Architecture is not supported."

#endif
