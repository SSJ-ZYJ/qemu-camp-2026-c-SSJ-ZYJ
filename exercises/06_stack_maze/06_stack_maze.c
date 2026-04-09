#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    int row;
    int col;
    int next_dir;
} Frame;

int dfs(Point path[], int *path_len) {
    int visited[MAX_ROW][MAX_COL] = {0};
    Frame stack[MAX_ROW * MAX_COL];
    int top = 0;
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    stack[top++] = (Frame){0, 0, 0};
    visited[0][0] = 1;
    path[(*path_len)++] = (Point){0, 0};

    while (top > 0) {
        Frame *current = &stack[top - 1];

        if (current->row == MAX_ROW - 1 && current->col == MAX_COL - 1) {
            return 1;
        }

        if (current->next_dir >= 4) {
            visited[current->row][current->col] = 0;
            (*path_len)--;
            top--;
            continue;
        }

        int dir = current->next_dir++;
        int next_row = current->row + dr[dir];
        int next_col = current->col + dc[dir];

        if (next_row < 0 || next_row >= MAX_ROW || next_col < 0 || next_col >= MAX_COL) {
            continue;
        }
        if (maze[next_row][next_col] != 0 || visited[next_row][next_col]) {
            continue;
        }

        visited[next_row][next_col] = 1;
        stack[top++] = (Frame){next_row, next_col, 0};
        path[(*path_len)++] = (Point){next_row, next_col};
    }

    return 0;
}

int main(void) {
    Point path[MAX_ROW * MAX_COL];
    int path_len = 0;

    if (!dfs(path, &path_len)) {
        printf("No path!\n");
        return 0;
    }

    for (int i = path_len - 1; i >= 0; i--) {
        printf("(%d, %d)\n", path[i].row, path[i].col);
    }
    
    return 0;
}