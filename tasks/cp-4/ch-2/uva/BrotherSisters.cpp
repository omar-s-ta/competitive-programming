#include "../../../../library/io.hpp"

using namespace io;

/**
 * Since the `a` is max 230, pre-compute the ANDS before each set of queries to
 * get the answer of each query in O(1)
 */
class BrotherSisters {
public:
  void solve() {
    int nt;
    in >> nt;
    for (int n, q; nt-- != 0; ) {
      in >> n >> q;
      std::vector<int> xs(n);
      in >> xs;
      std::vector<int> ands(ANDS, 0);
      for (int i = 0; i < ANDS; i++) {
        for (const int& x : xs) {
          ands[i] = std::max(ands[i], i & x);
        }
      }
      for (int x; q-- != 0; ) {
        in >> x;
        out << ands[x] << '\n';
      }
    }
  }

  BrotherSisters(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;

  const int ANDS = 230;
};