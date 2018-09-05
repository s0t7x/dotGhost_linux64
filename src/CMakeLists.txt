if (NVCtrlLib_FOUND)
    set (USE_NVIDIA 1)
endif()

configure_file(defines.h.in defines.h @ONLY)

add_executable(dotghost
    utils/_thread.cpp
    dotglow.cpp
    utils/centitylist.cpp
    helper.cpp
    config.cpp
    engine.cpp
    main.cpp
    offsets.cpp
    process.cpp
)


target_link_libraries(dotghost
    ${X11_LIBRARIES}
    ${X11_XTest_LIB}
    ${NVCtrlLib_LIBRARY}
    Threads::Threads
)

target_include_directories(dotghost PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${NVCtrlLib_INCLUDE_DIR}
)
set_property(TARGET dotghost PROPERTY CXX_STANDARD 11)