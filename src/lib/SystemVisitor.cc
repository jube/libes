#include <es/SystemVisitor.h>

namespace es {

  SystemVisitor::~SystemVisitor() {
  }

  void SystemVisitor::visitGlobalSystem(GlobalSystem& sys) {
    // nothing to do by default
  }

}
