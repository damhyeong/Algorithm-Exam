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
구간 합 구하기 5

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	99911	46378	34162	44.385%

문제
---
N×N개의 수가 N×N 크기의 표에 채워져 있다.

(x1, y1)부터 (x2, y2)까지 합을 구하는 프로그램을 작성하시오.

(x, y)는 x행 y열을 의미한다.

예를 들어, N = 4이고, 표가 아래와 같이 채워져 있는 경우를 살펴보자.

1	2	3	4
2	3	4	5
3	4	5	6
4	5	6	7

여기서 (2, 2)부터 (3, 4)까지 합을 구하면 3+4+5+4+5+6 = 27이고, (4, 4)부터 (4, 4)까지 합을 구하면 7이다.

표에 채워져 있는 수와 합을 구하는 연산이 주어졌을 때, 이를 처리하는 프로그램을 작성하시오.

입력
---
첫째 줄에 표의 크기 N과 합을 구해야 하는 횟수 M이 주어진다.

(1 ≤ N ≤ 1024, 1 ≤ M ≤ 100,000) 둘째 줄부터 N개의 줄에는 표에 채워져 있는 수가 1행부터 차례대로 주어진다.

다음 M개의 줄에는 네 개의 정수 x1, y1, x2, y2 가 주어지며,

(x1, y1)부터 (x2, y2)의 합을 구해 출력해야 한다.

표에 채워져 있는 수는 1,000보다 작거나 같은 자연수이다.

(x1 ≤ x2, y1 ≤ y2)


출력
---
총 M줄에 걸쳐 (x1, y1)부터 (x2, y2)까지 합을 구해 출력한다.

예제 입력 1
4 3
1 2 3 4
2 3 4 5
3 4 5 6
4 5 6 7
2 2 3 4
3 4 3 4
1 1 4 4
예제 출력 1
27
6
64
예제 입력 2
2 4
1 2
3 4
1 1 1 1
1 2 1 2
2 1 2 1
2 2 2 2
예제 출력 2
1
2
3
4
*/

/**
 * 어떠한 부분을 자를지 알아서 생각하면 되는 문제.
 *
 * ---
 *
 * 행 --> x, 열 --> y 이다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenzier(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(long target, int bufSize, char* buf);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char** tokens = tokenzier(stdin);

    int N = parseInt(*tokens);
    int M = parseInt(*(tokens + 1));

    freeArrs((void**)tokens);

    long** dps = (long**)malloc(sizeof(long*) * (N + 2));

    int idx = 0;
    while(idx <= N) {
        *(dps + idx++) = (long*)calloc(N + 2, sizeof(long));
    }

    idx = 1;
    while(idx <= N) {
        tokens = tokenzier(stdin);
        char** tokensPtr = tokens;

        int jdx = 1;
        while(jdx <= N) {
            long num = (long)parseInt(*tokensPtr++);

            long leftPart = *(*(dps + idx) + jdx - 1);
            long upperPart = *(*(dps + idx - 1) + jdx) - *(*(dps + idx - 1) + jdx - 1);

            *(*(dps + idx) + jdx) = num + leftPart + upperPart;
            jdx++;
        }

        freeArrs((void**)tokens);

        idx++;
    }

    idx = 0;
    while(idx++ < M) {
        tokens = tokenzier(stdin);

        long x1 = (long)parseInt(*tokens);
        long y1 = (long)parseInt(*(tokens + 1));
        long x2 = (long)parseInt(*(tokens + 2));
        long y2 = (long)parseInt(*(tokens + 3));

        freeArrs((void**)tokens);

        long result = *(*(dps + x2) + y2);
        long leftPart = *(*(dps + x2) + y1 - 1);
        long upperPart = *(*(dps + x1 - 1) + y2) - *(*(dps + x1 - 1) + y1 - 1);

        result = result - leftPart - upperPart;
        char buf[32];
        char* resultStr = intToStr(result, sizeof(buf), buf);
        fputs(resultStr, stdout); fputc('\n', stdout);
    }

    return 0;
}

char** tokenzier(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char ch;
    int tknSize = 0;

    char* buf = (char*)malloc(sizeof(char) * (100 + 1));
    *(buf + 100) = 0;
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0) {
                continue;
            }

            buf = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            *(buf + tknSize) = 0;
            *tokensPtr++ = buf; curr++;

            buf = (char*)malloc(sizeof(char) * (100 + 1));
            bufPtr = buf;
            tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch;
            tknSize++;
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
int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

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
