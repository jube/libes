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
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <es/Component.h>

#include <SFML/Graphics.hpp>

// The position of the ball in the world
struct Position : public es::Component {
  sf::Vector2f vec;

  Position(sf::Vector2f _vec)
    : vec(_vec)
  { }

#ifndef COMPILER_IS_NOT_CXX11_READY
  static const es::ComponentType type = "Position"_type;
#else
  static const es::ComponentType type = 1;
#endif
};

// The speed of the ball in the world
struct Speed : public es::Component {
  sf::Vector2f vec;

  Speed(sf::Vector2f _vec)
    : vec(_vec)
  { }

#ifndef COMPILER_IS_NOT_CXX11_READY
  static const es::ComponentType type = "Speed"_type;
#else
  static const es::ComponentType type = 2;
#endif
};

// The coordinates of the ball on the screen
struct Coords : public es::Component {
  sf::Vector2f vec;

  Coords(sf::Vector2f _vec)
    : vec(_vec)
  { }

#ifndef COMPILER_IS_NOT_CXX11_READY
  static const es::ComponentType type = "Coords"_type;
#else
  static const es::ComponentType type = 3;
#endif
};

// The appearance of the ball
struct Look : public es::Component {
  sf::Color color;

  Look(sf::Color _color)
    : color(_color)
  { }

#ifndef COMPILER_IS_NOT_CXX11_READY
  static const es::ComponentType type = "Look"_type;
#else
  static const es::ComponentType type = 4;
#endif
};

#endif // COMPONENTS_H
