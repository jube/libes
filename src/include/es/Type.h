/*
 * Copyright (c) 2013-2014, Julien Bernard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef ES_TYPE_H
#define ES_TYPE_H

#include <cstdint>
#include <string>

namespace es {

  /**
   * @brief A type.
   *
   * An type is a generic unsigned int that helps to distinguish several
   * elements of the same class.
   */
  typedef uint64_t Type;

#define INVALID_TYPE 0

#if  (defined(__GNUC__) && (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4))) \
  || (defined(__clang__)) \
  || (defined(_MSC_VER) && (_MSC_VER > 1800)) // > VS2013
  constexpr Type Hash(const char *str, std::size_t sz) {
    return sz == 0 ? 0xcbf29ce484222325 : (str[0] ^ Hash(str + 1, sz - 1)) * 0x100000001b3;
  }

  inline Type Hash(const std::string& str) {
    return Hash(str.c_str(), str.size());
  }
#endif
}

#if  (defined(__GNUC__) && (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4))) \
  || (defined(__clang__)) \
  || (defined(_MSC_VER) && (_MSC_VER > 1800)) // > VS2013
constexpr es::Type operator"" _type(const char *str, std::size_t sz) {
  return es::Hash(str, sz);
}
#endif

#endif // ES_TYPE_H
