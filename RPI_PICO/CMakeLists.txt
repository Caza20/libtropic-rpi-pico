###########################################################################
#                                                                         #
#   Rpi Pico Config                                                       #
#                                                                         #
###########################################################################

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)

###########################################################################
#                                                                         #
#   Paths and setup                                                       #
#                                                                         #
###########################################################################

# Path to libtropic (added as a submodule)
set(PATH_TO_LIBTROPIC "../libtropic")

# Import pico-sdk
include(pico_sdk_import.cmake)

if (NOT DEFINED LT_BUILD_EXAMPLES AND NOT DEFINED LT_BUILD_TESTS)
    message(FATAL_ERROR "Please define -DLT_BUILD_EXAMPLES=1 to build examples (and also select required example) or -DLT_BUILD_TESTS=1 to build tests. See docs. Nothing to do now, bye!")
endif()

###########################################################################
#                                                                         #
#   Define project's name                                                 #
#                                                                         #
###########################################################################

project(libtropic-rpi-pico C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

###########################################################################
#                                                                         #
#   Sources                                                               #
#                                                                         #
###########################################################################

# Specify other source files
set(SOURCES
    src/main.c
    ${PATH_TO_LIBTROPIC}/hal/port/rpi_pico/lt_port_rpi_pico.c
)

set(HEADERS
    inc/main.h
)

###########################################################################
#                                                                         #
#   Add libtropic                                                         #
#                                                                         #
###########################################################################

# Libtropic related setup, use trezor crypto library for host side cryptography
set(LT_USE_TREZOR_CRYPTO ON)

# libtropic
add_subdirectory(${PATH_TO_LIBTROPIC} "libtropic")

###########################################################################
#                                                                         #
#   EXAMPLES CONFIGURATION                                                #
#                                                                         #
###########################################################################

if (LT_BUILD_EXAMPLES)
    # So we can include preprocessed example registry (lt_ex_registry.c.inc).
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/libtropic)

    # Loop through examples defined in libtropic and prepare environment.
    foreach(example_name IN LISTS LIBTROPIC_EXAMPLE_LIST)
        # Create a correct macro from example name.
        string(TOUPPER ${example_name} example_macro)
        string(REPLACE " " "_" example_macro ${example_macro})

        set(exe_name ${example_name})

        # Define executable (separate for each example) and link dependencies.
        add_executable(${exe_name}
            ${SOURCES}
            ${HEADERS}
        )

        target_include_directories(${exe_name} PRIVATE
            inc/
            ${PATH_TO_LIBTROPIC}/include
            ${PATH_TO_LIBTROPIC}/hal/port/rpi_pico
        )

        # Pico-sdk libraries
        target_link_libraries(${exe_name}
            pico_stdlib
            pico_rand
            hardware_adc
            hardware_spi
            hardware_uart
            hardware_gpio
            tropic
        )

        # Warnings configs
        target_compile_options(${exe_name} PRIVATE
            -Wall
            -Wextra
            -Werror
            -Wno-error=unused-variable
            -Wno-error=unused-parameter
            -Wno-error=missing-prototypes
        )


        # Enable example registry using LT_BUILD_EXAMPLES and choose correct example for the binary.
        target_compile_definitions(${exe_name} PRIVATE  LT_BUILD_EXAMPLES)
        target_compile_definitions(${exe_name} PRIVATE  ${example_macro})

        pico_enable_stdio_usb(${exe_name} 1)
        pico_enable_stdio_uart(${exe_name} 0)
        pico_add_extra_outputs(${exe_name})

    endforeach()
endif()

###########################################################################
#                                                                         #
# FUNCTIONAL TESTS CONFIGURATION                                          #
#                                                                         #
# This section will automatically configure CTest for launching tests     #
# defined in libtropic. Do NOT hardcode any test definitions here.        #
# Define them in libtropic.                                               #
#                                                                         #
# To build functional tests, use -DLT_BUILD_TESTS=1 in cmake invocation.  #
#                                                                         #
###########################################################################

# if (LT_BUILD_TESTS)
#      # Enable CTest.
#     enable_testing()

#     # So we can include preprocessed test registry (lt_test_registry.c.inc).
#     include_directories(${CMAKE_CURRENT_BINARY_DIR}/libtropic)

#     # Loop through tests defined in libtropic and prepare environment.
#     foreach(test_name IN LISTS LIBTROPIC_TEST_LIST)

#         # Create a correct macro from test name.
#         string(TOUPPER ${test_name} test_macro)
#         string(REPLACE " " "_" test_macro ${test_macro})

#         set(exe_name ${test_name})

#         # Define executable (separate for each test) and link dependencies.
#         add_executable(${exe_name}
#             ${SOURCES}
#             ${HEADERS}
#             ${PATH_TO_LIBTROPIC}/tests/functional/${test_name}.c
#             ${PATH_TO_LIBTROPIC}/hal/port/rpi_pico/lt_port_rpi_pico.c
#         )

#         target_include_directories(${exe_name} PRIVATE
#             Inc/
#             ${PATH_TO_LIBTROPIC}/include
#             ${PATH_TO_LIBTROPIC}/hal/port/rpi_pico
#         )

#         # Pico-sdk libraries
#         target_link_libraries(${exe_name}
#             pico_stdlib
#             pico_rand
#             hardware_adc
#             hardware_spi
#             hardware_uart
#             hardware_gpio
#             tropic
#         )

#         # Warnings configs
#         target_compile_options(${exe_name} PRIVATE
#             -Wall
#             -Wextra
#             -Werror
#             -Wno-error=unused-variable
#             -Wno-error=unused-parameter
#             -Wno-error=missing-prototypes
#         )


#         # Enable test registry using LT_BUILD_TESTS and choose correct test for the binary.
#         target_compile_definitions(${exe_name} PRIVATE  LT_BUILD_TESTS)
#         target_compile_definitions(${exe_name} PRIVATE  ${test_macro})

#         # Used for testing. Do not use it on when running on standalone Nucleo board
#         if (LT_TESTING_RIG)
#             target_compile_definitions(${exe_name} PRIVATE LT_TESTING_RIG)
#         endif()

#         # Add CTest entry.
#         add_test(NAME ${test_name}
#                 COMMAND python3 -m lt_test_runner PICO_BOARD ${CMAKE_CURRENT_BINARY_DIR}/${exe_name}
#         )
#         # Correctly define Python module path, so we can call lt_test_runner.
#         get_filename_component(ABSOLUTE_PATH_TO_LIBTROPIC ${PATH_TO_LIBTROPIC} ABSOLUTE)
#         set_tests_properties(${test_name} PROPERTIES
#             ENVIRONMENT "PYTHONPATH=${ABSOLUTE_PATH_TO_LIBTROPIC}/scripts/test_runner"
#         )

#         pico_enable_stdio_usb(${exe_name} 1)
#         pico_enable_stdio_uart(${exe_name} 0)
#         pico_add_extra_outputs(${exe_name})

#     endforeach()
# endif()









