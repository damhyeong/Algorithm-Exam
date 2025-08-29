
/**
스타트와 링크

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	118831	59152	35089	46.758%

문제
---
오늘은 스타트링크에 다니는 사람들이 모여서 축구를 해보려고 한다.

축구는 평일 오후에 하고 의무 참석도 아니다.

축구를 하기 위해 모인 사람은 총 N명이고 신기하게도 N은 짝수이다.

이제 N/2명으로 이루어진 스타트 팀과 링크 팀으로 사람들을 나눠야 한다.

BOJ를 운영하는 회사 답게 사람에게 번호를 1부터 N까지로 배정했고, 아래와 같은 능력치를 조사했다.

능력치 Sij는 i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치이다.

팀의 능력치는 팀에 속한 모든 쌍의 능력치 Sij의 합이다.

Sij는 Sji와 다를 수도 있으며, i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치는 Sij와 Sji이다.

N=4이고, S가 아래와 같은 경우를 살펴보자.

i\j	1	2	3	4
1	 	1	2	3
2	4	 	5	6
3	7	1	 	2
4	3	4	5
예를 들어, 1, 2번이 스타트 팀, 3, 4번이 링크 팀에 속한 경우에 두 팀의 능력치는 아래와 같다.

스타트 팀: S12 + S21 = 1 + 4 = 5
링크 팀: S34 + S43 = 2 + 5 = 7

1, 3번이 스타트 팀, 2, 4번이 링크 팀에 속하면, 두 팀의 능력치는 아래와 같다.

스타트 팀: S13 + S31 = 2 + 7 = 9
링크 팀: S24 + S42 = 6 + 4 = 10

축구를 재미있게 하기 위해서 스타트 팀의 능력치와 링크 팀의 능력치의 차이를 최소로 하려고 한다.

위의 예제와 같은 경우에는 1, 4번이 스타트 팀, 2, 3번 팀이 링크 팀에 속하면 스타트 팀의 능력치는 6, 링크 팀의 능력치는 6이 되어서 차이가 0이 되고 이 값이 최소이다.

입력
---
첫째 줄에 N(4 ≤ N ≤ 20, N은 짝수)이 주어진다.

둘째 줄부터 N개의 줄에 S가 주어진다.

각 줄은 N개의 수로 이루어져 있고, i번 줄의 j번째 수는 Sij 이다.

Sii는 항상 0이고, 나머지 Sij는 1보다 크거나 같고, 100보다 작거나 같은 정수이다.


출력
---
첫째 줄에 스타트 팀과 링크 팀의 능력치의 차이의 최솟값을 출력한다.

예제 입력 1
4
0 1 2 3
4 0 5 6
7 1 0 2
3 4 5 0
예제 출력 1
0

예제 입력 2
6
0 1 2 3 4 5
1 0 2 3 4 5
1 2 0 3 4 5
1 2 3 0 4 5
1 2 3 4 0 5
1 2 3 4 5 0
예제 출력 2
2

예제 입력 3
8
0 5 4 5 4 5 4 5
4 0 5 1 2 3 4 5
9 8 0 1 2 3 1 2
9 9 9 0 9 9 9 9
1 1 1 1 0 1 1 1
8 7 6 5 4 0 3 2
9 1 9 1 9 1 0 9
6 5 4 3 2 1 9 0
예제 출력 3
1

힌트
---
예제 2의 경우에 (1, 3, 6), (2, 4, 5)로 팀을 나누면 되고,
예제 3의 경우에는 (1, 2, 4, 5), (3, 6, 7, 8)로 팀을 나누면 된다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

void recursive(int curr, int deep, int start, _Bool* selected, int** foldArr);

char** tokenizer(const char* input);
void freeArr(void** arr);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int minDiff = 1e9;

int main(void) {
    char input[1000];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int** arr = (int**)malloc(sizeof(int*) * (N + 1));
    *(arr + N) = NULL;

    int idx = 0;
    while(idx < N) {
        *(arr + idx) = (int*)malloc(sizeof(int) * (N + 1));

        idx++;
    }

    idx = 0;
    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = tokens;

        int jdx = 0;
        while(jdx < N) {
            int num = parseInt(*tokensPtr++);

            *(*(arr + idx) + jdx) = num;

            jdx++;
        }
        idx++;

        freeArr((void**)tokens);
    }

    int** foldArr = (int**)malloc(sizeof(int*) * (N + 1));
    *(foldArr + N) = NULL;

    int i = 0;
    while(i < N) {
        *(foldArr + i) = (int*)malloc(sizeof(int) * (N + 1));

        int j = i + 1;
        while(j < N) {
            *(*(foldArr + i) + j) = *(*(arr + i) + j) + *(*(arr + j) + i);

            j++;
        }
        i++;
    }

    _Bool* selected = (_Bool*)calloc(N + 1, sizeof(_Bool));

    recursive(0, N / 2, 0, selected, foldArr);


    char* resultStr = intToStr(minDiff);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    freeArr((void**)foldArr);
    freeArr((void**)arr);

    return 0;
}

void recursive(int curr, int deep, int start, _Bool* selected, int** foldArr) {
    int len = deep * 2;

    if(curr == deep) {
        int* list1 = (int*)malloc(sizeof(int) * (deep + 1));
        int* list1Ptr = list1;
        int total1 = 0;

        int* list2 = (int*)malloc(sizeof(int) * (deep + 1));
        int* list2Ptr = list2;
        int total2 = 0;

        int idx = 0;
        while(idx < len) {
            _Bool isSelected = *(selected + idx);

            if(isSelected) {
                *list1Ptr++ = idx;
            } else {
                *list2Ptr++ = idx;
            }

            idx++;
        }

        int i = 0;
        while(i < deep) {
            int j = i + 1;
            while(j < deep) {
                int y = *(list1 + i);
                int x = *(list1 + j);

                total1 += *(*(foldArr + y) + x);
                j++;
            }
            i++;
        }

        i = 0;
        while(i < deep) {
            int j = i + 1;
            while(j < deep) {
                int y = *(list2 + i);
                int x = *(list2 + j);

                total2 += *(*(foldArr + y) + x);
                j++;
            }
            i++;
        }

        int diff = total1 > total2 ? total1 - total2 : total2 - total1;

        minDiff = diff < minDiff ? diff : minDiff;

        free(list1); free(list2);

        return;
    }

    int idx = start;
    while(idx < len) {
        if(!*(selected + idx)) {
            *(selected + idx) = 1;

            recursive(curr + 1, deep, idx + 1, selected, foldArr);

            *(selected + idx) = 0;
        }
        idx++;
    }

    return;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }

            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeArr(void** arr) {
    void** arrPtr = arr;

    while(*arrPtr) {
        free(*arrPtr++);
    }
    free(arr);

    return;
}

char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    int temp = target;
    do {
        temp /= 10;
        len++;
    } while(temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    *(result + size) = 0;

    int idx = endIdx;
    while(idx >= startIdx) {
        *(result + idx--) = (target % 10) + '0';
        target /= 10;
    }
    *result = sign == 1 ? *result : '-';

    return result;
}
int parseInt(const char* str) {
    int sign = 1;
    int result = 0;

    char* strPtr = (char*)str;
    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(!isBlank(*strPtr)) {
        result *= 10;
        result += *strPtr++ - '0';
    }

    return result * sign;
}
_Bool isBlank(char ch) {
    if(ch == 32 || ch == 0) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
