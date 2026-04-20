# ChaiScript Extras

User contributed wrappers and modules for [ChaiScript](https://github.com/ChaiScript/ChaiScript).

All modules are header-only and live under `chaiscript::extras`. To use a module,
include its header and add the returned `Module` to your `ChaiScript` engine (or,
for math, register the namespace directly on the engine).

## Modules

| Module | Header | Description |
|---|---|---|
| [Math](#math) | `chaiscript/extras/math.hpp` | Standard C++ `<cmath>` functions, as flat globals or as a `math.*` namespace. |
| [String Methods](#string-methods) | `chaiscript/extras/string_methods.hpp` | Extra string utilities (`replace`, `trim`, `split`, `toLowerCase`, ...). |
| [String ID](#string-id) | `chaiscript/extras/string_id.hpp` | Bindings for [foonathan/string_id](https://github.com/foonathan/string_id) string hashing. |

---

## Math

Wraps the standard C++ `<cmath>` functions for ChaiScript. Two APIs are provided:

1. **`bootstrap()`** — registers the functions as free (global) names such as `cos(x)`.
   Includes `float`, `double`, and `long double` overloads for every function.
2. **`bootstrap_namespace()`** — registers a real `math` namespace on the engine so
   functions can be called as `math.cos(x)`, similar to Lua's `math` library.
   Double-precision only.

Both APIs may be used together; they do not conflict.

### Install

```cpp
#include "chaiscript/extras/math.hpp"
```

### Flat / global usage — `bootstrap()`

```cpp
chaiscript::ChaiScript chai;
auto mathlib = chaiscript::extras::math::bootstrap();
chai.add(mathlib);
```

```chaiscript
var result = cos(0.5)
```

### Namespace usage — `bootstrap_namespace()`

```cpp
chaiscript::ChaiScript chai;
chaiscript::extras::math::bootstrap_namespace(chai);
```

```chaiscript
import("math")
var result = math.cos(0.5)
```

### Available functions

All names below are available in both APIs unless noted. Functions marked **(advanced)**
are compiled in only when `CHAISCRIPT_EXTRAS_MATH_SKIP_ADVANCED` is **not** defined.

| Category | Functions |
|---|---|
| Trigonometric | `cos`, `sin`, `tan`, `acos`, `asin`, `atan`, `atan2` |
| Hyperbolic | `cosh`, `sinh`, `tanh`, `acosh` *(advanced)*, `asinh` *(advanced)*, `atanh` *(advanced)* |
| Exponential / logarithmic | `exp`, `log`, `log10`, `exp2` *(advanced)*, `expm1` *(advanced)*, `ilogb` *(advanced)*, `log1p` *(advanced)*, `log2` *(advanced)*, `logb` *(advanced)* |
| Exponential (flat-only) | `frexp`, `ldexp`, `modf`, `scalbn` *(advanced)*, `scalbln` *(advanced)* |
| Power | `pow`, `sqrt`, `cbrt` *(advanced)*, `hypot` *(advanced)* |
| Error / gamma *(advanced)* | `erf`, `erfc`, `tgamma`, `lgamma` |
| Rounding / remainder | `ceil`, `floor`, `fmod`, `trunc` *(advanced)*, `round` *(advanced)*, `lround` *(advanced)*, `llround` *(advanced)*, `rint` *(advanced)*, `lrint` *(advanced)*, `llrint` *(advanced)*, `nearbyint` *(advanced)*, `remainder` *(advanced)* |
| Rounding (flat-only, advanced) | `remquo` |
| Floating-point manipulation *(advanced)* | `copysign`, `nextafter`, `nexttoward`, `nan` *(flat-only)* |
| Min / max / difference *(advanced)* | `fdim`, `fmax`, `fmin` |
| Absolute value | `abs`, `fabs` *(advanced)*, `fma` *(advanced)* |
| Classification | `isfinite`, `isinf`, `isnan`, `isnormal`, `signbit`, `fpclassify` *(advanced)* |
| Comparison | `isgreater`, `isgreaterequal`, `isless`, `islessequal`, `islessgreater`, `isunordered` |

### Compile options

- `CHAISCRIPT_EXTRAS_MATH_SKIP_ADVANCED` — if defined, skips the functions marked *(advanced)*
  above. Useful for reducing compile time and binary size when only the basics are needed.

---

## String Methods

Adds method-style string utilities to ChaiScript strings.

### Install

```cpp
#include "chaiscript/extras/string_methods.hpp"
```

```cpp
chaiscript::ChaiScript chai;
// split() returns a vector of strings, so register the vector type if you plan to index into it:
chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<std::string>>("StringVector"));
auto stringmethods = chaiscript::extras::string_methods::bootstrap();
chai.add(stringmethods);
```

### Methods

| Method | Description |
|---|---|
| `string::replace(string search, string replace)` | Replace all occurrences of `search` with `replace`. |
| `string::replace(char search, char replace)` | Replace all occurrences of character `search` with `replace`. |
| `string::trim()` | Remove leading and trailing whitespace. |
| `string::trimStart()` | Remove leading whitespace. |
| `string::trimEnd()` | Remove trailing whitespace. |
| `string::split(string token)` | Split on `token`, returning a vector of strings. |
| `string::toLowerCase()` | Return a lowercase copy of the string. |
| `string::toUpperCase()` | Return an uppercase copy of the string. |
| `string::includes(string search)` | Return `true` if `search` occurs in the string. |
| `string::includes(char search)` | Return `true` if character `search` occurs in the string. |

### Usage

```chaiscript
var input = "Hello, World!"
var output = input.replace("Hello", "Goodbye")
// => "Goodbye, World!"

"  padded  ".trim()              // => "padded"
"a,b,c".split(",")[1]            // => "b"
"Hello".toUpperCase()            // => "HELLO"
"Hello World".includes("orld")   // => true
```

---

## String ID

Adds [foonathan/string_id](https://github.com/foonathan/string_id) support to
ChaiScript, exposing `string_id`, `string_info`, `default_database`, and
`basic_database` (when compiled with `FOONATHAN_STRING_ID_DATABASE`).

### Install

```cpp
#include "chaiscript/extras/string_id.hpp"
```

```cpp
chaiscript::ChaiScript chai;
auto string_idlib = chaiscript::extras::string_id::bootstrap();
chai.add(string_idlib);
```

Types registered: `default_database`, `basic_database`, `string_id`, `string_info`.
Operators `==` and `!=` are provided between `string_id` and `hash_type`.

---

## Building and testing

This is a header-only library, so no build is required to use it. To build and run the tests:

```sh
cmake -B build -S .
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Tests live in `tests/` and use [Catch2](https://github.com/catchorg/Catch2).
