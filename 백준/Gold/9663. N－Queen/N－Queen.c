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
N-Queen

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
10 초	128 MB	142701	69651	44646	47.109%

문제
---
N-Queen 문제는 크기가 N × N인 체스판 위에 퀸 N개를 서로 공격할 수 없게 놓는 문제이다.

N이 주어졌을 때, 퀸을 놓는 방법의 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. (1 ≤ N < 15)

출력
첫째 줄에 퀸 N개를 서로 공격할 수 없게 놓는 경우의 수를 출력한다.

예제 입력 1
8
예제 출력 1
92
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* calloc(size_t size, size_t byte);


_Bool canFix(int len, int y, int x, _Bool** fixList);

void recursive(int curr, int deep, int len, _Bool* nonFix, _Bool** fixList, int* result);

char* intToStr(int target);
_Bool isBlank(char ch);

int main(void) {
    char input[100];
    char* inputPtr = input;

    fgets(input, sizeof(input), stdin);

    int N = 0;
    while(!isBlank(*inputPtr)) {
        N *= 10;
        N += *inputPtr++ - '0';
    }

    _Bool* nonFix = (_Bool*)calloc(N + 1, sizeof(_Bool));

    _Bool** fixList = (_Bool**)malloc(sizeof(_Bool*) * (N + 1));
    *(fixList + N) = NULL;
    int idx = 0;
    while(idx < N) {
        *(fixList + idx) = (_Bool*)calloc(N + 1, sizeof(_Bool));
        idx++;
    }

    int* result = (int*)malloc(sizeof(int));
    *(result) = 0;

    recursive(0, N, N, nonFix, fixList, result);

    char* resultStr = intToStr(*result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr); free(result);
    free(fixList); free(nonFix);

    return 0;
}

_Bool canFix(int len, int y, int x, _Bool** fixList) {
    int i = y;
    int j = x;
    // 왼쪽 위 대각선
    while(--i >= 0 && --j >= 0) {
        if(*(*(fixList + i) + j)) {
            return 0;
        }
    }

    // 오른쪽 위 대각선
    i = y;
    j = x;
    while(--i >= 0 && ++j < len) {
        if(*(*(fixList + i) + j)) {
            return 0;
        }
    }

    return 1;
}

void recursive(int curr, int deep, int len, _Bool* nonFix, _Bool** fixList, int* result) {
    if(curr == deep) {
        *result += 1;

        return;
    }

    int idx = 0;
    while(idx < len) {
        if(!*(nonFix + idx) && canFix(len, curr, idx, fixList)) {
            *(nonFix + idx) = 1;
            *(*(fixList + curr) + idx) = 1;

            recursive(curr + 1, deep, len, nonFix, fixList, result);

            *(nonFix + idx) = 0;
            *(*(fixList + curr) + idx) = 0;
        }
        idx++;
    }

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

    *result = sign == 1 ? *result : '-';

    return result;
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
