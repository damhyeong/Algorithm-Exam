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
행렬 곱셈

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	23507	16017	13956	69.230%

문제
---
N*M크기의 행렬 A와 M*K크기의 행렬 B가 주어졌을 때, 두 행렬을 곱하는 프로그램을 작성하시오.

입력
---
첫째 줄에 행렬 A의 크기 N 과 M이 주어진다.

둘째 줄부터 N개의 줄에 행렬 A의 원소 M개가 순서대로 주어진다.

그 다음 줄에는 행렬 B의 크기 M과 K가 주어진다.

이어서 M개의 줄에 행렬 B의 원소 K개가 차례대로 주어진다.

N과 M, 그리고 K는 100보다 작거나 같고, 행렬의 원소는 절댓값이 100보다 작거나 같은 정수이다.


출력
---
첫째 줄부터 N개의 줄에 행렬 A와 B를 곱한 행렬을 출력한다.

행렬의 각 원소는 공백으로 구분한다.


예제 입력 1
3 2
1 2
3 4
5 6
2 3
-1 -2 0
0 0 3
예제 출력 1
-1 -2 6
-3 -6 12
-5 -10 18
*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

int getCellResult(int** arrs1, int** arrs2, int y, int x, int k);
int** mulMatrix(int** arrs1, int** arrs2, int i, int j, int k);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);



int main(void) {
    char** tokens = tokenizer(stdin);

    int N = parseInt(*tokens, NULL);
    int M = parseInt(*(tokens + 1), NULL);

    freeArrs((void**)tokens);

    int** arrs1 = (int**)malloc(sizeof(int*) * (N + 1));
    *(arrs1 + N) = NULL;

    int idx = 0;
    while(idx < N) {
        *(arrs1 + idx) = (int*)malloc(sizeof(int) * (M + 1));

        tokens = tokenizer(stdin);

        int jdx = 0;
        while(jdx < M) {
            int tmp = parseInt(*(tokens + jdx), NULL);
            *(*(arrs1 + idx) + jdx) = tmp;

            jdx++;
        }
        freeArrs((void**)tokens);
        idx++;
    }

    tokens = tokenizer(stdin);
    int K = parseInt(*(tokens + 1), NULL);

    freeArrs((void**)tokens);

    int** arrs2 = (int**)malloc(sizeof(int*) * (M + 1));
    *(arrs2 + M) = NULL;

    idx = 0;
    while(idx < M) {
        *(arrs2 + idx) = (int*)malloc(sizeof(int) * (K + 1));

        tokens = tokenizer(stdin);
        int jdx = 0;
        while(jdx < K) {
            int tmp = parseInt(*(tokens + jdx), NULL);
            *(*(arrs2 + idx) + jdx) = tmp;

            jdx++;
        }
        idx++;
    }

    int** result = mulMatrix(arrs1, arrs2, N, M, K);

    freeArrs((void**)arrs1);
    freeArrs((void**)arrs2);


    char buf[32];
    idx = 0;
    while(idx < N) {

        int jdx = 0;
        while(jdx < K) {
            char* tmpStr = intToStr(*(*(result + idx) + jdx), sizeof(buf), buf);

            fputs(tmpStr, stdout); fputc(' ', stdout);

            jdx++;
        }
        fputc('\n', stdout);

        idx++;
    }

    freeArrs((void**)result);

    return 0;
}

int getCellResult(int** arrs1, int** arrs2, int y, int x, int k) {
    int result = 0;
    int index = 0;
    while(index < k) {
        int num1 = *(*(arrs1 + y) + index);
        int num2 = *(*(arrs2 + index) + x);

        int tmp = num1 * num2;
        result += tmp;

        index++;
    }

    return result;
}

int** mulMatrix(int** arrs1, int** arrs2, int i, int j, int k) {
    int** newArrs = (int**)malloc(sizeof(int*) * (i + 1));
    *(newArrs + i) = NULL;
    int idx = 0;
    while(idx < i) {
        *(newArrs + idx) = (int*)malloc(sizeof(int) * (k + 1));
        idx++;
    }

    idx = 0;
    while(idx < i) {
        int jdx = 0;
        while(jdx < k) {
            *(*(newArrs + idx) + jdx) = getCellResult(arrs1, arrs2, idx, jdx, j);
            jdx++;
        }
        idx++;
    }

    return newArrs;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char ch;
    int tknSize = 0;
    int bufSize = 50;
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    *(buf + bufSize) = 0;
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(!tknSize)
                continue;

            *bufPtr = 0;
            *tokensPtr++ = realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            *(buf + bufSize) = 0;
            bufPtr = buf; tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch; tknSize++;
        }

        if(ch == '\n')
            break;
    }
    free(buf);

    *tokensPtr = NULL;

    return tokens;
}
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr)
        free(*arrsPtr++);
    free(arrs);

    return;
}

char* intToStr(int target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long temp = target;
    temp = target < 0 ? -temp : temp;

    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0)
        *--bufPtr = '-';

    return bufPtr;
}
int parseInt(const char* str, FILE* stream) {
    int sign = 1;
    int result = 0;

    if(stream == NULL) {
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
    if(ch == 32 || ch == 0)
        return 1;
    else if(ch >= 9 && ch <= 13)
        return 1;
    else
        return 0;
}
