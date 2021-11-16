#include <stdio.h>
#include <stdlib.h>


int is_enough_resources(const int *requested_matrix, const int *free, int no_resources) {
    for (int i = 0; i < no_resources; ++i) {
        if (requested_matrix[i] > free[i]) {
            return 0;
        }
    }
    return 1;
}

void free_resources(const int *current_allocation, int *free, int no_resources) {
    for (int i = 0; i < no_resources; ++i) {
        free[i] += current_allocation[i];
    }
}

int main() {

    FILE *inp = fopen("input.txt", "r");

    int resources_num;
    int processes_num;

    fscanf(inp, "%d", &resources_num);
    fscanf(inp, "%d", &processes_num);

    int exist[resources_num];
    int free[resources_num];
    int current_allocation[resources_num][processes_num];
    int requested_matrix_matrix[resources_num][processes_num];
    int is_finished[processes_num];

    for (int i = 0; i < resources_num; ++i) {
        fscanf(inp, "%d", &exist[i]);
    }

    for (int i = 0; i < resources_num; ++i) {
        fscanf(inp, "%d", &free[i]);
    }

    for (int i = 0; i < processes_num; ++i) {
        for (int j = 0; j < resources_num; ++j) {
            fscanf(inp, "%d", &current_allocation[i][j]);
        }
        is_finished[i] = 0;
    }

    for (int i = 0; i < processes_num; ++i) {
        for (int j = 0; j < resources_num; ++j) {
            fscanf(inp, "%d", &requested_matrix[i][j]);
        }
    }

    for (int i = 0; i < processes_num; ++i) {
        for (int process = 0; process < processes_num; ++process) {
            if (is_finished[process] == 0 && is_enough_resources(requested_matrix[process], free, resources_num) == 1) {
                free_resources(current_allocation[process], free, resources_num);
                is_finished[process] = 1;
            }
        }
    }

    int is_deadlock = 0;
    for (int i = 0; i < processes_num; ++i) {
        if (is_finished[i] == 0) {
            is_deadlock = 1;
            printf("Process %d is in deadlock\n", i);
        }
    }

    if (is_deadlock == 0) {
        printf("No deadlock\n");
    }

    return 0;
}