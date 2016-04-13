#include <iostream>
#include "chunker.h"
#include "common.h"

using namespace std;

struct printer : chunk_sink<printer> {
  inline void on_chunk(const std::string& s) {
    cout << s << '\n';
  }
};

int main() {
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);

  printer prntr;
  chunker<printer> chnkr {prntr};

  constexpr size_t buf_size = 1 << 16;
  char buf[buf_size];
  do {
    cin.read(buf, buf_size);
    chnkr(buf, cin.gcount());
  } while (!cin.eof());
}

// vim:et:sts=4:sw=2:
