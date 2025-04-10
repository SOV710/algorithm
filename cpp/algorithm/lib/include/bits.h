// lib/include/bits.h

#ifndef BITS_H
#define BITS_H

#include <concepts>

template <typename T>
concept Integer = std::integral<T>;

template <Integer T>
T bitAbs(T x) {
    return (x ^ (x >> 31)) - (x >> 31);
}

template <Integer T>
T bitSameSign(T a, T b) {
    return ((a ^ b) >= 0);
}

template <Integer T>
T bitMax(T a, T b) {
    return (b & ((a - b) >> 31)) | (a & (~(a - b) >> 31));
}

template <Integer T>
T bitMin(T a, T b) {
    return (a & ((a - b) >> 31)) | (b & (~(a - b) >> 31));
}

template <Integer T>
void bitSwap(T &a, T &b) {
    a ^= b ^= a ^= b;
}

template <Integer T>
T getBit(T a, T b) {
    return (a >> b) & 1;
}

template <Integer T>
T unsetBit(T a, T b) {
    return a & ~(1 << b);
}

template <Integer T>
T setBit(T a, T b) {
    return a | (1 << b);
}

template <Integer T>
T flapBit(T a, T b) {
    return a ^ (1 << b);
}

template <Integer T>
T popcount(T a) {
    int cnt = 0;
    while (a) {
        cnt += a & 1;
        a >>= 1;
    }
    return cnt;
}


#endif
