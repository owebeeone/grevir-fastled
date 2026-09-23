if(NOT COMMAND catch_discover_tests)
  find_package(grevir-test-support CONFIG REQUIRED)
endif()
if(NOT TARGET grevir::peripherals)
  find_package(grevir-peripherals CONFIG REQUIRED)
endif()
add_executable(grevir_fastled_runtime fastled_test.cpp)
target_link_libraries(grevir_fastled_runtime PRIVATE
  grevir::fastled grevir::peripherals Catch2::Catch2WithMain)
target_compile_definitions(grevir_fastled_runtime PRIVATE GREVIR_FASTLED_HOST_MOCK)
set_target_properties(grevir_fastled_runtime PROPERTIES CXX_EXTENSIONS OFF)
catch_discover_tests(grevir_fastled_runtime TEST_PREFIX "fastled."
  PROPERTIES LABELS "fastled" TIMEOUT 10)
