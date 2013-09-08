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
#ifndef ES_ARCHETYPE_H
#define ES_ARCHETYPE_H

#include <set>

#include "Component.h"
#include "Entity.h"
#include "Manager.h"

namespace es {

  /**
   * @brief An archetype.
   *
   * An archetype is a set of components types.
   */
  struct Archetype {

    /**
     * @brief Create a new entity with the declared component types.
     *
     * @param manager the manager
     * @param components the set of component types that the entity has
     * @returns a new entity
     */
    static Entity create(Manager *manager, std::set<ComponentType> components);

  };

}

#endif // ES_ARCHETYPE_H
