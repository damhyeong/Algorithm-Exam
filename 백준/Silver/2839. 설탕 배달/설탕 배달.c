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
1 초	128 MB	377014	147648	109054	38.434%

문제
---
상근이는 요즘 설탕공장에서 설탕을 배달하고 있다.

상근이는 지금 사탕가게에 설탕을 정확하게 N킬로그램을 배달해야 한다.

설탕공장에서 만드는 설탕은 봉지에 담겨져 있다.

봉지는 3킬로그램 봉지와 5킬로그램 봉지가 있다.

상근이는 귀찮기 때문에, 최대한 적은 봉지를 들고 가려고 한다.

예를 들어,

18킬로그램 설탕을 배달해야 할 때,

3킬로그램 봉지 6개를 가져가도 되지만,

5킬로그램 3개와 3킬로그램 1개를 배달하면,

더 적은 개수의 봉지를 배달할 수 있다.

상근이가 설탕을 정확하게 N킬로그램 배달해야 할 때, 봉지 몇 개를 가져가면 되는지 그 수를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 N이 주어진다.

(3 ≤ N ≤ 5000)


출력
---
상근이가 배달하는 봉지의 최소 개수를 출력한다.

만약, 정확하게 N킬로그램을 만들 수 없다면 -1 을 출력한다.


예제 입력 1
18
예제 출력 1
4
예제 입력 2
4
예제 출력 2
-1
예제 입력 3
6
예제 출력 3
2
예제 입력 4
9
예제 출력 4
3
예제 입력 5
11
예제 출력 5
3
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

    int result = -1;

    // 5 에 딱 맞춰서 떨어짐.
    if(N % 5 == 0) {
        result = N / 5;
    } else {
        // 이 때, 정확히 5 에 맞춰 떨어지지 않기 때문에, 1, 2, 3, 4 중 하나의 나머지를 생각할 수 있음.
        int baseFive = N / 5;

        int left = N - (baseFive * 5);

        while(left % 3 != 0 && baseFive > 0) {
            left = N - (--baseFive * 5);
        }

        if(left % 3 == 0) {
            result = (baseFive) + (left / 3);
        }
    }

    char* resultStr = (char*)intToStr(result);

    fputs(resultStr, stdout); fputc('\n', stdout);

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
