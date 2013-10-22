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
#include "systems.h"

#include "archetypes.h"
#include "parameters.h"

void Input::preUpdate(float delta) {
  sf::Event event;

  while (m_window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        m_window->close();
        break;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Escape:
            m_window->close();
            break;

          default:
            break;
        }
        break;

      case sf::Event::MouseButtonPressed:
        switch (event.mouseButton.button) {
          case sf::Mouse::Left:
            createBall(getManager(), {
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(HEIGHT - event.mouseButton.y)
            });
            break;

          case sf::Mouse::Right:
            for (int i = 0; i < 10; ++i) {
              createBall(getManager(), {
                  static_cast<float>(event.mouseButton.x),
                  static_cast<float>(HEIGHT - event.mouseButton.y)
              });
            }
            break;

          default:
            break;

        }
        break;

      default:
        break;
    }
  }
}

void Physics::updateEntity(float delta, es::Entity e) {
  Position *pos = getManager()->getComponent<Position>(e);
  assert(pos);

  Speed *speed = getManager()->getComponent<Speed>(e);
  assert(speed);

  // apply gravity
  speed->vec.y += -GRAVITY * delta;

  pos->vec.x += speed->vec.x * delta;
  pos->vec.y += speed->vec.y * delta;

  // detect collision with the ground
  if (pos->vec.y < RADIUS) {
    pos->vec.y = RADIUS;
    speed->vec.y = -speed->vec.y * LOSS;
  }

  // detect collision with the left wall
  if (pos->vec.x < RADIUS) {
    pos->vec.x = RADIUS;
    speed->vec.x = -speed->vec.x;
  }

  // detect collision with the right wall
  if (pos->vec.x > WIDTH - RADIUS) {
    pos->vec.x = WIDTH - RADIUS;
    speed->vec.x = -speed->vec.x;
  }

}


void Graphics::updateEntity(float delta, es::Entity e) {
  Position *pos = getManager()->getComponent<Position>(e);
  assert(pos);

  Coords *coords = getManager()->getComponent<Coords>(e);
  assert(coords);

  coords->vec.x = pos->vec.x;
  coords->vec.y = HEIGHT - pos->vec.y;
}


void Render::preUpdate(float delta) {
  m_window->clear(sf::Color::White);
}

void Render::updateEntity(float delta, es::Entity e) {
  Coords *coords = getManager()->getComponent<Coords>(e);
  assert(coords);

  Look *look = getManager()->getComponent<Look>(e);
  assert(look);

  sf::CircleShape shape(RADIUS);
  shape.setFillColor(look->color);
  shape.setOrigin(RADIUS, RADIUS);
  shape.setPosition(coords->vec);

  m_window->draw(shape);
}

void Render::postUpdate(float delta) {
  m_window->display();
}
