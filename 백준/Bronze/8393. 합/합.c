/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.

    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!
*/

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	333047	212042	178194	63.795%

문제
---
n이 주어졌을 때, 1부터 n까지 합을 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 n (1 ≤ n ≤ 10,000)이 주어진다.

출력
---
1부터 n까지 합을 출력한다.

예제 입력 1
3
예제 출력 1
6
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main (void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int num = parseInt(input);

    if(num < 0) {
        fputs("ERR : 0 이상의 숫자를 입력해야 합니다.\n", stderr);
        return 0;
    }

    long result = 0;
    while(num >= 0) {
        result += (long)num--;
    }

    char* resultStr = intToStr((int)result);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

    return 0;
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

    int size = (sign == 1) ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = (sign == 1) ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
        target /= 10;
    }
    if(sign == -1) {
        *result = '-';
    }

    return result;
}

int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
