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
1 초	128 MB	258311	149692	124036	57.749%

문제
---
두 자연수 A와 B가 있을 때, A%B는 A를 B로 나눈 나머지 이다.

예를 들어, 7, 14, 27, 38을 3으로 나눈 나머지는 1, 2, 0, 2이다.

수 10개를 입력받은 뒤, 이를 42로 나눈 나머지를 구한다.

그 다음 서로 다른 값이 몇 개 있는지 출력하는 프로그램을 작성하시오.

입력
---
첫째 줄부터 열번째 줄 까지 숫자가 한 줄에 하나씩 주어진다. 이 숫자는 1,000보다 작거나 같고, 음이 아닌 정수이다.

출력
---
첫째 줄에, 42로 나누었을 때, 서로 다른 나머지가 몇 개 있는지 출력한다.

예제 입력 1
1
2
3
4
5
6
7
8
9
10
예제 출력 1
10

각 수를 42로 나눈 나머지는 1, 2, 3, 4, 5, 6, 7, 8, 9, 10이다.

예제 입력 2
42
84
252
420
840
126
42
84
420
126
예제 출력 2
1
모든 수를 42로 나눈 나머지는 0이다.

예제 입력 3
39
40
41
42
43
44
82
83
84
85
예제 출력 3
6
각 수를 42로 나눈 나머지는 39, 40, 41, 0, 1, 2, 40, 41, 0, 1이다. 서로 다른 값은 6개가 있다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    int size = 42;
    int* extras = (int*) calloc(size + 1, sizeof(int));
    int* extrasPtr = (int*)extras;

    while(fgets(input, sizeof(input), stdin) != NULL) {
        int extra = parseInt(input) % size;

        *(extras + extra) = 1;
    }

    int idx = 0;
    int diff = 0;
    while(idx < size) {
        _Bool isExtra = *extrasPtr++;

        if(isExtra == 1) {
            diff++;
        }
        idx++;
    }

    char* result = intToStr(diff);

    fputs(result, stdout); fputc('\n', stdout);

    free(result);

    return 0;
}

char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= sign;
    }

    int temp = target;
    do {
        temp /= 10;
        len++;
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    int idx = endIdx;
    while(idx >= startIdx) {
        result[idx--] = target % 10 + '0';
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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
