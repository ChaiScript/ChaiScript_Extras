#include <cmath>

namespace chaiscript {
  namespace extras {
    namespace math {
      template<typename Ret, typename Param>
      ModulePtr floor(ModulePtr m = std::make_shared<Module>())
      {
        // using the overloads provided by C++11
        // http://www.cplusplus.com/reference/cmath/floor/
        m->add(chaiscript::fun(static_cast<Ret (Param)>(&std::floor)), "floor");
        return m;
      }

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        floor<double, double>(m);
        floor<long double, long double>(m);
        floor<float, float>(m);

        return m;
      }
    }
  }
}
