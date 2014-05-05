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
#ifndef ES_CUSTOM_SYSTEM_H
#define ES_CUSTOM_SYSTEM_H

#include <es/System.h>

namespace es {

  /**
   * @brief A custom system.
   *
   * A custom system is a System that provides defaut (empty) implementations
   * for pure virtual methods.
   */
  class CustomSystem : public System {
  public:
    /**
     * @brief Create a custom system.
     *
     * @param priority the priority of the system (small priority will
     * be executed first)
     * @param needed the set of needed component types that an entity must
     * have to be handled properly by this system
     * @param manager the manager (that is saved in the system so that the
     * system can easily access the manager)
     */
    CustomSystem(int priority, std::set<ComponentType> needed, Manager *manager)
      : System(priority, needed, manager)
    {
    }

    virtual bool addEntity(Entity e) override;
    virtual bool removeEntity(Entity e) override;

  };

}

#endif // ES_CUSTOM_SYSTEM_H
