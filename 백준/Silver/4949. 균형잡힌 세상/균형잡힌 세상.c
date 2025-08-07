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
1 초	128 MB	176599	61184	47135	33.305%

문제
---
세계는 균형이 잘 잡혀있어야 한다.

양과 음, 빛과 어둠 그리고 왼쪽 괄호와 오른쪽 괄호처럼 말이다.

정민이의 임무는 어떤 문자열이 주어졌을 때, 괄호들의 균형이 잘 맞춰져 있는지 판단하는 프로그램을 짜는 것이다.

문자열에 포함되는 괄호는 소괄호("()") 와 대괄호("[]")로 2종류이고,

문자열이 균형을 이루는 조건은 아래와 같다.

* 모든 왼쪽 소괄호("(")는 오른쪽 소괄호(")")와만 짝을 이뤄야 한다.
* 모든 왼쪽 대괄호("[")는 오른쪽 대괄호("]")와만 짝을 이뤄야 한다.
* 모든 오른쪽 괄호들은 자신과 짝을 이룰 수 있는 왼쪽 괄호가 존재한다.
* 모든 괄호들의 짝은 1:1 매칭만 가능하다. 즉, 괄호 하나가 둘 이상의 괄호와 짝지어지지 않는다.
* 짝을 이루는 두 괄호가 있을 때, 그 사이에 있는 문자열도 균형이 잡혀야 한다.
* 정민이를 도와 문자열이 주어졌을 때 균형잡힌 문자열인지 아닌지를 판단해보자.


입력
---
각 문자열은 마지막 글자를 제외하고 영문 알파벳, 공백, 소괄호("( )"), 대괄호("[ ]")로 이루어져 있으며, 온점(".")으로 끝나고, 길이는 100글자보다 작거나 같다.

입력의 종료조건으로 맨 마지막에 온점 하나(".")가 들어온다.


출력
---
각 줄마다 해당 문자열이 균형을 이루고 있으면 "yes"를, 아니면 "no"를 출력한다.

예제 입력 1
So when I die (the [first] I will see in (heaven) is a score list).
[ first in ] ( first out ).
Half Moon tonight (At least it is better than no Moon at all].
A rope may form )( a trail in a maze.
Help( I[m being held prisoner in a fortune cookie factory)].
([ (([( [ ] ) ( ) (( ))] )) ]).
 .
.
예제 출력 1
yes
yes
no
no
no
yes
yes

힌트
---
7번째의 " ."와 같이 괄호가 하나도 없는 경우도 균형잡힌 문자열로 간주할 수 있다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

int compare_str(char* s1, char* s2) {
    char* s1Ptr = s1;
    char* s2Ptr = s2;

    while(*s1Ptr && *s2Ptr) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
    }

    return *s1Ptr ? 1 : *s2Ptr ? -1 : 0;
}

int main(void) {
    char input[255];

    while(compare_str(fgets(input, sizeof(input), stdin), ".\n") != 0) {
        char* inputPtr = input;

        char* str = (char*)malloc(sizeof(char) * (101));
        *(str + 100) = 0;
        char* strPtr = str;

        while(*inputPtr) {
            char ch = *inputPtr++;

            if(ch == '(' || ch == '[') {
                *strPtr++ = ch;
            } else if(ch == ')' || ch == ']') {
                if(str == strPtr) {
                    strPtr++;
                    break;
                }

                char lastCh = *(strPtr - 1);

                _Bool isMatch1 = lastCh == '(' && ch == ')';
                _Bool isMatch2 = lastCh == '[' && ch == ']';

                if(isMatch1 || isMatch2) {
                    *--strPtr = 0;
                } else {
                    break;
                }
            }
        }

        if(str == strPtr) {
            fputs("yes\n", stdout);
        } else {
            fputs("no\n", stdout);
        }

        free(str);
    }

    return 0;
}
