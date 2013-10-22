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
#ifndef ES_LOCAL_SYSTEM_H
#define ES_LOCAL_SYSTEM_H

#include <vector>

#include "System.h"
#include "Entity.h"

namespace es {

  class LocalSystem : public System {
  public:

    LocalSystem(int priority, std::set<ComponentType> needed, Manager *manager, int width, int height)
      : System(priority, needed, manager), m_width(width), m_height(height)
    {
    }

    virtual void accept(SystemVisitor& vis) override;

    /**
     * @brief Update all the entities in the current time step.
     *
     * By default, it calls updateEntity on every entity that was already
     * added.
     *
     * @param delta the time (in second) since the last update
     * @param x the x-coordinate of the focus
     * @param y the y-coordinate of the focus
     */
    virtual void update(float delta, int x, int y);

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
    const std::set<Entity> getEntities(int x, int y) const;

  private:
    const int m_width;
    const int m_height;
    std::vector<std::set<Entity>> m_entities;
  };

}

#endif // ES_GLOBAL_SYSTEM_H
