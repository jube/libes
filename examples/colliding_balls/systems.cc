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

#include <cstdio>

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
                static_cast<float>(event.mouseButton.x / SCALE),
                static_cast<float>((HEIGHT - event.mouseButton.y) / SCALE)
            }, m_world);
            break;

          case sf::Mouse::Right:
            for (int i = 0; i < 10; ++i) {
              createBall(getManager(), {
                  static_cast<float>(event.mouseButton.x / SCALE),
                  static_cast<float>((HEIGHT - event.mouseButton.y) / SCALE)
              }, m_world);
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

void Physics::init() {
  // ground

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(WORLD_WIDTH / 2.0f, -THICKNESS);
  b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(WORLD_WIDTH / 2.0f + THICKNESS, THICKNESS);
  groundBody->CreateFixture(&groundBox, 0.0f);

  // right wall

  b2PolygonShape rightBox;
  b2Vec2 rightPos(WORLD_WIDTH / 2 + THICKNESS, 2 * WORLD_HEIGHT);
  rightBox.SetAsBox(THICKNESS, 2 * WORLD_HEIGHT + THICKNESS, rightPos, 0.0f);
  groundBody->CreateFixture(&rightBox, 0.0f);

  // left wall

  b2PolygonShape leftBox;
  b2Vec2 leftPos(- WORLD_WIDTH / 2 - THICKNESS, 2 * WORLD_HEIGHT);
  leftBox.SetAsBox(THICKNESS, 2 * WORLD_HEIGHT + THICKNESS, leftPos, 0.0f);
  groundBody->CreateFixture(&leftBox, 0.0f);

}

void Physics::update(float delta) {
  int32 velocityIterations = 10; // 6;
  int32 positionIterations = 8; // 2;
  m_world->Step(delta, velocityIterations, positionIterations);
}


void Graphics::updateEntity(float delta, es::Entity e) {
  Body *body = getManager()->getComponent<Body>(e);
  assert(body);

  Coords *coords = getManager()->getComponent<Coords>(e);
  assert(coords);

  b2Vec2 pos = body->body->GetPosition();

//   std::printf("pos: %f, %f\n", pos.x, pos.y);

  coords->vec.x = pos.x * SCALE;
  coords->vec.y = HEIGHT - (pos.y * SCALE);

//   std::printf("coords: %f, %f\n", coords->vec.x, coords->vec.y);
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
