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
#include <es/Manager.h>

#include <cassert>
#include <algorithm>

#include <es/System.h>
#include <es/SystemVisitor.h>

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
    auto ret = m_entities.insert(e);
    assert(ret.second);
    return e;
  }

  bool Manager::destroyEntity(Entity e) {
    auto count = m_entities.erase(e);
    return count > 0;
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

  namespace {

    class UpdateVisitor : public SystemVisitor {
    public:
      UpdateVisitor(float _delta)
      : delta(_delta)
      {
      }

      virtual void visitGlobalSystem(GlobalSystem& sys) override {
        sys.update(delta);
      }

    private:
      const float delta;
    };


  }

  void Manager::updateSystems(float delta) {
    for (auto& sys : m_systems) {
      sys->preUpdate(delta);
    }

    UpdateVisitor vis(delta);
    for (auto& sys : m_systems) {
      sys->accept(vis);
    }

    for (auto& sys : m_systems) {
      sys->postUpdate(delta);
    }
  }

}
