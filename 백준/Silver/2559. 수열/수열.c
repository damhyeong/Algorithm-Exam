
/**
수열

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	81137	31588	23747	37.472%

문제
---
매일 아침 9시에 학교에서 측정한 온도가 어떤 정수의 수열로 주어졌을 때,

연속적인 며칠 동안의 온도의 합이 가장 큰 값을 알아보고자 한다.

예를 들어, 아래와 같이 10일 간의 온도가 주어졌을 때,

3 -2 -4 -9 0 3 7 13 8 -3

모든 연속적인 이틀간의 온도의 합은 아래와 같다.

1 -6 -13 -9 3 10 20 21 5

이때, 온도의 합이 가장 큰 값은 21이다.

또 다른 예로 위와 같은 온도가 주어졌을 때, 모든 연속적인 5일 간의 온도의 합은 아래와 같으며,

-12 -12 -3 14 31 28

이때, 온도의 합이 가장 큰 값은 31이다.

매일 측정한 온도가 정수의 수열로 주어졌을 때,

연속적인 며칠 동안의 온도의 합이 가장 큰 값을 계산하는 프로그램을 작성하시오.


입력
---
첫째 줄에는 두 개의 정수 N과 K가 한 개의 공백을 사이에 두고 순서대로 주어진다.

첫 번째 정수 N은 온도를 측정한 전체 날짜의 수이다.

N은 2 이상 100,000 이하이다.

두 번째 정수 K는 합을 구하기 위한 연속적인 날짜의 수이다.

K는 1과 N 사이의 정수이다.

둘째 줄에는 매일 측정한 온도를 나타내는 N개의 정수가 빈칸을 사이에 두고 주어진다.

이 수들은 모두 -100 이상 100 이하이다.


출력
---
첫째 줄에는 입력되는 온도의 수열에서 연속적인 K일의 온도의 합이 최대가 되는 값을 출력한다.

예제 입력 1
10 2
3 -2 -4 -9 0 3 7 13 8 -3
예제 출력 1
21
예제 입력 2
10 5
3 -2 -4 -9 0 3 7 13 8 -3
예제 출력 2
31
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(void);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main(void) {
    char** tokens = tokenizer();

    int N = parseInt(*tokens); // 온도를 측정한 전체 날짜의 수
    int K = parseInt(*(tokens + 1)); // 합을 구하기 위한 연속적인 날짜의 수

    freeArrs((void**)tokens);

    int* dp = (int*)malloc(sizeof(int) * (N + 2));
    int* dpPtr = dp;
    *dpPtr++ = 0;

    tokens = tokenizer();
    char** tokensPtr = tokens;

    int accumulate = 0;
    while(*tokensPtr) {
        accumulate += parseInt(*tokensPtr++);
        *dpPtr++ = accumulate;
    }

    int idx = K;

    int max = -1000000000;
    while(idx <= N) {
        int tmpSum = *(dp + idx) - *(dp + idx - K);
        max = max < tmpSum ? tmpSum : max;
        idx++;
    }

    char buf[32];
    char* resultStr = intToStr(max, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

char** tokenizer(void) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char ch;
    int tknSize = 0;

    // 최대 100 자의 단어라고 상정.
    char* buf = (char*)malloc(sizeof(char) * (100 + 1));
    *(buf + 100) = 0;
    char* bufPtr = buf;

    /**
     * 빈 칸이 이어졌을 경우 무시하는 로직으로 약간 틀어야 함.
     */

    while((ch = fgetc(stdin)) != -1) {
        if(isBlank(ch)) { // 빈 칸이 나와서 토큰화.
            if(tknSize == 0) { // 완료
                continue;
            }

            *bufPtr = 0;
            buf = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            *tokensPtr++ = buf; curr++;

            tknSize = 0;
            buf = (char*)malloc(sizeof(char) * (100 + 1));
            *(buf + 100) = 0;
            bufPtr = buf;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else { // 아직 문자 나오는중.
            *bufPtr++ = ch;
            tknSize++;
        }

        if(ch == '\n') break;
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
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0) {
        *--bufPtr = '-';
    }

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
