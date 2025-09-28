#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class problem {
 public:
  inline int negative_mod(const int a, const int mod) { return (a % mod + mod) % mod; }

  void solve() {
    int n, m;
    in >> n >> m;

    std::vector<int> actions;
    for (std::string action; m != 0; m--) {
      in >> action;
      if (short undo; action.front() == 'u') {
        in >> undo;
        for (; undo != 0; undo--) {
          actions.pop_back();
        }
      } else {
        actions.emplace_back(std::stoi(action));
      }
    }

    const int total = std::ranges::fold_left(actions, 0, std::plus());
    std::println(out, "{}", negative_mod(total, n));
  }

  problem(std::istream& in, std::ostream& out) : in(in), out(out) {}

 private:
  std::istream& in;
  std::ostream& out;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  problem solver(std::cin, std::cout);
  solver.solve();
  return 0;
}
