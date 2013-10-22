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

  void LocalSystem::update(float delta) {
    auto copy = getEntities();
    for (Entity e : copy) {
      updateEntity(delta, e);
    }
  }

  const std::set<Entity> LocalSystem::getEntities() const {
    assert(0 <= m_x && m_x < m_width);
    assert(0 <= m_y && m_y < m_height);

    std::set<Entity> ret;

    int xmin = (m_x - 1 >= 0) ? m_x - 1 : m_x;
    int xmax = (m_x + 1 < m_width) ? m_x + 1 : m_x;
    int ymin = (m_y - 1 >= 0) ? m_y - 1 : m_y;
    int ymax = (m_y + 1 < m_height) ? m_y + 1 : m_y;

    for (int x = xmin; x <= xmax; ++x) {
      for (int y = ymin; y <= ymax; ++y) {
        int index = y * m_width + x;
        auto& set = m_entities[index];
        ret.insert(set.begin(), set.end());
      }
    }

    return std::move(ret);
  }

}
