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
1 초	256 MB	99367	65468	55904	67.236%

문제
---
2차원 평면 위의 점 N개가 주어진다.

좌표를 y좌표가 증가하는 순으로, y좌표가 같으면 x좌표가 증가하는 순서로 정렬한 다음 출력하는 프로그램을 작성하시오.


입력
---
첫째 줄에 점의 개수 N (1 ≤ N ≤ 100,000)이 주어진다.

둘째 줄부터 N개의 줄에는 i번점의 위치 xi와 yi가 주어진다.

(-100,000 ≤ xi, yi ≤ 100,000) 좌표는 항상 정수이고, 위치가 같은 두 점은 없다.


출력
---
첫째 줄부터 N개의 줄에 점을 정렬한 결과를 출력한다.


예제 입력 1
5
0 4
1 2
1 -1
2 2
3 3
예제 출력 1
1 -1
1 2
2 2
3 3
0 4
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Pointer {
    int x;
    int y;

    void (*print)(struct Pointer* this);
    int (*compare_to)(struct Pointer* this, struct Pointer* another);
} Pointer;

Pointer* NewPointer(int x, int y);
void freePtrArr(Pointer** ptrArr);

void print_ptr(Pointer* this);
int compare_to_ptr(Pointer* this, Pointer* another);

void sort_heap_ptr(Pointer** ptrArr, int length);
void heapify(Pointer** ptrArr, int limitIdx, int currIdx);
void swapPtrList(Pointer** ptrArr, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    Pointer** ptrArr = (Pointer**)malloc(sizeof(Pointer*) * (N + 1));
    *(ptrArr + N) = NULL;

    int idx = 0;

    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int x = parseInt(*tokensPtr++);
        int y = parseInt(*tokensPtr++);

        freeTokens(tokens);

        Pointer* newPtr = NewPointer(x, y);

        *(ptrArr + idx) = newPtr;

        idx++;
    }

    sort_heap_ptr(ptrArr, N);

    idx = 0;
    while(idx < N) {
        Pointer* currPtr = *(ptrArr + idx);

        currPtr->print(currPtr);

        idx++;
    }

    freePtrArr(ptrArr);

    return 0;
}

Pointer* NewPointer(int x, int y) {
    Pointer* newPtr = (Pointer*)malloc(sizeof(Pointer));

    newPtr->x = x;
    newPtr->y = y;

    newPtr->print = print_ptr;

    return newPtr;
}
void freePtrArr(Pointer** ptrArr) {
    Pointer** ptrArrPtr = (Pointer**)ptrArr;

    while(*ptrArrPtr) {
        free(*ptrArrPtr++);
    }
    free(ptrArr);

    return;
}

void print_ptr(Pointer* this) {
    char* x_str = intToStr(this->x);
    char* y_str = intToStr(this->y);

    fputs(x_str, stdout); fputc(' ', stdout); fputs(y_str, stdout); fputc('\n', stdout);

    free(x_str); free(y_str);

    return;
}
int compare_to_ptr(Pointer* this, Pointer* another) {
    int this_x = this->x;
    int another_x = another->x;

    int this_y = this->y;
    int another_y = another->y;

    if(this_y == another_y) {
        if(this_x == another_x) {
            return 0;
        }

        return this_x < another_x ? -1 : 1;
    } else {
        return this_y < another_y ? -1 : 1;
    }
}

void sort_heap_ptr(Pointer** ptrArr, int length) {
    int len = length;

    int idx = len / 2 - 1;
    while(idx >= 0) {
        heapify(ptrArr, len, idx--);
    }

    idx = len - 1;
    while(idx > 0) {
        swapPtrList(ptrArr, 0, idx);
        heapify(ptrArr, idx, 0);
        idx--;
    }

    return;
}
void heapify(Pointer** ptrArr, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && compare_to_ptr(*(ptrArr + parent), *(ptrArr + left)) < 0) {
        parent = left;
    }
    if(right < limitIdx && compare_to_ptr(*(ptrArr + parent), *(ptrArr + right)) < 0) {
        parent = right;
    }

    if(parent != currIdx) {
        swapPtrList(ptrArr, parent, currIdx);

        heapify(ptrArr, limitIdx, parent);
    }

    return;
}
void swapPtrList(Pointer** ptrArr, int i, int j) {
    Pointer* tempPtr = *(ptrArr + i);
    *(ptrArr + i) = *(ptrArr + j);
    *(ptrArr + j) = tempPtr;

    return;
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
