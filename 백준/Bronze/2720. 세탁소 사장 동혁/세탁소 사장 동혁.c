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
1 초	128 MB	55370	38177	34001	69.448%

문제
---
미국으로 유학간 동혁이는 세탁소를 운영하고 있다.

동혁이는 최근에 아르바이트로 고등학생 리암을 채용했다.

동혁이는 리암에게 실망했다.

리암은 거스름돈을 주는 것을 자꾸 실수한다.

심지어 $0.5달러를 줘야하는 경우에 거스름돈으로 $5달러를 주는것이다!

어쩔수 없이 뛰어난 코딩 실력을 발휘해 리암을 도와주는 프로그램을 작성하려고 하지만,

디아블로를 하느라 코딩할 시간이 없어서 이 문제를 읽고 있는 여러분이 대신 해주어야 한다.

거스름돈의 액수가 주어지면 리암이 줘야할

쿼터(Quarter, $0.25)의 개수, 다임(Dime, $0.10)의 개수, 니켈(Nickel, $0.05)의 개수, 페니(Penny, $0.01)의 개수를 구하는 프로그램을 작성하시오.

거스름돈은 항상 $5.00 이하이고, 손님이 받는 동전의 개수를 최소로 하려고 한다.

예를 들어, $1.24를 거슬러 주어야 한다면, 손님은 4쿼터, 2다임, 0니켈, 4페니를 받게 된다.


입력
---
첫째 줄에 테스트 케이스의 개수 T가 주어진다.

각 테스트 케이스는 거스름돈 C를 나타내는 정수 하나로 이루어져 있다.

C의 단위는 센트이다.

(1달러 = 100센트) (1<=C<=500)


출력
---
각 테스트케이스에 대해 필요한

쿼터의 개수, 다임의 개수, 니켈의 개수, 페니의 개수를 공백으로 구분하여 출력한다.


예제 입력 1
3
124
25
194
예제 출력 1
4 2 0 4
1 0 0 0
7 1 1 4
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int loop = parseInt(input);

    while(--loop >= 0) {
        fgets(input, sizeof(input), stdin);

        int total = parseInt(input);

        int quater = total / 25; total %= 25;
        int daim = total / 10; total %= 10;
        int nikel = total / 5; total %= 5;
        int sent = total;

        char* s1 = intToStr(quater);
        char* s2 = intToStr(daim);
        char* s3 = intToStr(nikel);
        char* s4 = intToStr(sent);

        fputs(s1, stdout); fputc(' ', stdout);
        fputs(s2, stdout); fputc(' ', stdout);
        fputs(s3, stdout); fputc(' ', stdout);
        fputs(s4, stdout); fputc('\n', stdout);

        free(s1); free(s2); free(s3); free(s4);
    }

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
    if(sign == -1) { *result = '-'; }

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
