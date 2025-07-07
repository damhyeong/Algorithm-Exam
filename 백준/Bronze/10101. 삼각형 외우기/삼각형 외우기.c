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
1 초	256 MB	58870	32089	29515	56.607%

문제
---
창영이는 삼각형의 종류를 잘 구분하지 못한다.

따라서 프로그램을 이용해 이를 외우려고 한다.

삼각형의 세 각을 입력받은 다음,

- 세 각의 크기가 모두 60이면, Equilateral
- 세 각의 합이 180이고, 두 각이 같은 경우에는 Isosceles
- 세 각의 합이 180이고, 같은 각이 없는 경우에는 Scalene
- 세 각의 합이 180이 아닌 경우에는 Error

를 출력하는 프로그램을 작성하시오.

입력
---
총 3개의 줄에 걸쳐 삼각형의 각의 크기가 주어진다. 모든 정수는 0보다 크고, 180보다 작다.

출력
---
문제의 설명에 따라 Equilateral, Isosceles, Scalene, Error 중 하나를 출력한다.

예제 입력 1
60
70
50
예제 출력 1
Scalene
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    int size = 3;

    int* intList = (int*)malloc(sizeof(int) * (size + 1));
    *(intList + size) = 0;

    int idx = 0;
    while(idx < size) {
        fgets(input, sizeof(input), stdin);

        *(intList + idx++) = parseInt(input);
    }

    idx = 0;

    int same = 1;
    int total = 0;
    int currNum = 0;

    while(idx < size) {
        int num = *(intList + idx++);
        total += num;

        if(currNum == num) {
            same++;
        } else {
            same = 1;
            currNum = num;
        }
    }

    if(same != 3) {
        same = *intList == *(intList + 2) ? 2 : same;
    }

    if(total == 180) {
        if(same == 3) {
            fputs("Equilateral\n", stdout);
        } else if(same == 2) {
            fputs("Isosceles\n", stdout);
        } else {
            fputs("Scalene\n", stdout);
        }
    } else {
        fputs("Error\n", stdout);
    }

    free(intList);

    return 0;
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
