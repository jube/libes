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
#include <es/GlobalSystem.h>

#include <es/SystemVisitor.h>

namespace es {

  void GlobalSystem::accept(SystemVisitor& vis) {
    vis.visitGlobalSystem(*this);
  }

  bool GlobalSystem::addEntity(Entity e) {
    auto ret = m_entities.insert(e);
    return ret.second;
  }

  bool GlobalSystem::removeEntity(Entity e) {
    auto ret = m_entities.erase(e);
    return ret > 0;
  }

  void GlobalSystem::update(float delta) {
    /* make a copy so that the entities can be safely removed from the system
     * without invalidating the iterators.
     */
    auto copy = getEntities();
    for (Entity e : copy) {
      updateEntity(delta, e);
    }
  }

  void GlobalSystem::updateEntity(float delta, Entity entity) {
    // nothing by default
  }


}