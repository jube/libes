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
#include <es/System.h>

namespace es {

  System::~System() {
  }

  bool System::addEntity(Entity e) {
    auto ret = m_entities.insert(e);
    return ret.second;
  }

  void System::init() {
    // nothing by default
  }

  void System::preUpdate() {
    // nothing by default
  }

  void System::update(float delta) {
    for (Entity e : m_entities) {
      updateEntity(delta, e);
    }
  }

  void System::postUpdate() {
    // nothing by default
  }

  void System::updateEntity(float delta, Entity entity) {
    // nothing by default
  }

}
