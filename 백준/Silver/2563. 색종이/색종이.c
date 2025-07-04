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
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	92795	59551	50101	64.197%

문제
---
가로, 세로의 크기가 각각 100인 정사각형 모양의 흰색 도화지가 있다.

이 도화지 위에

가로, 세로의 크기가 각각 10인 정사각형 모양의 검은색 색종이를 색종이의 변과 도화지의 변이 평행하도록 붙인다.

이러한 방식으로 색종이를 한 장 또는 여러 장 붙인 후 색종이가 붙은 검은 영역의 넓이를 구하는 프로그램을 작성하시오.

예를 들어 흰색 도화지 위에 세 장의 검은색 색종이를 그림과 같은 모양으로 붙였다면 검은색 영역의 넓이는 260이 된다.

입력
---
첫째 줄에 색종이의 수가 주어진다.

이어 둘째 줄부터 한 줄에 하나씩 색종이를 붙인 위치가 주어진다.

색종이를 붙인 위치는 두 개의 자연수로 주어지는데 첫 번째 자연수는 색종이의 왼쪽 변과 도화지의 왼쪽 변 사이의 거리이고,

두 번째 자연수는 색종이의 아래쪽 변과 도화지의 아래쪽 변 사이의 거리이다.

색종이의 수는 100 이하이며, 색종이가 도화지 밖으로 나가는 경우는 없다


출력
---
첫째 줄에 색종이가 붙은 검은 영역의 넓이를 출력한다.


예제 입력 1
3
3 7
15 7
5 2
예제 출력 1
260
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

void paint(_Bool** canvas, int x, int y, int len);

void freeArr(void** arr);

char** tokenzier(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    int width = 200;
    int height = 200;

    _Bool** canvas = (_Bool**)malloc(sizeof(_Bool*) * (height + 1));
    *(canvas + height) = NULL;
    _Bool** canvasPtr = (_Bool**)canvas;

    int i = 0;
    while(i++ < width) {
        *canvasPtr++ = (_Bool*)calloc(width + 1, sizeof(_Bool));
    }

    canvasPtr = (_Bool**)canvas;

    char input[255];

    fgets(input, sizeof(input), stdin);

    int loop = parseInt(input);

    while(--loop >= 0) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenzier(input);
        char** tokensPtr = (char**)tokens;

        int sX = parseInt(*tokensPtr++);
        int sY = parseInt(*tokensPtr++);

        paint(canvas, sX, sY, 10);
    }

    int painted = 0;

    int idx = 0;
    while(idx < height) {
        int jdx = 0;
        while(jdx < width) {
            painted = *(*(canvas + idx) + jdx) == 1 ? painted + 1 : painted;
            jdx++;
        }
        idx++;
    }

    char* result = intToStr(painted);

    fputs(result, stdout); fputc('\n', stdout);

    return 0;
}

void paint(_Bool** canvas, int x, int y, int len){
    int idx = y;
    while(idx < y + len) {

        int jdx = x;
        while(jdx < x + len) {
            *(*(canvas + idx) + jdx) = 1;
            jdx++;
        }
        idx++;
    }
}

void freeArr(void** arr) {
    void** arrPtr = (void**)arr;

    while(*arrPtr) {
        free(*arrPtr++);
    }
    free(arr);

    return;
}

char** tokenzier(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;

    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr++ = input[tknIdx++];
            }

            *tokensPtr++ = newTkn; currSize++;

            tknIdx = ++currIdx;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            currIdx++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = (char**)tokens;

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
    if(sign == -1) {
        *result = '-';
    }

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

    while(isBlank(*strPtr) != 1) {
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
