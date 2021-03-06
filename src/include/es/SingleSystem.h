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
#ifndef ES_SINGLE_SYSTEM_H
#define ES_SINGLE_SYSTEM_H

#include <es/System.h>

namespace es {

  /**
   * @brief A single system.
   *
   * A single system is a System that handle a single entity.
   */
  class SingleSystem : public System {
  public:
    /**
     * @brief Create a single system.
     *
     * @param priority the priority of the system (small priority will
     * be executed first)
     * @param needed the set of needed component types that an entity must
     * have to be handled properly by this system
     * @param manager the manager (that is saved in the system so that the
     * system can easily access the manager)
     */
    SingleSystem(int priority, std::set<ComponentType> needed, Manager *manager)
      : System(priority, needed, manager), m_entity(INVALID_ENTITY)
    {
    }

    virtual bool addEntity(Entity e) override;
    virtual bool removeEntity(Entity e) override;

  protected:
    Entity getEntity() {
      return m_entity;
    }

  private:
    Entity m_entity;
  };

}

#endif // ES_SINGLE_SYSTEM_H
