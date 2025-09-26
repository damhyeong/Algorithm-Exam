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
쿼드트리

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	61467	38595	29125	62.540%

문제
---
흑백 영상을 압축하여 표현하는 데이터 구조로 쿼드 트리(Quad Tree)라는 방법이 있다.

흰 점을 나타내는 0과 검은 점을 나타내는 1로만 이루어진 영상(2차원 배열)에서 같은 숫자의 점들이 한 곳에 많이 몰려있으면,

쿼드 트리에서는 이를 압축하여 간단히 표현할 수 있다.

주어진 영상이 모두 0으로만 되어 있으면 압축 결과는 "0"이 되고, 모두 1로만 되어 있으면 압축 결과는 "1"이 된다.

만약 0과 1이 섞여 있으면 전체를 한 번에 나타내지를 못하고,

왼쪽 위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래, 이렇게 4개의 영상으로 나누어 압축하게 되며,

이 4개의 영역을 압축한 결과를 차례대로 괄호 안에 묶어서 표현한다



위 그림에서 왼쪽의 영상은 오른쪽의 배열과 같이 숫자로 주어지며,

이 영상을 쿼드 트리 구조를 이용하여 압축하면 "(0(0011)(0(0111)01)1)"로 표현된다.

N ×N 크기의 영상이 주어질 때, 이 영상을 압축한 결과를 출력하는 프로그램을 작성하시오.


입력
---
첫째 줄에는 영상의 크기를 나타내는 숫자 N 이 주어진다.

N 은 언제나 2의 제곱수로 주어지며, 1 ≤ N ≤ 64의 범위를 가진다.

두 번째 줄부터는 길이 N의 문자열이 N개 들어온다.

각 문자열은 0 또는 1의 숫자로 이루어져 있으며, 영상의 각 점들을 나타낸다.


출력
---
영상을 압축한 결과를 출력한다.

예제 입력 1
8
11110000
11110000
00011100
00011100
11110000
11110000
11110011
11110011
예제 출력 1
((110(0101))(0010)1(0001))
*/

/**

*/

#include<stdio.h>
extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void pressing(char** arrs, int sY, int sX, int eY, int eX);
char checkSame(char** arrs, int sY, int sX, int eY, int eX);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {
    int N = parseInt(NULL, stdin);

    char** arrs = (char**)malloc(sizeof(char*) * (N + 1));
    *(arrs + N) = NULL;

    int idx = 0;
    while(idx < N) {
        char** tokens = tokenizer(stdin);

        char* copy = (char*)malloc(sizeof(char) * (N + 1));
        *(copy + N) = 0;

        int i = 0;
        while(i < N) {
            *(copy + i) = *(*tokens + i);
            i++;
        }

        freeArrs((void**)tokens);

        *(arrs + idx) = copy;

        idx++;
    }


    pressing(arrs, 0, 0, N, N);

    fputc('\n', stdout);

    freeArrs((void**)arrs);

    return 0;
}

void pressing(char** arrs, int sY, int sX, int eY, int eX) {
    int len = eY - sY;

    if(checkSame(arrs, sY, sX, eY, eX) != -1) {
        fputc(*(*(arrs + sY) + sX), stdout);

        return;
    }



    int midY = sY + (len / 2);
    int midX = sX + (len / 2);

    fputc('(', stdout);

    char checkSec1 = checkSame(arrs, sY, sX, midY, midX);
    char checkSec2 = checkSame(arrs, sY, midX, midY, eX);
    char checkSec3 = checkSame(arrs, midY, sX, eY, midX);
    char checkSec4 = checkSame(arrs, midY, midX, eY, eX);

    if(checkSec1 != -1) {
        fputc(checkSec1, stdout);
    } else {
        pressing(arrs, sY, sX, midY, midX);
    }

    if(checkSec2 != -1) {
        fputc(checkSec2, stdout);
    } else {
        pressing(arrs, sY, midX, midY, eX);
    }

    if(checkSec3 != -1) {
        fputc(checkSec3, stdout);
    } else {
        pressing(arrs, midY, sX, eY, midX);
    }

    if(checkSec4 != -1) {
        fputc(checkSec4, stdout);
    } else {
        pressing(arrs, midY, midX, eY, eX);
    }

    fputc(')', stdout);

    return;
}
char checkSame(char** arrs, int sY, int sX, int eY, int eX) {
    _Bool isSame = 1;

    char target = *(*(arrs + sY) + sX);
    int idx = sY;
    while(idx < eY) {
        int jdx = sX;
        while(jdx < eX) {
            if(target != *(*(arrs + idx) + jdx)) {
                isSame = 0;
                break;
            }
            jdx++;
        }
        idx++;
    }

    if(isSame) {
        return target;
    } else {
        return -1;
    }
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

    long temp = target < 0 ? -target : target;
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
