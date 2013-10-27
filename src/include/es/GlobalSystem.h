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

    virtual void update(float delta) override;

    virtual bool addEntity(Entity e) override;
    virtual bool removeEntity(Entity e) override;

  protected:
    /**
     * @brief Get a copy of the entities handled by this system.
     *
     * @returns the set of entities.
     */
    const std::set<Entity> getEntities() const {
      return m_entities;
    }

  private:
    std::set<Entity> m_entities;

  };


}


#endif // ES_GLOBAL_SYSTEM_H
