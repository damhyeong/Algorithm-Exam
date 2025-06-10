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
1 초	512 MB	293688	117327	105050	40.319%
문제
꼬마 정민이는 이제 A + B 정도는 쉽게 계산할 수 있다. 이제 A + B + C를 계산할 차례이다!

입력
첫 번째 줄에 A, B, C (1 ≤ A, B, C ≤ 10^12)이 공백을 사이에 두고 주어진다.

출력
A+B+C의 값을 출력한다.

예제 입력 1
77 77 7777
예제 출력 1
7931
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
char* longToStr(long target);
long parseLong(const char* str);
_Bool isBlank(char ch);

int main () {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    long result = 0;
    while(*tokensPtr) {
        result += parseLong(*tokensPtr++);
    }

    freeTokens(tokens);

    char* resultStr = longToStr(result);

    fputs(resultStr, stdout);
    fputc('\n', stdout);

    free(resultStr);

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
            char* newTkn = (char*)malloc(tknSize + 1);
            newTkn[tknSize] = '\0';
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                char currCh = input[tknIdx++];
                *newTknPtr++ = currCh;
            }

            *tokensPtr++ = newTkn;

            tknIdx = ++currIdx;

            currSize++;

            if(currSize == size) {
                size *= 2;
                tokens = realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)tokens[currSize];
            }
        } else {
            currIdx++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}

void freeTokens(char** tokens) {
    char** freeTknPtr = (char**)tokens;

    while(*freeTknPtr) {
        free(*freeTknPtr++);
    }

    free(tokens);
}

char* longToStr(long target) {
    long sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    long temp = target;

    do {
        temp /= 10;
        len++;
    } while (temp != 0);

    int size = (sign == 1) ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = (sign == 1) ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * size + 1);
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = (target % 10) + '0';
        target /= 10;
    }

    if(sign == -1) {
        result[0] = '-';
    }

    return result;
}

long parseLong(const char* str) {
    long result = 0;
    long sign = 1;

    char* strPtr = (char*)str;

    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(*strPtr) {
        char ch = *strPtr++;

        result *= 10; result += ch - '0';
    }

    return result * sign;
}

_Bool isBlank(char ch) {
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
