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
2 초	256 MB	44370	28937	23696	65.453%

문제
---
자연수를 원소로 갖는 공집합이 아닌 두 집합 A와 B가 있다.

이때, 두 집합의 대칭 차집합의 원소의 개수를 출력하는 프로그램을 작성하시오.

두 집합 A와 B가 있을 때, (A-B)와 (B-A)의 합집합을 A와 B의 대칭 차집합이라고 한다.


예를 들어, A = { 1, 2, 4 } 이고, B = { 2, 3, 4, 5, 6 } 라고 할 때,

A-B = { 1 } 이고, B-A = { 3, 5, 6 } 이므로, 대칭 차집합의 원소의 개수는 1 + 3 = 4개이다.


입력
---
첫째 줄에 집합 A의 원소의 개수와 집합 B의 원소의 개수가 빈 칸을 사이에 두고 주어진다.

둘째 줄에는 집합 A의 모든 원소가, 셋째 줄에는 집합 B의 모든 원소가 빈 칸을 사이에 두고 각각 주어진다.

각 집합의 원소의 개수는 200,000을 넘지 않으며, 모든 원소의 값은 100,000,000을 넘지 않는다.


출력
---
첫째 줄에 대칭 차집합의 원소의 개수를 출력한다.

예제 입력 1
3 5
1 2 4
2 3 4 5 6
예제 출력 1
4
*/

/**

이것도 딱히 HashMap 을 제작할 필요는 없고, 그냥 정수 원시값 배열을 만들어서 검색하면 된다.

인덱스 발견시, N + M - (M 에서 발견된 원소 개수) 하면 정답이 나온다.

원시 배열 + Heap_sort + binary_search 로 구현한다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void sort_heap(int* list, int length);
void heapify(int* list, int limitIdx, int currIdx);
void swap(int* list, int i, int j);

int binary_search(int* list, int target, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    const int NORMAL_LINE = 255;
    const int MAX_LINE = 2000000;

    char* input = (char*)malloc(sizeof(char) * (NORMAL_LINE));
    *(input + NORMAL_LINE) = 0;

    fgets(input, NORMAL_LINE, stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = (char**)tokens;

    free(input);

    int A = parseInt(*tokensPtr++);
    int B = parseInt(*tokensPtr++);

    int* list = (int*)malloc(sizeof(int) * (A + 1));

    input = (char*)malloc(sizeof(char) * (MAX_LINE + 1));
    *(input + MAX_LINE) = 0;

    fgets(input, MAX_LINE, stdin);

    tokens = tokenizer(input);

    free(input);

    int idx = 0;
    while(idx < A) {
        *(list + idx) = parseInt(*(tokens + idx));

        idx++;
    }
    freeTokens(tokens);

    sort_heap(list, A);

    input = (char*)malloc(sizeof(char) * (MAX_LINE + 1));
    *(input + MAX_LINE) = 0;

    fgets(input, MAX_LINE, stdin);

    tokens = tokenizer(input);

    free(input);

    int sharedNum = 0;
    idx = 0;
    while(idx < B) {
        int findNum = parseInt(*(tokens + idx));

        int findIdx = binary_search(list, findNum, 0, A - 1);

        if(findIdx != -1) {
            sharedNum++;
        }

        idx++;
    }

    freeTokens(tokens);

    free(list);

    int result = A + B - (sharedNum * 2);

    char* resultStr = (char*)intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    return 0;
}

void sort_heap(int* list, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(list, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap(list, idx, 0);
        heapify(list, idx, 0);
        idx--;
    }
}
void heapify(int* list, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && *(list + parent) < *(list + left)) {
        parent = left;
    }
    if(right < limitIdx && *(list + parent) < *(list + right)) {
        parent = right;
    }

    if(parent != currIdx) {
        swap(list, parent, currIdx);
        heapify(list, limitIdx, parent);
    }

    return;
}
void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

    return;
}

int binary_search(int* list, int target, int i, int j) {
    if(i > j) {
        return -1;
    }

    int midIdx = (i + j) / 2;
    int midNum = *(list + midIdx);

    if(midNum == target) {
        return midIdx;
    } else if(midNum < target) {
        return binary_search(list, target, midIdx + 1, j);
    } else {
        return binary_search(list, target, i, midIdx - 1);
    }
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
    while(*strPtr == '-') {
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
