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
1 초	64 MB	22469	11337	10081	50.367%

문제
---
서강대학교 컴퓨터공학과 실습실 R912호에는 현재 N개의 창문이 있고 또 N명의 사람이 있다.

1번째 사람은 1의 배수 번째 창문을 열려 있으면 닫고 닫혀 있으면 연다.

2번째 사람은 2의 배수 번째 창문을 열려 있으면 닫고 닫혀 있으면 연다.

이러한 행동을 N번째 사람까지 진행한 후 열려 있는 창문의 개수를 구하라.

단, 처음에 모든 창문은 닫혀 있다.


예를 들어 현재 3개의 창문이 있고 3명의 사람이 있을 때,

1번째 사람은 1의 배수인 1,2,3번 창문을 연다. (1, 1, 1)
2번째 사람은 2의 배수인 2번 창문을 닫는다. (1, 0, 1)
3번째 사람은 3의 배수인 3번 창문을 닫는다. (1, 0, 0)

결과적으로 마지막에 열려 있는 창문의 개수는 1개 이다.

입력
---
첫 번째 줄에는 창문의 개수와 사람의 수

N(1 ≤ N ≤ 2,100,000,000)이 주어진다.

출력
---
마지막에 열려 있는 창문의 개수를 출력한다.

예제 입력 1
3
예제 출력 1
1
예제 입력 2
24
예제 출력 2
4
*/

/**
문제의 변수 크기 특성상, 일단 N 기준의 루프문으로는 해결할 수 없다는 것을 알게 된다.

1억번 정도가 1초?(넉넉잡아) 정도로 취급되는데, 21 억이면 거의 21 초 이상이 걸리게 된다.

1 부터 N 까지의 창문과 N 명의 사람. 그리고, 각각의 사람은 자신이 1 번째라면 1 번 걸러 창문을 여닫으므로, 모든 창문을 여닫는다고 말할 수 있다.

2 번째 사람은 2 번 걸러 창문을 여닫으므로, 중간은 건너뛴다.

무언가 직관적으로 띄는 수학적 규칙이 없어서, 한번 N = 10 일 때를 상정해 보자.

1  : 1 1 1 1 1 1 1 1 1 1
2  : 1 0 1 0 1 0 1 0 1 0
3  : 1 0 0 0 1 1 1 0 0 0
4  : 1 0 0 1 1 1 1 1 0 0
5  : 1 0 0 1 0 1 1 1 0 1
6  : 1 0 0 1 0 0 1 1 0 1
7  : 1 0 0 1 0 0 0 1 0 1
8  : 1 0 0 1 0 0 0 0 0 1
9  : 1 0 0 1 0 0 0 0 1 1
10 : 1 0 0 1 0 0 0 0 1 0

무언가 규칙이 눈에 띌 것 같다. 이번에는 조금 고생한다는 생각으로, N = 17 일 때를 상정 해 보자.

1   : 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
2   : 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
3   : 1 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 1
4   : 1 0 0 1 1 1 1 1 0 0 1 0 1 0 0 1 1
5   : 1 0 0 1 0 1 1 1 0 1 1 0 1 0 1 1 1
6   : 1 0 0 1 0 0 1 1 0 1 1 1 1 0 1 1 1
7   : 1 0 0 1 0 0 0 1 0 1 1 1 1 1 1 1 1
8   : 1 0 0 1 0 0 0 0 0 1 1 1 1 1 1 0 1
9   : 1 0 0 1 0 0 0 0 1 1 1 1 1 1 1 0 1
10  : 1 0 0 1 0 0 0 0 1 0 1 1 1 1 1 0 1
11  : 1 0 0 1 0 0 0 0 1 0 0 1 1 1 1 0 1
12  : 1 0 0 1 0 0 0 0 1 0 0 0 1 1 1 0 1
13  : 1 0 0 1 0 0 0 0 1 0 0 0 0 1 1 0 1
14  : 1 0 0 1 0 0 0 0 1 0 0 0 0 0 1 0 1
15  : 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 1
16  : 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0 1 1
17  : 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0 1 0

여기서 발견되는 규칙이 존재한다.

그런데, 약간은 애매모호하기도 하다.

1. 중간에 들어가는 '0' 의 개수는, 2, 4, 6, .... 2 * N 의 형태인가?

아니면,

2. 2, 4, 6, 10, ..., idx(x - 2) + idx(x - 1) 의 형태인가?

나는 1 번의 형태를 가지고 있다고 생각한다.

그렇다면, 1이 발견되는 위치는,

1 번째, 4 번째, 9 번째, 16 번째 이다.

1, 3, 5, 7

그렇다면, 크기는 1 부터 시작하여, 2 씩 크기를 더해가며, 주어진 N 을 넘지 않을 때 까지 1 의 개수를 구하면 된다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int currLen = 1;
    int currIdx = 1;
    int total = 0;
    while(currIdx <= N) {
        total++;
        currLen += 2;
        currIdx += currLen;
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

    while(isBlank(*strPtr) != 1) {
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
