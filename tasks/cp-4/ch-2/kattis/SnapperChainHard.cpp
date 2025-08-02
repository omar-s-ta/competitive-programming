#include "../../../../library/io.hpp"

using namespace io;

/**
 * Simulate the snapping process:
 * n = 4
 * initial: 0000
 * snap 1 : 1000
 * snap 2 : 0100
 * snap 3 : 1100
 * snap 4 : 0010
 * snap 5 : 1010
 * snap 6 : 0110
 * snap 7 : 1110
 * snap 8 : 0001
 * ...
 *
 * Eventually you can see that it will be 'ON' only when all snappers are on which
 * will have this shape for every number n -> (2^n)-1 = (1<<n)-1
 *
 * So if after K snaps it reaches the above shape it should be 'ON', otherwise 'OFF'.
 */
class SnapperChainHard {
public:
  void solveOne(const int ci, int n, int k) {
    out << "Case #" << ci << ": ";
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