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
1 초	512 MB	45696	15811	14319	34.378%

문제
---
오늘도 서준이는 점근적 표기 수업 조교를 하고 있다.

아빠가 수업한 내용을 학생들이 잘 이해했는지 문제를 통해서 확인해보자.

알고리즘의 소요 시간을 나타내는 O-표기법(빅-오)을 다음과 같이 정의하자.

O(g(n)) = {f(n) | 모든 n ≥ n_0 에 대하여 f(n) ≤ c × g(n)인 양의 상수 c 와 n_0 가 존재한다}

이 정의는 실제 O-표기법(https://en.wikipedia.org/wiki/Big_O_notation)과 다를 수 있다.

함수 f(n) = a_1 * n + a_0,

양의 정수 c, n_0 가 주어질 경우 O(n) 정의를 만족하는지 알아보자.


입력
---
첫째 줄에 함수 f(n)을 나타내는 정수 a_1, a_0가 주어진다.

(0 ≤ |a_i| ≤ 100)

다음 줄에 양의 정수 c가 주어진다. (1 ≤ c ≤ 100)

다음 줄에 양의 정수 n_0가 주어진다. (1 ≤ n_0 ≤ 100)

출력
f(n), c, n_0 가 O(n) 정의를 만족하면 1, 아니면 0을 출력한다.

예제 입력 1
7 7
8
1
예제 출력 1
0
f(n) = 7n + 7, g(n) = n, c = 8, n0 = 1이다. f(1) = 14, c × g(1) = 8이므로 O(n) 정의를 만족하지 못한다.

예제 입력 2
7 7
8
10
예제 출력 2
1
f(n) = 7n + 7, g(n) = n, c = 8, n0 = 10이다. 모든 n ≥ 10에 대하여 7n + 7 ≤ 8n 이므로 O(n) 정의를 만족한다.
*/

/**
 * 첫 번째로 주어지는 것은, f(n) 에 사용될 차수들. f(n) = a_1 * n + a_0
 *
 * 두 번째로 주어지는 것은, g(n) 에 사용되는 n 의 곱을 의미한다 == c || g(n) = n 이므로, 결국 f(n) ≤ c × g(n) 이다.
 * 따라서, a_1(n) + a_0 <= c(n) 이다.
 *
 * 세 번째로 주어지는 것은, n_0 이다. n_0 은 1 ~ 100 사이의 자연수를 의미하며,
 * n_0 을 기점으로 같거나 더 큰 n 은 항상 a_1(n) + a_0 <= c(n) 이 식을 만족해야 한다는 것을 의미한다.
 *
 * 따라서, 식을 구성 한 뒤, n_0 이상의 모든 자연수에 대해 위의 식이 만족하는지에 따라 (정의 만족 == 1) or (정의 불만족 == 0) 으로 출력한다.
 *
 * 주목해야 할 점은, "a_1 * (n) + a_0 <= c * (n)" 이 식에서 a_1, a_0 는 -100 ~ 100 이며, 나머지 c 와 n_0 은 항상 자연수를 가진다.(음의 정수가 아님)
 *
 * 그렇다면, 이 식 또한 치환 대상으로서 분기점을 최소화 할 수 있다는 의미. (다행인 것은, 1차 방정식이라서 고려해야 할 점이 상대적으로 적다.)
 *
 * (a_1 - c) * (n) + a_0 <= 0
 *
 * 위의 식에서, (n) 은 곧 "n_0" 으로 입력된 수와 같거나 더 큰 모든 자연수를 일컫으며, 치환해야 한다.
 *
 * 그렇다면, 발생 할 수 있는 분기를 먼저 나눠보자.
 *
 * (a_1 - c) 가 0 인 경우 --> a_0 <= 0 ==> (a_0 이 자연수가 아닐 경우 "1", 자연수라면 "0")
 * (a_1 - c) 가 0 초과인 경우 --> {+(n) + a_0 <= 0 || n 은 양의 정수로 뻗음} ==> (a_0 값을 확인 할 것도 없이, "0")
 * (a_1 - c) 가 0 미만인 경우 --> {-(n) + a_0 <= 0 || n 은 양의 정수로 뻗음} ==> ((a_1 - c)(n_0) + a_0) 계산 후, 0 이하라면 "1", 0 초과라면 "0"
 *
 * 이렇게 문제를 푼다.
 */

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int a_1 = parseInt(*tokensPtr++);
    int a_0 = parseInt(*tokensPtr++);

    fgets(input, sizeof(input), stdin);

    int c = parseInt(input);

    fgets(input, sizeof(input), stdin);

    int n_0 = parseInt(input);

    /**
    * (a_1 - c) 가 0 인 경우 --> a_0 <= 0 ==> (a_0 이 자연수가 아닐 경우 "1", 자연수라면 "0")
    * (a_1 - c) 가 0 초과인 경우 --> {+(n) + a_0 <= 0 || n 은 양의 정수로 뻗음} ==> (a_0 값을 확인 할 것도 없이, "0")
    * (a_1 - c) 가 0 미만인 경우 --> {-(n) + a_0 <= 0 || n 은 양의 정수로 뻗음} ==> ((a_1 - c)(n_0) + a_0) 계산 후, 0 이하라면 "1", 0 초과라면 "0"
    */
    if(a_1 - c == 0) {
        if(a_0 <= 0) {
            fputs("1\n", stdout);
        } else {
            fputs("0\n", stdout);
        }
    } else if(a_1 - c > 0) {
        fputs("0\n", stdout);
    } else { // a_1 - c < 0
        int temp = (a_1 - c) * (n_0) + a_0;

        if(temp <= 0) {
            fputs("1\n", stdout);
        } else {
            fputs("0\n", stdout);
        }
    }

    return 0;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;

    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr++ = input[tknIdx++];
            }
            *tokensPtr++ = newTkn; currSize++;

            tknIdx = ++currIdx;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)malloc(sizeof(char*) * (size + 1));
                tokens = (char**)(tokens + currSize);
            }
        } else {
            currIdx++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        free(*tokensPtr++);
    }
    free(tokens);
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
    int startIdx = sign == 1 ? len : len + 1;

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
