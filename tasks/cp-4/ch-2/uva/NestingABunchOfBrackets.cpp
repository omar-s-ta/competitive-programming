#include <iostream>
#include <stack>
#include <string>

class problem {
 public:
  inline bool open(const int at, const std::string& expr) {
    return expr[at] == '(' || expr[at] == '[' || expr[at] == '{' || expr[at] == '<';
  }

  inline bool open_asterisk(const int at, const std::string& expr) {
    return expr[at] == '(' && at + 1 < expr.length() && expr[at + 1] == '*';
  }

  inline bool closed(const int at, const std::string& expr) {
    return expr[at] == ')' || expr[at] == ']' || expr[at] == '}' || expr[at] == '>';
  }

  inline bool closed_asterisk(const int at, const std::string& expr) {
    return expr[at] == '*' && at + 1 < expr.length() && expr[at + 1] == ')';
  }

  inline bool match(const char a, const char b) {
    if (a == '(') return b == ')';
    if (a == '[') return b == ']';
    if (a == '{') return b == '}';
    if (a == '<') return b == '>';
    if (a == '*') return b == '*';
    return false;
  }

  inline const std::string no(const short count) { return "NO " + std::to_string(count); }

  std::string solve(std::string& expr) {
    std::stack<char> st;
    short count = 1;
    for (short i = 0; i < short(expr.length()); i++, count++) {
      if (open(i, expr)) {
        i += int(open_asterisk(i, expr));
        st.emplace(expr[i]);
      } else if (closed_asterisk(i, expr)) {
        if (!st.empty() && match(st.top(), expr[i])) {
          st.pop();
        } else {
          return no(count);
        }
        i += 1;
      } else if (closed(i, expr)) {
        if (!st.empty() && match(st.top(), expr[i])) {
          st.pop();
        } else {
          return no(count);
        }
      }
    }
    return st.empty() ? yes : no(count);
  }

  void solve() {
    for (std::string expr; std::getline(in, expr);) {
      out << solve(expr) << '\n';
    }
  }

  problem(std::istream& in, std::ostream& out) : in(in), out(out) {}

 private:
  std::istream& in;
  std::ostream& out;

  const std::string yes = "YES";
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  problem solver(std::cin, std::cout);
  solver.solve();
  return 0;
}
