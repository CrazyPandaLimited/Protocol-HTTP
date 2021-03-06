cmake_minimum_required(VERSION 3.0)
project(panda-protocol-http LANGUAGES CXX)

set(LIB_TYPE STATIC)
option(PROTOCOL_HTTP_BUILD_TESTS OFF)
if (${PROTOCOL_HTTP_BUILD_TESTS})
    set(EXCLUDE_TEST)
else()
    set(EXCLUDE_TEST EXCLUDE_FROM_ALL)
endif()

file(GLOB_RECURSE libSource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/panda/*.cc")
add_library(${PROJECT_NAME} ${LIB_TYPE} ${libSource})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
set_source_files_properties(src/panda/protocol/http/CookieParser.cc  PROPERTIES COMPILE_FLAGS "-Wno-implicit-fallthrough -Wno-unused-const-variable")
set_source_files_properties(src/panda/protocol/http/CookieStorage.cc PROPERTIES COMPILE_FLAGS "-Wno-implicit-fallthrough -Wno-unused-const-variable")
set_source_files_properties(src/panda/protocol/http/MessageParser.cc PROPERTIES COMPILE_FLAGS "-Wno-implicit-fallthrough -Wno-unused-const-variable")

find_program(ragel_bin ragel)
if (ragel_bin)
    foreach(fpath src/panda/protocol/http/CookieParser src/panda/protocol/http/CookieStorage src/panda/protocol/http/MessageParser)
        add_custom_command(
            OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/${fpath}.cc
            COMMAND ragel -C -G2 ${fpath}.rl -o ${fpath}.cc
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${fpath}.rl
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endforeach()
endif()

find_package(Boost REQUIRED)
find_package(range-v3 REQUIRED)
find_package(panda-uri REQUIRED)
find_package(panda-date REQUIRED)
find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC panda-uri panda-date ZLIB::ZLIB)

########################tests#######################################
file(GLOB_RECURSE testSource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "tests/*.cc")
list(FILTER testSource EXCLUDE REGEX "tests/main.cc")

add_library(${PROJECT_NAME}-tests STATIC EXCLUDE_FROM_ALL ${testSource})
target_link_libraries(${PROJECT_NAME}-tests PUBLIC ${PROJECT_NAME})

find_package(Catch2)
target_link_libraries(${PROJECT_NAME}-tests PUBLIC Catch2::Catch2)

########################ctests######################################
enable_testing()
add_executable(${PROJECT_NAME}-runtests ${EXCLUDE_TEST} ${testSource} "tests/main.cc")
target_link_libraries(${PROJECT_NAME}-runtests ${PROJECT_NAME}-tests)
add_test(NAME test-all COMMAND ${PROJECT_NAME}-runtests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

########################install#####################################
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets ARCHIVE DESTINATION lib)

install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(FILES ${PROJECT_NAME}-config.cmake DESTINATION lib/cmake/${PROJECT_NAME})
