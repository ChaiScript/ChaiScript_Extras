set(CHAISCRIPT_VERSION 6.1.0)
find_package(chaiscript ${CHAISCRIPT_VERSION} QUIET)

if (NOT chaiscript_FOUND)
  include(FetchContent)

  # FetchContent_Populate is deprecated in CMake 3.30+, but it still gives us the
  # fine-grained control (EXCLUDE_FROM_ALL on add_subdirectory) we need to keep
  # the upstream `chai` REPL target out of the default build. Opt into the OLD
  # behaviour explicitly.
  if(POLICY CMP0169)
    cmake_policy(SET CMP0169 OLD)
  endif()

  FetchContent_Declare(
    chaiscript
    GIT_REPOSITORY https://github.com/ChaiScript/ChaiScript.git
    GIT_TAG v${CHAISCRIPT_VERSION}
  )

  FetchContent_GetProperties(chaiscript)
  if (NOT chaiscript_POPULATED)
    FetchContent_Populate(chaiscript)

    set(BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_MODULES OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(BUILD_LIBFUZZ_TESTER OFF CACHE BOOL "" FORCE)

    # ChaiScript 6.1.0's root CMakeLists.txt declares
    # cmake_minimum_required(VERSION 2.8), which CMake 4.x refuses. Force a
    # floor so the fetched subproject is accepted.
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

    # EXCLUDE_FROM_ALL keeps ChaiScript's `chai` REPL out of the default build.
    # We only consume ChaiScript's headers here, and its src/main.cpp in 6.1.0
    # does not compile on current MSVC (missing <chrono> include).
    add_subdirectory(${chaiscript_SOURCE_DIR} ${chaiscript_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()
