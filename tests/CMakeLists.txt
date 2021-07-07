
macro(add_compilation_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} cutempl)
endmacro()

add_compilation_test(test_at)
add_compilation_test(test_compose)
add_compilation_test(test_conjunction_of)
add_compilation_test(test_curry)
add_compilation_test(test_find_if)
add_compilation_test(test_game_of_life)
add_compilation_test(test_negation_of)
add_compilation_test(test_reverse)
add_compilation_test(test_set_insert)
add_compilation_test(test_sort)
add_compilation_test(test_zip)

