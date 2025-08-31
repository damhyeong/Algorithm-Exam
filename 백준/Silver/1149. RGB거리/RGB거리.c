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
RGB거리

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	128 MB	136083	79244	58591	57.198%

문제
---
RGB거리에는 집이 N개 있다.

거리는 선분으로 나타낼 수 있고, 1번 집부터 N번 집이 순서대로 있다.

집은 빨강, 초록, 파랑 중 하나의 색으로 칠해야 한다.

각각의 집을 빨강, 초록, 파랑으로 칠하는 비용이 주어졌을 때, 아래 규칙을 만족하면서 모든 집을 칠하는 비용의 최솟값을 구해보자.

* 1번 집의 색은 2번 집의 색과 같지 않아야 한다.

* N번 집의 색은 N-1번 집의 색과 같지 않아야 한다.

* i(2 ≤ i ≤ N-1)번 집의 색은 i-1번, i+1번 집의 색과 같지 않아야 한다.


입력
---
첫째 줄에 집의 수 N(2 ≤ N ≤ 1,000)이 주어진다.

둘째 줄부터 N개의 줄에는 각 집을 빨강, 초록, 파랑으로 칠하는 비용이 1번 집부터 한 줄에 하나씩 주어진다.

집을 칠하는 비용은 1,000보다 작거나 같은 자연수이다.


출력
---
첫째 줄에 모든 집을 칠하는 비용의 최솟값을 출력한다.

예제 입력 1
3
26 40 83
49 60 57
13 89 99
예제 출력 1
96

예제 입력 2
3
1 100 100
100 1 100
100 100 1
예제 출력 2
3

예제 입력 3
3
1 100 100
100 100 100
1 100 100
예제 출력 3
102

예제 입력 4
6
30 19 5
64 77 64
15 19 97
4 71 57
90 86 84
93 32 91
예제 출력 4
208

예제 입력 5
8
71 39 44
32 83 55
51 37 63
89 29 100
83 58 11
65 13 15
47 25 29
60 66 19
예제 출력 5
253
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeArrs(void** arrs);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int** arrs = (int**)malloc(sizeof(int*) * (N + 1));
    int** dps = (int**)malloc(sizeof(int*) * (N + 1));

    int idx = 0;
    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);

        *(arrs + idx) = (int*)malloc(sizeof(int*) * (3 + 1));
        *(dps + idx) = (int*)malloc(sizeof(int*) * (3 + 1));

        int jdx = 0;
        while(jdx < 3) {
            *(*(arrs + idx) + jdx) = parseInt(*(tokens + jdx));
            jdx++;
        }

        freeArrs((void**)tokens);

        idx++;
    }

    *(*(dps) + 0) = *(*(arrs) + 0);
    *(*(dps) + 1) = *(*(arrs) + 1);
    *(*(dps) + 2) = *(*(arrs) + 2);

    idx = 1;
    while(idx < N) {
        int jdx = 0;
        while(jdx < 3) {
            int currPrice = *(*(arrs + idx) + jdx);

            int prevTotal1 = *(*(dps + idx - 1) + ((jdx + 1) % 3));
            int prevTotal2 = *(*(dps + idx - 1) + ((jdx + 2) % 3));

            *(*(dps + idx) + jdx) = (prevTotal1 < prevTotal2 ? prevTotal1 : prevTotal2) + currPrice;

            jdx++;
        }

        idx++;
    }

    int min = *(*(dps + N - 1));
    min = *(*(dps + N - 1) + 1) < min ? *(*(dps + N - 1) + 1) : min;
    min = *(*(dps + N - 1) + 2) < min ? *(*(dps + N - 1) + 2) : min;

    char* resultStr = intToStr(min);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    freeArrs((void**)arrs); freeArrs((void**)dps);

    return 0;
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
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

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
