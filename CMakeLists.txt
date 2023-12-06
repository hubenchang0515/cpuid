cmake_minimum_required(VERSION 3.0)
project(cpuid)

add_compile_options(-W -Wall -Wextra)

set(PROJECT_LIB_TARGET ${PROJECT_NAME}_LIB)
set(PROJECT_EXE_TARGET ${PROJECT_NAME}_EXE)

# LIB
aux_source_directory(src SOURCES)
add_library(${PROJECT_LIB_TARGET} STATIC src/cpuid.c)
set_target_properties(${PROJECT_LIB_TARGET}
                        PROPERTIES
                        OUTPUT_NAME         ${PROJECT_NAME}
                        C_STANDARD          99
                        PUBLIC_HEADER       src/cpuid.h)

# EXE
add_executable(${PROJECT_EXE_TARGET} src/main.c)
set_target_properties(${PROJECT_EXE_TARGET}
                        PROPERTIES
                        OUTPUT_NAME         ${PROJECT_NAME}
                        C_STANDARD          99
                        LINK_LIBRARIES      ${PROJECT_LIB_TARGET})

# INSTALL
install(TARGETS ${PROJECT_LIB_TARGET} ${PROJECT_EXE_TARGET}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})