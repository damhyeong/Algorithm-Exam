
/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	129760	71624	63041	55.678%

문제
---
예제를 보고 규칙을 유추한 뒤에 별을 찍어 보세요.

입력
---
첫째 줄에 N(1 ≤ N ≤ 100)이 주어진다.

출력
---
첫째 줄부터 2×N-1번째 줄까지 차례대로 별을 출력한다.

예제 입력 1
5
예제 출력 1
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
*/

#include<stdio.h>

int absFromNum(int target, int num);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int loop = 2 * N - 1;

    int idx = 1;
    while(idx <= loop) {
        int blanks = absFromNum(idx++, N);
        int stars = (N - blanks) * 2 - 1;

        int jdx = 0;
        while(jdx++ < blanks) {
            fputc(' ', stdout);
        }
        jdx = 0;
        while(jdx++ < stars) {
            fputc('*', stdout);
        }
        fputc('\n', stdout);
    }

    return 0;
}

int absFromNum(int target, int num) {
    return (target > num) ? target - num : num - target;
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
