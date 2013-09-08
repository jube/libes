/*
 * Copyright (c) 2013, Julien Bernard
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
#ifndef ES_COMPONENT_H
#define ES_COMPONENT_H

namespace es {

  /**
   * @brief A component type.
   *
   * A component type is a strictly positive integer that must be unique
   * among all component types.
   */
  typedef unsigned long ComponentType;

#define INVALID_COMPONENT 0

  /**
   * @brief A component.
   *
   * This structure is empty and must be the father of all components. A
   * component must have a class variable to indicate its type.
   */
  struct Component {
    /**
     * The default (invalid) component type.
     */
    static const ComponentType type = INVALID_COMPONENT;
  };

}

#endif // ES_COMPONENT_H