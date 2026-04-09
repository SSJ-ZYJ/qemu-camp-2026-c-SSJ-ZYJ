#include <stdio.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (students[i].score >= students[j].score) {
            temp[k++] = students[i++];
        } else {
            temp[k++] = students[j++];
        }
    }

    while (i < mid) {
        temp[k++] = students[i++];
    }

    while (j < right) {
        temp[k++] = students[j++];
    }

    for (i = left; i < right; i++) {
        students[i] = temp[i];
    }
}

void merge_sort(int left, int right) {
    if (right - left <= 1) {
        return;
    }
    int mid = left + ((right - left) >> 1);
    merge_sort(left, mid);
    merge_sort(mid, right);
    merge(left, mid, right);
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1) {
        printf("错误：读取学生人数失败\n");
        fclose(file);
        return 1;
    }

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%49s %d", students[i].name, &students[i].score) != 2) {
            printf("错误：第 %d 条学生信息格式无效\n", i + 1);
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    merge_sort(0, n);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}