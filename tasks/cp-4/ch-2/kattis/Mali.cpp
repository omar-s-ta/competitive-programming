#include "../../../../library/io.hpp"

using namespace io;

class Mali {
public:
  void solve() {
    int n;
    in >> n;
    std::vector<int> fa(M), fb(M);
    for (int i = 0; i < n; i++) {
      int a, b;
      std_read(in, a, b);
      fa[a] += 1;
      fb[b] += 1;
      out << f(fa, fb) << '\n';
    }
  }

  int f(std::vector<int> fa, std::vector<int> fb) {
    int result = 0;
    int ai = 0, bi = 100;
    while (true) {
      while (fa[ai] == 0 && ai < M) {
        ai += 1;
      }
      while (fb[bi] == 0 && bi > 0) {
        bi -= 1;
      }
      if (ai >= M || bi <= 0) {
        break;
      }
      result = std::max(result, ai + bi);
      const int cnt = std::min(fa[ai], fb[bi]);
      fa[ai] -= cnt;
      fb[bi] -= cnt;
    }
    return result;
  }

  Mali(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;

  const int M = 101;
};