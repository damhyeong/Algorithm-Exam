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
1 초	256 MB	308459	171734	140155	56.060%

문제
---
N개의 숫자가 공백 없이 쓰여있다.

이 숫자를 모두 합해서 출력하는 프로그램을 작성하시오.


입력
---
첫째 줄에 숫자의 개수 N (1 ≤ N ≤ 100)이 주어진다.

둘째 줄에 숫자 N개가 공백없이 주어진다.


출력
---
입력으로 주어진 숫자 N개의 합을 출력한다.

예제 입력 1
1
1
예제 출력 1
1
예제 입력 2
5
54321
예제 출력 2
15
예제 입력 3
25
7000000000000000000000000
예제 출력 3
7
예제 입력 4
11
10987654321
예제 출력 4
46
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int total = 0;
    char ch;
    while(isBlank(ch = fgetc(stdin)) != 1) {
        total += ch - '0';
    }

    char* result = intToStr(total);
    fputs(result, stdout); fputc('\n', stdout);

    free(result);

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
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    int idx = endIdx;
    while(idx >= startIdx) {
        result[idx--] = (target % 10) + '0';
        target /= 10;
    }
    if(sign == -1) {
        *result = '-';
    }

    return result;
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
