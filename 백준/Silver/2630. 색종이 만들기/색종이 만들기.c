
/**
색종이 만들기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	62282	43946	33891	70.322%

문제
---
아래 <그림 1>과 같이 여러개의 정사각형칸들로 이루어진 정사각형 모양의 종이가 주어져 있고, 각 정사각형들은 하얀색으로 칠해져 있거나 파란색으로 칠해져 있다.

주어진 종이를 일정한 규칙에 따라 잘라서 다양한 크기를 가진 정사각형 모양의 하얀색 또는 파란색 색종이를 만들려고 한다.



전체 종이의 크기가 N×N(N=2k, k는 1 이상 7 이하의 자연수) 이라면 종이를 자르는 규칙은 다음과 같다.

전체 종이가 모두 같은 색으로 칠해져 있지 않으면 가로와 세로로 중간 부분을 잘라서

<그림 2>의 I, II, III, IV와 같이 똑같은 크기의 네 개의 N/2 × N/2색종이로 나눈다.

나누어진 종이 I, II, III, IV 각각에 대해서도 앞에서와 마찬가지로 모두 같은 색으로 칠해져 있지 않으면 같은 방법으로 똑같은 크기의 네 개의 색종이로 나눈다.

이와 같은 과정을 잘라진 종이가 모두 하얀색 또는 모두 파란색으로 칠해져 있거나,

하나의 정사각형 칸이 되어 더 이상 자를 수 없을 때까지 반복한다.

위와 같은 규칙에 따라 잘랐을 때

<그림 3>은 <그림 1>의 종이를 처음 나눈 후의 상태를,

<그림 4>는 두 번째 나눈 후의 상태를,

<그림 5>는 최종적으로 만들어진 다양한 크기의 9장의 하얀색 색종이와 7장의 파란색 색종이를 보여주고 있다.

입력으로 주어진 종이의 한 변의 길이 N과 각 정사각형칸의 색(하얀색 또는 파란색)이 주어질 때 잘라진 하얀색 색종이와 파란색 색종이의 개수를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에는 전체 종이의 한 변의 길이 N이 주어져 있다.

N은 2, 4, 8, 16, 32, 64, 128 중 하나이다.

색종이의 각 가로줄의 정사각형칸들의 색이 윗줄부터 차례로 둘째 줄부터 마지막 줄까지 주어진다.

하얀색으로 칠해진 칸은 0, 파란색으로 칠해진 칸은 1로 주어지며, 각 숫자 사이에는 빈칸이 하나씩 있다.


출력
---
첫째 줄에는 잘라진 햐얀색 색종이의 개수를 출력하고, 둘째 줄에는 파란색 색종이의 개수를 출력한다.

예제 입력 1
8
1 1 0 0 0 0 1 1
1 1 0 0 0 0 1 1
0 0 0 0 1 1 0 0
0 0 0 0 1 1 0 0
1 0 0 0 1 1 1 1
0 1 0 0 1 1 1 1
0 0 1 1 1 1 1 1
0 0 1 1 1 1 1 1
예제 출력 1
9
7
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void getPapers(char** arrs, int sY, int sX, int eY, int eX);

_Bool isSame(char** arrs, int sY, int sX, int eY, int eX);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int white = 0;
int blue = 0;

int main(void) {

    int N = parseInt(NULL, stdin);

    char** arrs = (char**)malloc(sizeof(char*) * (N + 1));
    *(arrs + N) = NULL;

    int idx = 0;
    while(idx < N)
        *(arrs + idx++) = (char*)malloc(sizeof(char) * (N + 1));

    idx = 0;
    while(idx < N) {
        char** tokens = tokenizer(stdin);

        int jdx = 0;
        while(jdx < N) {
            *(*(arrs + idx) + jdx) = *(*(tokens + jdx));
            jdx++;
        }

        freeArrs((void**)tokens);
        idx++;
    }

    getPapers(arrs, 0, 0, N, N);
    char buf[32];
    char* resultStr = intToStr(white, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    resultStr = intToStr(blue, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    freeArrs((void**)arrs);

    return 0;
}

void getPapers(char** arrs, int sY, int sX, int eY, int eX) {
    _Bool isPaper = isSame(arrs, sY, sX, eY, eX);

    int len = eY - sY;

    if(isPaper) {
        return;
    } else {
        getPapers(arrs, sY, sX, sY + len / 2, sX + len / 2);
        getPapers(arrs, sY, sX + len / 2, sY + len / 2, sX + len);
        getPapers(arrs, sY + len / 2, sX, sY + len, sX + len / 2);
        getPapers(arrs, sY + len / 2, sX + len / 2, sY + len, sX + len);

        return;
    }
}

_Bool isSame(char** arrs, int sY, int sX, int eY, int eX) {
    char target = *(*(arrs + sY) + sX);

    _Bool isPaper = 1;

    int idx = sY;
    while(idx < eY) {
        int jdx = sX;
        while(jdx < eX) {
            char ch = *(*(arrs + idx) + jdx);

            if(ch != target){
                isPaper = 0;
                break;
            }
            jdx++;
        }
        idx++;
    }

    if(isPaper) {
        white = target == '0' ? white + 1 : white;
        blue = target == '1' ? blue + 1 : blue;
    }

    return isPaper;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    int bufSize = 10;
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    *(buf + bufSize) = 0;
    char* bufPtr = buf;

    char ch;
    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0)
                continue;

            *bufPtr = 0;
            *tokensPtr++ = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
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
