cmake_minimum_required(VERSION 3.20)
project(competitive-programmers-handbook)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  competitive-programmers-handbook
  c02_4_maximum_subarray_sum.cpp
  c03_1_sorting_theory.cpp
  c03_3_binary_search.cpp
  c05_1_generating_subsets.cpp
  c05_2_generating_permutations.cpp
  c05_3_backtracking.cpp
  c05_4_pruning_the_search.cpp
  c05_5_meet_in_the_middle.cpp
  c06_1_coin_problem.cpp
  c06_2_scheduling.cpp
  c06_3_tasks_and_deadlines.cpp
  c06_4_minimizing_sums.cpp
  c06_5_data_compression.cpp
  c07_1_coin_problem.cpp
  c07_2_longest_increasing_subseqence.cpp
  c07_3_paths_in_a_grid.cpp
  c07_4_knapsack_problems.cpp
  c07_5_edit_distance.cpp
  c07_6_counting_tilings.cpp
  c08_1_two_pointers_method.cpp
  c08_2_nearest_smaller_elements.cpp
  c08_3_sliding_window_minimum.cpp
  c09_1_static_array_queries.cpp
  c09_2_binary_indexed_tree.cpp
  c09_3_segment_tree.cpp
  c09_4_additional_techniques.cpp
  c10_2_bit_operations.cpp
  c10_4_bit_optimizations.cpp
  c10_5_dynamic_programming.cpp
  c12_1_depth_first_search.cpp
  c12_2_breadth_first_search.cpp
  c12_3_applications.cpp
  c13_1_bellman_ford.cpp
  c13_2_dijkstras_algorithm.cpp
  c13_3_floyd_warshall_algorithm.cpp
  c14_1_graph_traversal.cpp
  c14_2_diameter.cpp
  c14_3_all_longest_paths.cpp
  c14_4_binary_trees.cpp
  c15_1_kruskals_algorithm.cpp
  c15_2_union_find_structure.cpp
  c15_3_prims_algorithm.cpp
  c16_1_topological_sorting.cpp
  c16_2_dynamic_programming.cpp
  c16_3_successor_paths.cpp
  c16_4_cycle_detection.cpp
  c17_1_kosarajus_algorithm.cpp
  c17_2_2sat_problem.cpp
  c18_1_finding_ancestors.cpp
  c18_2_subtrees_and_paths.cpp
  c18_3_lowest_common_ancestor.cpp
  c18_4_offline_algorithms.cpp
  c19_1_eulerian_paths.cpp
  c19_2_hamiltonian_path.cpp
  c19_3_de_brujin_sequences.cpp
  c19_4_knights_tours.cpp
  c20_1_ford_fulkerson_algorithm.cpp
  c20_2_disjoint_paths.cpp
  c20_3_maximum_matchings.cpp
  c20_4_path_covers.cpp
  c21_1_primes_and_factors.cpp
  c21_2_modular_arithmetic.cpp
  c21_3_solving_equations.cpp
  c21_4_other_results.cpp
  c22_1_binomial_coefficients.cpp
  c22_2_catalan_numbers.cpp
  c22_3_inclusion_exclusion.cpp
  c22_4_burnsides_lemma.cpp
  c22_5_cayleys_formula.cpp
  c23_1_operations.cpp
  c23_2_linear_recurrences.cpp
  c23_3_graphs_and_matrices.cpp
  c24_3_random_variables.cpp
  c24_4_markov_chains.cpp
  c24_5_randomized_algorithms.cpp
  c25_3_sprague_grundy_theorem.cpp
  c26_2_trie_structure.cpp
  c26_3_string_hashing.cpp
  c26_4_z_algorithm.cpp
  c27_0_square_root_algorithms.cpp
  c27_1_combining_algorithms.cpp
  c27_2_integer_partitions.cpp
  c27_3_mos_algorithm.cpp
  c28_0_segment_tree_revisited.cpp
  c28_1_lazy_propagation.cpp
  c28_2_dynamic_trees.cpp
  c28_3_data_structures.cpp
  c28_4_two_dimensionality.cpp
  c29_1_complex_numbers.cpp
  c29_2_points_and_lines.cpp
  c29_3_polygon_area.cpp
  c29_4_distance_functions.cpp
  c30_0_sweep_line_algorithms.cpp
  c30_1_intersection_points.cpp
  c30_2_closest_pair_problem.cpp
  c30_3_convex_hull_problem.cpp
  util.cpp
)
target_link_libraries(
  competitive-programmers-handbook
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(competitive-programmers-handbook)
