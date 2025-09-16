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
체스판 다시 칠하기 2

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	12208	4923	3718	39.087%

문제
---
지민이는 자신의 저택에서 MN개의 단위 정사각형으로 나누어져 있는 M×N 크기의 보드를 찾았다.

어떤 정사각형은 검은색으로 칠해져 있고, 나머지는 흰색으로 칠해져 있다.

지민이는 이 보드를 잘라서 K×K 크기의 체스판으로 만들려고 한다.

체스판은 검은색과 흰색이 번갈아서 칠해져 있어야 한다.

구체적으로, 각 칸이 검은색과 흰색 중 하나로 색칠되어 있고, 변을 공유하는 두 개의 사각형은 다른 색으로 칠해져 있어야 한다.

따라서 이 정의를 따르면 체스판을 색칠하는 경우는 두 가지뿐이다.

하나는 맨 왼쪽 위 칸이 흰색인 경우, 하나는 검은색인 경우이다.

보드가 체스판처럼 칠해져 있다는 보장이 없어서, 지민이는 K×K 크기의 체스판으로 잘라낸 후에 몇 개의 정사각형을 다시 칠해야겠다고 생각했다.

당연히 K×K 크기는 아무데서나 골라도 된다.

지민이가 다시 칠해야 하는 정사각형의 최소 개수를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 정수 N, M, K가 주어진다.

둘째 줄부터 N개의 줄에는 보드의 각 행의 상태가 주어진다.

B는 검은색이며, W는 흰색이다.


출력
---
첫째 줄에 지민이가 잘라낸 K×K 보드를 체스판으로 만들기 위해 다시 칠해야 하는 정사각형 개수의 최솟값을 출력한다.

제한
---
1 ≤ N, M ≤ 2000
1 ≤ K ≤ min(N, M)
예제 입력 1
4 4 3
BBBB
BBBB
BBBW
BBWB
예제 출력 1
2
예제 입력 2
8 8 8
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBBBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
예제 출력 2
1
예제 입력 3
10 13 10
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
WWWWWWWWWWBWB
WWWWWWWWWWBWB
예제 출력 3
30
예제 입력 4
9 23 9
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBWWWWWWWW
예제 출력 4
40
*/

/**

행, 그리고 열의 합 --> IDX(row) + IDX(col) 의 합이 짝수, 혹은 홀수인지에 따라 하얀색, 검정색을 결정할 수 있다.

*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void* realloc(void* memory, size_t byte);
extern void free(void* memory);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* parseStr(FILE* stream);
char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char** tokens = tokenizer(stdin);

    int N = parseInt(*tokens); // --> row
    int M = parseInt(*(tokens + 1)); // --> col
    int K = parseInt(*(tokens + 2));

    freeArrs((void**)tokens);

    int** wDps = (int**)malloc(sizeof(int*) * (N + 2)); // --> 하얀색 시작 보드
    int** bDps = (int**)malloc(sizeof(int*) * (N + 2)); // --> 검정색 시작 보드

    int idx = 0;
    while(idx <= N) {
        *(wDps + idx) = (int*)calloc(M + 2, sizeof(int));
        *(bDps + idx) = (int*)calloc(M + 2, sizeof(int));

        idx++;
    }

    idx = 1;
    while(idx <= N) {
        char* line = parseStr(stdin);

        int jdx = 1;
        while(jdx <= M) {
            char ch = *(line + jdx - 1);

            char wCh = (idx + jdx) % 2 == 0 ? 'W' : 'B';
            char bCh = (idx + jdx) % 2 == 0 ? 'B' : 'W';

            *(*(wDps + idx) + jdx)
                = *(*(wDps + idx) + jdx - 1)
                + (*(*(wDps + idx - 1) + jdx) - *(*(wDps + idx - 1) + jdx - 1))
                + (ch != wCh ? 1 : 0);

            *(*(bDps + idx) + jdx)
                = *(*(bDps + idx) + jdx - 1)
                + (*(*(bDps + idx - 1) + jdx) - *(*(bDps + idx - 1) + jdx - 1))
                + (ch != bCh ? 1 : 0);

            jdx++;
        }
        idx++;
    }

    int min = 10000000;
    idx = K;
    while(idx <= N) {
        int jdx = K;
        while(jdx <= M) {
            int wDiff
                = *(*(wDps + idx) + jdx) - *(*(wDps + idx) + jdx - K)
                - (*(*(wDps + idx - K) + jdx) - *(*(wDps + idx - K) + jdx - K));

            int bDiff
                = *(*(bDps + idx) + jdx) - *(*(bDps + idx) + jdx - K)
                - (*(*(bDps + idx - K) + jdx) - *(*(bDps + idx - K) + jdx - K));

            int tempMin = wDiff < bDiff ? wDiff : bDiff;
            min = tempMin < min ? tempMin : min;

            jdx++;
        }
        idx++;
    }

    char buf[32];
    char* resultStr = intToStr(min, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    char* buf = (char*)malloc(sizeof(char) * (100 + 1));
    *(buf + 100) = 0;
    char* bufPtr = buf;

    char ch;
    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0) {
                continue;
            }

            buf = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            *(buf + tknSize) = 0;
            *tokensPtr++ = buf; curr++;

            buf = (char*)malloc(sizeof(char) * (100 + 1));
            *(buf + 100) = 0;
            bufPtr = buf; tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch;
            tknSize++;
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


char* parseStr(FILE* stream) {
    int bufSize = 5;
    int currSize = 0;

    char* str = (char*)malloc(sizeof(char) * (bufSize + 1));
    *(str + bufSize) = 0;
    char* strPtr = str;

    char ch;
    while((ch = fgetc(stream)) != -1) {
        *strPtr++ = ch; currSize++;

        if(bufSize == currSize) {
            bufSize *= 2;
            str = (char*)realloc(str, sizeof(char) * (bufSize + 1));
            strPtr = (char*)(str + currSize);
        }

        if(ch == '\n') {
            break;
        }
    }

    str = (char*)realloc(str, sizeof(char) * (currSize + 1));
    *(str + currSize) = 0;

    return str;
}
char* intToStr(int target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long temp = target;
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
