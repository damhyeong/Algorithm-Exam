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
1 초	128 MB	162312	95172	82493	58.409%

문제
---
상근이의 할머니는 아래 그림과 같이 오래된 다이얼 전화기를 사용한다.

* 1 --> 할당 알파벳 없음 : 2초         |
* 2 --> A, B, C                   |
* 3 --> D, E, F                   | 밑으로 갈 수록 1 초씩 늘어남.
* 4 --> G, H, I                   v
* 5 --> J, K, L
* 6 --> M, N, O
* 7 --> P, Q, R, S
* 8 --> T, U, V
* 9 --> W, X, Y, Z
* 0 --> 알파벳이 아님

전화를 걸고 싶은 번호가 있다면, 숫자를 하나를 누른 다음에 금속 핀이 있는 곳 까지 시계방향으로 돌려야 한다. 숫자를 하나 누르면 다이얼이 처음 위치로 돌아가고, 다음 숫자를 누르려면 다이얼을 처음 위치에서 다시 돌려야 한다.

숫자 1을 걸려면 총 2초가 필요하다. 1보다 큰 수를 거는데 걸리는 시간은 이보다 더 걸리며, 한 칸 옆에 있는 숫자를 걸기 위해선 1초씩 더 걸린다.

상근이의 할머니는 전화 번호를 각 숫자에 해당하는 문자로 외운다. 즉, 어떤 단어를 걸 때, 각 알파벳에 해당하는 숫자를 걸면 된다. 예를 들어, UNUCIC는 868242와 같다.

할머니가 외운 단어가 주어졌을 때, 이 전화를 걸기 위해서 필요한 최소 시간을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 알파벳 대문자로 이루어진 단어가 주어진다. 단어의 길이는 2보다 크거나 같고, 15보다 작거나 같다.

출력
첫째 줄에 다이얼을 걸기 위해서 필요한 최소 시간을 출력한다.

예제 입력 1
WA
예제 출력 1
13
예제 입력 2
UNUCIC
예제 출력 2
36
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

int chToTime(char ch);
char* intToStr(int target);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char* inputPtr = (char*)input;

    int result = 0;

    while(*inputPtr) {
        result += chToTime(*inputPtr++);
    }

    char* resultStr = intToStr(result);

    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}


// * 1 --> 할당 알파벳 없음 : 2초         |
// * 2 --> A, B, C                   |
// * 3 --> D, E, F                   | 밑으로 갈 수록 1 초씩 늘어남.
// * 4 --> G, H, I                   v
// * 5 --> J, K, L
// * 6 --> M, N, O
// * 7 --> P, Q, R, S
// * 8 --> T, U, V
// * 9 --> W, X, Y, Z
// * 0 --> 알파벳이 아님
int chToTime(char ch) {
    switch(ch) {
        case 'A':
        case 'B':
        case 'C':
        return 3;

        case 'D':
        case 'E':
        case 'F':
        return 4;

        case 'G':
        case 'H':
        case 'I':
        return 5;

        case 'J':
        case 'K':
        case 'L':
        return 6;

        case 'M':
        case 'N':
        case 'O':
        return 7;

        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        return 8;

        case 'T':
        case 'U':
        case 'V':
        return 9;

        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        return 10;

        default:
        return 0;
    }
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
    if(sign == -1) {
        *result = '-';
    }

    return result;
}
