
/**
파도반 수열

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	128257	57702	47345	43.640%

문제
---
오른쪽 그림과 같이 삼각형이 나선 모양으로 놓여져 있다.

첫 삼각형은 정삼각형으로 변의 길이는 1이다.

그 다음에는 다음과 같은 과정으로 정삼각형을 계속 추가한다.

나선에서 가장 긴 변의 길이를 k라 했을 때, 그 변에 길이가 k인 정삼각형을 추가한다.

파도반 수열 P(N)은 나선에 있는 정삼각형의 변의 길이이다.

P(1)부터 P(10)까지 첫 10개 숫자는 1, 1, 1, 2, 2, 3, 4, 5, 7, 9이다.

N이 주어졌을 때, P(N)을 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 테스트 케이스의 개수 T가 주어진다.

각 테스트 케이스는 한 줄로 이루어져 있고, N이 주어진다.

(1 ≤ N ≤ 100)


출력
---
각 테스트 케이스마다 P(N)을 출력한다.

예제 입력 1
2
6
12
예제 출력 1
3
16
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char* intToStr(long target);
long parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    long* list = (long*)malloc(sizeof(long) * (101 + 1));
    long* listPtr = list;

    *listPtr++ = 0;
    *listPtr++ = 1;
    *listPtr++ = 1;
    *listPtr++ = 1;
    *listPtr++ = 2;
    *listPtr++ = 2;
    *listPtr++ = 3;

    int idx = 7;
    while(idx++ <= 100) {
        *listPtr = *(listPtr - 1) + *(listPtr - 5);
        listPtr++;
    }


    char input[100];

    fgets(input, sizeof(input), stdin);

    int T = parseInt(input);

    while(--T >= 0) {
        fgets(input, sizeof(input), stdin);

        long N = parseInt(input);

        char* resultStr = intToStr(*(list + N));

        fputs(resultStr, stdout); fputc('\n', stdout);
        free(resultStr);
    }

    return 0;
}

char* intToStr(long target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    long temp = target;
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
long parseInt(const char* str) {
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
