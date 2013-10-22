#include <es/GlobalSystem.h>

#include <es/SystemVisitor.h>

namespace es {

  void GlobalSystem::accept(SystemVisitor& vis) {
    vis.visitGlobalSystem(*this);
  }

  bool GlobalSystem::addEntity(Entity e) {
    auto ret = m_entities.insert(e);
    return ret.second;
  }

  bool GlobalSystem::removeEntity(Entity e) {
    auto ret = m_entities.erase(e);
    return ret > 0;
  }

  void GlobalSystem::update(float delta) {
    /* make a copy so that the entities can be safely removed from the system
     * without invalidating the iterators.
     */
    auto copy = m_entities;
    for (Entity e : copy) {
      updateEntity(delta, e);
    }
  }

  void GlobalSystem::updateEntity(float delta, Entity entity) {
    // nothing by default
  }


}
