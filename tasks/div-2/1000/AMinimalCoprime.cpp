#include "../../../library/io.hpp"

using namespace io;

class AMinimalCoprime {
public:
  void solveOne() {
    int a, b;
    std_read(in, a, b);
    if (a == 1 && b == 1) {
      out << 1 << '\n';
    } else {
      out << b - a << '\n';
    }
  }

  void solve() {
    int nt;
    in >> nt;
    for (int _ = 1; _ <= nt; _++) {
      solveOne();
    }
  }

  AMinimalCoprime(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};