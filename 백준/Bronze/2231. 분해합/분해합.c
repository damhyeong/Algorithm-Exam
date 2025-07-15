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
2 초	192 MB	193382	90030	70819	45.521%

문제
---
어떤 자연수 N이 있을 때, 그 자연수 N의 분해합은 N과 N을 이루는 각 자리수의 합을 의미한다.

어떤 자연수 M의 분해합이 N인 경우, M을 N의 생성자라 한다.

예를 들어, 245의 분해합은 256(=245+2+4+5)이 된다.

따라서 245는 256의 생성자가 된다.

물론, 어떤 자연수의 경우에는 생성자가 없을 수도 있다.

반대로, 생성자가 여러 개인 자연수도 있을 수 있다.


자연수 N이 주어졌을 때, N의 가장 작은 생성자를 구해내는 프로그램을 작성하시오.

입력
---
첫째 줄에 자연수 N(1 ≤ N ≤ 1,000,000) 이 주어진다.

출력
---
첫째 줄에 답을 출력한다.

생성자가 없는 경우에는 0을 출력한다.


예제 입력 1
216
예제 출력 1
198
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

    int constructorNum = 0;

    int idx = 1;
    while(idx <= N) {
        char* tempStr = intToStr(idx);

        char* tempStrPtr = (char*)tempStr;

        int tmpTotal = idx;

        while(isBlank(*tempStrPtr) != 1) {
            tmpTotal += *tempStrPtr++ - '0';
        }

        free(tempStr);

        if(tmpTotal == N) {
            constructorNum = idx;
            break;
        }

        idx++;
    }

    char* resultStr = intToStr(constructorNum);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

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
