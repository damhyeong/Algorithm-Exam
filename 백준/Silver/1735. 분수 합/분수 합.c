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
2 초	128 MB	47584	22392	19627	47.584%

문제
---
분수 A/B는 분자가 A, 분모가 B인 분수를 의미한다.

A와 B는 모두 자연수라고 하자.

두 분수의 합 또한 분수로 표현할 수 있다.

두 분수가 주어졌을 때, 그 합을 기약분수의 형태로 구하는 프로그램을 작성하시오.

기약분수란 더 이상 약분되지 않는 분수를 의미한다.


입력
---
첫째 줄과 둘째 줄에, 각 분수의 분자와 분모를 뜻하는 두 개의 자연수가 순서대로 주어진다.

입력되는 네 자연수는 모두 30,000 이하이다.


출력
---
첫째 줄에 구하고자 하는 기약분수의 분자와 분모를 뜻하는 두 개의 자연수를 빈 칸을 사이에 두고 순서대로 출력한다.

예제 입력 1
2 7
3 5
예제 출력 1
31 35
*/

/**
이 문제는 "단계별 풀어보기" 중 약수, 배수와 소수-2 에 속하며, 여태까지 풀어온 윗 단계를 활용하여 문제를 풀어야 한다.

즉, 최소공배수, 최대공약수를 이용해야 한다.

하나의 줄의 입력은 분자, 분모가 차례로 이루어지며, 이 두 분수의 합이 "기약분수" 형태가 되도록 만들어야 한다.

그렇다면, 의식의 흐름대로 이러한 단계를 거치게 될 것이다.

1. 각 분모의 최소공배수를 구한다.
2. 각 분자는 (최소공배수 / 분모) 의 몫 만큼 곱해진다.
3. 이렇게 계산된 2 개의 분자는 더해진다.
4. 더해진 분자 / 최소공배수 형태를 띄게 된다.
5. 이 형태는 완성된 것이 아니며, (더해진 분자), (최소공배수) 사이의 최대공약수를 찾는다.
6. 이 최대공약수를 각각 나눠준다.
7. <결과 분자> <결과 분모> 이렇게 출력한다.
*/

#include<stdio.h>

int min_multiple(int n1, int n2);
int max_divisor(int n1, int n2);

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int numerator1 = parseInt(*tokensPtr++);
    int denominator1 = parseInt(*tokensPtr++);

    freeTokens(tokens);

    fgets(input, sizeof(input), stdin);

    tokens = tokenizer(input);
    tokensPtr = (char**)tokens;

    int numerator2 = parseInt(*tokensPtr++);
    int denominator2 = parseInt(*tokensPtr++);

    freeTokens(tokens);

    int denoMinMul = min_multiple(denominator1, denominator2); // 분모
    numerator1 = numerator1 * (denoMinMul / denominator1);
    numerator2 = numerator2 * (denoMinMul / denominator2);
    int totalNumerator = numerator1 + numerator2; // 분자

    int max_div = max_divisor(totalNumerator, denoMinMul);

    int resultNumerator = totalNumerator / max_div;
    int resultDenominator = denoMinMul / max_div;

    char* result1 = intToStr(resultNumerator);
    char* result2 = intToStr(resultDenominator);

    fputs(result1, stdout); fputc(' ', stdout); fputs(result2, stdout); fputc('\n', stdout);

    free(result1); free(result2);

    return 0;
}

int min_multiple(int n1, int n2) {
    int small = n1 > n2 ? n2 : n1;
    int big = n1 > n2 ? n1 : n2;

    int max_div = max_divisor(small, big);

    int tmp_mul = small / max_div;

    int result = big * tmp_mul;

    return result;
}
int max_divisor(int n1, int n2) {

    int tmp = 1;
    int max_div = -1;
    while(tmp <= n1 / 2 && tmp <= n2 / 2) {
        max_div = n1 % tmp == 0 && n2 % tmp == 0 ? tmp : max_div;

        tmp++;
    }

    max_div = n1 % n2 == 0 ? n2 : max_div;
    max_div = n2 % n1 == 0 ? n1 : max_div;

    return max_div;
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
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
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

    return;
}

char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
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
