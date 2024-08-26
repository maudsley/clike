#include "test_common.h"

TEST(test_basic, return_constant) {
  BasicTestInterpreter app("test_001.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, return_simple_expression) {
  BasicTestInterpreter app("test_002.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, constant_assignment) {
  BasicTestInterpreter app("test_003.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, chained_assignment) {
  BasicTestInterpreter app("test_004.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(456, ret);
}

TEST(test_basic, chained_initialization) {
  BasicTestInterpreter app("test_005.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, unary_postfix_plus_pre) {
  BasicTestInterpreter app("test_006.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(122, ret);
}

TEST(test_basic, unary_postfix_plus_post) {
  BasicTestInterpreter app("test_007.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, struct_declaration) {
  BasicTestInterpreter app("test_008.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, struct_definition) {
  BasicTestInterpreter app("test_009.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, declaration_default_initialization) {
  BasicTestInterpreter app("test_010.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, array_declaration) {
  BasicTestInterpreter app("test_011.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, struct_with_array_declaration) {
  BasicTestInterpreter app("test_012.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, array_read_write) {
  BasicTestInterpreter app("test_013.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(456, ret);
}

TEST(test_basic, multi_dimensional_array_read_write) {
  BasicTestInterpreter app("test_014.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(789, ret);
}

TEST(test_basic, struct_usage) {
  BasicTestInterpreter app("test_015.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, struct_with_array) {
  BasicTestInterpreter app("test_016.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(456, ret);
}

TEST(test_basic, array_of_structs) {
  BasicTestInterpreter app("test_017.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(789, ret);
}

TEST(test_basic, nested_struct_usage) {
  BasicTestInterpreter app("test_018.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, function_calls) {
  BasicTestInterpreter app("test_019.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, function_call_with_arguments) {
  BasicTestInterpreter app("test_020.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(8, ret);
}

TEST(test_basic, minimal_for_loop) {
  BasicTestInterpreter app("test_021.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, nested_struct_with_multi_dimensional_array) {
  BasicTestInterpreter app("test_022.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, external_type_access) {
  BasicTestInterpreter app("test_023.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(234, ret);
}

TEST(test_basic, nested_external_type_access) {
  BasicTestInterpreter app("test_024.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(111, ret);
}

TEST(test_basic, structs_arrays_with_external_types) {
  BasicTestInterpreter app("test_025.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, struct_assignment) {
  BasicTestInterpreter app("test_026.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, nested_struct_assignment_with_arrays) {
  BasicTestInterpreter app("test_027.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(111, ret);
}

TEST(test_basic, function_return_var_name_conflict) {
  BasicTestInterpreter app("test_028.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, chained_struct_assignment) {
  BasicTestInterpreter app("test_029.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, function_return_struct_name_conflict) {
  BasicTestInterpreter app("test_030.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(222, ret);
}

TEST(test_basic, array_assignment) {
  BasicTestInterpreter app("test_031.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(333, ret);
}

TEST(test_basic, return_struct_scalar_access) {
  BasicTestInterpreter app("test_032.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, return_struct_array_access) {
  BasicTestInterpreter app("test_033.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(234, ret);
}

TEST(test_basic, pass_struct_as_argument) {
  BasicTestInterpreter app("test_034.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, pass_array_as_argument) {
  BasicTestInterpreter app("test_035.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(789, ret);
}

TEST(test_basic, array_access_of_temporary) {
  BasicTestInterpreter app("test_036.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, struct_access_of_temporary) {
  BasicTestInterpreter app("test_037.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, constant_loop_iteration) {
  BasicTestInterpreter app("test_038.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(20, ret);
}

TEST(test_basic, data_dependent_array_access) {
  BasicTestInterpreter app("test_039.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(234, ret);
}

TEST(test_basic, data_dependent_array_access_self_assignment) {
  BasicTestInterpreter app("test_040.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(345, ret);
}

TEST(test_basic, if_statement_executed) {
  BasicTestInterpreter app("test_041.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, if_statement_not_executed) {
  BasicTestInterpreter app("test_042.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, if_statement_else_not_executed) {
  BasicTestInterpreter app("test_043.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, if_statement_else_executed) {
  BasicTestInterpreter app("test_044.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, if_statement_scope) {
  BasicTestInterpreter app("test_045.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, if_else_statement_scope) {
  BasicTestInterpreter app("test_046.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, if_statement_scope_copy) {
  BasicTestInterpreter app("test_047.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, elseif_not_executed) {
  BasicTestInterpreter app("test_048.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, elseif_else_executed) {
  BasicTestInterpreter app("test_049.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, elseif_executed) {
  BasicTestInterpreter app("test_050.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, nested_ifeslse_executed) {
  BasicTestInterpreter app("test_051.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, nested_ifeslse_not_executed) {
  BasicTestInterpreter app("test_052.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, loop_with_arithmetic) {
  BasicTestInterpreter app("test_053.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(812339799, ret);
}

TEST(test_basic, unary_minus) {
  BasicTestInterpreter app("test_054.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xffffffffffffffff, ret);
}

TEST(test_basic, inline_declaration) {
  BasicTestInterpreter app("test_055.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, inline_array_declaration) {
  BasicTestInterpreter app("test_056.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, for_loop_initializer) {
  BasicTestInterpreter app("test_057.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(20, ret);
}

TEST(test_basic, multiple_inline_declarations) {
  BasicTestInterpreter app("test_058.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, scope_with_var) {
  BasicTestInterpreter app("test_059.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, return_from_branch_during_loop) {
  BasicTestInterpreter app("test_060.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, loop_break) {
  BasicTestInterpreter app("test_061.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, loop_continue) {
  BasicTestInterpreter app("test_062.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, nested_loop) {
  BasicTestInterpreter app("test_063.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(9, ret);
}

TEST(test_basic, return_from_loop) {
  BasicTestInterpreter app("test_064.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, return_from_nested_loop) {
  BasicTestInterpreter app("test_065.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, break_from_nested_loop) {
  BasicTestInterpreter app("test_066.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(7, ret);
}

TEST(test_basic, continue_in_nested_loop) {
  BasicTestInterpreter app("test_067.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(8, ret);
}

TEST(test_basic, return_struct_from_nested_loop) {
  BasicTestInterpreter app("test_068.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, array_initialization_loop) {
  BasicTestInterpreter app("test_069.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, uint64_construction) {
  BasicTestInterpreter app("test_070.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, int8_to_uint64_construction) {
  BasicTestInterpreter app("test_071.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, implicit_int8_to_int64_assignment) {
  BasicTestInterpreter app("test_072.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, signed_integer_addition) {
  BasicTestInterpreter app("test_073.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, integer_cast_during_addition) {
  BasicTestInterpreter app("test_074.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, external_vector_constructor) {
  BasicTestInterpreter app("test_075.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(234, ret);
}

TEST(test_basic, external_matrix_constructor) {
  BasicTestInterpreter app("test_076.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, matrix_vector_construction_from_var) {
  BasicTestInterpreter app("test_077.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(111, ret);
}

TEST(test_basic, return_dynamic_matrix) {
  BasicTestInterpreter app("test_078.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, call_function_with_array) {
  BasicTestInterpreter app("test_079.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, initializer_list) {
  BasicTestInterpreter app("test_080.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, initializer_list_2d) {
  BasicTestInterpreter app("test_081.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, initializer_list_3d) {
  BasicTestInterpreter app("test_082.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, array_assignment_after_initialization) {
  BasicTestInterpreter app("test_083.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(11, ret);
}

TEST(test_basic, array_of_structs_assignment) {
  BasicTestInterpreter app("test_084.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, break_statement_without_scope) {
  BasicTestInterpreter app("test_085.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, break_from_scope_within_for_loop) {
  BasicTestInterpreter app("test_086.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, if_statement_without_scope) {
  BasicTestInterpreter app("test_087.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, if_else_statement_without_scope) {
  BasicTestInterpreter app("test_088.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, switch_without_scope) {
  BasicTestInterpreter app("test_089.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(4));
}

TEST(test_basic, switch_without_default) {
  BasicTestInterpreter app("test_090.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(4));
}

TEST(test_basic, switch_default_only) {
  BasicTestInterpreter app("test_091.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, switch_default_and_one_case) {
  BasicTestInterpreter app("test_092.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, switch_execute_first_case_break) {
  BasicTestInterpreter app("test_093.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, switch_execute_first_case_fallthrough) {
  BasicTestInterpreter app("test_094.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, switch_case_with_scope) {
  BasicTestInterpreter app("test_095.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, switch_prevent_declaration) {
  BasicTestInterpreter app("test_096.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(6));
}

TEST(test_basic, switch_multiple_statements) {
  BasicTestInterpreter app("test_097.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, while_loop) {
  BasicTestInterpreter app("test_098.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, do_while_loop) {
  BasicTestInterpreter app("test_099.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, for_no_init_no_cond_no_inc) {
  BasicTestInterpreter app("test_100.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, for_no_cond_no_inc) {
  BasicTestInterpreter app("test_101.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, for_no_init_no_inc) {
  BasicTestInterpreter app("test_102.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, no_inc) {
  BasicTestInterpreter app("test_103.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, for_no_init_no_cond) {
  BasicTestInterpreter app("test_104.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, for_no_cond) {
  BasicTestInterpreter app("test_105.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, for_no_init) {
  BasicTestInterpreter app("test_106.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, ternary_false) {
  BasicTestInterpreter app("test_107.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(456, ret);
}

TEST(test_basic, ternary_true) {
  BasicTestInterpreter app("test_108.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, ternary_true_not_evaluated) {
  BasicTestInterpreter app("test_109.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, ternary_true_evaluated) {
  BasicTestInterpreter app("test_110.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(124, ret);
}

TEST(test_basic, ternary_false_not_evaluated) {
  BasicTestInterpreter app("test_111.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(456, ret);
}

TEST(test_basic, ternary_false_evaluated) {
  BasicTestInterpreter app("test_112.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(457, ret);
}

TEST(test_basic, ternary_bad_condition) {
  BasicTestInterpreter app("test_113.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(9));
}

TEST(test_basic, ternary_bad_types) {
  BasicTestInterpreter app("test_114.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(5));
}

TEST(test_basic, ternary_result_type) {
  BasicTestInterpreter app("test_115.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(5));
}

TEST(test_basic, ternary_with_function_call) {
  BasicTestInterpreter app("test_116.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, ternary_nested_ternary) {
  BasicTestInterpreter app("test_117.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, bad_if_condition_type) {
  BasicTestInterpreter app("test_118.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, bad_switch_expression_type) {
  BasicTestInterpreter app("test_119.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, bad_array_index_type) {
  BasicTestInterpreter app("test_120.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, bad_for_condition) {
  BasicTestInterpreter app("test_121.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(7));
}

TEST(test_basic, bad_while_condition) {
  BasicTestInterpreter app("test_122.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(7));
}

TEST(test_basic, bad_do_while_condition) {
  BasicTestInterpreter app("test_123.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, binary_operator_on_struct) {
  BasicTestInterpreter app("test_124.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, binary_operator_on_struct_and_int) {
  BasicTestInterpreter app("test_125.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_false_or_false) {
  BasicTestInterpreter app("test_126.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, logical_true_or_false) {
  BasicTestInterpreter app("test_127.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, logical_false_or_true) {
  BasicTestInterpreter app("test_128.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, logical_true_or_true) {
  BasicTestInterpreter app("test_129.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, logical_or_short_circuit) {
  BasicTestInterpreter app("test_130.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, logical_or_evaluation_order) {
  BasicTestInterpreter app("test_131.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, logical_or_branch) {
  BasicTestInterpreter app("test_132.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, logical_or_type_promotion) {
  BasicTestInterpreter app("test_133.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, logical_or_require_cast) {
  BasicTestInterpreter app("test_134.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(4));
}

TEST(test_basic, logical_or_bad_type_lhs) {
  BasicTestInterpreter app("test_135.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_or_bad_type_rhs) {
  BasicTestInterpreter app("test_136.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_or_bad_types) {
  BasicTestInterpreter app("test_137.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_or_missing_rhs) {
  BasicTestInterpreter app("test_138.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, logical_or_missing_lhs) {
  BasicTestInterpreter app("test_139.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, logical_false_and_false) {
  BasicTestInterpreter app("test_140.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, logical_true_and_false) {
  BasicTestInterpreter app("test_141.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, logical_false_and_true) {
  BasicTestInterpreter app("test_142.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, logical_true_and_true) {
  BasicTestInterpreter app("test_143.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, logical_and_short_circuit) {
  BasicTestInterpreter app("test_144.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, logical_and_evaluation_order) {
  BasicTestInterpreter app("test_145.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, logical_and_branch) {
  BasicTestInterpreter app("test_146.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, logical_and_type_promotion) {
  BasicTestInterpreter app("test_147.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, logical_and_require_cast) {
  BasicTestInterpreter app("test_148.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(4));
}

TEST(test_basic, logical_and_bad_type_lhs) {
  BasicTestInterpreter app("test_149.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_and_bad_type_rhs) {
  BasicTestInterpreter app("test_150.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_and_bad_types) {
  BasicTestInterpreter app("test_151.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, logical_and_missing_rhs) {
  BasicTestInterpreter app("test_152.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, logical_and_missing_lhs) {
  BasicTestInterpreter app("test_153.clike");
  EXPECT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, bitwise_or) {
  BasicTestInterpreter app("test_154.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, bitwise_or_literals) {
  BasicTestInterpreter app("test_155.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, bitwise_xor) {
  BasicTestInterpreter app("test_156.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, bitwise_xor_literals) {
  BasicTestInterpreter app("test_157.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, bitwise_and) {
  BasicTestInterpreter app("test_158.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, bitwise_and_literals) {
  BasicTestInterpreter app("test_159.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_eq) {
  BasicTestInterpreter app("test_160.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_eq_literals) {
  BasicTestInterpreter app("test_161.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_eq_2) {
  BasicTestInterpreter app("test_162.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_eq_literals_2) {
  BasicTestInterpreter app("test_163.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_neq) {
  BasicTestInterpreter app("test_164.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_neq_literals) {
  BasicTestInterpreter app("test_165.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_neq_2) {
  BasicTestInterpreter app("test_166.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_neq_literals_2) {
  BasicTestInterpreter app("test_167.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lt) {
  BasicTestInterpreter app("test_168.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_lt_literals) {
  BasicTestInterpreter app("test_169.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_lt_2) {
  BasicTestInterpreter app("test_170.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lt_literals_2) {
  BasicTestInterpreter app("test_171.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lt_3) {
  BasicTestInterpreter app("test_172.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lt_literals_3) {
  BasicTestInterpreter app("test_173.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_gt) {
  BasicTestInterpreter app("test_174.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_gt_literals) {
  BasicTestInterpreter app("test_175.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_gt_2) {
  BasicTestInterpreter app("test_176.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_gt_literals_2) {
  BasicTestInterpreter app("test_177.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_gt_3) {
  BasicTestInterpreter app("test_178.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_gt_literals_3) {
  BasicTestInterpreter app("test_179.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lte) {
  BasicTestInterpreter app("test_180.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_lte_literals) {
  BasicTestInterpreter app("test_181.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_lte_2) {
  BasicTestInterpreter app("test_182.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lte_literals_2) {
  BasicTestInterpreter app("test_183.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_lte_3) {
  BasicTestInterpreter app("test_184.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_lte_literals_3) {
  BasicTestInterpreter app("test_185.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_gte) {
  BasicTestInterpreter app("test_186.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_gte_literals) {
  BasicTestInterpreter app("test_187.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_gte_2) {
  BasicTestInterpreter app("test_188.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_gte_literals_2) {
  BasicTestInterpreter app("test_189.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_gte_3) {
  BasicTestInterpreter app("test_190.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_gte_literals_3) {
  BasicTestInterpreter app("test_191.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_shl) {
  BasicTestInterpreter app("test_192.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_literals) {
  BasicTestInterpreter app("test_193.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_2) {
  BasicTestInterpreter app("test_194.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  uint64_t a = 0x1122334455667711;
  EXPECT_EQ(a, ret);
}

TEST(test_basic, operator_shl_literals_2) {
  BasicTestInterpreter app("test_195.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  uint64_t a = 0x1122334455667711;
  EXPECT_EQ(a, ret);
}

TEST(test_basic, operator_shl_3) {
  BasicTestInterpreter app("test_196.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  uint64_t a = 0x1122334455667711;
  uint64_t b = a << 3;
  EXPECT_EQ(b, ret);
}

TEST(test_basic, operator_shl_literals_3) {
  BasicTestInterpreter app("test_197.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  uint64_t a = 0x1122334455667711;
  uint64_t b = a << 3;
  EXPECT_EQ(b, ret);
}

TEST(test_basic, operator_shl_4) {
  BasicTestInterpreter app("test_198.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x8000000000000000, ret);
}

TEST(test_basic, operator_shl_literals_4) {
  BasicTestInterpreter app("test_199.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x8000000000000000, ret);
}

TEST(test_basic, operator_shl_5) {
  BasicTestInterpreter app("test_200.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_literals_5) {
  BasicTestInterpreter app("test_201.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_6) {
  BasicTestInterpreter app("test_202.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_literals_6) {
  BasicTestInterpreter app("test_203.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_7) {
  BasicTestInterpreter app("test_204.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shl_literals_7) {
  BasicTestInterpreter app("test_205.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr) {
  BasicTestInterpreter app("test_206.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_literals) {
  BasicTestInterpreter app("test_207.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_2) {
  BasicTestInterpreter app("test_208.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x8822334455667711, ret);
}

TEST(test_basic, operator_shr_literals_2) {
  BasicTestInterpreter app("test_209.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x8822334455667711, ret);
}

TEST(test_basic, operator_shr_3) {
  BasicTestInterpreter app("test_210.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  uint64_t a = 0x8822334455667711;
  uint64_t b = a >> 3;
  EXPECT_EQ(b, ret);
}

TEST(test_basic, operator_shr_literals_3) {
  BasicTestInterpreter app("test_211.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  int64_t a = 0x8822334455667711;
  int64_t b = a >> 3;
  EXPECT_EQ(b, ret);
}

TEST(test_basic, operator_shr_4) {
  BasicTestInterpreter app("test_212.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_shr_literals_4) {
  BasicTestInterpreter app("test_213.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFF, ret);
}

TEST(test_basic, operator_shr_5) {
  BasicTestInterpreter app("test_214.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_literals_5) {
  BasicTestInterpreter app("test_215.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_6) {
  BasicTestInterpreter app("test_216.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_literals_6) {
  BasicTestInterpreter app("test_217.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_7) {
  BasicTestInterpreter app("test_218.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_shr_literals_7) {
  BasicTestInterpreter app("test_219.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, operator_arith_add) {
  BasicTestInterpreter app("test_220.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_arith_add_literals) {
  BasicTestInterpreter app("test_221.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_arith_add_evaluation_order) {
  BasicTestInterpreter app("test_222.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, operator_arith_add_evaluation_order_2) {
  BasicTestInterpreter app("test_223.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, operator_arith_sub) {
  BasicTestInterpreter app("test_224.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(8, ret);
}

TEST(test_basic, operator_arith_sub_literals) {
  BasicTestInterpreter app("test_225.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(8, ret);
}

TEST(test_basic, operator_arith_sub_evaluation_order) {
  BasicTestInterpreter app("test_226.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, operator_arith_sub_evaluation_order_2) {
  BasicTestInterpreter app("test_227.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, operator_arith_mul) {
  BasicTestInterpreter app("test_228.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(20, ret);
}

TEST(test_basic, operator_arith_mul_literals) {
  BasicTestInterpreter app("test_229.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(20, ret);
}

TEST(test_basic, operator_arith_mul_evaluation_order) {
  BasicTestInterpreter app("test_230.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(100, ret);
}

TEST(test_basic, operator_arith_mul_evaluation_order_2) {
  BasicTestInterpreter app("test_231.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_arith_div) {
  BasicTestInterpreter app("test_232.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, operator_arith_div_literals) {
  BasicTestInterpreter app("test_233.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, operator_arith_div_evaluation_order) {
  BasicTestInterpreter app("test_234.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(50, ret);
}

TEST(test_basic, operator_arith_div_evaluation_order_2) {
  BasicTestInterpreter app("test_235.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_arith_mod) {
  BasicTestInterpreter app("test_236.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, operator_arith_mod_literals) {
  BasicTestInterpreter app("test_237.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, operator_arith_mod_evaluation_order) {
  BasicTestInterpreter app("test_238.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, operator_arith_mod_evaluation_order_2) {
  BasicTestInterpreter app("test_239.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(16, ret);
}

TEST(test_basic, operator_postfix_inc) {
  BasicTestInterpreter app("test_240.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, operator_postfix_inc_2) {
  BasicTestInterpreter app("test_241.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, operator_postfix_inc_literal) {
  BasicTestInterpreter app("test_242.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, operator_postfix_dec) {
  BasicTestInterpreter app("test_243.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, operator_postfix_dec_2) {
  BasicTestInterpreter app("test_244.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_postfix_dec_literal) {
  BasicTestInterpreter app("test_245.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, const_init) {
  BasicTestInterpreter app("test_246.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, const_prevent_assignment) {
  BasicTestInterpreter app("test_247.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, const_function_arg_const_input) {
  BasicTestInterpreter app("test_248.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, const_function_arg_nonconst_input) {
  BasicTestInterpreter app("test_249.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, const_function_assignment_to_parameter) {
  BasicTestInterpreter app("test_250.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, functon_const_return_type) {
  BasicTestInterpreter app("test_251.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, functon_const_return_type_2) {
  BasicTestInterpreter app("test_252.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, assignment_to_function_expression) {
  BasicTestInterpreter app("test_253.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(6));
}

TEST(test_basic, const_struct_member) {
  BasicTestInterpreter app("test_254.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, const_struct_member_assignment) {
  BasicTestInterpreter app("test_255.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(8));
}

TEST(test_basic, return_const_struct_member) {
  BasicTestInterpreter app("test_256.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, increment_func_return_expr) {
  BasicTestInterpreter app("test_257.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(6));
}

TEST(test_basic, increment_struct_member) {
  BasicTestInterpreter app("test_258.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, assignment_to_function_call) {
  BasicTestInterpreter app("test_259.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(6));
}

TEST(test_basic, prefix_inc) {
  BasicTestInterpreter app("test_260.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, prefix_inc_2) {
  BasicTestInterpreter app("test_261.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, prefix_inc_constant) {
  BasicTestInterpreter app("test_262.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, prefix_inc_literal) {
  BasicTestInterpreter app("test_263.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, prefix_inc_pre) {
  BasicTestInterpreter app("test_264.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, prefix_inc_function_call_post) {
  BasicTestInterpreter app("test_265.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, prefix_inc_function_call_pre) {
  BasicTestInterpreter app("test_266.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, prefix_dec) {
  BasicTestInterpreter app("test_267.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, prefix_dec_2) {
  BasicTestInterpreter app("test_268.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, prefix_dec_constant) {
  BasicTestInterpreter app("test_269.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, prefix_dec_literal) {
  BasicTestInterpreter app("test_270.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, prefix_dec_pre) {
  BasicTestInterpreter app("test_271.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, prefix_dec_function_call_post) {
  BasicTestInterpreter app("test_272.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, prefix_dec_function_call_pre) {
  BasicTestInterpreter app("test_273.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, prefix_inc_overflow) {
  BasicTestInterpreter app("test_274.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, prefix_dec_underflow) {
  BasicTestInterpreter app("test_275.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xffffffffffffffff, ret);
}

TEST(test_basic, overflow_8bit) {
  BasicTestInterpreter app("test_276.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, literal_truncation_hex) {
  BasicTestInterpreter app("test_277.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xff, ret);
}

TEST(test_basic, literal_truncation_dec) {
  BasicTestInterpreter app("test_278.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(255, ret);
}

TEST(test_basic, literal_truncation_hex_2) {
  BasicTestInterpreter app("test_279.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xff, ret);
}

TEST(test_basic, literal_truncation_dec_2) {
  BasicTestInterpreter app("test_280.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(255, ret);
}

TEST(test_basic, prefix_plus_twice) {
  BasicTestInterpreter app("test_281.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, assignment_to_expression) {
  BasicTestInterpreter app("test_282.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, ternary_evaluation_order) {
  BasicTestInterpreter app("test_283.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, assignment_evaluation_order) {
  BasicTestInterpreter app("test_284.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, array_subscript_evaluation_order) {
  BasicTestInterpreter app("test_285.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_prefix_inc) {
  BasicTestInterpreter app("test_286.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, operator_prefix_inc_2) {
  BasicTestInterpreter app("test_287.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(4, ret);
}

TEST(test_basic, operator_prefix_inc_literal) {
  BasicTestInterpreter app("test_288.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, operator_prefix_dec) {
  BasicTestInterpreter app("test_289.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_prefix_dec_2) {
  BasicTestInterpreter app("test_290.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, operator_prefix_dec_literal) {
  BasicTestInterpreter app("test_291.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, postfix_plus_twice) {
  BasicTestInterpreter app("test_292.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, unary_minus_2) {
  BasicTestInterpreter app("test_293.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFF, ret);
}

TEST(test_basic, unary_minus_3) {
  BasicTestInterpreter app("test_294.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, unary_minus_4) {
  BasicTestInterpreter app("test_295.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFF, ret);
}

TEST(test_basic, unary_minus_5) {
  BasicTestInterpreter app("test_296.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, unary_minus_6) {
  BasicTestInterpreter app("test_297.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_minus_7) {
  BasicTestInterpreter app("test_298.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, unary_minus_8) {
  BasicTestInterpreter app("test_299.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, unary_minus_9) {
  BasicTestInterpreter app("test_300.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFE, ret);
}

TEST(test_basic, unary_minus_10) {
  BasicTestInterpreter app("test_301.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFE, ret);
}

TEST(test_basic, unary_minus_assignment) {
  BasicTestInterpreter app("test_302.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, unary_bitwise_negate) {
  BasicTestInterpreter app("test_303.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x5A5A5A5A5A5A5A5A, ret);
}

TEST(test_basic, unary_bitwise_negate_2) {
  BasicTestInterpreter app("test_304.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x5A5A5A5A5A5A5A5A, ret);
}

TEST(test_basic, unary_bitwise_negate_3) {
  BasicTestInterpreter app("test_305.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x5A5A5A5A5A5A5A5A, ret);
}

TEST(test_basic, unary_bitwise_negate_4) {
  BasicTestInterpreter app("test_306.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xA5A5A5A5A5A5A5A5, ret);
}

TEST(test_basic, unary_bitwise_negate_5) {
  BasicTestInterpreter app("test_307.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x5A5A5A5A5A5A5A5A, ret);
}

TEST(test_basic, unary_bitwise_negate_6) {
  BasicTestInterpreter app("test_308.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x5A5A5A5A5A5A5A5A, ret);
}

TEST(test_basic, unary_bitwise_negate_7) {
  BasicTestInterpreter app("test_309.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xA5A5A5A5A5A5A5A5, ret);
}

TEST(test_basic, unary_bitwise_negate_8) {
  BasicTestInterpreter app("test_310.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0x5A5A5A5A5A5A5A5A, ret);
}

TEST(test_basic, unary_bitwise_negate_9) {
  BasicTestInterpreter app("test_311.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFD, ret);
}

TEST(test_basic, unary_bitwise_negate_10) {
  BasicTestInterpreter app("test_312.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, double_unary_bitwise_negate) {
  BasicTestInterpreter app("test_313.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, unary_logical_negate) {
  BasicTestInterpreter app("test_314.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_2) {
  BasicTestInterpreter app("test_315.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_3) {
  BasicTestInterpreter app("test_316.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_4) {
  BasicTestInterpreter app("test_317.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, unary_logical_negate_5) {
  BasicTestInterpreter app("test_318.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_6) {
  BasicTestInterpreter app("test_319.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_7) {
  BasicTestInterpreter app("test_320.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, unary_logical_negate_8) {
  BasicTestInterpreter app("test_321.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_9) {
  BasicTestInterpreter app("test_322.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, unary_logical_negate_10) {
  BasicTestInterpreter app("test_323.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, double_unary_logical_negate) {
  BasicTestInterpreter app("test_324.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, unary_logical_negate_branch_1) {
  BasicTestInterpreter app("test_325.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, unary_logical_negate_branch_2) {
  BasicTestInterpreter app("test_326.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(456, ret);
}

TEST(test_basic, signed_arith) {
  BasicTestInterpreter app("test_327.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFCE, ret);
}

TEST(test_basic, signed_arith_2) {
  BasicTestInterpreter app("test_328.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFF38, ret);
}

TEST(test_basic, signed_arith_3) {
  BasicTestInterpreter app("test_329.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, signed_arith_4) {
  BasicTestInterpreter app("test_330.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFA, ret);
}

TEST(test_basic, signed_arith_5) {
  BasicTestInterpreter app("test_331.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFD, ret);
}

TEST(test_basic, signed_arith_6) {
  BasicTestInterpreter app("test_332.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0xFFFFFFFFFFFFFFFA, ret);
}

TEST(test_basic, signed_cmp_literal_literal) {
  BasicTestInterpreter app("test_333.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_uint64_uint64) {
  BasicTestInterpreter app("test_334.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, signed_cmp_uint64_uint64_2) {
  BasicTestInterpreter app("test_335.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(0, ret);
}

TEST(test_basic, signed_cmp_int64_int64) {
  BasicTestInterpreter app("test_336.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int64_int64_2) {
  BasicTestInterpreter app("test_337.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int16_int16) {
  BasicTestInterpreter app("test_338.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int16_int16_2) {
  BasicTestInterpreter app("test_339.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int16_literal) {
  BasicTestInterpreter app("test_340.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_literal_int16) {
  BasicTestInterpreter app("test_341.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int64_int8) {
  BasicTestInterpreter app("test_342.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int8_int64) {
  BasicTestInterpreter app("test_343.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_cmp_int8_uint64_fail) {
  BasicTestInterpreter app("test_344.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, signed_cmp_uint64_int8_fail) {
  BasicTestInterpreter app("test_345.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, assignment_mul) {
  BasicTestInterpreter app("test_346.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(14, ret);
}

TEST(test_basic, assignment_div) {
  BasicTestInterpreter app("test_347.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(3, ret);
}

TEST(test_basic, assignment_mod) {
  BasicTestInterpreter app("test_348.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, assignment_add) {
  BasicTestInterpreter app("test_349.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(9, ret);
}

TEST(test_basic, assignment_sub) {
  BasicTestInterpreter app("test_350.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, assignment_shl) {
  BasicTestInterpreter app("test_351.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(20, ret);
}

TEST(test_basic, assignment_shr) {
  BasicTestInterpreter app("test_352.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(5, ret);
}

TEST(test_basic, assignment_and) {
  BasicTestInterpreter app("test_353.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(2, ret);
}

TEST(test_basic, assignment_xor) {
  BasicTestInterpreter app("test_354.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, assignment_or) {
  BasicTestInterpreter app("test_355.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(7, ret);
}

TEST(test_basic, assignment_mul_type_error) {
  BasicTestInterpreter app("test_356.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(4));
}

TEST(test_basic, assignment_mul_type_ok) {
  BasicTestInterpreter app("test_357.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(10, ret);
}

TEST(test_basic, assignment_mul_evaluation_order) {
  BasicTestInterpreter app("test_358.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(15, ret);
}

TEST(test_basic, assignment_mul_evaluation_order_2) {
  BasicTestInterpreter app("test_359.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(30, ret);
}

TEST(test_basic, subtract_negative_inequality) {
  BasicTestInterpreter app("test_360.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, array_size_constant_fold) {
  BasicTestInterpreter app("test_361.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, switch_case_constant_fold) {
  BasicTestInterpreter app("test_362.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, array_size_constant_fold_error) {
  BasicTestInterpreter app("test_363.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(3));
}

TEST(test_basic, switch_case_constant_fold_error) {
  BasicTestInterpreter app("test_364.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(6));
}

TEST(test_basic, array_function_argument_constant_fold) {
  BasicTestInterpreter app("test_365.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(789, ret);
}

TEST(test_basic, unary_constant_fold) {
  BasicTestInterpreter app("test_366.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, unary_constant_fold_2) {
  BasicTestInterpreter app("test_367.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(123, ret);
}

TEST(test_basic, zero_array_size_error) {
  BasicTestInterpreter app("test_368.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, not_zero_literal_constant) {
  BasicTestInterpreter app("test_369.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, switch_case_unary_fold) {
  BasicTestInterpreter app("test_370.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, literal_zero_divide) {
  BasicTestInterpreter app("test_371.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, runtime_zero_divide) {
  BasicTestInterpreter app("test_372.clike");
  ASSERT_NE(nullptr, app.tree());
  app.evaluate();
  EXPECT_TRUE(app.error_on_line(4));
}

TEST(test_basic, unsigned_integer_literal) {
  BasicTestInterpreter app("test_373.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, signed_integer_literal) {
  BasicTestInterpreter app("test_374.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(1, ret);
}

TEST(test_basic, unsigned_to_signed_bad_assignment) {
  BasicTestInterpreter app("test_375.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, signed_to_unsigned_bad_assignment) {
  BasicTestInterpreter app("test_376.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, bad_literal_suffix) {
  BasicTestInterpreter app("test_377.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, unsigned_literal_truncation) {
  BasicTestInterpreter app("test_378.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, signed_literal_truncation) {
  BasicTestInterpreter app("test_379.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, multiple_function_calls) {
  BasicTestInterpreter app("test_380.clike");
  ASSERT_NE(nullptr, app.tree());
  uint64_t ret = app.evaluate();
  EXPECT_EQ(6, ret);
}

TEST(test_basic, undeclared_function_call) {
  BasicTestInterpreter app("test_381.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, recursive_function_call) {
  BasicTestInterpreter app("test_382.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, access_caller_scope) {
  BasicTestInterpreter app("test_383.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}

TEST(test_basic, access_caller_scope_from_if_statement) {
  BasicTestInterpreter app("test_384.clike");
  ASSERT_EQ(nullptr, app.tree());
  EXPECT_TRUE(app.error_on_line(2));
}
