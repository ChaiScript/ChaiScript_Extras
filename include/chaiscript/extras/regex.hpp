/**
 * @file ChaiScript Regex Support
 *
 * Adds std::regex support to ChaiScript:
 *
 *     regex(string pattern)
 *     regex(string pattern, regex_constants flag)
 *     regex_search(string subject, regex pattern)
 *     regex_search(string subject, regex pattern, smatch results)
 *     regex_match(string subject, regex pattern)
 *     regex_replace(string subject, regex pattern, string replacement)
 *     smatch::size()
 *     smatch[index]
 *     regex_icase()
 */

#ifndef CHAISCRIPT_EXTRAS_REGEX_HPP_
#define CHAISCRIPT_EXTRAS_REGEX_HPP_

#include <regex>
#include <string>
#include <vector>
#include <chaiscript/chaiscript.hpp>

namespace chaiscript {
  namespace extras {
    namespace regex {

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        m->add(user_type<std::regex>(), "regex");
        m->add(user_type<std::smatch>(), "smatch");

        m->add(constructor<std::regex(const std::string &)>(), "regex");
        m->add(constructor<std::regex(const std::string &, std::regex_constants::syntax_option_type)>(), "regex");
        m->add(constructor<std::smatch()>(), "smatch");

        m->add(fun([](){ return std::regex_constants::icase; }), "regex_icase");

        m->add(fun([](const std::string &subject, const std::regex &pattern) {
          return std::regex_search(subject, pattern);
        }), "regex_search");

        m->add(fun([](const std::string &subject, const std::regex &pattern, std::smatch &results) {
          return std::regex_search(subject, results, pattern);
        }), "regex_search");

        m->add(fun([](const std::string &subject, const std::regex &pattern) {
          return std::regex_match(subject, pattern);
        }), "regex_match");

        m->add(fun([](const std::string &subject, const std::regex &pattern, const std::string &replacement) {
          return std::regex_replace(subject, pattern, replacement);
        }), "regex_replace");

        m->add(fun([](const std::smatch &results) {
          return static_cast<int>(results.size());
        }), "size");

        m->add(fun([](const std::smatch &results, int index) {
          return results[index].str();
        }), "[]");

        return m;
      }
    }
  }
}

#endif /* CHAISCRIPT_EXTRAS_REGEX_HPP_ */
