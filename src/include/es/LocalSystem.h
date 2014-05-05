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
#ifndef ES_LOCAL_SYSTEM_H
#define ES_LOCAL_SYSTEM_H

#include <cassert>
#include <vector>

#include <es/System.h>
#include <es/Entity.h>

namespace es {

  /**
   * @brief A local system.
   *
   * A local system handles the entities in a rectangular grid and updates the
   * entities that are in the focused cell.
   */
  class LocalSystem : public System {
  public:

    /**
     * @brief Create a local system.
     *
     * @param priority the priority of the system (small priority will
     * be executed first)
     * @param needed the set of needed component types that an entity must
     * have to be handled properly by this system
     * @param manager the manager (that is saved in the system so that the
     * system can easily access the manager)
     * @param width the width of the grid
     * @param height the height of the grid
     */
    LocalSystem(int priority, std::set<ComponentType> needed, Manager *manager, int width, int height)
      : System(priority, needed, manager), m_width(width), m_height(height), m_x(0), m_y(0), m_entities(width * height)
    {
      assert(width > 0);
      assert(height > 0);
    }

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

    /**
     * @brief Reset the grid dimensions.
     *
     * @param width the width of the grid
     * @param height the height of the grid
     */
    void reset(int width, int height);

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

    /**
     * @brief Add an entity in the (x,y) cell of the grid.
     *
     * @param e the entity
     * @param x the x coordinate
     * @param y the y coordinate
     * @returns true if the entity was added
     */
    bool addLocalEntity(Entity e, int x, int y);

    /**
     * @brief Remove an entity from the (x,y) cell of the grid.
     *
     * @param e the entity
     * @param x the x coordinate
     * @param y the y coordinate
     * @returns true if the entity was added
     */
    bool removeLocalEntity(Entity e, int x, int y);

  protected:
    const std::set<Entity> getEntities() const;

  private:
    int getIndex(int x, int y) const {
      return y * m_width + x;
    }

    int m_width;
    int m_height;

    int m_x;
    int m_y;

    std::vector<std::set<Entity>> m_entities;
  };

}

#endif // ES_GLOBAL_SYSTEM_H
