#include "bignum.h"

BigInt::BigInt(const int n) {
  int input = n;
  for (int i = 0; i < len - 1; i++) {
    int digit = (input % 10);
    value[i] = digit;
    input /= 10;
  }
}
