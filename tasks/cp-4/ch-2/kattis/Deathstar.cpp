#include "../../../../library/io.hpp"
#include "../../../../library/matrix.hpp"

using namespace io;

/*
 * Since the input is only 1000, it can be done in O(n^2)
 *   `ai & aj = c` <- `c` will have the common on-bits between ai & aj, so we are sure that the element
 *   in `ai` and `aj` will definitely have these bits on.
 *   then all you need to do is to `or` the element in `ai` and `aj` with `c` to set these bits on.
 */

class Deathstar {
public:
  void solve() {
    int n;
    in >> n;
    matrix<int> ands(n);
    in >> ands;
    std::vector<int> results(n, 0);
    ands.for_each_with_indices([&results](const int i, const int j, const int value) -> void {
      if (i == j) return;
      results[i] |= value;
      results[j] |= value;
    });
    out << results << '\n';
  }

  Deathstar(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};