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
1 초	128 MB	482263	263303	219522	54.734%
문제
시험 점수를 입력받아 90 ~ 100점은 A, 80 ~ 89점은 B, 70 ~ 79점은 C, 60 ~ 69점은 D, 나머지 점수는 F를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 시험 점수가 주어진다. 시험 점수는 0보다 크거나 같고, 100보다 작거나 같은 정수이다.

출력
시험 성적을 출력한다.

예제 입력 1
100
예제 출력 1
A
*/
#include<stdio.h>

int parseInt(const char* str);
_Bool isBlank(char ch);

int main () {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int score = parseInt(input);

    if(score >= 90) {
        fputs("A\n", stdout);
    } else if(score >= 80) {
        fputs("B\n", stdout);
    } else if(score >= 70) {
        fputs("C\n", stdout);
    } else if(score >= 60) {
        fputs("D\n", stdout);
    } else {
        fputs("F\n", stdout);
    }

    return 0;
}

int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

    char* strPtr = (char*)str;

    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(isBlank(*strPtr) != 1) {
        char ch = *strPtr++;
        result *= 10;
        result += ch - '0';
    }

    return result * sign;
}

_Bool isBlank(char ch) {
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
