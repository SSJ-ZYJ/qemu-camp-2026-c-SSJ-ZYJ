#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];

void quick_sort(int left, int right) {
    if (right - left <= 1) {
        return;
    }
    const int pivot = students[left + rand() % (right - left)].score;
    int i = left;
    int j = right - 1;

    while (i <= j) {
        while (i <= j && students[i].score > pivot) {
            i++;
        }
        while (i <= j && students[j].score < pivot) {
            j--;
        }
        if (i <= j) {
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            i++;
            j--;
        }
    }

    quick_sort(left, i);
    quick_sort(i, right);
}

int main(void) {
    FILE *file = fopen("03_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 03_students.txt\n");
        return 1;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1) {
        printf("错误：读取学生人数失败\n");
        fclose(file);
        return 1;
    }

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
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

    quick_sort(0, n);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}