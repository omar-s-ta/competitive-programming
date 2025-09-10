#include <cstddef>
#include <iostream>
#include <string>

class problem {
 public:
  void solve() {
    short n;
    in >> n;
    size_t st_size = 0;
    std::string st[N];
    for (short i = 0; i < n; i++) {
      std::string cmd;
      in >> cmd;
      const char& ch = cmd.front();
      if (ch == 'S') {
        in >> cmd;
        st[st_size] = cmd;
        st_size += 1;
      } else if (ch == 'K') {
        if (st_size == 0) {
          continue;
        }
        st_size -= 1;
      } else {
        out << (st_size == 0 ? "Not in a dream" : st[st_size - 1]) << '\n';
      }
    }
  }

  problem(std::istream& in, std::ostream& out) : in(in), out(out) {}

 private:
  std::istream& in;
  std::ostream& out;

  const size_t N = 10001;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  problem solver(std::cin, std::cout);
  solver.solve();
  return 0;
}
