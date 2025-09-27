#include <array>
#include <cassert>
#include <iostream>
#include <print>
#include <string>

class problem {
 public:
  inline void from_waiter(const int dishes, std::array<int, 2>& stacks) {
    stacks[P2] += dishes;
    std::println(out, "DROP 2 {}", dishes);
  }

  inline void to_dishwasher(int dishes, std::array<int, 2>& stacks) {
    if (stacks[P1] < dishes) {
      if (stacks[P1] == 0) {
        stacks[P1] += stacks[P2];
        std::println(out, "MOVE 2->1 {}", stacks[P2]);
        std::println(out, "TAKE 1 {}", dishes);
        stacks[P2] = 0;
      } else {
        std::println(out, "TAKE 1 {}", stacks[P1]);
        dishes -= stacks[P1];
        stacks[P1] = stacks[P2];
        std::println(out, "MOVE 2->1 {}", stacks[P2]);
        stacks[P2] = 0;
        std::println(out, "TAKE 1 {}", dishes);
      }
    } else {
      std::println(out, "TAKE 1 {}", dishes);
    }
    stacks[P1] -= dishes;
  }

  inline void to_better_dishwasher(int dishes, std::array<int, 2>& stacks) {
    int to_take = std::min(dishes, stacks[P1]);  // dishes 'm' always bigger than 0
    if (to_take != 0) {                          // if P1 has plates to consume
      std::println(out, "TAKE 1 {}", to_take);
      stacks[P1] -= to_take;
      dishes -= to_take;
    }
    // all plates in P1 are consumed
    // still need to send the remaining dishes to the dishwasher
    if (dishes != 0) {
      stacks[P1] += stacks[P2] - dishes;
      std::println(out, "MOVE 2->1 {}", stacks[P2]);
      stacks[P2] = 0;
      std::println(out, "TAKE 1 {}", dishes);
    }
  }

  void solve() {
    for (int n, dishes = -1; in >> n;) {
      if (n == 0) {
        break;
      }
      if (dishes != -1) {
        std::println(out);
      }

      std::array<int, 2> stacks{};
      for (std::string cmd; n != 0; n -= 1) {
        in >> cmd >> dishes;
        if (cmd.front() == 'D') {
          from_waiter(dishes, stacks);
        } else {
          to_better_dishwasher(dishes, stacks);
        }
      }
    }
  }

  problem(std::istream& in, std::ostream& out) : in(in), out(out) {}

 private:
  std::istream& in;
  std::ostream& out;

  const int P2 = 0;
  const int P1 = 1;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  problem solver(std::cin, std::cout);
  solver.solve();
  return 0;
}
