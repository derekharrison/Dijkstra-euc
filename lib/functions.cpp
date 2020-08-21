/*
 * functions.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: d-w-h
 */

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/functions.hpp"
#include "../inc/user_types.hpp"

bool** bool2D(const int size) {
    bool** p = new bool*[size];

    for(int i = 0; i < size; ++i)
        p[i] = new bool[size];

    return p;
}

float** float2D(const int size) {
    float** p = new float*[size];

    for(int i = 0; i < size; ++i)
        p[i] = new float[size];

    return p;
}

void delete_bool2D(bool** p, int size) {
    for(int i = 0; i < size; ++i)
        delete [] p[i];

    delete [] p;
}

void delete_float2D(float** p, int size) {
    for(int i = 0; i < size; ++i)
        delete [] p[i];

    delete [] p;
}

void init_adj_mat(bool** adj_mat, bool** adj_mat_ref, int size_graph) {
    for(int i = 0; i < size_graph; ++i)
        for(int j = 0; j < size_graph; ++j) {
            adj_mat[i][j] = adj_mat_ref[i][j];
        }
}

void init_weight_mat(float** weight_mat, float** weight_mat_ref, int size_graph) {
    for(int i = 0; i < size_graph; ++i)
        for(int j = 0; j < size_graph; ++j) {
            weight_mat[i][j] = weight_mat_ref[i][j];
        }
}

void init_sum_node(float* sum_node, int size_graph) {
    sum_node[0] = 0.0;
    for(int i = 1; i < size_graph; ++i) {
        sum_node[i] = inf;
    }
}

void init_visited(bool* visited, int size_graph) {
    visited[0] = true;
    for(int i  = 1; i < size_graph; ++i) {
        visited[i] = false;
    }
}

void init_adj_and_weight(bool** adj_mat, float** weight_mat, int size_graph) {
    for(int i = 0; i < size_graph; ++i)
        for(int j = 0; j < size_graph; ++j) {
            adj_mat[i][j] = false;
            weight_mat[i][j] = 0.0;
        }
}

void init_coordinates(euc_c* coordinates, euc_c* coordinates_ref, int size_graph) {
    for(int i = 0; i < size_graph; ++i) {
        coordinates[i] = coordinates_ref[i];
    }
}

void populate_adj_and_weight(bool** adj_mat, euc_c* coordinates, float** weight_mat, int size_graph, float density) {
    init_adj_and_weight(adj_mat, weight_mat, size_graph);

    srand(time(NULL));
    float max_coordinates = 10.0;
    for(int i = 0; i < size_graph; ++i) {
        float rand_num_x = (float) rand() / RAND_MAX;
        float rand_num_y = (float) rand() / RAND_MAX;
        coordinates[i].x = rand_num_x * max_coordinates;
        coordinates[i].y = rand_num_y * max_coordinates;
    }

    for(int i = 0; i < size_graph; ++i)
        for(int j = i; j < size_graph; ++j) {
            float rand_num = (float) rand() / RAND_MAX;
            if(i != j) {
                adj_mat[j][i] = adj_mat[i][j] = rand_num > (1 - density);
                if(adj_mat[i][j]) {
                    weight_mat[j][i] = weight_mat[i][j] = sqrt((coordinates[i].x - coordinates[j].x)*(coordinates[i].x - coordinates[j].x) +
                                                               (coordinates[i].y - coordinates[j].y)*(coordinates[i].y - coordinates[j].y));
                }
            }
        }
}
