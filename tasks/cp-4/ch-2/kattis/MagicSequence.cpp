#include "../../../../library/io.hpp"
#include "../../../../library/radix_sort.hpp"

using namespace io;

class MagicSequence {
public:
  void solveOne() {
    int n;
    int64_t a, b, c;
    int64_t x, y;
    std_read(in, n, a, b, c, x, y);
    std::vector<int64_t> s(n);
    s.front() = a;
    for (int i = 1; i < n; i++) {
      s[i] = (s[i - 1] * b + a) % c;
    }
    radix_sort(s);
    int64_t v = 0;
    for (int i = 0; i < n; i++) {
      v = (v * x + s[i]) % y;
    }
    out << v << '\n';
  }

  void solve() {
    int nt;
    in >> nt;
    while (nt-- != 0) {
      solveOne();
    }
  }

  MagicSequence(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};