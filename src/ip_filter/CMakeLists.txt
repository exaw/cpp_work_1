cmake_minimum_required(VERSION 3.2)
# 
project(helloworld VERSION ${PROJECT_VESRION})

add_executable(ip_filter ip_filter.cpp main.cpp)
add_executable(ip_filter_test ip_filter.cpp ip_filter_test.cpp)

set_target_properties(ip_filter ip_filter_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
        PRIVATE "${CMAKE_SOURCE_DIR}/src/version"
        )

target_link_libraries(ip_filter
        version
        )

target_link_libraries(ip_filter_test
    gtest pthread
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_test PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

add_test(test ip_filter_test)
