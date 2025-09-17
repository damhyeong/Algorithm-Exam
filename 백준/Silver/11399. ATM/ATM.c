/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "코드를 보다가 궁금하시면 EMAIL 로 연락 주셔도 괜찮습니다!"

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.


    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
ATM

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	139883	97343	76802	69.893%

문제
---
인하은행에는 ATM이 1대밖에 없다.

지금 이 ATM앞에 N명의 사람들이 줄을 서있다.

사람은 1번부터 N번까지 번호가 매겨져 있으며, i번 사람이 돈을 인출하는데 걸리는 시간은 P_i분이다.

사람들이 줄을 서는 순서에 따라서, 돈을 인출하는데 필요한 시간의 합이 달라지게 된다.

예를 들어, 총 5명이 있고, P_1 = 3, P_2 = 1, P_3 = 4, P_4 = 3, P_5 = 2 인 경우를 생각해보자.

[1, 2, 3, 4, 5] 순서로 줄을 선다면, 1번 사람은 3분만에 돈을 뽑을 수 있다.

{3, 1, 4, 3, 2}

2번 사람은 1번 사람이 돈을 뽑을 때 까지 기다려야 하기 때문에, 3+1 = 4분이 걸리게 된다.

3번 사람은 1번, 2번 사람이 돈을 뽑을 때까지 기다려야 하기 때문에, 총 3+1+4 = 8분이 필요하게 된다.

4번 사람은 3+1+4+3 = 11분,

5번 사람은 3+1+4+3+2 = 13분이 걸리게 된다.

이 경우에 각 사람이 돈을 인출하는데 필요한 시간의 합은 3+4+8+11+13 = 39분이 된다.

줄을 [2, 5, 1, 4, 3] 순서로 줄을 서면,

2번 사람은 1분만에, 5번 사람은 1+2 = 3분, 1번 사람은 1+2+3 = 6분, 4번 사람은 1+2+3+3 = 9분, 3번 사람은 1+2+3+3+4 = 13분이 걸리게 된다.

각 사람이 돈을 인출하는데 필요한 시간의 합은 1+3+6+9+13 = 32분이다.

이 방법보다 더 필요한 시간의 합을 최소로 만들 수는 없다.


줄을 서 있는 사람의 수 N과 각 사람이 돈을 인출하는데 걸리는 시간 P_i가 주어졌을 때,

각 사람이 돈을 인출하는데 필요한 시간의 합의 최솟값을 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 사람의 수 N(1 ≤ N ≤ 1,000)이 주어진다.

둘째 줄에는 각 사람이 돈을 인출하는데 걸리는 시간 P_i가 주어진다. (1 ≤ P_i ≤ 1,000)


출력
---
첫째 줄에 각 사람이 돈을 인출하는데 필요한 시간의 합의 최솟값을 출력한다.

예제 입력 1
5
3 1 4 3 2
예제 출력 1
32
*/

/**
가장 인출시간이 작은 사람이 먼저 행동해야 나머지의 대기시간이 짧아진다.

따라서, 입력을 저장 한 후, 정렬하고,

각 엘리먼트의 대기 시간을 누적하면 끝난다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void sort_heap(int* arr, int length);
void heapify(int* arr, int limitIdx, int currIdx);
void swap(int* arr, int i, int j);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(long target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {
    int N = parseInt(NULL, stdin);

    char** tokens = tokenizer(stdin);

    int* arr = (int*)malloc(sizeof(int) * (N + 1));

    int idx = 0;
    while(idx < N) {
        *(arr + idx) = parseInt(*(tokens + idx), NULL);
        idx++;
    }

    sort_heap(arr, N);

    long total = 0;
    long result = 0;
    idx = 0;
    while(idx < N) {
        int n = *(arr + idx++);

        total += n;
        result += total;
    }

    char buf[32];
    char* resultStr = intToStr(result, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

void sort_heap(int* arr, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0)
        heapify(arr, length, idx--);

    idx = length - 1;
    while(idx > 0) {
        swap(arr, idx, 0);
        heapify(arr, idx--, 0);
    }

    return;
}
void heapify(int* arr, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && *(arr + parent) < *(arr + left))
        parent = left;
    if(right < limitIdx && *(arr + parent) < *(arr + right))
        parent = right;

    if(parent != currIdx) {
        swap(arr, parent, currIdx);
        heapify(arr, limitIdx, parent);
    }

    return;
}
void swap(int* arr, int i, int j) {
    int temp = *(arr + i);
    *(arr + i) = *(arr + j);
    *(arr + j) = temp;

    return;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    char ch;

    int bufSize = 100;

    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(!tknSize) {
                continue;
            }

            *bufPtr = 0;
            *tokensPtr++ = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            tknSize = 0;
            bufSize = 100;

            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            bufPtr = buf;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }

        } else {
            *bufPtr++ = ch; tknSize++;

            if(bufSize == tknSize) {
                bufSize *= 2;
                buf = (char*)realloc(buf, sizeof(char) * (bufSize + 1));
                bufPtr = (char*)(buf + tknSize);
            }
        }


        if(ch == '\n') {
            break;
        }
    }
    free(buf);

    *tokensPtr = NULL;

    return tokens;
}
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

    return;
}

char* intToStr(long target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long long temp = target;
    if(target < 0) {
        temp *= -1;
    }

    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0) {
        *--bufPtr = '-';
    }

    return bufPtr;
}
int parseInt(const char* str, FILE* stream) {
    int sign = 1;
    int result = 0;

    if(stream == NULL){
        char* strPtr = (char*)str;
        if(*strPtr == '-') {
            sign = -1;
            strPtr++;
        }

        while(!isBlank(*strPtr)) {
            result *= 10;
            result += *strPtr++ - '0';
        }
    } else {
        char ch = fgetc(stream);
        if(ch == '-') {
            sign = -1;
            ch = fgetc(stream);
        }

        while(!isBlank(ch)) {
            result *= 10;
            result += ch - '0';

            ch = fgetc(stream);
        }
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
