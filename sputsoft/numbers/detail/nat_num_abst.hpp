/* 
 * File:   sputsoft/numbers/detail/nat_num_abst.hpp
 * Author: Jan Marthedal Rasmussen
 *
 * Created 2010-05-02 7:55Z
 *
 * (C) Copyright SputSoft 2010
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 */

#ifndef _SPUTSOFT_NUMBERS_DETAIL_NAT_NUM_ABST_HPP
#define _SPUTSOFT_NUMBERS_DETAIL_NAT_NUM_ABST_HPP

#include <sputsoft/numbers/detail/number_abst.hpp>

namespace sputsoft {
namespace numbers {
namespace detail {

template <typename T>
class natnum;

template <typename T>
struct resolve_binary<ops::binary::rem, numb<natnum<T> >, unsigned short> {
  typedef unsigned short return_type;
};

template <typename T>
struct resolve_binary<ops::binary::rem, numb<natnum<T> >, unsigned> {
  typedef unsigned return_type;
};

template <typename T>
struct resolve_binary<ops::binary::rem, numb<natnum<T> >, unsigned long> {
  typedef unsigned long return_type;
};

#ifdef SPUTSOFT_HAS_LONG_LONG
template <typename T>
struct resolve_binary<ops::binary::rem, numb<natnum<T> >, unsigned long long> {
  typedef unsigned long long return_type;
};
#endif

/* Make compatible with int literals */
template <typename T>
struct resolve_binary<ops::binary::rem, numb<natnum<T> >, int> {
  typedef unsigned return_type;
};

template <typename T>
struct set_2_eval<numb<natnum<T> >, int> {
  static inline void set(numb<natnum<T> >& r, int v) {
    sputsoft::numbers::set(r, (unsigned) v);
  }
};
template <typename T>
struct add_3_eval<numb<natnum<T> >, numb<natnum<T> >, int> {
  static inline void add(numb<natnum<T> >& r, const numb<natnum<T> >& v1, int v2) {
    if (v2 >= 0)
      sputsoft::numbers::add(r, v1, (unsigned) v2);
    else
      sputsoft::numbers::sub(r, v1, (unsigned) -v2);
  }
};
template <typename T>
struct add_3_eval<numb<natnum<T> >, int, numb<natnum<T> > > {
  static inline void add(numb<natnum<T> >& r, int v1, const numb<natnum<T> >& v2) {
    if (v1 >= 0)
      sputsoft::numbers::add(r, (unsigned) v1, v2);
    else
      sputsoft::numbers::sub(r, (unsigned) -v1, v2);
  }
};
template <typename T>
struct sub_3_eval<numb<natnum<T> >, numb<natnum<T> >, int> {
  static inline void sub(numb<natnum<T> >& r, const numb<natnum<T> >& v1, int v2) {
    if (v2 >= 0)
      sputsoft::numbers::sub(r, v1, (unsigned) v2);
    else
      sputsoft::numbers::add(r, v1, (unsigned) -v2);
  }
};
template <typename T>
struct mul_3_eval<numb<natnum<T> >, numb<natnum<T> >, int> {
  static inline void mul(numb<natnum<T> >& r, const numb<natnum<T> >& v1, int v2) {
    sputsoft::numbers::mul(r, v1, (unsigned) v2);
  }
};
template <typename T>
struct mul_3_eval<numb<natnum<T> >, int, numb<natnum<T> > > {
  static inline void mul(numb<natnum<T> >& r, int v1, const numb<natnum<T> >& v2) {
    sputsoft::numbers::mul(r, (unsigned) v1, v2);
  }
};
template <typename T>
struct div_3_eval<numb<natnum<T> >, int, numb<natnum<T> > > {
  static inline void div(numb<natnum<T> >& r, const numb<natnum<T> >& v1, int v2) {
    sputsoft::numbers::div(r, v1, (unsigned) v2);
  }
};
template <typename T>
struct rem_3_eval<unsigned, numb<natnum<T> >, int> {
  static inline void rem(unsigned& r, const numb<natnum<T> >& v1, int v2) {
    sputsoft::numbers::rem(r, v1, (unsigned) v2);
  }
};
template <typename T>
struct quotrem_4_eval<numb<natnum<T> >, unsigned, numb<natnum<T> >, int> {
  static inline void quotrem(numb<natnum<T> >& q, unsigned& r, const numb<natnum<T> >& v1, int v2) {
    sputsoft::numbers::quotrem(q, r, v1, (unsigned) v2);
  }
};
template <typename T>
struct cmp_r2_eval<numb<natnum<T> >, int> {
  static inline int cmp(const numb<natnum<T> >& v1, int v2) {
    return sputsoft::numbers::compare(v1, (unsigned) v2);
  }
};
template <typename T>
struct cmp_r2_eval<int, numb<natnum<T> > > {
  static inline int cmp(int v1, const numb<natnum<T> >& v2) {
    return sputsoft::numbers::compare((unsigned) v1, v2);
  }
};
/*****************************************/

template <typename T>
struct abs_2_eval<numb<natnum<T> >, numb<natnum<T> > > {
  static inline void abs(numb<natnum<T> >& r, const numb<natnum<T> >& v) {
    sputsoft::numbers::set(r, v);
  }
};

template <typename T>
struct is_positive_r1_eval<numb<natnum<T> > > {
  static inline bool is_positive(const numb<natnum<T> >& v) {
    return !sputsoft::numbers::is_zero(v);
  }
};

template <typename T>
struct is_negative_r1_eval<numb<natnum<T> > > {
  static inline bool is_negative(const numb<natnum<T> >& v) {
    return false;
  }
};

template <typename T>
struct log2_floor_evaluator<numb<natnum<T> > > {
  static std::size_t log2_floor(const numb<natnum<T> >& n) {
    return n.log2_floor();
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const numb<natnum<T> >& n)
{
  unsigned max_digits = n ? log2_floor(n) / 3 + 2 : 2;
  char st[max_digits];
  char* p = st + max_digits;
  *--p = 0;
  numb<natnum<T> > t = n;
  do {
    unsigned r = quotrem(t, t, 10u);
    *--p = (char) r + '0';
  } while (t);
  return os << p;
}

template <typename T, typename Forw>
struct set_4_eval<numb<natnum<T> >, Forw> {
  static void set(numb<natnum<T> >& n, Forw first, const Forw last, unsigned base) {
    sputsoft::numbers::set(n, 0u);
    if (base >= 2 && base <= 36) {
      unsigned v;
      while (first != last) {
        char c = *first++;
        if (c >= '0' && c <= '9') v = c - '0';
        else if (c >= 'a' && c <= 'z') v = c - 'a' + 10;
        else if (c >= 'A' && c <= 'Z') v = c - 'A' + 10;
        else break;
        sputsoft::numbers::mul(n, n, base);
        sputsoft::numbers::add(n, n, v);
      }
    }
  }
};

} // namespace detail
} // namespace sputsoft
} // namespace numbers

#endif // _SPUTSOFT_NUMBERS_DETAIL_NAT_NUM_ABST_HPP
