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
1 초	128 MB	130871	53252	46077	41.422%

문제
---
<그림 1>과 같이 9×9 격자판에 쓰여진 81개의 자연수 또는 0이 주어질 때,

이들 중 최댓값을 찾고 그 최댓값이 몇 행 몇 열에 위치한 수인지 구하는 프로그램을 작성하시오.


예를 들어, 다음과 같이 81 개의 수가 주어지면

 	1열	2열	3열	4열	5열	6열	7열	8열	9열
1행	3	23	85	34	17	74	25	52	65
2행	10	7	39	42	88	52	14	72	63
3행	87	42	18	78	53	45	18	84	53
4행	34	28	64	85	12	16	75	36	55
5행	21	77	45	35	28	75	90	76	1
6행	25	87	65	15	28	11	37	28	74
7행	65	27	75	41	7	89	78	64	39
8행	47	47	70	45	23	65	3	41	44
9행	87	13	82	38	31	12	29	29	80

이들 중 최댓값은 90이고,

이 값은 5행 7열에 위치한다.


입력
---
첫째 줄부터 아홉 번째 줄까지 한 줄에 아홉 개씩 수가 주어진다.

주어지는 수는 100보다 작은 자연수 또는 0이다.


출력
---
첫째 줄에 최댓값을 출력하고, 둘째 줄에 최댓값이 위치한 행 번호와 열 번호를 빈칸을 사이에 두고 차례로 출력한다.

최댓값이 두 개 이상인 경우 그 중 한 곳의 위치를 출력한다.


예제 입력 1
3 23 85 34 17 74 25 52 65
10 7 39 42 88 52 14 72 63
87 42 18 78 53 45 18 84 53
34 28 64 85 12 16 75 36 55
21 77 45 35 28 75 90 76 1
25 87 65 15 28 11 37 28 74
65 27 75 41 7 89 78 64 39
47 47 70 45 23 65 3 41 44
87 13 82 38 31 12 29 29 80
예제 출력 1
90
5 7
*/

#include <stdatomic.h>
#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    int biggest = -1;
    int I = -1;
    int J = -1;

    int idx = 0;
    while(idx < 9) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int jdx = 0;
        while(jdx < 9) {

            int tempNum = parseInt(*tokensPtr++);

            if(biggest < tempNum) {
                I = idx + 1;
                J = jdx + 1;
                biggest = tempNum;
            }

            jdx++;
        }
        idx++;

        freeTokens(tokens);
    }

    char* biggestStr = intToStr(biggest);
    char* iStr = intToStr(I);
    char* jStr = intToStr(J);

    fputs(biggestStr, stdout); fputc('\n', stdout);
    fputs(iStr, stdout); fputc(' ', stdout); fputs(jStr, stdout); fputc('\n', stdout);

    free(biggestStr); free(iStr); free(jStr);

    return 0;
}

char** tokenizer(const char* input) {
    int size = 2;
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
