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
#include <cstdlib>
#include <ctime>

#include <es/Manager.h>

#include "archetypes.h"
#include "parameters.h"
#include "systems.h"

int main() {
  std::srand(std::time(0));

  es::Manager manager;

  // prepare the components

  manager.createStoreFor(Position::type);
  manager.createStoreFor(Speed::type);
  manager.createStoreFor(Coords::type);
  manager.createStoreFor(Look::type);

  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "libes demo", sf::Style::Titlebar | sf::Style::Close);

  // prepare the systems

  manager.addSystem(new Input(&manager, &window));
  manager.addSystem(new Physics(&manager));
  manager.addSystem(new Graphics(&manager));
  manager.addSystem(new Render(&manager, &window));

  manager.initSystems();

  createBall(&manager, { WIDTH / 2.0f, HEIGHT / 2.0f});

  // enter the game loop

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    float delta = elapsed.asSeconds();
    manager.updateSystems(delta);
  }

  // clean up

  std::set<es::Entity> entities = manager.getEntities();

  for (auto e : entities) {
    destroyBall(&manager, e);
  }

  return 0;
}
