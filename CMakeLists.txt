cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build google test" ON)

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME} "main.cpp" "print_ip.h" "generator.h")
#add_library(CustomAllocator_lib "CustomAllocator.h")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

#set_target_properties(print_ip_lib PROPERTIES
#    CXX_STANDARD 20
#    CXX_STANDARD_REQUIRED ON
#)

#target_include_directories(print_ip_lib
#    PRIVATE "${CMAKE_BINARY_DIR}"
#)

#target_link_libraries(${PROJECT_NAME} PRIVATE
#    print_ip_lib
#)

if(WITH_GTEST)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest" "googletest")
    add_executable(test_print_ip "test_print_ip.cpp")

    target_include_directories(test_print_ip PRIVATE
        ${GTEST_INCLUDE_DIRS}
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )

    set_target_properties(test_print_ip PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

#    target_compile_definitions(test_print_ip PRIVATE
#        $<$<CONFIG:Debug>:DEBUG_VER>
#        $<$<CONFIG:Release>:RELEASE_VER>
#    )

    target_link_libraries(test_print_ip PRIVATE
        ${GTEST_BOTH_LIBRARIES}
        gtest
        gtest_main
    )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4 /await
    )
#    target_compile_options(print_ip_lib PRIVATE
#        /W4 /await
#    )
    if(WITH_GTEST)
        target_compile_options(test_print_ip PRIVATE
            /W4 /await
        )
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE
        "-Wall" "-Wextra" "-Werror" "-pedantic" "-fcoroutines"
    )
#    target_compile_options(print_ip_lib PRIVATE
#        "-Wall" "-Wextra" "-Werror" "-pedantic" "-fcoroutines"
#    )
    if(WITH_GTEST)
        target_compile_options(test_print_ip PRIVATE
            "-Wall" "-Wextra" "-Werror" "-pedantic" "-fcoroutines"
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT divmy@yandex.ru)
include(CPack)

if(WITH_GTEST)
    include(CTest)
    enable_testing()
    add_test(test_print_ip test_print_ip)
endif()
