#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "../include/chaiscript/extras/random.hpp"

TEST_CASE( "MT19937_Engine type is usable in ChaiScript", "[random]" ) {
  auto randomlib = chaiscript::extras::random::bootstrap();

  auto stdlib = chaiscript::Std_Lib::library();
  chaiscript::ChaiScript chai(stdlib);
  chai.add(randomlib);

  SECTION("default constructor creates a valid engine") {
    const auto result = chai.eval<int>("var rng = MT19937_Engine(); rng.random_int(0, 100)");
    CHECK(result >= 0);
    CHECK(result <= 100);
  }

  SECTION("seeded constructor creates a valid engine") {
    const auto result = chai.eval<int>("var rng = MT19937_Engine(42u); rng.random_int(0, 100)");
    CHECK(result >= 0);
    CHECK(result <= 100);
  }

  SECTION("seed produces deterministic sequences") {
    chai.eval("var rng = MT19937_Engine()");
    chai.eval("rng.seed(42u)");
    const auto first = chai.eval<int>("rng.random_int(0, 1000)");
    chai.eval("rng.seed(42u)");
    const auto second = chai.eval<int>("rng.random_int(0, 1000)");
    CHECK(first == second);
  }

  SECTION("copy constructor copies engine state") {
    chai.eval("var rng = MT19937_Engine(99u)");
    chai.eval("var rng2 = MT19937_Engine(rng)");
    const auto a = chai.eval<int>("rng.random_int(0, 1000)");
    const auto b = chai.eval<int>("rng2.random_int(0, 1000)");
    CHECK(a == b);
  }

  SECTION("assignment copies engine state") {
    chai.eval("var rng = MT19937_Engine(77u)");
    chai.eval("var rng2 = MT19937_Engine()");
    chai.eval("rng2 = rng");
    const auto a = chai.eval<int>("rng.random_int(0, 1000)");
    const auto b = chai.eval<int>("rng2.random_int(0, 1000)");
    CHECK(a == b);
  }

  SECTION("random_int returns values in range") {
    chai.eval("var rng = MT19937_Engine(42u)");
    const auto result = chai.eval<int>("rng.random_int(5, 10)");
    CHECK(result >= 5);
    CHECK(result <= 10);
  }

  SECTION("random_float returns values in range") {
    chai.eval("var rng = MT19937_Engine(42u)");
    const auto result = chai.eval<double>("rng.random_float(0.0, 1.0)");
    CHECK(result >= 0.0);
    CHECK(result < 1.0);
  }

  SECTION("different seeds produce different sequences") {
    chai.eval("var rng1 = MT19937_Engine(1u)");
    chai.eval("var rng2 = MT19937_Engine(2u)");
    const auto a = chai.eval<int>("rng1.random_int(0, 1000000)");
    const auto b = chai.eval<int>("rng2.random_int(0, 1000000)");
    CHECK(a != b);
  }
}
