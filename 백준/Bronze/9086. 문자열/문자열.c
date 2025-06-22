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
1 초	128 MB	110517	69745	62682	63.688%

문제
---
문자열을 입력으로 주면 문자열의 첫 글자와 마지막 글자를 출력하는 프로그램을 작성하시오.

입력
---
입력의 첫 줄에는 테스트 케이스의 개수 T(1 ≤ T ≤ 10)가 주어진다.

각 테스트 케이스는 한 줄에 하나의 문자열이 주어진다.

문자열은 알파벳 A~Z 대문자로 이루어지며 알파벳 사이에 공백은 없으며 문자열의 길이는 1000보다 작다.

출력
---
각 테스트 케이스에 대해서 주어진 문자열의 첫 글자와 마지막 글자를 연속하여 출력한다.

예제 입력 1
3
ACDKJFOWIEGHE
O
AB
예제 출력 1
AE
OO
AB
*/

#include<stdio.h>

_Bool isBlank(char ch);

int main(void) {
    char input[2000];

    fgets(input, sizeof(input), stdin);

    while(fgets(input, sizeof(input), stdin) != NULL) {
        char ch = *input;

        char* inputPtr = (char*)input;

        char lastCh;

        while(isBlank(*inputPtr) != 1) {
            lastCh = *inputPtr;
            inputPtr++;
        }

        fputc(ch, stdout); fputc(lastCh, stdout); fputc('\n', stdout);
    }

    return 0;

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
