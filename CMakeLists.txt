cmake_minimum_required(VERSION 2.8)
project(chaiscript_extras)

if(BIICODE)
  include("biicode.cmake")
  RETURN()
endif()

# MINGW does not yet support C++11's concurrency features
if(MINGW)
  option(MULTITHREAD_SUPPORT_ENABLED "Multithreaded Support Enabled" FALSE)
else()
  option(MULTITHREAD_SUPPORT_ENABLED "Multithreaded Support Enabled" TRUE)
endif()



if(CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable Coverage Reporting in GCC" FALSE)

  if(ENABLE_COVERAGE)
    add_definitions(--coverage -O0)
    set(LINKER_FLAGS "${LINKER_FLAGS} --coverage")
  endif()
endif()

if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  option(ENABLE_THREAD_SANITIZER "Enable thread sanitizer testing in gcc/clang" FALSE)
  if(ENABLE_THREAD_SANITIZER)
    add_definitions(-fsanitize=thread -g)
    set(LINKER_FLAGS "${LINKER_FLAGS} -fsanitize=thread")
  endif()

  option(ENABLE_ADDRESS_SANITIZER "Enable address sanitizer testing in gcc/clang" FALSE)
  if(ENABLE_ADDRESS_SANITIZER)
    add_definitions(-fsanitize=address -g)
    set(LINKER_FLAGS "${LINKER_FLAGS} -fsanitize=address")
  endif()

  option(ENABLE_MEMORY_SANITIZER "Enable memory sanitizer testing in gcc/clang" FALSE)
  if(ENABLE_MEMORY_SANITIZER)
    add_definitions(-fsanitize=memory -g)
    set(LINKER_FLAGS "${LINKER_FLAGS} -fsanitize=memory")
  endif()

  option(ENABLE_UNDEFINED_SANITIZER "Enable undefined behavior sanitizer testing in gcc/clang" FALSE)
  if(ENABLE_UNDEFINED_SANITIZER)
    add_definitions(-fsanitize=undefined -g)
    set(LINKER_FLAGS "${LINKER_FLAGS} -fsanitize=undefined")
  endif()

  option(ENABLE_LTO "Enable Link Time Optimization" FALSE)

  if (ENABLE_LTO)
    add_definitions(-flto)
    set(LINKER_FLAGS "${LINKER_FLAGS} -flto")
  endif()

  option(PROFILE_GENERATE "Generate profile data" FALSE)
  if (PROFILE_GENERATE)
    add_definitions(-fprofile-generate)
    set(LINKER_FLAGS "${LINKER_FLAGS} -fprofile-generate")
  endif()

  option(PROFILE_USE "Use profile data" FALSE)
  if (PROFILE_USE)
    add_definitions(-fprofile-use)
    set(LINKER_FLAGS "${LINKER_FLAGS} -fprofile-use")
  endif()


endif()


include(CTest)
enable_testing()



if(CMAKE_COMPILER_IS_GNUCC)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

  if(GCC_VERSION VERSION_LESS 4.8)
    set(CPP11_FLAG "-std=c++0x")
  else()
    set(CPP11_FLAG "-std=c++11")
  endif()
else()
  set(CPP11_FLAG "-std=c++11")
endif()

if(MSVC)
  add_definitions(/W4 /w44640)
  add_definitions(/bigobj)
  # Note on MSVC compiler flags.
  # The code base selective disables warnings as necessary when the compiler is complaining too much
  # about something that is perfectly valid, or there is simply no technical way around it
  # This particular warning, C4503 is in regards to the decorated names that MSVC generates internally.
  # The error did not come up until the move to C++11, but the compiler doesn't give enough information
  # to determine where the error is coming from, and the internet provides no real information for
  # how to workaround or fix the error. So I'm disabling it globally.
  add_definitions(/wd4503)
else()
  add_definitions(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual  -pedantic ${CPP11_FLAG})

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Weverything -Wno-c++98-compat -Wno-documentation -Wno-switch-enum -Wno-weak-vtables -Wno-sign-conversion -Wno-missing-prototypes -Wno-padded -Wno-missing-noreturn)
  else()
    add_definitions(-Wnoexcept)
  endif()

  if(APPLE)
    add_definitions(-Wno-sign-compare)
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  option(USE_LIBCXX "Use clang's libcxx" TRUE)

  if(USE_LIBCXX)
    add_definitions(-stdlib=libc++)
    set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG} -stdlib=libc++")
  else()
    set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG}")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC)
  set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG}")
