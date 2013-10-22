#ifndef ES_SYSTEM_VISITOR_H
#define ES_SYSTEM_VISITOR_H

#include "GlobalSystem.h"

namespace es {

  class SystemVisitor {
  public:
    virtual ~SystemVisitor();
    virtual void visitGlobalSystem(GlobalSystem& sys);
  };

}

#endif // ES_SYSTEM_VISITOR_H
