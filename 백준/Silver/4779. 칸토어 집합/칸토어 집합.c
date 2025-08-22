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
칸토어 집합

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	27908	13053	10393	45.627%

문제
---
칸토어 집합은 0과 1사이의 실수로 이루어진 집합으로,

구간 [0, 1]에서 시작해서 각 구간을 3등분하여 가운데 구간을 반복적으로 제외하는 방식으로 만든다.

전체 집합이 유한이라고 가정하고, 다음과 같은 과정을 통해서 칸토어 집합의 근사를 만들어보자.

1. -가 3N개 있는 문자열에서 시작한다.

2. 문자열을 3등분 한 뒤, 가운데 문자열을 공백으로 바꾼다. 이렇게 하면, 선(문자열) 2개가 남는다.

3. 이제 각 선(문자열)을 3등분 하고, 가운데 문자열을 공백으로 바꾼다. 이 과정은 모든 선의 길이가 1일때 까지 계속 한다.

예를 들어, N=3인 경우, 길이가 27인 문자열로 시작한다.

---------------------------
여기서 가운데 문자열을 공백으로 바꾼다.

---------         ---------
남은 두 선의 가운데 문자열을 공백으로 바꾼다.

---   ---         ---   ---
한번 더

- -   - -         - -   - -

모든 선의 길이가 1이면 멈춘다.

N이 주어졌을 때, 마지막 과정이 끝난 후 결과를 출력하는 프로그램을 작성하시오.


입력
---
입력을 여러 줄로 이루어져 있다.

각 줄에 N이 주어진다.

파일의 끝에서 입력을 멈춘다.

N은 0보다 크거나 같고, 12보다 작거나 같은 정수이다.


출력
---
입력으로 주어진 N에 대해서, 해당하는 칸토어 집합의 근사를 출력한다.

예제 입력 1
0
1
3
2
예제 출력 1
-
- -
- -   - -         - -   - -
- -   - -
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void cantoer(char* str, int i, int j);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    while(fgets(input, sizeof(input), stdin) != NULL) {
        int num = parseInt(input);

        if(num == 0) {
            fputs("-\n", stdout);
            continue;
        }

        int N = 1;
        while(num-- > 0) {
            N *= 3;
        }

        char* str = (char*)malloc(sizeof(char) * (N + 1));
        *(str + N) = 0;

        char* strPtr = str;
        int idx = 0;
        while(idx++ < N) {
            *strPtr++ = '-';
        }

        cantoer(str, 0, N);

        fputs(str, stdout); fputc('\n', stdout);
        free(str);
    }


    return 0;
}

void cantoer(char* str, int i, int j) {
    if(j - i <= 1) {
        return;
    }

    int len = j - i;
    int leftPivot = i + (len / 3);
    int rightPivot = j - (len / 3);

    int idx = leftPivot;
    while(idx < rightPivot) {
        *(str + idx++) = ' ';
    }

    cantoer(str, i, leftPivot); cantoer(str, rightPivot, j);

    return;
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
    *result = sign == 1 ? *result : '-';

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

    while(!isBlank(*strPtr)) {
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
