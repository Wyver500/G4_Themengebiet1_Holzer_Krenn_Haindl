add_library(Funktionen STATIC Funktionen.c)

add_executable(DEMO main.c)
target_link_libraries (DEMO Funktionen)

#add_subdirectory(demo)