endif()

# limitations in MinGW require us to make an optimized build
# for the sake of object sizes or something
if(MINGW OR CYGWIN)
  add_definitions(-O3)
endif()


if(NOT MULTITHREAD_SUPPORT_ENABLED)
  add_definitions(-DCHAISCRIPT_NO_THREADS)
endif()

if(CMAKE_HOST_UNIX)
  if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Haiku")
    list(APPEND LIBS "dl")
  endif()

  if(MULTITHREAD_SUPPORT_ENABLED)
    if(CMAKE_COMPILER_IS_GNUCC)
      execute_process(COMMAND ${CMAKE_C_COMPILER} --version OUTPUT_VARIABLE GCC_FULL_VERSION)
      if(GCC_FULL_VERSION MATCHES "4.8.1.*ubuntu")
        set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--no-as-needed -pthread")
      else()
        set(LINKER_FLAGS "${LINKER_FLAGS} -pthread")
      endif()
    else()
      set(LINKER_FLAGS "${LINKER_FLAGS} -pthread")
    endif()

    add_definitions(-pthread)
  endif()

endif()

list(APPEND LIBS ${READLINE_LIB})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")





set(CHAISCRIPT_BRANCH master)

file(DOWNLOAD https://github.com/ChaiScript/ChaiScript/archive/${CHAISCRIPT_BRANCH}.tar.gz "${CMAKE_BINARY_DIR}/chaiscript/chaiscript-${CHAISCRIPT_BRANCH}.tar.gz"
  INACTIVITY_TIMEOUT 180 TIMEOUT 180 TLS_VERIFY off)

execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf "${CMAKE_BINARY_DIR}/chaiscript/chaiscript-${CHAISCRIPT_BRANCH}.tar.gz" "${CMAKE_BINARY_DIR}/chaiscript"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/chaiscript")

include_directories("${CMAKE_BINARY_DIR}/chaiscript/ChaiScript-${CHAISCRIPT_BRANCH}/include")


# Add catch tests macro
macro(ADD_CATCH_TESTS executable)
  if (MSVC)
    file(TO_NATIVE_PATH "${QT_LIBRARY_DIR}" QT_LIB_PATH)
    set(NEWPATH "${QT_LIB_PATH};$ENV{PATH}")
  else()
    set(NEWPATH $ENV{PATH})
  endif()

  get_target_property(target_files ${executable} SOURCES)

  message("Files: ${target_files}")

  foreach(source ${target_files})
    if(NOT "${source}" MATCHES "/moc_.*cxx")
      string(REGEX MATCH .*cpp source "${source}")
      if(source)
        file(READ "${source}" contents)
        string(REGEX MATCHALL "TEST_CASE\\([ ]*\"[^\"]+\"" found_tests ${contents})
        foreach(hit ${found_tests})
          message("Found Test: ${hit}")
          string(REGEX REPLACE "TEST_CASE\\([ ]*(\"[^\"]+\").*" "\\1" test_name ${hit})
          add_test(${test_name} "${executable}" ${test_name})
          set_tests_properties(${test_name} PROPERTIES TIMEOUT 660 ENVIRONMENT "PATH=${NEWPATH}")
        endforeach()
      endif()
    endif()
  endforeach()
endmacro()



add_executable(math_test tests/math.cpp)
target_link_libraries(math_test ${LIBS})
ADD_CATCH_TESTS(math_test)


