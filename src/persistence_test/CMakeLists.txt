# interface library for headers only module
add_library(persistence_test INTERFACE)

# modules linking to this library will include following
# directories. two options are provided for installed package
# and for in-tree source build
target_include_directories(persistence_test INTERFACE
    $<INSTALL_INTERFACE:include/persistence_test>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

# libraries this module links to
target_link_libraries(persistence_test INTERFACE belt.pp)

# what to do on make install
install(TARGETS persistence_test
        EXPORT persistence_test.package
        DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_LIBRARY})

set(SRC_FILES
    global.hpp)

install(FILES
    ${SRC_FILES}
    DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_INCLUDE}/persistence_test)

#
# add custom target simply for IDE to show the files
#
add_custom_target(persistence_test.include SOURCES
    ${SRC_FILES})
