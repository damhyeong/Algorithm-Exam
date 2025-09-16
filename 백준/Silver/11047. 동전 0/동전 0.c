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
동전 0

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	179554	98469	74785	53.681%

문제
---
준규가 가지고 있는 동전은 총 N종류이고, 각각의 동전을 매우 많이 가지고 있다.

동전을 적절히 사용해서 그 가치의 합을 K로 만들려고 한다.

이때 필요한 동전 개수의 최솟값을 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 N과 K가 주어진다.

(1 ≤ N ≤ 10, 1 ≤ K ≤ 100,000,000)

둘째 줄부터 N개의 줄에 동전의 가치 A_i가 오름차순으로 주어진다.

(1 ≤ A_i ≤ 1,000,000, A_1 = 1, i ≥ 2인 경우에 Ai는 A_i-1의 배수)


출력
---
첫째 줄에 K원을 만드는데 필요한 동전 개수의 최솟값을 출력한다.

예제 입력 1
10 4200
1
5
10
50
100
500
1000
5000
10000
50000
예제 출력 1
6
예제 입력 2
10 4790
1
5
10
50
100
500
1000
5000
10000
50000
예제 출력 2
12
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** parseTwoTkn(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {

    char** tokens = parseTwoTkn(stdin);

    int N = parseInt(*tokens, NULL);
    int K = parseInt(*(tokens + 1), NULL);

    freeArrs((void**)tokens);

    int* divide = (int*)malloc(sizeof(int) * (N + 1));

    int idx = 0;
    while(idx < N)
        *(divide + idx++) = parseInt(NULL, stdin);

    int result = 0;
    idx = N - 1;
    while(idx >= 0) {
        int divNum = *(divide + idx--);

        result += K / divNum;
        K %= divNum;
    }

    char buf[32];
    char* resultStr = intToStr(result, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    free(divide);

    return 0;
}

char** parseTwoTkn(FILE* stream) {
    char* tkn1 = (char*)malloc(sizeof(char) * (20));
    char* tkn1Ptr = tkn1;

    char* tkn2 = (char*)malloc(sizeof(char) * (20));
    char* tkn2Ptr = tkn2;

    char ch;
    while(!isBlank(ch = fgetc(stream))) {
        *tkn1Ptr++ = ch;
    }
    *tkn1Ptr = 0;

    while(!isBlank(ch = fgetc(stream))) {
        *tkn2Ptr++ = ch;
    }
    *tkn2Ptr = 0;

    char** result = (char**)malloc(sizeof(char*) * (2 + 1));
    *(result + 2) = NULL;

    *result = tkn1;
    *(result + 1) = tkn2;

    return result;
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

        while(ch != -1) {
            if(ch == '\n') {
                break;
            }

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
