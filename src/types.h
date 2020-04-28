typedef signed char Int8;
typedef signed short Int16;
typedef signed long Int32;
typedef signed long long Int64;

typedef unsigned long long UInt64;
typedef unsigned long UInt32;
typedef unsigned short UInt16;
typedef unsigned char UInt8;

typedef float Float32;
typedef double Float64;

typedef unsigned char Bool;

#if defined(__LP64__) || defined(_LP64)

    typedef signed long long Int;
    typedef unsigned long long UInt;
    typedef double Float;

#endif
