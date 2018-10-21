# ChaiScript Extras

User contributed wrappers for ChaiScript.

## Modules

- Math: Adds common math methods to ChaiScript.
- String ID: String hashing with [string_id](https://github.com/foonathan/string_id)
- String Methods: Introduces some extra string methods to ChaiScript strings

### Math

The Math module adds some standard math functions to ChaiScript.

#### Install
``` cpp
#include "chaiscript/extras/math.hpp"
```
``` cpp
chaiscript::ChaiScript chai;
auto mathlib = chaiscript::extras::math::bootstrap();
chai.add(mathlib);
```

#### Usage

``` chaiscript
var result = cos(0.5f)
```

### String ID

Adds [String ID](https://github.com/foonathan/string_id) support to ChaiScript.

#### Install

``` cpp
#include "chaiscript/extras/string_id.hpp"
```

``` cpp
auto string_idlib = chaiscript::extras::string_id::bootstrap();
chai.add(string_idlib);
```

### String Methods

Adds various string methods to extend how strings can be used in ChaiScript:
- `string::replace(string, string)`
- `string::trim()`
- `string::split(string)`
- `string::toLowerCase()`
- `string::toUpperCase()`

#### Install

``` cpp
#include "chaiscript/extras/string_methods.hpp"
```

``` cpp
auto stringmethods = chaiscript::extras::string_methods::bootstrap();
chai.add(stringmethods);
```

#### Usage

``` chaiscript
var input = "Hello, World!"
var output = input.replace("Hello", "Goodbye")
// => "Goodbye, World!"
```