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
#ifndef ES_GLOBAL_SYSTEM_H
#define ES_GLOBAL_SYSTEM_H

#include "System.h"

namespace es {

  class GlobalSystem : public System {
  public:
    GlobalSystem(int priority, std::set<ComponentType> needed, Manager *manager)
      : System(priority, needed, manager)
    {
    }

    virtual void accept(SystemVisitor& vis);

    virtual bool addEntity(Entity e) override;
    virtual bool removeEntity(Entity e) override;

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
    std::set<Entity> m_entities;

  };


}


#endif // ES_GLOBAL_SYSTEM_H
