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
1 초	256 MB	348521	173969	148353	50.284%
문제
준하는 사이트에 회원가입을 하다가 joonas라는 아이디가 이미 존재하는 것을 보고 놀랐다. 준하는 놀람을 ??!로 표현한다. 준하가 가입하려고 하는 사이트에 이미 존재하는 아이디가 주어졌을 때, 놀람을 표현하는 프로그램을 작성하시오.

입력
첫째 줄에 준하가 가입하려고 하는 사이트에 이미 존재하는 아이디가 주어진다. 아이디는 알파벳 소문자로만 이루어져 있으며, 길이는 50자를 넘지 않는다.

출력
첫째 줄에 준하의 놀람을 출력한다. 놀람은 아이디 뒤에 ??!를 붙여서 나타낸다.

예제 입력 1
joonas
예제 출력 1
joonas??!
예제 입력 2
baekjoon
예제 출력 2
baekjoon??!
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

char** tokenizer(const char* str);
void freeTokens(char** tokens);
_Bool isBlank(char ch);

int main() {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);

    char* idStr = *tokens;

    fputs(idStr, stdout);

    char backword[] = {'?', '?', '!', '\n', '\0'};

    fputs(backword, stdout);

    freeTokens(tokens);

    return 0;
}

char** tokenizer(const char* str) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* strPtr = (char*)str;

    int tknIdx = 0;
    int currIdx = 0;

    while(*strPtr) {
        char ch = *strPtr;

        strPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx++; currIdx++;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* token = (char*)malloc(sizeof(char) * (tknSize + 1));
            char* tokenPtr = (char*)token;

            while(tknIdx != currIdx) {
                char currCh = str[tknIdx++];
                *tokenPtr = currCh;
                tokenPtr++;
            }

            *tokensPtr = (char*)token;
            tokensPtr++; currSize++;

            tknIdx = ++currIdx;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)tokens[currSize];
            }

        } else {
            currIdx++;
        }
    }

    *tokensPtr = (char*) NULL;

    return tokens;
}

void freeTokens(char** tokens) {
    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        free(*tokensPtr);
        tokensPtr++;
    }

    free(tokens);
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
