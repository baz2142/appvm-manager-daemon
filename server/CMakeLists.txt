add_executable(daemon
    Client.cpp
    Server.cpp
    Listener.cpp
    main.cpp
)

target_link_libraries(daemon PRIVATE common)
