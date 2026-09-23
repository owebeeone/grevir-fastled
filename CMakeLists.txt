cmake_minimum_required(VERSION 3.20)
project(grevir_fastled VERSION 0.1.0 LANGUAGES CXX)

if(NOT TARGET grevir::base)
  find_package(grevir-base CONFIG REQUIRED)
endif()

foreach(dependency IN ITEMS core)
  if(NOT TARGET grevir::${dependency})
    find_package(grevir-${dependency} CONFIG REQUIRED)
  endif()
endforeach()

add_library(grevir_fastled INTERFACE)
add_library(grevir::fastled ALIAS grevir_fastled)
set_target_properties(grevir_fastled PROPERTIES EXPORT_NAME fastled)
target_compile_features(grevir_fastled INTERFACE cxx_std_23)
target_link_libraries(grevir_fastled INTERFACE grevir::base grevir::core)
target_include_directories(grevir_fastled INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

include(GNUInstallDirs)
install(TARGETS grevir_fastled EXPORT GrevirFastLEDTargets)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING
  PATTERN "*.hpp" PATTERN "*.h")
install(EXPORT GrevirFastLEDTargets NAMESPACE grevir::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-fastled)
install(FILES cmake/grevir-fastled-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-fastled)
install(FILES LICENSE.txt DESTINATION ${CMAKE_INSTALL_DATADIR}/grevir-fastled)

option(GREVIR_BUILD_COMPILE_CHECKS "Compile native headers and template users" OFF)
option(GREVIR_BUILD_HOST_TESTS "Run deterministic native behavior tests" OFF)
if(GREVIR_BUILD_HOST_TESTS)
  enable_testing()
endif()
if(GREVIR_BUILD_COMPILE_CHECKS OR GREVIR_BUILD_HOST_TESTS)
  add_subdirectory(tests)
endif()
