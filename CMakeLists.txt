cmake_minimum_required(VERSION 3.2)
project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.h.in version.h)

add_executable(print_ip print_ip.cpp)

set_target_properties(print_ip PROPERTIES
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
	CMAKE_CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "-std=c++1z")

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mikhail.gorshkov@gmail.com)

include(CPack)
