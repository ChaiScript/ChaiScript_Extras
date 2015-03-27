#include "chaiscript/chaiscript.hpp"
#include "chaiscript/chaiscript_stdlib.hpp"
#include "include/chaiscript/extras/math.hpp"

#include <iostream>

int main()
{
  auto stdlib = chaiscript::Std_Lib::library();
  auto mathlib = chaiscript::extras::math::bootstrap();

  chaiscript::ChaiScript chai(stdlib);
  chai.add(mathlib);
}
