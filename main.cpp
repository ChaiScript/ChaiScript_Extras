#include "chaiscript/chaiscript.hpp"
#include "chaiscript/chaiscript_stdlib.hpp"
#include "include/chaiscript/extras/math.hpp"
#include "include/chaiscript/extras/string_id.hpp"

#include <iostream>

int main()
{
  auto stdlib = chaiscript::Std_Lib::library();
  auto mathlib = chaiscript::extras::math::bootstrap();
  auto string_idlib = chaiscript::extras::string_id::bootstrap();

  chaiscript::ChaiScript chai(stdlib);
  chai.add(mathlib);
  chai.add(string_idlib);
}
