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
1 초	128 MB	78135	47968	43921	62.041%

문제
---
4 × 3 = 12이다.

이 식을 통해 다음과 같은 사실을 알 수 있다.

3은 12의 약수이고, 12는 3의 배수이다.

4도 12의 약수이고, 12는 4의 배수이다.

두 수가 주어졌을 때, 다음 3가지 중 어떤 관계인지 구하는 프로그램을 작성하시오.

첫 번째 숫자가 두 번째 숫자의 약수이다. - "factor"
첫 번째 숫자가 두 번째 숫자의 배수이다. - "multiple"
첫 번째 숫자가 두 번째 숫자의 약수와 배수 모두 아니다. - "neither"

입력
---
입력은 여러 테스트 케이스로 이루어져 있다. 각 테스트 케이스는 10,000이 넘지않는 두 자연수로 이루어져 있다. 마지막 줄에는 0이 2개 주어진다. 두 수가 같은 경우는 없다.

출력
---
각 테스트 케이스마다 첫 번째 숫자가 두 번째 숫자의 약수라면 factor를, 배수라면 multiple을, 둘 다 아니라면 neither를 출력한다.

예제 입력 1
8 16
32 4
17 5
0 0
예제 출력 1
factor
multiple
neither
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

_Bool isEqual(const char* str1, const char* str2);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    while(isEqual(fgets(input, sizeof(input), stdin), "0 0") != 1) {
        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int n1 = parseInt(*tokensPtr++);
        int n2 = parseInt(*tokensPtr++);

        freeTokens(tokens);

        char* result = "neither";

        if(n2 % n1 == 0) {
            result = "factor";
        } else if(n1 % n2 == 0) {
            result = "multiple";
        }

        fputs(result, stdout); fputc('\n', stdout);
    }

    return 0;
}

_Bool isEqual(const char* str1, const char* str2) {
    char* str1Ptr = (char*)str1;
    char* str2Ptr = (char*)str2;

    _Bool isSame = 1;

    while(isBlank(*str1Ptr) != 1 && isBlank(*str2Ptr) != 1) {
        char ch1 = *str1Ptr++;
        char ch2 = *str2Ptr++;

        if(ch1 != ch2) {
            isSame = 0;
            break;
        }
    }

    return isSame;
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
                tokensPtr = (char**)(tokens + currIdx);
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
