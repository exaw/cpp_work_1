cmake_minimum_required(VERSION 3.2)

project(helloworld VERSION ${PROJECT_VESRION})

configure_file(version_number.h.in version_number.h)

add_library(version version.cpp)
add_executable(test_version test_version.cpp)

set_target_properties( version test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(version
        PRIVATE "${CMAKE_BINARY_DIR}/src/version"
        )

target_link_libraries(test_version PRIVATE
        version gtest pthread
        )

if (MSVC)
    target_compile_options(version PRIVATE
            /W4
            )
    target_compile_options(test_version PRIVATE
            /W4
            )
else ()
    target_compile_options(version PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

enable_testing()

add_test(test_version test_version)

