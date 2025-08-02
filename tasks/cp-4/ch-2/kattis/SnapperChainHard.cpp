#include "../../../../library/io.hpp"

using namespace io;

class SnapperChainHard {
public:
  void solveOne(const int ci, int n, int k) {
    out << "Case #" << ci << ": ";
    if (n == 1) {
      out << (k % 2 == 0 ? "OFF" : "ON") << '\n';
      return;
    }
    out << (((k % (1 << n)) == (1 << n) - 1) ? "ON" : "OFF") << '\n';
  }

  void solve() {
    int nt;
    in >> nt;
    for (int _ = 1; _ <= nt; _++) {
      int n, k;
      std_read(in, n, k);
      solveOne(_, n, k);
    }
  }

  SnapperChainHard(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};