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
1 초	128 MB	254484	123025	88029	46.960%

문제
---
괄호 문자열(Parenthesis String, PS)은 두 개의 괄호 기호인 ‘(’ 와 ‘)’ 만으로 구성되어 있는 문자열이다.

그 중에서 괄호의 모양이 바르게 구성된 문자열을 올바른 괄호 문자열(Valid PS, VPS)이라고 부른다.

한 쌍의 괄호 기호로 된 “( )” 문자열은 기본 VPS 이라고 부른다.

만일 x 가 VPS 라면 이것을 하나의 괄호에 넣은 새로운 문자열 “(x)”도 VPS 가 된다.

그리고 두 VPS x 와 y를 접합(concatenation)시킨 새로운 문자열 xy도 VPS 가 된다.

예를 들어 “(())()”와 “((()))” 는 VPS 이지만

“(()(”, “(())()))” , 그리고 “(()” 는 모두 VPS 가 아닌 문자열이다.

여러분은 입력으로 주어진 괄호 문자열이 VPS 인지 아닌지를 판단해서 그 결과를 YES 와 NO 로 나타내어야 한다.

입력
---
입력 데이터는 표준 입력을 사용한다.

입력은 T개의 테스트 데이터로 주어진다.

입력의 첫 번째 줄에는 입력 데이터의 수를 나타내는 정수 T가 주어진다.

각 테스트 데이터의 첫째 줄에는 괄호 문자열이 한 줄에 주어진다.

하나의 괄호 문자열의 길이는 2 이상 50 이하이다.


출력
---
출력은 표준 출력을 사용한다.

만일 입력 괄호 문자열이 올바른 괄호 문자열(VPS)이면 “YES”,

아니면 “NO”를 한 줄에 하나씩 차례대로 출력해야 한다.


예제 입력 1
6
(())())
(((()())()
(()())((()))
((()()(()))(((())))()
()()()()(()()())()
(()((())()(
예제 출력 1
NO
NO
YES
NO
YES
NO

예제 입력 2
3
((
))
())(()
예제 출력 2
NO
NO
NO
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* parseToken(const char* str);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int T = parseInt(input);

    int idx = 0;
    while(idx++ < T) {
        int currPtr = 0;

        fgets(input, sizeof(input), stdin);

        char* parenthesis = parseToken(input);
        char* parenthesisPtr = parenthesis;

        while(*parenthesisPtr) {
            char ch = *parenthesisPtr++;

            if(ch == '(') {
                currPtr++;
            } else if(ch == ')') {
                currPtr--;

                if(currPtr < 0) {
                    break;
                }
            }
        }

        if(currPtr == 0) {
            fputs("YES\n", stdout);
        } else {
            fputs("NO\n", stdout);
        }

        free(parenthesis);
    }

    return 0;
}

char* parseToken(const char* str) {
    char* strPtr = (char*)str;

    int len = 0;

    while(isBlank(*strPtr++) != 1) {
        len++;
    }

    char* result = (char*)malloc(sizeof(char) * (len + 1));
    *(result + len) = 0;

    int idx = 0;
    while(idx < len) {
        *(result + idx) = *(str + idx);
        idx++;
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
