/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.

    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	51033	33658	30579	66.679%

문제
---
2022 연세대학교 미래캠퍼스 슬기로운 코딩생활에 N 명의 학생들이 응시했다.

이들 중 점수가 가장 높은 k 명은 상을 받을 것이다.

이 때, 상을 받는 커트라인이 몇 점인지 구하라.

커트라인이란 상을 받는 사람들 중 점수가 가장 가장 낮은 사람의 점수를 말한다.

입력
---
첫째 줄에는 응시자의 수 N 과 상을 받는 사람의 수 k 가 공백을 사이에 두고 주어진다.

둘째 줄에는 각 학생의 점수 x가 공백을 사이에 두고 주어진다.

출력
---
상을 받는 커트라인을 출력하라.

제한
---
1 ≤ N ≤ 1,000

1 ≤ k ≤ N

0 ≤ x ≤ 10,000

예제 입력 1
5 2
100 76 85 93 98
예제 출력 1
98

시험 응시자들 가운데 1등은 100점, 2등은 98점, 3등은 93점이다. 2등까지 상을 받으므로 커트라인은 98점이다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void sort_quick(int* list, int start, int end);
void swap(int* list, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[20000];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int N = parseInt(*tokensPtr++);
    int k = parseInt(*tokensPtr++);

    free(tokens);

    int* list = (int*)malloc(sizeof(int) * (N + 1));

    fgets(input, sizeof(input), stdin);

    tokens = (char**)tokenizer(input);
    tokensPtr = (char**)tokens;

    int idx = 0;
    while(*tokensPtr) {
        *(list + idx++) = parseInt(*tokensPtr++);
    }

    free(tokens);

    sort_quick(list, 0, N - 1);

    // idx = 0;
    // while(idx < N) {
    //     fputs(intToStr(*(list + idx++)), stdout); fputc(' ', stdout);
    // }

    int cutline = *(list + N - k);

    char* resultStr = intToStr(cutline);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

    return 0;
}

void sort_quick(int* list, int start, int end) {
    if(start >= end) {
        return;
    }

    int pivot = start;
    int i = start;
    int j = end;

    while(i < j) {
        while(*(list + pivot) < *(list + j)) {
            j--;
        }
        while(i < j && *(list + pivot) >= *(list + i)) {
            i++;
        }
        swap(list, i, j);
    }
    swap(list, pivot, i);

    sort_quick(list, start, i - 1);
    sort_quick(list, i + 1, end);
}
void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

    return;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;

    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr++ = input[tknIdx++];
            }

            *tokensPtr++ = newTkn; currSize++;

            tknIdx = ++currIdx;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            currIdx++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        free(*tokensPtr++);
    }
    free(tokens);

    return;
}

char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        target *= -1;
        sign = -1;
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
    if(sign == -1) {
        *result = '-';
    }

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

    while(isBlank(*strPtr) != 1) {
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
