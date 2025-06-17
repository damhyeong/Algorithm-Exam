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
1 초	256 MB	377309	206630	165532	54.253%
문제
정수 N개로 이루어진 수열 A와 정수 X가 주어진다. 이때, A에서 X보다 작은 수를 모두 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 X가 주어진다. (1 ≤ N, X ≤ 10,000)

둘째 줄에 수열 A를 이루는 정수 N개가 주어진다. 주어지는 정수는 모두 1보다 크거나 같고, 10,000보다 작거나 같은 정수이다.

출력
X보다 작은 수를 입력받은 순서대로 공백으로 구분해 출력한다. X보다 작은 수는 적어도 하나 존재한다.

예제 입력 1
10 5
1 10 4 9 2 3 8 5 7 6
예제 출력 1
1 4 2 3
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

typedef struct IntList {
    struct IntList* this;

    int size;
    int currIdx;

    int* list;
    int* listPtr;

    struct IntList* (*add)(struct IntList* this, int newNum);
    int* (*to_list)(struct IntList* this);
} IntList;

IntList* NewIntList(void);
void DeleteIntList(IntList* this);

IntList* add_i_list(IntList* this, int newNum);
int* to_list_i_list(IntList* this);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[50000];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int N = parseInt(*tokensPtr++);
    int X = parseInt(*tokensPtr++);

    freeTokens(tokens);

    fgets(input, sizeof(input), stdin);

    char** intTkns = (char**)tokenizer(input);
    char** intTknsPtr = (char**)intTkns;

    IntList* intList = (IntList*) NewIntList();

    while(*intTknsPtr) {
        int newNum = parseInt(*intTknsPtr++);

        if(newNum < X) {
            intList->add(intList, newNum);
        }
    }

    freeTokens(intTkns);

    int* intIter = (int*)intList->to_list(intList);

    while(*intIter != 0) {
        char* tempResult = intToStr(*intIter++);

        fputs(tempResult, stdout); fputc(' ', stdout);

        free(tempResult);
    }
    fputc('\n', stdout);

    DeleteIntList(intList);

    return 0;
}


IntList* NewIntList(void) {
    IntList* intList = (IntList*)malloc(sizeof(IntList));

    intList->this = intList;

    intList->size = 2;
    intList->currIdx = 0;

    intList->list = (int*)malloc(sizeof(int) * (intList->size + 1));
    intList->list[intList->size] = 0;

    intList->listPtr = intList->list;

    intList->add = add_i_list;
    intList->to_list = to_list_i_list;

    return intList;
}

void DeleteIntList(IntList* this) {
    free(this->list);
    free(this);
}

IntList* add_i_list(IntList* this, int newNum) {
    *this->listPtr++ = newNum; this->currIdx++;

    if(this->size == this->currIdx) {
        this->size *= 2;
        this->list = (int*)realloc(this->list, sizeof(int) * (this->size + 1));
        this->list[this->size] = 0;
        this->listPtr = (int*)(this->list + this->currIdx);
    }

    return this;
}
int* to_list_i_list(IntList* this) {
    *this->listPtr = 0;

    return this->list;
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
            newTkn[tknSize] = '\0';
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
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
