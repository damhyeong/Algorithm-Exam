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
팩토리얼 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	50063	23343	20835	47.586%

문제
---
0보다 크거나 같은 정수 N이 주어진다.

이때, N!을 출력하는 프로그램을 작성하시오.

입력
---
첫째 줄에 정수 N(0 ≤ N ≤ 20)이 주어진다.

출력
---
첫째 줄에 N!을 출력한다.

예제 입력 1
10
예제 출력 1
3628800
예제 입력 2
0
예제 출력 2
1
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

long processFactorial(int deep, int limit);

char* longToStr(long target);
long parseLong(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    long N = parseLong(input);
    long result;
    if(N == 0) {
        result = 1;
    } else {
        result = processFactorial(1, N);
    }

    char* resultStr = longToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    return 0;
}

long processFactorial(int deep, int limit) {
    if(deep >= limit) {
        return limit;
    }

    return processFactorial(deep + 1, limit) * deep;
}

char* longToStr(long target) {
    short sign = 1;
    short len = 0;

    if(target < 0) {
        target *= -1;
        sign = -1;
    }

    long temp = target;
    do {
        temp /= 10;
        len++;
    } while(temp != 0);

    short size = sign == 1 ? len : len + 1;
    short endIdx = size - 1;
    short startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    *(result + size) = 0;

    short idx = endIdx;
    while(idx >= startIdx) {
        *(result + idx--) = (target % 10) + '0';
        target /= 10;
    }
    if(sign == -1) {
        *result = '-';
    }

    return result;
}
long parseLong(const char* str) {
    long sign = 1;
    long result = 0;

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
