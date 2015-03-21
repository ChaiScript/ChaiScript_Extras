#include <cmath>
#include <memory>

#include "../dispatchkit/dispatchkit.hpp"
#include "../chaiscript.hpp"

namespace chaiscript {
  namespace extras {
    namespace math {
      template<typename Ret, typename Param>
      ModulePtr floor(ModulePtr m = std::make_shared<Module>())
      {
        // using the overloads provided by C++11
        // http://www.cplusplus.com/reference/cmath/floor/
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::floor)), "floor");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr cos(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::cos)), "cos");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr sin(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::sin)), "sin");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr tan(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::tan)), "tan");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr acos(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::acos)), "acos");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr asin(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::asin)), "asin");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr atan(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::atan)), "atan");
        return m;
      }

      template<typename Ret, typename Param1, typename Param2>
      ModulePtr atan2(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param1, Param2)>(&std::atan2)), "atan2");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr cosh(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::cosh)), "cosh");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr sinh(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::sinh)), "sinh");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr tanh(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::tanh)), "tanh");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr acosh(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::acosh)), "acosh");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr asinh(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::asinh)), "asinh");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr atanh(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::atanh)), "atanh");
        return m;
      }

      template<typename Ret, typename Param1, typename Param2>
      ModulePtr pow(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param1, Param2)>(&std::pow)), "pow");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr sqrt(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::sqrt)), "sqrt");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr cbrt(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::cbrt)), "cbrt");
        return m;
      }

      template<typename Ret, typename Param1, typename Param2>
      ModulePtr hypot(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param1, Param2)>(&std::hypot)), "hypot");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr erf(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::erf)), "erf");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr erfc(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::erfc)), "erfc");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr tgamma(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::tgamma)), "tgamma");
        return m;
      }

      template<typename Ret, typename Param>
      ModulePtr lgamma(ModulePtr m = std::make_shared<Module>())
      {
        m->add(chaiscript::fun(static_cast<Ret (*)(Param)>(&std::lgamma)), "lgamma");
        return m;
      }

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        floor<double, double>(m);
        floor<long double, long double>(m);
        floor<float, float>(m);

        cos<double, double>(m);
        cos<float, float>(m);
        cos<long double, long double>(m);

        sin<double, double>(m);
        sin<float, float>(m);
        sin<long double, long double>(m);

        tan<double, double>(m);
        tan<float, float>(m);
        tan<long double, long double>(m);

        acos<double, double>(m);
        acos<float, float>(m);
        acos<long double, long double>(m);

        asin<double, double>(m);
        asin<float, float>(m);
        asin<long double, long double>(m);

        atan<double, double>(m);
        atan<float, float>(m);
        atan<long double, long double>(m);

        atan2<double, double, double>(m);
        atan2<float, float, float>(m);
        atan2<long double, long double, long double>(m);

        cosh<double, double>(m);
        cosh<float, float>(m);
        cosh<long double, long double>(m);

        sinh<double, double>(m);
        sinh<float, float>(m);
        sinh<long double, long double>(m);

        tanh<double, double>(m);
        tanh<float, float>(m);
        tanh<long double, long double>(m);

        acosh<double, double>(m);
        acosh<float, float>(m);
        acosh<long double, long double>(m);

        asinh<double, double>(m);
        asinh<float, float>(m);
        asinh<long double, long double>(m);

        atanh<double, double>(m);
        atanh<float, float>(m);
        atanh<long double, long double>(m);

        pow<double, double, double>(m);
        pow<float, float, float>(m);
        pow<long double, long double, long double>(m);

        sqrt<double, double>(m);
        sqrt<float, float>(m);
        sqrt<long double, long double>(m);

        cbrt<double, double>(m);
        cbrt<float, float>(m);
        cbrt<long double, long double>(m);

        hypot<double, double, double>(m);
        hypot<float, float, float>(m);
        hypot<long double, long double, long double>(m);

        erf<double, double>(m);
        erf<float, float>(m);
        erf<long double, long double>(m);

        erfc<double, double>(m);
        erfc<float, float>(m);
        erfc<long double, long double>(m);

        tgamma<double, double>(m);
        tgamma<float, float>(m);
        tgamma<long double, long double>(m);

        lgamma<double, double>(m);
        lgamma<float, float>(m);
        lgamma<long double, long double>(m);

        return m;
      }
    }
  }
}
