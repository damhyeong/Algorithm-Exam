/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "코드를 보다가 궁금하시면 EMAIL 로 연락 주셔도 괜찮습니다!"

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.


    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
구간 합 구하기 4

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	165570	68227	49377	38.485%

문제
---
수 N개가 주어졌을 때, i번째 수부터 j번째 수까지 합을 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 수의 개수 N과 합을 구해야 하는 횟수 M이 주어진다.

둘째 줄에는 N개의 수가 주어진다.

수는 1,000보다 작거나 같은 자연수이다.

셋째 줄부터 M개의 줄에는 합을 구해야 하는 구간 i와 j가 주어진다.


출력
---
총 M개의 줄에 입력으로 주어진 i번째 수부터 j번째 수까지 합을 출력한다.


제한
---
1 ≤ N ≤ 100,000
1 ≤ M ≤ 100,000
1 ≤ i ≤ j ≤ N

예제 입력 1
5 3
5 4 3 2 1
1 3
2 4
5 5
예제 출력 1
12
9
1
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    int NORMAL = 255;
    int MAX = 400000;

    char* input = (char*)malloc(sizeof(char) * (NORMAL + 1));
    *(input + NORMAL) = 0;

    fgets(input, NORMAL, stdin);

    char** tokens = tokenizer(input);

    free(input);

    int N = parseInt(*tokens);
    int M = parseInt(*(tokens + 1));
    freeArrs((void**)tokens);

    input = (char*)malloc(sizeof(char) * (MAX + 1));
    *(input + MAX) = 0;
    fgets(input, MAX, stdin);

    tokens = tokenizer(input);
    char** tokensPtr = tokens;

    free(input);

    int* dp = (int*)malloc(sizeof(int) * (N + 2));
    int* dpPtr = dp; *dpPtr++ = 0;

    int idx = 0;
    while(idx++ < N) {
        *dpPtr = parseInt(*tokensPtr++) + *(dpPtr - 1);
        dpPtr++;
    }

    freeArrs((void**)tokens);

    idx = 0;
    while(idx++ < M) {
        input = (char*)malloc(sizeof(char) * (NORMAL + 1));
        *(input + NORMAL) = 0;

        fgets(input, NORMAL, stdin);

        tokens = tokenizer(input);
        free(input);

        int i = parseInt(*tokens);
        int j = parseInt(*(tokens + 1));

        freeArrs((void**)tokens);

        int result = *(dp + j) - *(dp + i - 1);

        char buf[32];
        char* tmpStr = intToStr(result, sizeof(buf), buf);
        fputs(tmpStr, stdout); fputc('\n', stdout);
    }

    return 0;
}

char** tokenizer(const char* input) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0; int end = 0;

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
            *tokensPtr++ = newTkn; curr++;

            start = ++end;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

    return;
}

char* intToStr(int target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long temp = target;
    if(target < 0) {
        temp *= -1;
    }

    do {
        *--bufPtr = temp % 10 + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0)
        *--bufPtr = '-';

    return bufPtr;
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
