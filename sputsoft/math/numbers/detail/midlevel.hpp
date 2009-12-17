/*
 * File:   math/numbers/detail/midlevel.hpp
 * Author: Jan Marthedal Rasmussen
 *
 * Created 2009-12-15 12:00Z
 *
 * (C) Copyright SputSoft 2009
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 */

#ifndef _SPUTSOFT_MATH_NUMBERS_DETAIL_MIDLEVEL_HPP_
#define _SPUTSOFT_MATH_NUMBERS_DETAIL_MIDLEVEL_HPP_

#include <boost/integer_traits.hpp>

template <typename T>
std::size_t log2_floor(T n) {
  std::size_t r = -1;
  while (n) {
    ++r;
    n >>= 1;
  }
  return r;
}


/*namespace sputsoft {
namespace math {
namespace numbers {*/
namespace detail {

template <typename Con, typename LowLevel>
class midlevel {

  typedef typename Con::digit_type digit_type;
  static const unsigned digit_bits = boost::integer_traits<digit_type>::digits;

  static void add3(Con& r, const Con& x, const Con& y) {
    std::size_t xs = x.size();
    digit_type carry = LowLevel::add(r.get(), x.get(), xs, y.get(), y.size());
    if (carry) r[xs++] = carry;
    r.set_size(xs);
  }

  // x.size() >= y.size() >= 1
  static void add2(Con& r, const Con& x, const Con& y) {
    std::size_t xs = x.size();
    if (!r.will_fit(xs + 1)) {
      Con t(xs + 1);
      add3(t, x, y);
      r.swap(t);
    } else 
      add3(r, x, y);
  }

  static void add3(Con& r, const Con& x, unsigned long y) {
    std::size_t xs = x.size();
    digit_type carry = LowLevel::add_1(r.get(), x.get(), xs, y);
    if (carry) r[xs++] = carry;
    r.set_size(xs);
  }

  // x.size() >= 1, y != 0
  static void add2(Con& r, const Con& x, unsigned long y) {
    std::size_t xs = x.size();
    if (!r.will_fit(xs + 1)) {
      Con t(xs + 1);
      add3(t, x, y);
      r.swap(t);
    } else 
      add3(r, x, y);    
  }

public:
  
  typedef Con container_type;

  static void set(Con& r, digit_type x) {
    if (x) {
      if (!r.will_fit(1)) Con(1).swap(r);
      r[0] = x;
      r.set_size(1);
    } else
      r.set_size(0);
  }

  static void set(Con& r, const Con& x) {
    LowLevel::copy(r.get(), x.get(), x.size());
    r.set_size(x.size());
  }

  static void add(Con& r, const Con& x, const Con& y) {
    if (y.is_empty())             set(r, x);
    else if (x.is_empty())        set(r, y);
    else if (x.size() > y.size()) add2(r, x, y);
    else                          add2(r, y, x);
  }

  static void add(Con& r, const Con& x, digit_type y) {
    if (x.is_empty()) set(r, y);
    else if (!y)      set(r, x);
    else              add2(r, x, y);
  }

  static inline digit_type remainder(const Con& u, digit_type v) {
    return LowLevel::rem_1(u.get(), u.size(), v);
  }

  static inline std::string to_string(const Con& x, unsigned base) {
    Con tmp(x);
    unsigned max_digits = tmp.size() * digit_bits / log2_floor(base) + 1;
    unsigned char st[max_digits];
    std::size_t used = LowLevel::to_chars(st, base, tmp.get(), tmp.size());
    for (unsigned i=0; i < used; ++i) st[i] += '0';
    st[used] = 0;
    return std::string((const char*)st, used);
  }

};

} // namespace detail
/*} // namespace numbers
} // namespace math
} // namespace sputsoft*/

#endif // _SPUTSOFT_MATH_NUMBERS_DETAIL_MIDLEVEL_HPP_

