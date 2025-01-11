#include "../../../../library/io.hpp"

using namespace io;

/**
 * Start small and notice the pattern:
 *
 *  n = 1:
 *    0 -> (0)
 *    1 -> (1)
 *
 *  n = 2:
 *    00 -> 0 (0) -> (00)
 *    01 -> 0 (1) -> (10)
 *    10 -> 0 (1) -> (10)
 *    11 -> 1 (1) -> (11)
 *
 *  n = 3:
 *    000 -> 00 (0) -> 0 (00) -0 (000)
 *    001 -> 01 (0) -> 0 (01) -> (010)
 *    010 -> 00 (1) -> 0 (10) -> (100)
 *    100 -> 10 (0) -> 0 (01) -> (010)
 *    011 -> 01 (1) -> 0 (11) -> (110)
 *    101 -> 11 (0) -> 1 (01) -> (011)
 *    110 -> 10 (1) -> 0 (11) -> (110)
 *    111 -> 11 (1) -> 1 (11) -> (111)
 *
 */

class AlgorithmOfPhil {
public:
  inline void mod(int &a, const int b) {
    if (a >= b) {
      a -= b;
    }
  }

  int solveOne(const std::string &a) {
    const int n = a.size();
    int result = 0;
    int R = n / 2;
    int L = R - 1;
    if (n % 2 != 0) {
      result += (a[R] - '0');
      R += 1;
    }
    for (; L >= 0; L--, R++) {
      result <<= 1;
      mod(result, MOD);
      result <<= 1;
      mod(result, MOD);
      const int s = (a[L] - '0') + (a[R] - '0');
      if (s == 0) {
        continue;
      }
      result += (s + 1);
      mod(result, MOD);
    }
    return result;
  }

  void solve() {
    int nt;
    in >> nt;
    for (int _ = 1; _ <= nt; _++) {
      std::string a;
      in >> a;
      out << "Case #" << _ << ": " << solveOne(a) << '\n';
    }
  }

  AlgorithmOfPhil(std::istream &in, std::ostream &out) : in(in), out(out) {}

private:
  std::istream &in;
  std::ostream &out;

  const int MOD = (1e9) + 7;
};
