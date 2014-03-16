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
#include <es/Manager.h>

#include <cassert>
#include <algorithm>

#include <es/System.h>

namespace es {

  Manager::~Manager() {
    for (auto store : m_stores) {
      // TODO: delete the content of the store?
      delete store.second;
    }
  }

  Entity Manager::createEntity() {
    Entity e = m_next++;
    assert(e != INVALID_ENTITY);
#if defined(__GNUC__) && (__GNUC_MINOR__ < 8) // GCC 4.4 - 4.7 have std::move(), but only GCC >= 4.8 have map::emplace()
    auto ret = m_entities.insert(std::move(std::make_pair(e, std::set<ComponentType>())));
#else
    auto ret = m_entities.emplace(e, std::set<ComponentType>());
#endif
    assert(ret.second);
    return e;
  }

  bool Manager::destroyEntity(Entity e) {
    auto count = m_entities.erase(e);
    return count > 0;
  }

  std::set<Entity> Manager::getEntities() const {
    std::set<Entity> ret;

    for (auto entity : m_entities) {
      ret.insert(entity.first);
    }

    return std::move(ret);
  }

  Store *Manager::getStore(ComponentType ct) {
    auto it = m_stores.find(ct);
    return it == m_stores.end() ? nullptr : it->second;
  }

  bool Manager::createStoreFor(ComponentType ct) {
    auto ret = m_stores.insert(std::make_pair(ct, new Store));
    return ret.second;
  }

  Component *Manager::getComponent(Entity e, ComponentType ct) {
    if (e == INVALID_ENTITY || ct == INVALID_COMPONENT) {
      return nullptr;
    }

    Store *store = getStore(ct);

    if (store == nullptr) {
      return nullptr;
    }

    return store->get(e);
  }

  bool Manager::addComponent(Entity e, ComponentType ct, Component *c) {
    if (e == INVALID_ENTITY || ct == INVALID_COMPONENT) {
      return false;
    }

    Store *store = getStore(ct);

    if (store == nullptr) {
      return false;
    }

    /*
     * associate the component type to the entity
     */
    auto it = m_entities.find(e);

    if (it == m_entities.end()) {
      // this probably indicates that the entity has not been created here
      return false;
    }

    it->second.insert(ct);
    return store->add(e, c);
  }

  Component *Manager::extractComponent(Entity e, ComponentType ct) {
    if (e == INVALID_ENTITY || ct == INVALID_COMPONENT) {
      return nullptr;
    }

    Store *store = getStore(ct);

    if (store == nullptr) {
      return nullptr;
    }

    /*
     * de-associate the component type to the entity
     */
    auto it = m_entities.find(e);
    if (it == m_entities.end()) {
      // this probably indicates that the entity has already been destroyed
      return nullptr;
    }
    it->second.erase(ct);

    Component *c = store->get(e);
    store->remove(e);
    return c;
  }

  int Manager::subscribeEntityToSystems(Entity e, std::set<ComponentType> components) {
    if (e == INVALID_ENTITY) {
      return 0;
    }

    int n = 0;

    for (auto& sys : m_systems) {
      const std::set<ComponentType> needed = sys->getNeededComponents();
      if (std::includes(components.begin(), components.end(), needed.begin(), needed.end())) {
        sys->addEntity(e);
        n++;
      } else {
        sys->removeEntity(e);
      }
    }

    return n;
  }

  int Manager::subscribeEntityToSystems(Entity e) {
    auto it = m_entities.find(e);

    if (it == m_entities.end()) {
      return 0;
    }

    return subscribeEntityToSystems(e, it->second);
  }


  bool Manager::addSystem(std::shared_ptr<System> sys) {
    if (sys) {
      m_systems.push_back(sys);
    }

    return true;
  }

  void Manager::initSystems() {
    std::sort(m_systems.begin(), m_systems.end(), [](const std::shared_ptr<System>& lhs, const std::shared_ptr<System>& rhs) {
      return lhs->getPriority() < rhs->getPriority();
    });

    for (auto& sys : m_systems) {
      sys->init();
    }
  }

  void Manager::updateSystems(float delta) {
    for (auto& sys : m_systems) {
      sys->preUpdate(delta);
    }

    for (auto& sys : m_systems) {
      sys->update(delta);
    }

    for (auto& sys : m_systems) {
      sys->postUpdate(delta);
    }
  }


  void Manager::registerHandler(EventType type, EventHandler handler) {
    assert(handler);
    auto it = m_handlers.find(type);

    if (it == m_handlers.end()) {
      bool inserted;
      std::tie(it, inserted) = m_handlers.insert(std::make_pair(type, std::vector<EventHandler>()));
      assert(inserted);
    }

    it->second.push_back(handler);
  }

  void Manager::triggerEvent(es::Entity origin, EventType type, Event *event) {
    auto it = m_handlers.find(type);

    if (it == m_handlers.end()) {
      return;
    }

    std::vector<EventHandler> kept;

    for (auto handler : it->second) {
      if (handler(origin, type, event) == EventStatus::KEEP) {
        kept.push_back(handler);
      }
    }

    std::swap(it->second, kept);
  }

}
