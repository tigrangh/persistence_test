if( WIN32 )
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_RUNTIME bin)
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_LIBRARY lib)
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_ARCHIVE lib)
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_INCLUDE include)
else( WIN32 )
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_RUNTIME bin/persistence_test)
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_LIBRARY lib/persistence_test)
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_ARCHIVE lib/persistence_test)
    SET(PERSISTENCE_TEST_INSTALL_DESTINATION_INCLUDE include/persistence_test)
endif( WIN32 )

if( NOT WIN32 )
    # don't skip the full RPATH for the build tree
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

    # when building, don't use the install RPATH already
    # (but later on when installing)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/persistence_test;${CMAKE_INSTALL_PREFIX}/lib/belt.pp;${CMAKE_INSTALL_PREFIX}/lib/mesh.pp")

endif()

include(cmake_utility/utility.cmake)

if(NOT TARGET belt.pp)
add_subdirectory(belt.pp)
endif()
if(NOT TARGET mesh.pp)
add_subdirectory(mesh.pp)
endif()
# find_package(belt.pp)
# find_package(mesh.pp)

add_subdirectory(persistence_test)
add_subdirectory(test)

# following is used for find_package functionality
install(FILES persistence_test-config.cmake DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_LIBRARY})
install(EXPORT persistence_test.package NAMESPACE persistence_test:: DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_LIBRARY})
