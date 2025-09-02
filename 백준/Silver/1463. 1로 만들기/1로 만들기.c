
/**
1로 만들기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.15 초 (하단 참고)	128 MB	366436	129085	82496	33.761%

문제
---
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

1. X가 3으로 나누어 떨어지면, 3으로 나눈다.
2. X가 2로 나누어 떨어지면, 2로 나눈다.
3. 1을 뺀다.

정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다.

연산을 사용하는 횟수의 최솟값을 출력하시오.

입력
---
첫째 줄에 1보다 크거나 같고, 10^6보다 작거나 같은 정수 N이 주어진다.

출력
---
첫째 줄에 연산을 하는 횟수의 최솟값을 출력한다.

예제 입력 1
2
예제 출력 1
1
예제 입력 2
10
예제 출력 2
3

힌트
---
10의 경우에 10 → 9 → 3 → 1 로 3번 만에 만들 수 있다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* dp = (int*)malloc(sizeof(int) * (N + 2));
    *(dp + 1) = 0;

    int idx = 2;
    while(idx <= N) {
        int min = 1e7;
        if(idx % 2 == 0) {
            min = *(dp + (idx / 2)) < min ? *(dp + (idx / 2)) : min;
        }
        if(idx % 3 == 0) {
            min = *(dp + (idx / 3)) < min ? *(dp + (idx / 3)) : min;
        }

        min = *(dp + idx - 1) < min ? *(dp + idx - 1) : min;

        *(dp + idx++) = min + 1;
    }

    char* resultStr = intToStr(*(dp + N));
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);
    free(dp);

    return 0;
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
    *result = idx == 0 ? '0' : *result;

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
