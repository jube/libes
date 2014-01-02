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
#include "archetypes.h"

#include <cstdlib>

#include "components.h"

es::Entity createBall(es::Manager *manager, sf::Vector2f pos) {
  es::Entity e = manager->createEntity();

  manager->addComponent(e, new Position(pos));
  manager->addComponent(e, new Speed({
      static_cast<float>(std::rand() % 500) - 250.0f,
      static_cast<float>(std::rand() % 300) - 150.0f
  }));
  manager->addComponent(e, new Coords({ 0., 0.}));
  manager->addComponent(e, new Look({
    static_cast<sf::Uint8>(std::rand() % 256),
    static_cast<sf::Uint8>(std::rand() % 256),
    static_cast<sf::Uint8>(std::rand() % 256),
    192 // some transparency
  }));

  manager->subscribeEntityToSystems(e);

  return e;
}

void destroyBall(es::Manager *manager, es::Entity e) {
  delete manager->extractComponent<Position>(e);
  delete manager->extractComponent<Speed>(e);
  delete manager->extractComponent<Coords>(e);
  delete manager->extractComponent<Look>(e);
  manager->destroyEntity(e);
}
