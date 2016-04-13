#ifndef JEXPLODE_CHUNKER_H
#define JEXPLODE_CHUNKER_H

#include <string>
#include "common.h"

template<typename T>
struct chunk_sink {
  inline void operator()(const std::string& s) {
    static_cast<T*>(this)->on_chunk(s);
  }

  inline void operator()(std::string&& s) {
    static_cast<T*>(this)->on_chunk(std::move(s));
  }
};

template<typename T>
struct chunker {
  static constexpr size_t min_depth = 1;
  chunk_sink<T>& sink;

  chunker(chunk_sink<T>& sink_) : sink{sink_} {}

  inline void operator()(char c) {
    bool inside = depth >= min_depth;

    if (quoted) {
      if (bslash) {
        bslash = false;
        if (c == 'u') unesc = here + 5;
        else unesc = here + 1;
      } else if (unesc <= here) {
        if      (c == '"') quoted = false;
        else if (c == '\\') bslash = true;
      }
    } else {
      if      (c == '{') inside = ++depth >= min_depth;
      else if (c == '}') --depth;
      else if (c == '\n') c = ' ';
    }

    if (inside) buf.push_back(c);
    ++here;

    if (inside && (depth < min_depth)) {
      sink(buf);
      buf.clear();
    }
  }

  inline void operator()(const std::string& s) {
    for (auto c : s) operator()(c);
  }

  inline void operator()(const char* buf, size_t len) {
    for (size_t i = 0; i < len; i++) operator()(buf[i]);
  }
private:
  std::string buf;
  size_t here = 0; // index of next byte
  size_t unesc = 0; // index of next unescaped byte

  bool quoted = false;
  bool bslash = false;
  unsigned depth = 0;
};

#endif // JEXPLODE_CHUNKER_H
// vim:et:sts=4:sw=2:
