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
#ifndef ES_STORE_H
#define ES_STORE_H

#include <cassert>
#include <map>
#include <set>
#include <type_traits>

#include "Entity.h"
#include "Component.h"

namespace es {

  /**
   * @brief A store.
   *
   * A store is tied to a component type. It handles the association between
   * an entity and its component of this type.
   *
   */
  class Store {
  public:
    /**
     * @brief Tell whether an entity is present in this store.
     *
     * @param e the entity
     * @returns true if the store has the entity
     */
    bool has(Entity e);

    /**
     * @brief Get the compnent associated to an entity.
     *
     * @param e the entity
     * @returns the component or null if the entity has no component of this
     * type
     */
    Component *get(Entity e);

    /**
     * @brief Add a component to an entity
     *
     * The user is responsible to allocate the component.
     *
     * @param e the entity
     * @param c the component
     * @return true if the component was actually added
     *
     */
    bool add(Entity e, Component *c);

    /**
     * @brief Remove a component from an entity
     *
     * The user is responsible for deleting the component.
     *
     * @param e the entity
     * @returns true if component was actually removed
     *
     */
    bool remove(Entity e);

    /**
     * @brief Get all the entities that have a component of this type
     *
     * @returns a set of entities
     */
    std::set<Entity> getEntities() const;

  private:
    template <typename C>
    friend class ComponentStore;

    std::map<Entity, Component *> m_store;
  };

  /**
   * @brief A type-safe wrapper around a store
   *
   */
  template<typename C>
  class ComponentStore {
    static_assert(std::is_base_of<Component, C>::value, "ComponentStore requires a child of Component");
  public:
    ComponentStore(Store *store)
    : m_store(store) {
      assert(store);
    }

    /**
     * @brief Tell whether an entity is present in this store.
     *
     * @param e the entity
     * @returns true if the store has the entity
     */
    bool has(Entity e) {
      return m_store->has(e);
    }

    /**
     * @brief Get the compnent associated to an entity.
     *
     * @param e the entity
     * @returns the component or null if the entity has no component of this
     * type
     */
    C *get(Entity e) {
      return static_cast<C *>(m_store->get(e));
    }

    /**
     * @brief Add a component to an entity
     *
     * The user is responsible to allocate the component.
     *
     * @param e the entity
     * @param c the component
     * @return true if the component was actually added
     *
     */
    bool add(Entity e, C *c) {
      return m_store->add(e, c);
    }

    /**
     * @brief Remove a component from an entity
     *
     * The user is responsible for deleting the component.
     *
     * @param e the entity
     * @returns true if component was actually removed
     *
     */
    bool remove(Entity e) {
      return m_store->remove(e);
    }

  private:
    Store * const m_store;
  };

}


#endif // ES_STORE_H
