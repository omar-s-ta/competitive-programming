#include "../../../library/io.hpp"

using namespace io;

class BSubsequenceUpdate {
public:
  void solveOne() {
    int n, l, r;
    std_read(in, n, l, r);
    std::vector<int64_t> a(n);
    in >> a;

    l -= 1;
    r -= 1;

    std::sort(a.begin(), a.begin() + l);
    std::sort(a.begin() + l, a.begin() + r + 1);
    std::sort(a.begin() + r + 1, a.end());

    int64_t r1 = 0;
    for (int i = l; i <= r; i++) {
      if (r * 2 + 1 - i >= n) {
        r1 += a[i];
      } else {
        r1 += std::min(a[i], a[r * 2 + 1 - i]);
      }
    }

    std::reverse(a.begin(), a.begin() + l);
    std::reverse(a.begin() + l, a.begin() + r + 1);

    int64_t r2 = 0;
    for (int i = l; i <= r; i++) {
      if (l * 2 - i - 1 < 0) {
        r2 += a[i];
      } else {
        r2 += std::min(a[i], a[l * 2 - i - 1]);
      }
    }

    out << std::min(r1, r2) << '\n';
  }

  void solve() {
    int nt;
    in >> nt;
    for (int _ = 1; _ <= nt; _++) {
      solveOne();
    }
  }

  BSubsequenceUpdate(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};