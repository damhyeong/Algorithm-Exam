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
1 초	128 MB	390474	240571	198149	62.111%

문제
---
첫째 줄에는 별 1개, 둘째 줄에는 별 2개, N번째 줄에는 별 N개를 찍는 문제

입력
---
첫째 줄에 N(1 ≤ N ≤ 100)이 주어진다.

출력
---
첫째 줄부터 N번째 줄까지 차례대로 별을 출력한다.

예제 입력 1
5
예제 출력 1
*
**
***
****
*****
*/

/**
복잡한 문자열을 출력하는 것이 아니기 때문에,

StringBuilder 와 같은 structure 는 만들지 않고, 직접 출력한다.
*/

#include<stdio.h>


int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int length = parseInt(input);

    int currStar = 0;

    while(currStar++ < length) {
        for(int i = 0; i < currStar; i++) {
            fputc('*', stdout);
        }
        fputc('\n', stdout);
    }

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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
