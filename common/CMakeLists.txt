add_subdirectory(demo)

add_library(LPS25HP STATIC LPS25HP.c)

add_executable(LPS25HPexe main.c)
target_link_libraries (LPS25HPexe LPS25HP)
