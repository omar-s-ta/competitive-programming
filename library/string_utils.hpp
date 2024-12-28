#ifndef STRING_UTILS
#define STRING_UTILS

std::vector<std::string> substrings_slow(const std::string& str) {
  const std::size_t n = str.length();
  std::vector<std::string> subs;
  for (std::size_t i = 0; i < n; i++) {
    for (std::size_t j = 1; j <= n - i; j++) {
      subs.emplace_back(str.substr(i, j));
    }
  }
  return subs;
}

std::vector<std::string> split_at_space(const std::string& line) {
  std::stringstream sin(line);
  std::vector<std::string> parts;
  for (std::string part; sin >> part; parts.emplace_back(part));
  return parts;
}

template<typename Fun>
void foreach_token_split_at_space(const std::string& line, Fun&& f) {
  std::stringstream sin(line);
  for (std::string token; sin >> token; f(token));
}

template<typename Fun>
void foreach_token_split_at_space_with_index(const std::string& line, Fun&& f) {
  std::stringstream sin(line);
  int pos = 0;
  for (std::string token; sin >> token; f(pos++, token));
}

#endif
