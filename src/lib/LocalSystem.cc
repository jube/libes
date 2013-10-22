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
#include <es/LocalSystem.h>

#include <cassert>
#include <es/SystemVisitor.h>

namespace es {

  void LocalSystem::accept(SystemVisitor& vis) {
    vis.visitLocalSystem(*this);
  }

  void LocalSystem::update(float delta, int x, int y) {
    auto copy = getEntities(x, y);
    for (Entity e : copy) {
      updateEntity(delta, e);
    }
  }

  void LocalSystem::updateEntity(float delta, Entity e) {
    // nothing by default
  }

  const std::set<Entity> LocalSystem::getEntities(int x, int y) const {
    assert(x < m_width);
    assert(y < m_height);

    std::set<Entity> ret;

    int xmin = (x - 1 >= 0) ? x - 1 : x;
    int xmax = (x + 1 < m_width) ? x + 1 : x;
    int ymin = (y - 1 >= 0) ? y - 1 : y;
    int ymax = (y + 1 < m_height) ? y + 1 : y;

    for (x = xmin; x <= xmax; ++x) {
      for (y = ymin; y <= ymax; ++y) {
        int index = y * m_width + x;
        auto& set = m_entities[index];
        ret.insert(set.begin(), set.end());
      }
    }

    return std::move(ret);
  }

}
