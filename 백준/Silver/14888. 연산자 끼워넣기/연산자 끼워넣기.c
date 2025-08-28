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
연산자 끼워넣기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	127499	59484	39586	47.225%

문제
---
N개의 수로 이루어진 수열 A1, A2, ..., AN이 주어진다.

또, 수와 수 사이에 끼워넣을 수 있는 N-1개의 연산자가 주어진다.

연산자는 덧셈(+), 뺄셈(-), 곱셈(×), 나눗셈(÷)으로만 이루어져 있다.

우리는 수와 수 사이에 연산자를 하나씩 넣어서, 수식을 하나 만들 수 있다.

이때, 주어진 수의 순서를 바꾸면 안 된다.

예를 들어, 6개의 수로 이루어진 수열이 1, 2, 3, 4, 5, 6이고,

주어진 연산자가 덧셈(+) 2개, 뺄셈(-) 1개, 곱셈(×) 1개, 나눗셈(÷) 1개인 경우에는 총 60가지의 식을 만들 수 있다.

예를 들어, 아래와 같은 식을 만들 수 있다.

1+2+3-4×5÷6
1÷2+3+4-5×6
1+2÷3×4-5+6
1÷2×3-4+5+6

식의 계산은 연산자 우선 순위를 무시하고 앞에서부터 진행해야 한다.

또, 나눗셈은 정수 나눗셈으로 몫만 취한다.

음수를 양수로 나눌 때는 C++14의 기준을 따른다.

즉, 양수로 바꾼 뒤 몫을 취하고, 그 몫을 음수로 바꾼 것과 같다.

이에 따라서, 위의 식 4개의 결과를 계산해보면 아래와 같다.

1+2+3-4×5÷6 = 1
1÷2+3+4-5×6 = 12
1+2÷3×4-5+6 = 5
1÷2×3-4+5+6 = 7

N개의 수와 N-1개의 연산자가 주어졌을 때, 만들 수 있는 식의 결과가 최대인 것과 최소인 것을 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 수의 개수 N(2 ≤ N ≤ 11)가 주어진다.

둘째 줄에는 A1, A2, ..., AN이 주어진다.

(1 ≤ A_i ≤ 100)

셋째 줄에는 합이 N-1인 4개의 정수가 주어지는데,

차례대로 덧셈(+)의 개수, 뺄셈(-)의 개수, 곱셈(×)의 개수, 나눗셈(÷)의 개수이다.


출력
---
첫째 줄에 만들 수 있는 식의 결과의 최댓값을, 둘째 줄에는 최솟값을 출력한다.

연산자를 어떻게 끼워넣어도 항상 -10억보다 크거나 같고, 10억보다 작거나 같은 결과가 나오는 입력만 주어진다.

또한, 앞에서부터 계산했을 때, 중간에 계산되는 식의 결과도 항상 -10억보다 크거나 같고, 10억보다 작거나 같다.

예제 입력 1
2
5 6
0 0 1 0
예제 출력 1
30
30
예제 입력 2
3
3 4 5
1 0 1 0
예제 출력 2
35
17
예제 입력 3
6
1 2 3 4 5 6
2 1 1 1
예제 출력 3
54
-24

힌트
---
세 번째 예제의 경우에 다음과 같은 식이 최댓값/최솟값이 나온다.

최댓값: 1-2÷3+4+5×6
최솟값: 1+2+3÷4-5×6
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

void recursive(int curr, int deep, int* orderList, _Bool* selectedList, char* calStr, int* list);

char* calculatorToStr(int plus, int minus, int multiple, int divide);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int max = -1000000002;
int min = 1000000002;

int main(void) {
    char input[1000];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));
    *(list + N) = 0;

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);

    int idx = 0;
    while(idx < N) {
        *(list + idx) = parseInt(*(tokens + idx));
        idx++;
    }

    freeTokens(tokens);

    fgets(input, sizeof(input), stdin);

    tokens = tokenizer(input);

    int plus = parseInt(*tokens);
    int minus = parseInt(*(tokens + 1));
    int multiple = parseInt(*(tokens + 2));
    int divide = parseInt(*(tokens + 3));

    freeTokens(tokens);

    char* calStr = calculatorToStr(plus, minus, multiple, divide);

    int* orderList = (int*)calloc(N, sizeof(int));
    _Bool* selectedList = (_Bool*)calloc(N, sizeof(_Bool));

    recursive(0, N - 1, orderList, selectedList, calStr, list);

    char* maxStr = intToStr(max);
    char* minStr = intToStr(min);

    fputs(maxStr, stdout); fputc('\n', stdout);
    fputs(minStr, stdout); fputc('\n', stdout);
    free(maxStr); free(minStr);

    free(calStr); free(orderList); free(selectedList); free(list);

    return 0;
}

int calculater(int base, int num, char ch) {
    int result = base;

    switch(ch) {
        case '+':
            result += num;
            break;
        case '-':
            result -= num;
            break;
        case '/':
            result /= num;
            break;
        case '*':
            result *= num;
            break;
    }

    return result;
}

void recursive(int curr, int deep, int* orderList, _Bool* selectedList, char* calStr, int* list) {
    if(curr == deep) {
        int* listPtr = list;
        int base = *listPtr++;
        int idx = 0;
        while(idx < deep) {
            char order = *(calStr + *(orderList + idx));
            int num = *listPtr++;

            base = calculater(base, num, order);
            idx++;
        }

        min = base < min ? base : min;
        max = base > max ? base : max;

        return;
    }

    int idx = 0;
    while(idx < deep) {
        if(!*(selectedList + idx)) {
            *(selectedList + idx) = 1;
            *(orderList + curr) = idx;

            recursive(curr + 1, deep, orderList, selectedList, calStr, list);

            *(selectedList + idx) = 0;
            *(orderList + curr) = 0;
        }

        idx++;
    }

    return;
}

char* calculatorToStr(int plus, int minus, int multiple, int divide) {
    int size = plus + minus + multiple + divide;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    *(result + size) = 0;

    int idx = 0;
    while(plus-- > 0) {
        *(result + idx++) = '+';
    }
    while(minus-- > 0) {
        *(result + idx++) = '-';
    }
    while(multiple-- > 0) {
        *(result + idx++) = '*';
    }
    while(divide-- > 0) {
        *(result + idx++) = '/';
    }

    return result;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }
            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = tokens;
    while(*tokensPtr) {
        free(*tokensPtr++);
    }
    free(tokens);

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
