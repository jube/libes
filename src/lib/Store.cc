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
#include <es/Store.h>

namespace es {

  bool Store::has(Entity e) {
    auto it = m_store.find(e);
    return it != m_store.end();
  }

  Component *Store::get(Entity e) {
    auto it = m_store.find(e);
    return (it == m_store.end() ? nullptr : it->second);
  }

  bool Store::add(Entity e, Component *c) {
    auto ret = m_store.insert(std::make_pair(e, c));
    return ret.second;
  }

  bool Store::remove(Entity e) {
    auto count = m_store.erase(e);
    return count > 1;
  }

  std::set<Entity> Store::getEntities() const {
    std::set<Entity> ret;

    for (auto elt : m_store) {
      ret.insert(elt.first);
    }

    return ret;
  }

}
