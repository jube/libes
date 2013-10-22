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
#ifndef ES_MANAGER_H
#define ES_MANAGER_H

#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include "Entity.h"
#include "Store.h"
#include "System.h"

namespace es {

  /**
   * @brief The manager.
   *
   * The role of the manager is to manage entities, stores, components and systems. It
   * can also create entities.
   *
   */
  class Manager {
  public:
    /**
     * @brief Create a manager.
     */
    Manager()
    : m_next(1), m_x(0), m_y(0) { }

    ~Manager();

    ///@{

    /**
     * @brief Create a new entity.
     *
     * @returns a new entity
     */
    Entity createEntity();

    /**
     * @brief Destroy an entity.
     *
     * @param e the entity to destroy
     * @returns true if the entity was actually present and destroyed
     */
    bool destroyEntity(Entity e);

    /**
     * @brief Get all the entities
     *
     * @returns a copy of the set of entities
     */
    std::set<Entity> getEntities() const {
      return m_entities;
    }

    /// @}


    /// @{

    /**
     * @brief Get the store associated to a component type.
     *
     * @param ct a component type
     * @returns the store or nullptr if the store does not exist
     */
    Store *getStore(ComponentType ct);

    /**
     * @brief Create a store for a component type.
     *
     * @param ct a component type
     * @returns true if the store was created
     */
    bool createStoreFor(ComponentType ct);

    /**
     * @brief Create a store for a component type.
     *
     * @returns true if the store was createds
     */
    template<typename C>
    bool createStoreFor() {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return createStoreFor(C::type);
    }

    /// @}


    /// @{

    /**
     * @brief Get the component associated to an entity.
     *
     * @param e the entity
     * @param ct the component type
     * @returns the component or null if the entity is not valid, or if the
     *   store does not exist or if the entity has no component of this type
     */
    Component *getComponent(Entity e, ComponentType ct);

    /**
     * @brief Get the component associated to an entity.
     *
     * @param e the entity
     * @returns the component or null if the entity is not valid, or if the
     *   store does not exist or if the entity has no component of this type
     */
    template<typename C>
    C *getComponent(Entity e) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return static_cast<C*>(getComponent(e, C::type));
    }

    /**
     * @brief Add a component to an entity.
     *
     * @param e the entity
     * @param ct the component type
     * @param c the component to be added
     * @returns true if the component was actually added
     */
    bool addComponent(Entity e, ComponentType ct, Component *c);

    /**
     * @brief Add a component to an entity.
     *
     * @param e the entity
     * @param c the component to be added
     * @returns true if the component was actually added
     */
    template<typename C>
    bool addComponent(Entity e, C *c) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return addComponent(e, C::type, c);
    }

    /**
     * @brief Extract the component associated to an entity.
     *
     * The component is removed from the associated store and returned.
     *
     * @param e the entity
     * @param ct the component type
     * @returns the component or null if the entity is not valid, or if the
     *   store does not exist or if the entity has no component of this type
     */
    Component *extractComponent(Entity e, ComponentType ct);

    /**
     * @brief Extract the component associated to an entity.
     *
     * The component is removed from the associated store and returned.
     *
     * @param e the entity
     * @returns the component or null if the entity is not valid, or if the
     *   store does not exist or if the entity has no component of this type
     */
    template<typename C>
    C *extractComponent(Entity e) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return static_cast<C*>(extractComponent(e, C::type));
    }


    /// @}


    /// @{

    /**
     * @brief Subscribe and entity to the systems.
     *
     * @param e the entity
     * @param components the set of component types that the entity has
     * @returns the number of systems the entity was subscribed
     *
     */
    int subscribeEntityToSystems(Entity e, std::set<ComponentType> components);

    /**
     * @brief Add a system to the manager.
     *
     * @param sys the system
     * @returns true if the system was actually added
     */
    bool addSystem(std::shared_ptr<System> sys);


    /**
     * @brief Add a system to the manager.
     *
     * @param args the arguments to pass to the system's constructor
     * @returns true if the system was actually added
     */
    template<typename S, typename ... Args>
    bool addSystem(Args&&... args) {
      static_assert(std::is_base_of<System, S>::value, "S must be a System");
      return addSystem(std::make_shared<S>(std::forward<Args>(args)...));
    }

    /**
     * @brief Initialize all systems.
     */
    void initSystems();

    /**
     * @brief Update all systems.
     *
     * @param delta the time (in second) since the last update
     */
    void updateSystems(float delta);

    /**
     * @brief Set the focus for local systems.
     *
     * @param x the x-coordinate of the focus
     * @param y the y-coordinate of the focus
     */
    void setFocus(int x, int y) {
      m_x = x;
      m_y = y;
    }

    /// @}

  private:
    Entity m_next;

    std::set<Entity> m_entities;
    std::vector<std::shared_ptr<System>> m_systems;
    std::map<ComponentType, Store *> m_stores;

    int m_x;
    int m_y;
  };

}

#endif // ES_MANAGER_H
