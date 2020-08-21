/*
 * Dijkstra.hpp
 *
 *  Created on: Jul 29, 2020
 *      Author: d-w-h
 */

#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include "user_types.hpp"

class Dijkstra {
private:
    int size_graph;
    bool** adj_mat;
    euc_c* coordinates;
    float** weight_mat;
    float* sum_node;
    bool* visited;
    int* prev_vertex;

    bool is_connected(int node_a, int node_b);
    bool node_not_visited(int node);
    bool curr_sum_greater(int node_a, int node_b);
    int update_curr_node();
    bool check_unvisited();
public:
    Dijkstra(bool** adj_mat, euc_c* coordinates, float** weight_mat, int size_graph);
    ~Dijkstra();
    void dijkstra_algo();
    void print_results();
    void print_adj_mat();
    void print_weight_mat();
    float avg_path();
    void get_sum_node(float* sum_node);
    void get_prev_vertex(int* prev_vertex);
};

#endif /* DIJKSTRA_HPP_ */
