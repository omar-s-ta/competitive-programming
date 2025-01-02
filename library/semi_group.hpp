#ifndef SEMI_GROUP
#define SEMI_GROUP

/**
 * The `smoosh` (append) operation must satisfy the `associativity` rule.
 *   - smoosh(a, smoosh(b, c)) == smoosh(smoosh(a, b), c)
 */

template<typename T>
struct semi_group {
  virtual ~semi_group() = default;

  template<typename A, typename B>
  T smoosh(A&& a, B&& b) const {
    return smoosh_impl(std::forward<A>(a), std::forward<B>(b));
  }

 [[nodiscard]] virtual T smoosh_impl(const T& a, const T& b) const = 0;
};

struct string_smoosh : public semi_group<std::string> {
  [[nodiscard]] std::string smoosh_impl(const std::string& a, const std::string& b) const override { return a + b; }
};

struct multiply_smoosh : public semi_group<int> {
  [[nodiscard]] int smoosh_impl(const int& a, const int& b) const override { return a * b; }
};

#endif
