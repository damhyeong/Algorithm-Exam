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
1 초	128 MB	302214	141845	118510	46.742%

문제
---
1에서부터 6까지의 눈을 가진 3개의 주사위를 던져서 다음과 같은 규칙에 따라 상금을 받는 게임이 있다.

같은 눈이 3개가 나오면 10,000원+(같은 눈)×1,000원의 상금을 받게 된다.

같은 눈이 2개만 나오는 경우에는 1,000원+(같은 눈)×100원의 상금을 받게 된다.

모두 다른 눈이 나오는 경우에는 (그 중 가장 큰 눈)×100원의 상금을 받게 된다.

예를 들어, 3개의 눈 3, 3, 6이 주어지면 상금은 1,000+3×100으로 계산되어 1,300원을 받게 된다.

또 3개의 눈이 2, 2, 2로 주어지면 10,000+2×1,000 으로 계산되어 12,000원을 받게 된다.

3개의 눈이 6, 2, 5로 주어지면 그중 가장 큰 값이 6이므로 6×100으로 계산되어 600원을 상금으로 받게 된다.

3개 주사위의 나온 눈이 주어질 때, 상금을 계산하는 프로그램을 작성 하시오.

입력
----
첫째 줄에 3개의 눈이 빈칸을 사이에 두고 각각 주어진다.

출력
----
첫째 줄에 게임의 상금을 출력 한다.

예제 입력 1
3 3 6
예제 출력 1
1300
예제 입력 2
2 2 2
예제 출력 2
12000
예제 입력 3
6 2 5
예제 출력 3
600
*/

/**

개인적인 생각
---

물론, 이 세 가지 경우의 수를 모두 나눠서 판단할 수도 있겠지만, 그렇다면 너무 코드가 많아진다.

따라서, 수를 파싱 후, 한번만 순회하면서, 조건문으로 사용될 분기를 한번에 계산 할 예정

"같은 수 주사위가 몇 개 인가" 만 조건문으로 사용하여 곧바로 출력 할 예정.
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

int* toIntList(char** tokens);
char** tokenizer(char* input);
void freeTokens(char** tokens);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);

    int* intList = (int*)toIntList(tokens);
    int* intListPtr = (int*)intList;

    freeTokens(tokens);

    int biggestNum = -1; // 주사위로 될 수 없는 수
    int smallestNum = 10; // 이 또한 주사위에 없는 수
    int sameNum = -1;
    int same = 1;

    biggestNum = *intListPtr;
    smallestNum = *intListPtr++;


    while(*intListPtr) {
        int num = *intListPtr++;

        if(biggestNum < num) {
            biggestNum = num;
        } else if(smallestNum > num) {
            smallestNum = num;
        } else if(num == biggestNum || num == smallestNum){ // 수가 같다는 이야기
            sameNum = num;
            same++;
        }
    }
    free(intList);

    /**
    같은 눈이 3개가 나오면 10,000원+(같은 눈)×1,000원의 상금을 받게 된다.

    같은 눈이 2개만 나오는 경우에는 1,000원+(같은 눈)×100원의 상금을 받게 된다.

    모두 다른 눈이 나오는 경우에는 (그 중 가장 큰 눈)×100원의 상금을 받게 된다.
    */
    int prize = 0;
    switch (same) {
        case 3:
            prize = 10000 + (sameNum * 1000);
            break;
        case 2:
            prize = 1000 + (sameNum * 100);
            break;
        case 1:
            prize = biggestNum * 100;
            break;
    }

    char* result = (char*)intToStr(prize);
    fputs(result, stdout); fputc('\n', stdout);

    free(result);

    return 0;
}

int* toIntList(char** tokens) {
    int size = 5;
    int currSize = 0;

    int* intList = (int*)malloc(sizeof(int) * (size + 1));
    int* intListPtr = (int*)intList;

    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        *intListPtr++ = (int)parseInt(*tokensPtr++); currSize++;

        if(currSize == size) {
            size *= 2;
            intList = (int*)malloc(sizeof(int) * (size + 1));
            intListPtr = (int*)(intList + currSize);
        }
    }
    *intListPtr = 0;

    return intList;
}

char** tokenizer(char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    int tknIdx = 0;
    int currIdx = 0;

    char* inputPtr = (char*)input;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            newTkn[tknSize] = '\0';
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr++ = input[tknIdx++];
            }

            *tokensPtr++ = newTkn;

            tknIdx = ++currIdx; currSize++;

            if(currSize == size) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**) (tokens + currSize);
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
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
        target /= 10;
    }

    if(sign == -1) {
        result[0] = '-';
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

    while(*strPtr) {
        result *= 10;
        result += *strPtr++ - '0';
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
