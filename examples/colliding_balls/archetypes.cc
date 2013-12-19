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
#include "archetypes.h"
#include "parameters.h"

#include <cstdlib>

#include "components.h"

es::Entity createBall(es::Manager *manager, b2Vec2 pos, b2World *world) {
  es::Entity e = manager->createEntity();

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = pos;
  b2Body* body = world->CreateBody(&bodyDef);

  b2CircleShape circle;
  circle.m_radius = RADIUS / SCALE;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &circle;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.001f;
  fixtureDef.restitution = RESTITUTION;

  body->CreateFixture(&fixtureDef);



  b2Vec2 impulse;
  impulse.Set(
    static_cast<float>(std::rand() % 200 - 100) / 1000.0f,
    static_cast<float>(std::rand() % 50) / 1000.0f
  );
  body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

  manager->addComponent(e, new Body(body));
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
  delete manager->extractComponent<Body>(e);
  delete manager->extractComponent<Coords>(e);
  delete manager->extractComponent<Look>(e);
  manager->destroyEntity(e);
}
