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
종이의 개수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	53999	33261	25018	60.738%

문제
---
N×N크기의 행렬로 표현되는 종이가 있다.

종이의 각 칸에는 -1, 0, 1 중 하나가 저장되어 있다.

우리는 이 행렬을 다음과 같은 규칙에 따라 적절한 크기로 자르려고 한다.

만약 종이가 모두 같은 수로 되어 있다면 이 종이를 그대로 사용한다.

(1)이 아닌 경우에는 종이를 같은 크기의 종이 9개로 자르고, 각각의 잘린 종이에 대해서 (1)의 과정을 반복한다.

이와 같이 종이를 잘랐을 때, -1로만 채워진 종이의 개수, 0으로만 채워진 종이의 개수, 1로만 채워진 종이의 개수를 구해내는 프로그램을 작성하시오.

입력
---
첫째 줄에 N(1 ≤ N ≤ 37, N은 3k 꼴)이 주어진다.

다음 N개의 줄에는 N개의 정수로 행렬이 주어진다.


출력
---
첫째 줄에 -1로만 채워진 종이의 개수를, 둘째 줄에 0으로만 채워진 종이의 개수를, 셋째 줄에 1로만 채워진 종이의 개수를 출력한다.

예제 입력 1
9
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
0 1 -1 0 1 -1 0 1 -1
0 -1 1 0 1 -1 0 1 -1
0 1 -1 1 0 -1 0 1 -1
예제 출력 1
10
12
11
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);


void conquer(int** arrs, int sY, int sX, int eY, int eX, int* n1, int* n2, int* n3);
int checkSame(int** arrs, int sY, int sX, int eY, int eX);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);



int main(void) {
    int N = parseInt(NULL, stdin);

    int** arrs = (int**)malloc(sizeof(int*) * (N + 1));
    *(arrs + N) = NULL;

    int idx = 0;
    while(idx < N)
        *(arrs + idx++) = (int*)malloc(sizeof(int) * (N + 1));

    idx = 0;
    while(idx < N) {
        char** tokens = tokenizer(stdin);
        int jdx = 0;
        while(jdx < N) {
            int n = parseInt(*(tokens + jdx), NULL);
            *(*(arrs + idx) + jdx) = n;

            jdx++;
        }
        freeArrs((void**)tokens);

        idx++;
    }

    int n1 = 0, n2 = 0, n3 = 0;
    conquer(arrs, 0, 0, N, N, &n1, &n2, &n3);

    freeArrs((void**)arrs);

    char buf[32];
    char* str = intToStr(n1, sizeof(buf), buf);
    fputs(str, stdout); fputc('\n', stdout);
    str = intToStr(n2, sizeof(buf), buf);
    fputs(str, stdout); fputc('\n', stdout);
    str = intToStr(n3, sizeof(buf), buf);
    fputs(str, stdout); fputc('\n', stdout);

    return 0;
}

void conquer(int** arrs, int sY, int sX, int eY, int eX, int* n1, int* n2, int* n3) {

    int checkResult = checkSame(arrs, sY, sX, eY, eX);
    if(checkResult != -2) {

        if(checkResult == 1) {
            *n3 = *n3 + 1;
        } else if(checkResult == 0) {
            *n2 = *n2 + 1;
        } else {
            *n1 = *n1 + 1;
        }
        return;
    }

    int fix = (eY - sY) / 3;

    int idx = 0;
    while(idx < 3) {
        int jdx = 0;
        while(jdx < 3) {
            conquer(arrs, sY + fix * idx, sX + fix * jdx, sY + fix * idx + fix, sX + fix * jdx + fix, n1, n2, n3);
            jdx++;
        }
        idx++;
    }

    return;
}
int checkSame(int** arrs, int sY, int sX, int eY, int eX) {
    _Bool isSame = 1;

    int tmpNum = *(*(arrs + sY) + sX);
    int idx = sY;
    while(idx < eY) {
        int jdx = sX;
        while(jdx < eX) {
            if(tmpNum != *(*(arrs + idx) + jdx)) {
                isSame = 0;
                break;
            }

            jdx++;
        }
        idx++;
    }

    if(isSame)
        return tmpNum;
    else
        return -2;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    char ch;

    int bufSize = 10;
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    *(buf + bufSize) = 0;
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0)
                continue;

            *bufPtr = 0;
            *tokensPtr++ = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            *(buf + bufSize) = 0;
            bufPtr = buf;
            tknSize = 0;

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
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
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
    if(ch == 32 || ch == 0) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
