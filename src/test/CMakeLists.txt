# define the executable
add_executable(test
    main.cpp)

# libraries this module links to
target_link_libraries(test PRIVATE
    persistence_test
    mesh.pp
    systemutility
    belt.pp
    log
    Boost::locale
    )

if(NOT WIN32 AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(test PRIVATE Threads::Threads)
endif()

# what to do on make install
install(TARGETS test
        EXPORT persistence_test.package
        RUNTIME DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_RUNTIME}
        LIBRARY DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_LIBRARY}
        ARCHIVE DESTINATION ${PERSISTENCE_TEST_INSTALL_DESTINATION_ARCHIVE})
