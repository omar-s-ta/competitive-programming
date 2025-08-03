#include "../../../../library/io.hpp"

using namespace io;

/**
 * Basic addition simulation.
 * The only optimization done is stopping whenever there is no more carry when
 * the two given numbers do not have equal number of digits.
 */
class PrimaryArithmetic {
public:
  void solveOne(int64_t a, int64_t b) {
    if (a < b) {
      std::swap(a, b);
    }
    int result = 0, carry = 0;
    for (; a != 0 && b != 0; a /= 10, b /= 10) {
      const int al = a % 10;
      const int bl = b % 10;
      const int s = carry + al + bl;
      result += (int) (s >= 10);
      carry = s / 10;
    }
    for (; a != 0 && carry > 0; a /= 10) {
      const int s = carry + (a % 10);
      result += (int) (s >= 10);
      carry = s / 10;
    }
    if (!result) out << "No carry operation.";
    else if (result == 1) out << result << " carry operation.";
    else out << result << " carry operations.";
    out << '\n';
  }

  void solve() {
    for (int64_t a, b; in >> a >> b && (a || b); solveOne(a, b));
  }

  PrimaryArithmetic(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};