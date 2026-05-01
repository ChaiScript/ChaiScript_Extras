#ifndef CHAISCRIPT_EXTRAS_RANDOM_HPP_
#define CHAISCRIPT_EXTRAS_RANDOM_HPP_

#include <memory>
#include <random>

#include <chaiscript/chaiscript.hpp>

namespace chaiscript {
  namespace extras {
    namespace random {
      class MT19937_Engine {
      public:
        MT19937_Engine()
          : m_engine(std::random_device{}())
        {
        }

        explicit MT19937_Engine(unsigned int t_seed)
          : m_engine(t_seed)
        {
        }

        MT19937_Engine(const MT19937_Engine &) = default;
        MT19937_Engine &operator=(const MT19937_Engine &) = default;

        void seed(unsigned int t_seed) {
          m_engine.seed(t_seed);
        }

        int random_int(int t_min, int t_max) {
          std::uniform_int_distribution<int> dist(t_min, t_max);
          return dist(m_engine);
        }

        double random_float(double t_min, double t_max) {
          std::uniform_real_distribution<double> dist(t_min, t_max);
          return dist(m_engine);
        }

      private:
        std::mt19937 m_engine;
      };

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        m->add(user_type<MT19937_Engine>(), "MT19937_Engine");
        m->add(constructor<MT19937_Engine ()>(), "MT19937_Engine");
        m->add(constructor<MT19937_Engine (unsigned int)>(), "MT19937_Engine");
        m->add(constructor<MT19937_Engine (const MT19937_Engine &)>(), "MT19937_Engine");

        m->add(fun(&MT19937_Engine::seed), "seed");
        m->add(fun(&MT19937_Engine::random_int), "random_int");
        m->add(fun(&MT19937_Engine::random_float), "random_float");

        m->add(fun([](MT19937_Engine &t_lhs, const MT19937_Engine &t_rhs) -> MT19937_Engine & {
          t_lhs = t_rhs;
          return t_lhs;
        }), "=");

        return m;
      }
    }
  }
}

#endif /* CHAISCRIPT_EXTRAS_RANDOM_HPP_ */
