/*
 * dijkstra.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: d-w-h
 */

#include <iostream>

#include "../inc/dijkstra.hpp"
#include "../inc/functions.hpp"
#include "../inc/user_types.hpp"

const char* file_name = "shortest_path_data.txt";

Dijkstra::Dijkstra(bool** adj_mat, euc_c* coordinates, float** weight_mat, int size_graph) {
    this->size_graph = size_graph;

    this->adj_mat = bool2D(size_graph);
    init_adj_mat(this->adj_mat, adj_mat, size_graph);

    this->weight_mat = float2D(size_graph);
    init_weight_mat(this->weight_mat, weight_mat, size_graph);

    this->sum_node = new float[size_graph];
    init_sum_node(this->sum_node, size_graph);

    this->visited = new bool[size_graph];
    init_visited(this->visited, size_graph);

    this->prev_vertex = new int[size_graph];

    this->coordinates = new euc_c[size_graph];
    init_coordinates(this->coordinates, coordinates, size_graph);
}

Dijkstra::~Dijkstra() {
    delete_bool2D(this->adj_mat, this->size_graph);
    delete_float2D(this->weight_mat, this->size_graph);
    delete [] this->sum_node;
    delete [] this->visited;
    delete [] this->prev_vertex;
    delete [] this->coordinates;
}

void Dijkstra::dijkstra_algo() {
    int current_node = 0;
    int it_counter = 0;
    FILE *file_ptr = fopen(file_name, "w");
    bool unvisited_is_empty = Dijkstra::check_unvisited();
    /* Main iteration loop */
    while(unvisited_is_empty == false) {
        for(int node = 0; node < this->size_graph; ++node) {
            if(is_connected(current_node, node) && node_not_visited(node) && curr_sum_greater(current_node, node)) {
                this->sum_node[node] = this->sum_node[current_node] + this->weight_mat[current_node][node];
                this->prev_vertex[node] = current_node;
            }
        }

        current_node = Dijkstra::update_curr_node();
        int parent_node = this->prev_vertex[current_node];
        this->visited[current_node] = true;

        /* Export data to file */
        fprintf(file_ptr, "%i %f %f %i %f %f %f %f %f\n", parent_node,
                                                          this->coordinates[parent_node].x,
                                                          this->coordinates[parent_node].y,
                                                          current_node,
                                                          this->coordinates[current_node].x,
                                                          this->coordinates[current_node].y,
                                                          weight_mat[parent_node][current_node],
                                                          this->coordinates[it_counter].x,
                                                          this->coordinates[it_counter].y);

        unvisited_is_empty = Dijkstra::check_unvisited();
        it_counter++;
        if(it_counter > this->size_graph + 2) {
            printf("Entered infinite loop, some vertices could not be reached\n");
            break;
        }
    }

    fclose(file_ptr);
}

int Dijkstra::update_curr_node() {
    float min_dist = inf;
    int current_node = 0;
    for(int node = 0; node < this->size_graph; ++node) {
        if(min_dist > this->sum_node[node] && node_not_visited(node)) {
            min_dist = this->sum_node[node];
            current_node = node;
        }
    }

    return current_node;
}

bool Dijkstra::node_not_visited(int node) {
    return !this->visited[node];
}

bool Dijkstra::is_connected(int node_a, int node_b) {
    return this->adj_mat[node_a][node_b];
}

bool Dijkstra::curr_sum_greater(int current_node, int node) {
    return this->sum_node[node] > this->sum_node[current_node] + this->weight_mat[current_node][node];
}

bool Dijkstra::check_unvisited() {
    for(int i = 0; i < this->size_graph; ++i) {
        if(this->visited[i] == false) {
            return false;
        }
    }

    return true;
}

void Dijkstra::print_results() {
    printf("vertex: 0, distance from vertex 0: %.1E\n", this->sum_node[0]);
    for(int i = 1; i < this->size_graph; ++i) {
        printf("vertex: %i, distance from vertex 0: %.2E, previous vertex: %i\n",
                i, this->sum_node[i], this->prev_vertex[i]);
    }
}

void Dijkstra::print_adj_mat() {
    printf("adjancy matrix\n");
    for(int i = 0; i < this->size_graph; ++i) {
        for(int j = 0; j < this->size_graph; ++j) {
            printf("(%i,%i): %d ", i, j, this->adj_mat[i][j]);
        }
        printf("\n");
    }
}

void Dijkstra::print_weight_mat() {
    printf("weight matrix\n");
    for(int i = 0; i < this->size_graph; ++i) {
        for(int j = 0; j < this->size_graph; ++j) {
            printf("(%i,%i): %.2f ", i, j, this->weight_mat[i][j]);
        }
        printf("\n");
    }
}

float Dijkstra::avg_path() {
    float avg_path = 0.0;

    for(int i = 0; i < this->size_graph; i++) {
        avg_path += this->sum_node[i];
    }

    return avg_path = avg_path / (this->size_graph - 1);
}

void Dijkstra::get_sum_node(float* sum_node) {
    for(int i = 0; i < this->size_graph; i++) {
        sum_node[i] = this->sum_node[i];
    }
}

void Dijkstra::get_prev_vertex(int* prev_vertex) {
    for(int i = 0; i < this->size_graph; i++) {
        prev_vertex[i] = this->prev_vertex[i];
    }
}
