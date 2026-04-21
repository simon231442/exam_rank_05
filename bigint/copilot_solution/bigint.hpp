#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

class bigint {
 private:
  std::string _string;

  static bool isDigitsOnly(const std::string& s);
  static std::string normalize(const std::string& s);
  static int compareAbs(const std::string& a, const std::string& b);
  static std::string addStrings(const std::string& a, const std::string& b);
  static std::string subStrings(const std::string& a, const std::string& b);
  static std::string mulStrings(const std::string& a, const std::string& b);

 public:
  bigint();
  bigint(unsigned int n);
  bigint(const std::string& str);
  bigint(const bigint& original);
  ~bigint();

  std::string getArbiter_value() const;

  bigint operator+(const bigint& other) const;
  bigint operator-(const bigint& other) const;
  bigint operator*(const bigint& other) const;
  bigint& operator=(const bigint& other);

  friend std::ostream& operator<<(std::ostream& out, const bigint& value);
};
