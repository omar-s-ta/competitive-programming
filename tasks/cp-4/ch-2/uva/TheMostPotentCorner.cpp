#include "../../../../library/io.hpp"

using namespace io;

/**
 * Two vertices (corners) of an N-dimensional unit cube are neighbours if they differ by exactly `one coordinate`
 *   - (0, 0, 0) and (0, 1, 0) are neighbours.
 *   - (0, 0, 0) and (0, 1, 1) are not neighbours.
 *
 * So for each vertex, we can go-over (iterate) over it's coordinates and flip coordinate `i` to get the
 * neighbour coordinate.
 *   - for v = (b1, b2, ..., bn), the neighbours are:
 *     {(b1, b2, ..., !bi, ..., bn}) for i=0 to n-1
 *     where !bi is a flipped bit
 */
class TheMostPotentCorner {
public:
  void solve() {
    for (int n; in >> n; ) {
      std::vector<int> weight(1 << n);
      in >> weight;
      std::vector<int> potency(1 << n, 0);
      for (int corner = 0; corner < 1 << n; corner++) {
        for (int i = 0; i < n; i++) {
          potency[corner] += weight[corner ^ (1 << i)];
        }
      }
      int result = 0;
      for (int corner = 0; corner < 1 << n; corner++) {
        for (int i = 0; i < n; i++) {
          result = std::max(result, potency[corner] + potency[corner ^ (1 << i)]);
        }
      }
      out << result << '\n';
    }
  }

  TheMostPotentCorner(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};