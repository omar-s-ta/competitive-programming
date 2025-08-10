#include "../../../../library/io.hpp"

using namespace io;

class EvenUpSolitaire {
public:
  void solve() {
    int nt;
    in >> nt;
    std::stack<short> cards, other;
    for (short ci; nt-- != 0; cards.push(ci)) {
      in >> ci;
    }
    for (std::size_t size = cards.size(); true; size = cards.size()) {
      while (!cards.empty()) {
        const short a = cards.top();
        cards.pop();
        if (!cards.empty() && (a + cards.top()) % 2 == 0) {
          cards.pop();
        } else {
          other.push(a);
        }
      }
      if (other.empty() || other.size() == size) {
        break;
      } else {
        cards.swap(other);
      }
    }
    out << other.size() << '\n';
  }

  EvenUpSolitaire(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;
};