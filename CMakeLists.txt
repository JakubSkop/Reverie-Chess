cmake_minimum_required(VERSION 3.25.0)
project(SFML_GUI3 VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 20)

include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES} main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(SFML_DIR "SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES True)

find_package(SFML 2.5.1 COMPONENTS network audio graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
install(TARGETS ${PROJECT_NAME})


add_executable(MyTests ${TEST_FILES} ${SRC_FILES})
target_link_libraries(MyTests GTest::gtest_main sfml-network sfml-audio sfml-graphics sfml-window sfml-system)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(GoogleTest)
gtest_discover_tests(MyTests)
