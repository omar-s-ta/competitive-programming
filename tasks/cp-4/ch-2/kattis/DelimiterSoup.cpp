#include <cctype>
#include <iostream>
#include <print>
#include <stack>
#include <string>

/*
 * Just a normal expression parsing
 * `push` on open tokens
 * `pop`  on matching tokens, fail if tokens are not matching
 */
class problem {
 public:
  inline bool is_open(const char ch) const { return ch == '(' || ch == '{' || ch == '['; }

  inline bool is_match(const char a, const char b) const {
    if (a == '(') return b == ')';
    if (a == '{') return b == '}';
    if (a == '[') return b == ']';
    return false;
  }

  void solve() {
    int n;
    in >> n;

    in.ignore();

    std::string program;
    std::getline(in, program);

    std::stack<char> st;
    for (int i = 0; i < n; i++) {
      const char& ch = program[i];
      if (std::isblank(ch)) {
        continue;
      }
      if (is_open(ch)) {
        st.emplace(ch);
      } else {
        if (st.empty() || !is_match(st.top(), ch)) {
          std::println(out, "{} {}", ch, i);
          return;
        }
        st.pop();
      }
    }

    std::println(out, "ok so far");
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
