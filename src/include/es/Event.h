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
#ifndef ES_EVENT_H
#define ES_EVENT_H

namespace es {

  /**
   * @brief An event type.
   *
   * An event type is a strictly positive integer that must be unique among
   * all event types.
   */
  typedef unsigned long EventType;

#define INVALID_EVENT 0

  /**
   * @brief An event.
   *
   * This structure is empty and must be the father of all events. An event
   * must have a class variable to indicate its type.
   */
  struct Event {
    /**
     * The default (invalid) event type.
     */
    static const EventType type = INVALID_EVENT;
  };

}

#endif // ES_EVENT_H
