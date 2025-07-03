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
1 초	128 MB	124891	65869	56393	53.058%

문제
---
N*M크기의 두 행렬 A와 B가 주어졌을 때, 두 행렬을 더하는 프로그램을 작성하시오.


입력
---
첫째 줄에 행렬의 크기 N 과 M이 주어진다.

둘째 줄부터 N개의 줄에 행렬 A의 원소 M개가 차례대로 주어진다.

이어서 N개의 줄에 행렬 B의 원소 M개가 차례대로 주어진다.

N과 M은 100보다 작거나 같고, 행렬의 원소는 절댓값이 100보다 작거나 같은 정수이다.


출력
---
첫째 줄부터 N개의 줄에 행렬 A와 B를 더한 행렬을 출력한다.

행렬의 각 원소는 공백으로 구분한다.


예제 입력 1
3 3
1 1 1
2 2 2
0 1 0
3 3 3
4 4 4
5 5 100
예제 출력 1
4 4 4
6 6 6
5 6 100
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
void freeArr(void** arr);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[2000];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int N = parseInt(*tokensPtr++);
    int M = parseInt(*tokensPtr++);

    freeTokens(tokens);

    int** list1 = (int**)malloc(sizeof(int*) * (N + 1));
    int** list1Ptr = list1;
    int** list2 = (int**)malloc(sizeof(int*) * (N + 1));
    int** list2Ptr = list2;

    int idx = 0;
    while(idx++ < N) {
        *list1Ptr++ = (int*)malloc(sizeof(int) * (M + 1));
        *list2Ptr++ = (int*)malloc(sizeof(int) * (M + 1));
    }
    *(list1 + N) = NULL; *(list2 + N) = NULL;

    list1Ptr = list1; list2Ptr = list2;

    idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        tokens = (char**)tokenizer(input);
        tokensPtr = (char**)tokens;

        int* currIntArr = *list1Ptr++;

        while(*tokensPtr) {
            *currIntArr++ = parseInt(*tokensPtr++);
        }

        free(tokens);
    }

    idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        tokens = (char**)tokenizer(input);
        tokensPtr = (char**)tokens;

        int* currIntArr = *list2Ptr++;

        while(*tokensPtr) {
            *currIntArr++ = parseInt(*tokensPtr++);
        }

        free(tokens);
    }

    list1Ptr = list1;
    list2Ptr = list2;
    while(*list1Ptr && *list2Ptr) {
        int* currArr1 = *list1Ptr++;
        int* currArr2 = *list2Ptr++;

        idx = 0;
        while(idx++ < M) {
            int num1 = *currArr1++;
            int num2 = *currArr2++;

            int intResult = num1 + num2;

            char* addResult = intToStr(intResult);

            if(idx < M) {
                fputs(addResult, stdout); fputc(' ', stdout);
            } else {
                fputs(addResult, stdout);
            }

            free(addResult);
        }
        fputc('\n', stdout);
    }

    freeArr((void**)list1);
    freeArr((void**)list2);

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
}

void freeArr(void** arr) {
    void** arrPtr = arr;

    while(*arrPtr) {
        free(*arrPtr++);
    }
    free(arr);
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
