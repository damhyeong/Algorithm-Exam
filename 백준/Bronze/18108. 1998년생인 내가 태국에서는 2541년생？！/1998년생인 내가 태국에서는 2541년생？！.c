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
1 초 (추가 시간 없음)	1024 MB	251312	158878	140655	63.292%
문제
ICPC Bangkok Regional에 참가하기 위해 수완나품 국제공항에 막 도착한 팀 레드시프트 일행은 눈을 믿을 수 없었다. 공항의 대형 스크린에 올해가 2562년이라고 적혀 있던 것이었다.

불교 국가인 태국은 불멸기원(佛滅紀元), 즉 석가모니가 열반한 해를 기준으로 연도를 세는 불기를 사용한다. 반면, 우리나라는 서기 연도를 사용하고 있다. 불기 연도가 주어질 때 이를 서기 연도로 바꿔 주는 프로그램을 작성하시오.

입력
서기 연도를 알아보고 싶은 불기 연도 y가 주어진다. (1000 ≤ y ≤ 3000)

출력
불기 연도를 서기 연도로 변환한 결과를 출력한다.

예제 입력 1
2541
예제 출력 1
1998
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

char* intToStr(int target);
char** tokenizer(const char* input);
int parseInt(const char* str);
_Bool isBlank(char ch);
void freeTokens(char** tokens);

int main() {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);

    int diff = 2541 - 1998;

    int anotherBirth = parseInt(*tokens);

    int realBirth = anotherBirth - diff;

    char* birthStr = intToStr(realBirth);

    fputs(birthStr, stdout);

    free(birthStr);

    char end[] = {'\n', '\0'};

    fputs(end, stdout);

    return 0;
}

char* intToStr(int target){
    int sign = 1;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    int len = 0;
    int tempNum = target;

    do {
        tempNum /= 10;
        len++;
    } while(tempNum != 0);


    int extra = sign == 1 ? 1 : 2;
    int size = len + extra;
    char* result = (char*)malloc(sizeof(char) * (len + extra));
    result[size - 1] = '\0';

    int lastIdx = sign == 1 ? 0 : 1;

    if(sign == -1)
        result[0] = '-';

    for(int i = size - 2; i >= lastIdx; i--) {
        int currNum = target % 10;
        target /= 10;
        result[i] = currNum + '0';
    }

    return result;
}

char** tokenizer(const char* input){
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;

    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr;

        inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            newTkn[tknSize] = '\0';
            char* newTknPtr = (char*)newTkn;

            while(currIdx != tknIdx) {
                char currCh = input[tknIdx++];

                *newTknPtr = currCh;
                newTknPtr++;
            }

            *tokensPtr = newTkn;

            tokensPtr++;

            tknIdx = ++currIdx;

            currSize++;

            if(currSize == size) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char) * (size + 1));
                tokensPtr = (char**)tokens[currSize];
            }


        } else {
            currIdx++;
        }
    }

    *tokensPtr = NULL;

    return tokens;
}

int parseInt(const char* str){
    int result = 0;
    int sign = 1;

    char* strPtr = (char*)str;

    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(*strPtr) {
        result *= 10;
        result += *strPtr - '0';
        strPtr++;
    }

    return result * sign;
}

_Bool isBlank(char ch){
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}

void freeTokens(char** tokens){
    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        free(*tokensPtr);
        tokensPtr++;
    }

    free(tokens);
}
