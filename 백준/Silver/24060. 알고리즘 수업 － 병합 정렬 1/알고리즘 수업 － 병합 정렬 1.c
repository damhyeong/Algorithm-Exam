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
알고리즘 수업 - 병합 정렬 1

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	23528	11095	9028	47.629%

문제
---
오늘도 서준이는 병합 정렬 수업 조교를 하고 있다.

아빠가 수업한 내용을 학생들이 잘 이해했는지 문제를 통해서 확인해보자.

N개의 서로 다른 양의 정수가 저장된 배열 A가 있다.

병합 정렬로 배열 A를 오름차순 정렬할 경우 배열 A에 K 번째 저장되는 수를 구해서 우리 서준이를 도와주자.

크기가 N인 배열에 대한 병합 정렬 의사 코드는 다음과 같다.
---------------------------------------------------------------
merge_sort(A[p..r]) { # A[p..r]을 오름차순 정렬한다.
    if (p < r) then {
        q <- ⌊(p + r) / 2⌋;       # q는 p, r의 중간 지점
        merge_sort(A, p, q);      # 전반부 정렬
        merge_sort(A, q + 1, r);  # 후반부 정렬
        merge(A, p, q, r);        # 병합
    }
}
# A[p..q]와 A[q+1..r]을 병합하여 A[p..r]을 오름차순 정렬된 상태로 만든다.
# A[p..q]와 A[q+1..r]은 이미 오름차순으로 정렬되어 있다.
merge(A[], p, q, r) {
    i <- p; j <- q + 1; t <- 1;
    while (i ≤ q and j ≤ r) {
        if (A[i] ≤ A[j])
        then tmp[t++] <- A[i++]; # tmp[t] <- A[i]; t++; i++;
        else tmp[t++] <- A[j++]; # tmp[t] <- A[j]; t++; j++;
    }
    while (i ≤ q)  # 왼쪽 배열 부분이 남은 경우
        tmp[t++] <- A[i++];
    while (j ≤ r)  # 오른쪽 배열 부분이 남은 경우
        tmp[t++] <- A[j++];
    i <- p; t <- 1;
    while (i ≤ r)  # 결과를 A[p..r]에 저장
        A[i++] <- tmp[t++];
}
---------------------------------------------------------------

입력
---
첫째 줄에 배열 A의 크기 N(5 ≤ N ≤ 500,000), 저장 횟수 K(1 ≤ K ≤ 10^8)가 주어진다.

다음 줄에 서로 다른 배열 A의 원소 A1, A2, ..., AN이 주어진다.

(1 ≤ Ai ≤ 109)

출력
---
배열 A에 K 번째 저장 되는 수를 출력한다.

저장 횟수가 K 보다 작으면 -1을 출력한다.

예제 입력 1
5 7
4 5 1 3 2
예제 출력 1
3

4 5 1 3 2 -> 4 5 1 3 2 -> 4 5 1 3 2 -> 1 5 1 3 2 -> 1 4 1 3 2 -> 1 4 5 3 2 -> 1 4 5 2 2 -> 1 4 5 2 3 -> 1 4 5 2 3 -> 1 2 5 2 3 -> 1 2 3 2 3 -> 1 2 3 4 3 -> 1 2 3 4 5. 총 12회 저장이 발생하고 일곱 번째 저장되는 수는 3이다.

예제 입력 2
5 13
4 5 1 3 2
예제 출력 2
-1
저장 횟수 12가 K 보다 작으므로 -1을 출력한다.
*/

/**
이 문제에서 말하는 A 에 저장되는 배열의 몇 번째를 구하라 라는 의미는,

내가 평소 사용하던 merge_sort 와는 사뭇 다르다.

뭐가 다른가 살펴보았는데, 정확히 내가 왼쪽 배열과 오른쪽 배열을 나누는 기준이 다르다.

만약에, 길이가 5 인 배열을 정렬한다고 가정한다면, 왼쪽은 3, 오른쪽은 2 이다.

계속해서 저장되는 순서가 이해가 되질 않았는데, 이러한 점을 알고 나서 확실히 이해가 되었다.

따라서, 문제에 주어진 로직을 그대로 사용하되, 현재 몇 번째 수 인지 알기 위해, 정적 변수를 사용하는 것은 불가피한 것으로 보인다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void sort_merge(int* list, int length, int* result);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int currOper = 0;
int findOper = -1;

int main(void) {
    const int NORMAL_SIZE = 255;
    const int MAX_SIZE = 5000000;

    char* input = (char*)malloc(sizeof(char) * (NORMAL_SIZE + 1));
    *(input + NORMAL_SIZE) = 0;

    fgets(input, NORMAL_SIZE, stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = tokens;

    free(input);

    int N = parseInt(*tokensPtr++);
    findOper = parseInt(*tokensPtr++);

    input = (char*)malloc(sizeof(char) * (MAX_SIZE + 1));
    *(input + MAX_SIZE) = 0;

    fgets(input, MAX_SIZE, stdin);

    tokens = tokenizer(input);
    tokensPtr = tokens;

    free(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));

    int* listPtr = list;
    while(*tokensPtr) {
        *listPtr++ = parseInt(*tokensPtr++);
    }
    freeTokens(tokens);

    int* result = (int*)malloc(sizeof(int));
    *result = -1;
    sort_merge(list, N, result);

    char* resultStr = intToStr(*result);
    free(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    free(list);

    return 0;
}

void sort_merge(int* list, int length, int* result) {
    if(length <= 1) {
        return;
    }

    int mid;
    mid = length % 2 == 0 ? length / 2 : length / 2 + 1;

    int left = mid;
    int right = length - mid;

    int* leftList = (int*)malloc(sizeof(int) * (left + 1));
    int* rightList = (int*)malloc(sizeof(int) * (right + 1));

    int i = 0, idx = 0;
    while(i < left) {
        *(leftList + i++) = *(list + idx++);
    }
    i = 0;
    while(i < right) {
        *(rightList + i++) = *(list + idx++);
    }

    sort_merge(leftList, left, result); sort_merge(rightList, right, result);

    i = 0, idx = 0;
    int j = 0;

    while(i < left && j < right) {
        int leftNum = *(leftList + i);
        int rightNum = *(rightList + j);

        if(leftNum <= rightNum) {
            *(list + idx) = *(leftList + i++);
        } else {
            *(list + idx) = *(rightList + j++);
        }

        currOper++;
        *result = currOper == findOper ? *(list + idx) : *result;

        idx++;
    }

    while(i < left) {
        *(list + idx) = *(leftList + i++);

        currOper++;
        *result = currOper == findOper ? *(list + idx) : *result;

        idx++;
    }

    while(j < right) {
        *(list + idx) = *(rightList + j++);

        currOper++;
        *result = currOper == findOper ? *(list + idx) : *result;

        idx++;
    }

    return;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }
            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = tokens;
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
    *result = sign == 1 ? *result : '-';

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

    while(!isBlank(*strPtr)) {
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
