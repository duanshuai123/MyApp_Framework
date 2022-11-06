cmake_minimum_required(VERSION 3.0.0)
project(MyProject_EXE)

include_directories(
  ${FORM_LIB_SOURCE_DIR}
  ${GEOENGINE_LIB_SOURCE_DIR}
  ${LeetCode_LIB_SOURCE_DIR}
)

set(THIRD_PARTY_LIBS
  FORM_LIB
  GEOENGINE_LIB
  LeetCode_LIB
  )

add_executable( MyProject_EXE main.cpp)
target_link_libraries(MyProject_EXE  ${THIRD_PARTY_LIBS})

add_executable(MyProject_Test_Leetcode  test_leetcode.cpp)
target_link_libraries(MyProject_Test_Leetcode  ${THIRD_PARTY_LIBS})


