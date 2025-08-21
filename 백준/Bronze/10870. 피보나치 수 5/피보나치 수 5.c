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
1 초	256 MB	132312	80211	67078	61.047%

문제
---
피보나치 수는 0과 1로 시작한다.

0번째 피보나치 수는 0이고, 1번째 피보나치 수는 1이다.

그 다음 2번째 부터는 바로 앞 두 피보나치 수의 합이 된다.

이를 식으로 써보면 Fn = Fn-1 + Fn-2 (n ≥ 2)가 된다.

n=17일때 까지 피보나치 수를 써보면 다음과 같다.

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597

n이 주어졌을 때, n번째 피보나치 수를 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 n이 주어진다. n은 20보다 작거나 같은 자연수 또는 0이다.

출력
---
첫째 줄에 n번째 피보나치 수를 출력한다.

예제 입력 1
10
예제 출력 1
55
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

int fibonachi(int index);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int result = fibonachi(N);

    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    return 0;
}

int fibonachi(int index) {
    if(index == 0 || index == 1) {
        return index == 0 ? 0 : 1;
    }

    return fibonachi(index - 1) + fibonachi(index - 2);
}

char* intToStr(int target) {
    short sign = 1;
    short len = 0;

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
