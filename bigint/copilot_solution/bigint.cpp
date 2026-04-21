#include "bigint.hpp"

#include <algorithm>
#include <sstream>
#include <vector>

bool bigint::isDigitsOnly(const std::string& s) {
  if (s.empty()) {
    return false;
  }
  for (std::string::size_type i = 0; i < s.size(); ++i) {
    if (s[i] < '0' || s[i] > '9') {
      return false;
    }
  }
  return true;
}

std::string bigint::normalize(const std::string& s) {
  std::string::size_type i = 0;
  while (i < s.size() && s[i] == '0') {
    ++i;
  }
  if (i == s.size()) {
    return "0";
  }
  return s.substr(i);
}

int bigint::compareAbs(const std::string& a, const std::string& b) {
  if (a.size() < b.size()) {
    return -1;
  }
  if (a.size() > b.size()) {
    return 1;
  }
  if (a == b) {
    return 0;
  }
  return (a < b) ? -1 : 1;
}

std::string bigint::addStrings(const std::string& a, const std::string& b) {
  std::string result;
  int i = static_cast<int>(a.size()) - 1;
  int j = static_cast<int>(b.size()) - 1;
  int carry = 0;

  while (i >= 0 || j >= 0 || carry != 0) {
    int da = (i >= 0) ? (a[static_cast<std::string::size_type>(i)] - '0') : 0;
    int db = (j >= 0) ? (b[static_cast<std::string::size_type>(j)] - '0') : 0;
    int sum = da + db + carry;

    result.push_back(static_cast<char>('0' + (sum % 10)));
    carry = sum / 10;
    --i;
    --j;
  }

  std::reverse(result.begin(), result.end());
  return normalize(result);
}

std::string bigint::subStrings(const std::string& a, const std::string& b) {
  std::string result;
  int i = static_cast<int>(a.size()) - 1;
  int j = static_cast<int>(b.size()) - 1;
  int borrow = 0;

  while (i >= 0) {
    int da = a[static_cast<std::string::size_type>(i)] - '0' - borrow;
    int db = (j >= 0) ? (b[static_cast<std::string::size_type>(j)] - '0') : 0;

    if (da < db) {
      da += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result.push_back(static_cast<char>('0' + (da - db)));
    --i;
    --j;
  }

  std::reverse(result.begin(), result.end());
  return normalize(result);
}

std::string bigint::mulStrings(const std::string& a, const std::string& b) {
  if (a == "0" || b == "0") {
    return "0";
  }

  std::vector<int> acc(a.size() + b.size(), 0);

  for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
    for (int j = static_cast<int>(b.size()) - 1; j >= 0; --j) {
      int da = a[static_cast<std::string::size_type>(i)] - '0';
      int db = b[static_cast<std::string::size_type>(j)] - '0';

      int posLow = i + j + 1;
      int posHigh = i + j;

      int sum = da * db + acc[static_cast<std::size_t>(posLow)];
      acc[static_cast<std::size_t>(posLow)] = sum % 10;
      acc[static_cast<std::size_t>(posHigh)] += sum / 10;
    }
  }

  std::string result;
  std::size_t k = 0;
  while (k < acc.size() && acc[k] == 0) {
    ++k;
  }
  for (; k < acc.size(); ++k) {
    result.push_back(static_cast<char>('0' + acc[k]));
  }

  return normalize(result);
}

bigint::bigint() : _string("0") {}

bigint::bigint(unsigned int n) {
  std::ostringstream oss;
  oss << n;
  _string = normalize(oss.str());
}

bigint::bigint(const std::string& str) {
  if (!isDigitsOnly(str)) {
    throw std::invalid_argument("bigint: invalid numeric string");
  }
  _string = normalize(str);
}

bigint::bigint(const bigint& original) : _string(original._string) {}

bigint::~bigint() {}

std::string bigint::getArbiter_value() const { return _string; }

bigint bigint::operator+(const bigint& other) const {
  return bigint(addStrings(_string, other._string));
}

bigint bigint::operator-(const bigint& other) const {
  if (compareAbs(_string, other._string) < 0) {
    throw std::underflow_error("bigint: negative result is not supported");
  }
  return bigint(subStrings(_string, other._string));
}

bigint bigint::operator*(const bigint& other) const {
  return bigint(mulStrings(_string, other._string));
}

bigint& bigint::operator=(const bigint& other) {
  if (this != &other) {
    _string = other._string;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& out, const bigint& value) {
  out << value._string;
  return out;
}
