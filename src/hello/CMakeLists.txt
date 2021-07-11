cmake_minimum_required(VERSION 3.2)
project(helloworld VERSION ${PROJECT_VESRION})

add_executable(helloworld_cli main.cpp)

set_target_properties(helloworld_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld_cli
        PRIVATE "${CMAKE_SOURCE_DIR}/src/version"
        )

target_link_libraries(helloworld_cli PRIVATE
    version
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)


