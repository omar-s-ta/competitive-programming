#include <bitset>
#include <cctype>
#include <iostream>
#include <stack>

/*
 * Problem:
 *   https://open.kattis.com/problems/circuitmath
 *
 * Use 'stack' to evaluate postfix operators.
 */
class problem {
 public:
  void solve() {
    int n;
    in >> n;
    std::bitset<26> gates;
    gates.reset();

    for (int i = 0; i < n; i++) {
      char ch;
      in >> ch;
      gates[i] = ch == 'T';
    }

    std::stack<bool> expr;
    for (char ch; in >> ch;) {
      if (std::isalpha(ch)) {
        expr.emplace(gates[ch - 'A']);
      } else {
        const bool a = expr.top();
        if (ch == '*') {
          expr.pop();
          expr.top() &= a;
        } else if (ch == '+') {
          expr.pop();
          expr.top() |= a;
        } else if (ch == '-') {
          expr.top() = !expr.top();
        }
      }
    }

    out << (expr.top() ? 'T' : 'F') << '\n';
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
