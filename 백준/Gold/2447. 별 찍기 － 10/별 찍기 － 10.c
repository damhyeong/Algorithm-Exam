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
별 찍기 - 10

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	85613	48827	36473	56.739%

문제
---
재귀적인 패턴으로 별을 찍어 보자.

N이 3의 거듭제곱(3, 9, 27, ...)이라고 할 때, 크기 N의 패턴은 N×N 정사각형 모양이다.

크기 3의 패턴은 가운데에 공백이 있고, 가운데를 제외한 모든 칸에 별이 하나씩 있는 패턴이다.

***
* *
***
*
N이 3보다 클 경우, 크기 N의 패턴은 공백으로 채워진 가운데의 (N/3)×(N/3) 정사각형을 크기 N/3의 패턴으로 둘러싼 형태이다.

예를 들어 크기 27의 패턴은 예제 출력 1과 같다.

입력
---
첫째 줄에 N이 주어진다.

N은 3의 거듭제곱이다.

즉 어떤 정수 k에 대해 N=3^k이며, 이때 1 ≤ k < 8 이다.

출력
---
첫째 줄부터 N번째 줄까지 별을 출력한다.

예제 입력 1
27
예제 출력 1
***************************
* ** ** ** ** ** ** ** ** *
***************************
***   ******   ******   ***
* *   * ** *   * ** *   * *
***   ******   ******   ***
***************************
* ** ** ** ** ** ** ** ** *
***************************
*********         *********
* ** ** *         * ** ** *
*********         *********
***   ***         ***   ***
* *   * *         * *   * *
***   ***         ***   ***
*********         *********
* ** ** *         * ** ** *
*********         *********
***************************
* ** ** ** ** ** ** ** ** *
***************************
***   ******   ******   ***
* *   * ** *   * ** *   * *
***   ******   ******   ***
***************************
* ** ** ** ** ** ** ** ** *
***************************
*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void recursive(char** strList, int i, int j, int len);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    char** strList = (char**)malloc(sizeof(char*) * (N + 1));
    *(strList + N) = NULL;
    char** strListPtr = strList;

    int idx = 0;
    while(idx++ < N) {
        char* line = (char*)malloc(sizeof(char) * (N + 1));
        *(line + N) = 0;
        char* linePtr = line;
        int jdx = 0;
        while(jdx++ < N) {
            *linePtr++ = '*';
        }

        *strListPtr++ = line;
    }

    recursive(strList, 0, 0, N);

    idx = 0;
    while(idx < N) {
        char* str = *(strList + idx++);
        fputs(str, stdout); fputc('\n', stdout);
        free(str);
    }
    free(strList);

    return 0;
}

void recursive(char** strList, int i, int j, int len) {
    if(len <= 1) {
        return;
    }

    int leftPivot = i + (len / 3);
    int rightPivot = j + (len / 3);

    int idx = leftPivot;
    while(idx < leftPivot + (len / 3)) {
        int jdx = rightPivot;
        while(jdx < rightPivot + (len / 3)) {
            *(*(strList + idx) + jdx) = ' ';
            jdx++;
        }
        idx++;
    }

    int x = 0;
    while(x < 3) {
        int y = 0;
        while(y < 3) {
            if(x == 1 && y == 1) {
                y++;
                continue;
            }
            recursive(strList, (len / 3) * x + i, (len / 3) * y + j, len / 3);

            y++;
        }
        x++;
    }

    return;
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
        len++;
        temp /= 10;
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
