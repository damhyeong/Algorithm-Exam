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
2 초	256 MB	144021	62541	45691	43.101%

문제
---
숫자 카드는 정수 하나가 적혀져 있는 카드이다.

상근이는 숫자 카드 N개를 가지고 있다.

정수 M개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 가지고 있는지 아닌지를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 상근이가 가지고 있는 숫자 카드의 개수 N(1 ≤ N ≤ 500,000)이 주어진다.

둘째 줄에는 숫자 카드에 적혀있는 정수가 주어진다.

숫자 카드에 적혀있는 수는

-10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다.

두 숫자 카드에 같은 수가 적혀있는 경우는 없다.

셋째 줄에는 M(1 ≤ M ≤ 500,000)이 주어진다.

넷째 줄에는 상근이가 가지고 있는 숫자 카드인지 아닌지를 구해야 할 M개의 정수가 주어지며,

이 수는 공백으로 구분되어져 있다.

이 수도 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다

출력
첫째 줄에 입력으로 주어진 M개의 수에 대해서, 각 수가 적힌 숫자 카드를 상근이가 가지고 있으면 1을, 아니면 0을 공백으로 구분해 출력한다.

예제 입력 1
5
6 3 2 10 -10
8
10 9 -5 2 3 4 5 -10
예제 출력 1
1 0 0 1 1 0 0 1
*/

/**
나에게는 스스로 걸어온 제약이 있다. 바로, stdio.h 라이브러리를 제외하고, "모든" 기능들을 직접 제작해야 한다는 것.

물론 실력이 쑥쑥 늘어온 것은 사실이나, 컴퓨팅 지능과 성장 포텐셜을 올리기 위해서는 어쩔수 없는 선택이다.

잡설은 여기까지.

수의 크기는 최대 천만까지. 즉, int 타입으로 충분.

그러나, 제일 큰 문제는 바로 입력 토큰의 개수이다.

최대 500_000 개의 토큰이 들어온다.

그렇다면, 이 문제를 풀기 위한 적절한 조치는 바로 HashSet or HashMap 을 이용하여 구현하는 것이다.

문제를 풀기 위한 2 가지 방법이 있다.

1. Heap Sort and Binary Search

2. HashSet Implementation

이 분야에서 HashSet, HashMap 을 구현하게 될 테니, 나는 먼저 Heap 으로 정렬 후 이진 검색을 구현 해 보자.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

int binary_search(int* list, int target, int start, int end);

void sort_heap(int* list, int length);
void heapify(int* list, int limitIdx, int currIdx);
void swap(int* list, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    size_t inputSize = 100;
    char* input = (char*)malloc(sizeof(char) * inputSize);

    fgets(input, (int)inputSize, stdin);

    int N = parseInt(input);

    free(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));

    inputSize = 10000000;
    input = (char*)malloc(sizeof(char) * inputSize);

    fgets(input, (int)inputSize, stdin);

    char** tokens = (char**)tokenizer(input);

    int idx = 0;
    while(idx < N) {
        *(list + idx) = parseInt(*(tokens + idx));
        idx++;
    }
    freeTokens(tokens);

    free(input);

    sort_heap(list, N);

    inputSize = 100;
    input = (char*)malloc(sizeof(char) * inputSize);
    fgets(input, (int)inputSize, stdin);

    int M = parseInt(input);

    free(input);

    inputSize = 10000000;
    input = (char*)malloc(sizeof(char) * inputSize);
    fgets(input, (int)inputSize, stdin);

    tokens = (char**)tokenizer(input);

    idx = 0;
    while(idx < M) {
        int target = parseInt(*(tokens + idx));
        int findIdx = binary_search(list, target, 0, N - 1);

        if(findIdx == -1) {
            fputs("0 ", stdout);
        } else {
            fputs("1 ", stdout);
        }

        idx++;
    }
    fputc('\n', stdout);

    freeTokens(tokens);

    free(input);

    free(list);

    return 0;
}

int binary_search(int* list, int target, int start, int end) {
    int middle = (start + end) / 2;
    int midNum = *(list + middle);

    if(start >= end) {
        return midNum == target ? middle : -1;
    }

    if(midNum == target) {
        return middle;
    } else if(midNum < target) {
        return binary_search(list, target, middle + 1, end);
    } else {
        return binary_search(list, target, 0, middle - 1);
    }
}

void sort_heap(int* list, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(list, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap(list, 0, idx);
        heapify(list, idx, 0);
        idx--;
    }
}
void heapify(int* list, int limitIdx, int currIdx){
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
}
void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

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
