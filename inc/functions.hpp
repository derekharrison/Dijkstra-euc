/*
 * functions.hpp
 *
 *  Created on: Jul 29, 2020
 *      Author: d-w-h
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include "user_types.hpp"

const int inf = 3e+8;

bool** bool2D(const int size);
float** float2D(const int size);
void delete_bool2D(bool** p, int size);
void delete_float2D(float** p, int size);
void init_adj_mat(bool** adj_mat, bool** adj_mat_ref, int size_graph);
void init_weight_mat(float** weight_mat, float** weight_mat_ref, int size_graph);
void init_sum_node(float* sum_node, int size_graph);
void init_visited(bool* visited, int size_graph);
void init_adj_and_weight(bool** adj_mat, float** weight_mat, int size_graph);
void init_coordinates(euc_c* coordinates, euc_c* coordinates_ref, int size_graph);
void populate_adj_and_weight(bool** adj_mat, euc_c* coordinates, float** weight_mat, int size_graph, float density);

#endif /* FUNCTIONS_HPP_ */
