#include "bigint.hpp"

#include <iostream>

int main() {
  try {
    bigint a("123456789012345678901234567890");
    bigint b(987654321);

    bigint sum = a + b;
    bigint diff("1000000000000000000000");
    bigint diff2("999999999999999999999");
    bigint prod = bigint("123456789") * bigint("987654321");

    std::cout << "a      = " << a << '\n';
    std::cout << "b      = " << b << '\n';
    std::cout << "a + b  = " << sum << '\n';
    std::cout << "d1-d2  = " << (diff - diff2) << '\n';
    std::cout << "prod   = " << prod << '\n';

    bigint z("0000000");
    std::cout << "zero   = " << z << '\n';

    // This line intentionally demonstrates input validation.
    // bigint bad("12a34");
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
