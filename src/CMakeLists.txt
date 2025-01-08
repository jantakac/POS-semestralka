find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main.out)
target_link_libraries(main.out PRIVATE ${CURSES_LIBRARIES} menu)

target_sources(main.out PRIVATE main.c startmenu.c game.c server.c client.c)
target_include_directories(main.out PRIVATE ${CMAKE_SOURCE_DIR}/include)

