find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main.out)
target_link_libraries(main.out PRIVATE ${CURSES_LIBRARIES})

target_sources(main.out PRIVATE main.c menu.c)
target_include_directories(main.out PRIVATE ${CMAKE_SOURCE_DIR}/include)
