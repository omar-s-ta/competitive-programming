#include "../../../../library/io.hpp"

using namespace io;

/**
 * No need to use bit-manipulation you need extra space to mark `unspecified` values anyway.
 */

class BitByBit {
public:
  inline int at(const int i) const {
    return BITS - i - 1;
  }

  inline void do_and(int i, int j, std::vector<int>& a) {
    i = at(i), j = at(j);
    a[i] = a[i] == 1 && a[j] == 1 ? 1 : a[i] == 0 || a[j] == 0 ? 0 : -1;
  }

  inline void do_or(int i, int j, std::vector<int>& a) {
    i = at(i), j = at(j);
    a[i] = a[i] == 1 || a[j] == 1 ? 1 : a[i] == 0 && a[j] == 0 ? 0 : -1;
  }

  void solve() {
    for (int q; in >> q && q != 0; ) {
      std::vector<int> bits(BITS, -1);
      while (q-- != 0) {
        std::string cmd;
        int where;
        std_read(in, cmd, where);
        switch (cmd.front()) {
          case 'S':
            bits[at(where)] = 1;
            break;
          case 'C':
            bits[at(where)] = 0;
            break;
          case 'A':
            int and_op;
            in >> and_op;
            do_and(where, and_op, bits);
            break;
          case 'O':
            int or_op;
            in >> or_op;
            do_or(where, or_op, bits);
            break;
          default:
            break;
        }
      }
      for (const int bit : bits) {
        if (bit == -1) out << '?'; else out << bit;
      }
      out << '\n';
    }
  }

  BitByBit(std::istream& in, std::ostream& out)
    : in(in), out(out) { }

private:
  std::istream& in;
  std::ostream& out;

  const int BITS = 32;
};