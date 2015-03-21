#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "../include/chaiscript/extras/math.hpp"

TEST_CASE( "Math functions work", "[math]" ) {
  auto stdlib = chaiscript::Std_Lib::library();
  auto mathlib = chaiscript::extras::math::bootstrap();

  chaiscript::ChaiScript chai(stdlib);
  chai.add(mathlib);

  CHECK(chai.eval<double>("floor(2.2)") == floor(2.2));

  CHECK(chai.eval<double>("cos(0.5)") == cos(0.5));
  CHECK(chai.eval<double>("sin(0.5)") == sin(0.5));
  CHECK(chai.eval<double>("tan(0.5)") == tan(0.5));

  CHECK(chai.eval<double>("acos(0.5)") == acos(0.5));
  CHECK(chai.eval<double>("asin(0.5)") == asin(0.5));
  CHECK(chai.eval<double>("atan(0.5)") == atan(0.5));
  CHECK(chai.eval<double>("atan2(0.5, 0.5)") == atan2(0.5, 0.5));

  CHECK(chai.eval<double>("cosh(0.5)") == cosh(0.5));
  CHECK(chai.eval<double>("sinh(0.5)") == sinh(0.5));
  CHECK(chai.eval<double>("tanh(0.5)") == tanh(0.5));

  CHECK(chai.eval<double>("acosh(1.0)") == acosh(1.0));
  CHECK(chai.eval<double>("asinh(0.5)") == asinh(0.5));
  CHECK(chai.eval<double>("atanh(0.5)") == atanh(0.5));

  CHECK(chai.eval<double>("pow(0.5, 3.0)") == pow(0.5, 3.0));
  CHECK(chai.eval<double>("sqrt(0.5)") == sqrt(0.5));
  CHECK(chai.eval<double>("cbrt(0.5)") == cbrt(0.5));
  CHECK(chai.eval<double>("hypot(0.5, 0.5)") == hypot(0.5, 0.5));

  CHECK(chai.eval<double>("erf(0.5)") == erf(0.5));
  CHECK(chai.eval<double>("erfc(0.5)") == erfc(0.5));
  CHECK(chai.eval<double>("tgamma(0.5)") == tgamma(0.5));
  CHECK(chai.eval<double>("lgamma(0.5)") == lgamma(0.5));
}


