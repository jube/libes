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
#ifndef ES_SYSTEM_H
#define ES_SYSTEM_H

#include <set>

#include "Entity.h"
#include "Component.h"

namespace es {
  class Manager;

  /**
   * @brief A system.
   *
   * A system handles a set of components that belongs to an entity.
   *
   */
  class System {
  public:
    /**
     * @brief A system constructor.
     *
     * @param priority the priority of the system (small priority will
     * be executed first)
     * @param needed the set of needed component types that an entity must
     * have to be handled properly by this system
     * @param manager the manager (that is saved in the system so that the
     * system can easily access the manager)
     *
     */
    System(int priority, std::set<ComponentType> needed, Manager *manager)
    : m_priority(priority), m_needed(needed), m_manager(manager) {
    }

    virtual ~System();

    /**
     * @brief Get the priority of the system.
     *
     * @returns the priority of the system
     */
    int getPriority() const {
      return m_priority;
    }

    /**
     * @brief Get the needed component types.
     *
     * @returns the needed component types
     */
    std::set<ComponentType> getNeededComponents() const {
      return m_needed;
    }

    /**
     * @brief Get the manager.
     *
     * @returns the manager
     */
    Manager *getManager() {
      return m_manager;
    }

    /**
     * @brief Add an entity in the system.
     *
     * The entity must have the needed components (this is not verified by
     * the library). The order in which the entity are added is not saved.
     *
     * @param e the entity
     * @returns true if the entity was actually added
     */
    bool addEntity(Entity e);

    /**
     * @brief Removes an entity from the system.
     *
     * @param e the entity
     * @returns true if the entity was actually removed
     */
    bool removeEntity(Entity e);

    /**
     * @brief Initialize the system
     *
     * By default, does nothing
     */
    virtual void init();

    /**
     * @brief Do something before the individual update of each entity.
     *
     * This function is called at every step. By default, do nothing.
     */
    virtual void preUpdate();

    /**
     * @brief Update all the entities in the current time step.
     *
     * By default, it calls updateEntity on every entity that was already
     * added.
     *
     * @param delta the time (in second) since the last update
     */
    virtual void update(float delta);

    /**
     * @brief Do something after the individual update of each entity.
     *
     * This function is called at every step. By default, do nothing.
     *
     */
    virtual void postUpdate();

    /**
     * @brief Update an entity in the current time step.
     *
     * This function is called by update. By default, do nothing.
     *
     * @param delta the time (in second) since the last update
     * @param e the entity
     */
    virtual void updateEntity(float delta, Entity e);

  protected:
    /**
     * @brief Get the set of entities handled by this system.
     *
     * @returns the set of entities.
     */
    const std::set<Entity>& getEntities() {
      return m_entities;
    }

  private:
    const int m_priority;
    const std::set<ComponentType> m_needed;

    Manager * const m_manager;

    std::set<Entity> m_entities;
  };

}

#endif // ES_SYSTEM_H
