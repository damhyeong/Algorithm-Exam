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
2 초	128 MB	215272	98417	83672	45.148%

문제
---

위의 그림과 같이 육각형으로 이루어진 벌집이 있다.

그림에서 보는 바와 같이 중앙의 방 1부터 시작해서 이웃하는 방에 돌아가면서 1씩 증가하는 번호를 주소로 매길 수 있다.

숫자 N이 주어졌을 때,

벌집의 중앙 1에서 N번 방까지 최소 개수의 방을 지나서 갈 때 몇 개의 방을 지나가는지(시작과 끝을 포함하여)를 계산하는 프로그램을 작성하시오.

예를 들면,

- 13까지는 3개,
- 58까지는 5개를 지난다.

입력
---
첫째 줄에 N(1 ≤ N ≤ 1,000,000,000)이 주어진다.

출력
---
입력으로 주어진 방까지 최소 개수의 방을 지나서 갈 때 몇 개의 방을 지나는지 출력한다.

예제 입력 1
13
예제 출력 1
3
*/

/**
 * 1 번째 레이어 : 6개 - 결과 : 2
 * 2 번째 레이어 : 12개 - 결과 : 3
 * 3 번쨰 레이어 : 18개 - 결과 : 4
 *
 * 즉, 레이어 마다 6 개씩 늘어난다.
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
    N -= 1;

    int currDistance = 1;

    int base = 6;

    while(N > 0) {
        currDistance++;
        N -= base;
        base += 6;
    }

    char* resultStr = intToStr(currDistance);

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
