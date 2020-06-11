add_executable(demo_fnc_ptr main_fnc_ptr.c)
target_link_libraries (demo_fnc_ptr)

add_executable(demo_person_from_file main_person_from_file.c)
target_link_libraries (demo_person_from_file person list)

add_executable(demo_person main_person.c)
target_link_libraries (demo_person person list)
