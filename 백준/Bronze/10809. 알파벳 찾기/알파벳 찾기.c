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
1 초	256 MB	267864	144616	118814	53.625%

문제
---
알파벳 소문자로만 이루어진 단어 S가 주어진다.

각각의 알파벳에 대해서,

단어에 포함되어 있는 경우에는 처음 등장하는 위치를,

포함되어 있지 않은 경우에는 -1을 출력하는 프로그램을 작성하시오.

입력
---
첫째 줄에 단어 S가 주어진다.

단어의 길이는 100을 넘지 않으며, 알파벳 소문자로만 이루어져 있다.

출력
---
각각의 알파벳에 대해서,

a가 처음 등장하는 위치, b가 처음 등장하는 위치, ... z가 처음 등장하는 위치를 공백으로 구분해서 출력한다.

만약, 어떤 알파벳이 단어에 포함되어 있지 않다면 -1을 출력한다.

단어의 첫 번째 글자는 0번째 위치이고, 두 번째 글자는 1번째 위치이다.


예제 입력 1
baekjoon
예제 출력 1
1 0 -1 -1 2 -1 -1 -1 -1 4 3 -1 -1 7 5 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
_Bool isBlank(char ch);

int main(void) {
    int alphabets['z' - 'a' + 1];

    int idx = 0;
    while(idx < ('z' - 'a' + 1)) {
        alphabets[idx++] = -1;
    }

    char input[255];

    fgets(input, sizeof(input), stdin);

    char* inputPtr = (char*)input;

    char ch;
    idx = 0;
    while(isBlank(*inputPtr) != 1) {
        ch = *inputPtr++;

        alphabets[ch - 'a'] = alphabets[ch - 'a'] == -1 ? idx : alphabets[ch - 'a'];
        idx++;
    }

    idx = 0;
    while(idx < ('z' - 'a' + 1)) {
        char* result = intToStr(alphabets[idx++]);
        fputs(result, stdout); fputc(' ', stdout);
        free(result);
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
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    int idx = endIdx;
    while(idx >= startIdx) {
        result[idx--] = (target % 10) + '0';
        target /= 10;
    }
    if(sign == -1) {
        *result = '-';
    }

    return result;
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
