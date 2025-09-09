#include <iostream>
#include <vector>
#include <string>

class problem {
public:
  void solve() {
    std::string coming;
    for (int ci = 1; in >> coming && coming != "end"; ci++) {
      std::vector<short> stk(N, -1);
      short stacks = 0;
      stk[coming.front() - 'A'] = stacks;
      stacks += 1;

      const short containers = coming.length();
      for (short i = 1; i < containers; i++) {
        const short container = coming[i] - 'A';
        if (stk[container] != -1) {
          continue;
        }
        bool found = false;
        for (short c = container + 1; c < N && !found; c++) {
          if (stk[c] != -1) {
            stk[container] = stk[c];
            stk[c] = -1;
            found = true;
          }
        }
        if (!found) {
          stk[container] = stacks;
          stacks += 1;
        }
      }

      out << "Case " << ci << ": " << stacks << '\n';
    }
  }

  problem(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;

  const size_t N = 26;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  problem solver(std::cin, std::cout);
  solver.solve();
  return 0;
}
