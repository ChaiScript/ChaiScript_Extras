#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <string>
#include <vector>
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "../include/chaiscript/extras/regex.hpp"

TEST_CASE( "regex functions work", "[regex]" ) {
  // Create the ChaiScript environment with stdlib available.
  auto stdlib = chaiscript::Std_Lib::library();
  chaiscript::ChaiScript chai(stdlib);

  // Add the regex module.
  auto regexlib = chaiscript::extras::regex::bootstrap();
  chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<std::string>>("StringVector"));
  chai.add(regexlib);

  // regex_search - match anywhere in string
  CHECK(chai.eval<bool>("regex_search(\"Hello World 123\", regex(\"[0-9]+\"))") == true);
  CHECK(chai.eval<bool>("regex_search(\"Hello World\", regex(\"[0-9]+\"))") == false);

  // regex_match - match entire string
  CHECK(chai.eval<bool>("regex_match(\"123\", regex(\"[0-9]+\"))") == true);
  CHECK(chai.eval<bool>("regex_match(\"Hello 123\", regex(\"[0-9]+\"))") == false);

  // regex_replace
  CHECK(chai.eval<std::string>("regex_replace(\"Hello World 123\", regex(\"[0-9]+\"), \"456\")") == "Hello World 456");
  CHECK(chai.eval<std::string>("regex_replace(\"abc 123 def 456\", regex(\"[0-9]+\"), \"NUM\")") == "abc NUM def NUM");

  // smatch - capture groups via regex_search
  CHECK(chai.eval<std::string>(R"chai(
    var m = smatch()
    regex_search("Hello 123 World", regex("([0-9]+)"), m)
    m[0]
  )chai") == "123");

  CHECK(chai.eval<std::string>(R"chai(
    var m2 = smatch()
    regex_search("2024-01-15", regex("([0-9]{4})-([0-9]{2})-([0-9]{2})"), m2)
    m2[1]
  )chai") == "2024");

  CHECK(chai.eval<std::string>(R"chai(
    var m3 = smatch()
    regex_search("2024-01-15", regex("([0-9]{4})-([0-9]{2})-([0-9]{2})"), m3)
    m3[2]
  )chai") == "01");

  // smatch size
  CHECK(chai.eval<int>(R"chai(
    var m4 = smatch()
    regex_search("2024-01-15", regex("([0-9]{4})-([0-9]{2})-([0-9]{2})"), m4)
    m4.size()
  )chai") == 4);

  // regex with flags - icase
  CHECK(chai.eval<bool>("regex_search(\"HELLO\", regex(\"hello\", regex_icase()))") == true);
  CHECK(chai.eval<bool>("regex_search(\"HELLO\", regex(\"hello\"))") == false);
}
