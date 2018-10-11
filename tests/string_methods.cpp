#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <string>
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "../include/chaiscript/extras/string_methods.hpp"

#include <iostream>

TEST_CASE( "Math functions work", "[math]" ) {
  auto stringmethods = chaiscript::extras::string_methods::bootstrap();

  chaiscript::ChaiScript chai;
  chai.add(stringmethods);

  CHECK(chai.eval<std::string>("\"   Hello World!    \".trim()") == "Hello World!");
}