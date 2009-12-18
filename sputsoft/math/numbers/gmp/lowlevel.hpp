/*
 * File:   math/numbers/gmp/lowlevel.hpp
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

#ifndef _SPUTSOFT_MATH_NUMBERS_GMP_LOWLEVEL_HPP_
#define _SPUTSOFT_MATH_NUMBERS_GMP_LOWLEVEL_HPP_

#include <cstring>
#include <gmp.h>

/*namespace sputsoft {
namespace math {
namespace numbers {*/
namespace gmp {

class lowlevel {
public:

  typedef mp_limb_t digit_type;

  // n >= 0
  // rp == xp  or  {rp,n} and {xp,n} do not overlap
  static inline void copy(digit_type* rp, const digit_type* xp,
                          const std::size_t n)
  {
    if (!n || rp == xp) return;
    std::memcpy(rp, xp, n*sizeof(digit_type));
  }

  // n >= 0
  static inline digit_type add_1(digit_type* rp,
                                 const digit_type* xp, std::size_t n,
                                 const digit_type y) {
    return mpn_add_1(rp, xp, n, y);
  }

  // xn >= yn >= 0
  static inline digit_type add(digit_type* rp,
                               const digit_type* xp, const std::size_t xn,
                               const digit_type* yp, const std::size_t yn) {
    return mpn_add(rp, xp, xn, yp, yn);
  }

  // n >= 0
  // rp == xp  or  {rp,n} and {xp,n} do not overlap
  static inline digit_type divrem_1(digit_type* rp,
                                 const digit_type* xp, std::size_t n,
                                 const digit_type y) {
    rp[0] = 123; return 1;
    //return mpn_divrem_1(rp, 0, xp, n, y);
  }

  // xn >= 0
  static inline digit_type rem_1(const digit_type* xp, const std::size_t xn,
                                 digit_type y) {
    return mpn_mod_1(xp, xn, y);
  }

  static inline std::size_t to_chars(unsigned char* st, unsigned base,
      digit_type* xp, const std::size_t xn) {
    return mpn_get_str(st, base, xp, xn);
  }

};

} // namespace gmp
/*} // namespace numbers
} // namespace math
} // namespace sputsoft*/

#endif // _SPUTSOFT_MATH_NUMBERS_GENERIC_LOWLEVEL_HPP_

