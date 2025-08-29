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
신나는 함수 실행

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	55777	25184	19048	43.432%

문제
---
재귀 호출만 생각하면 신이 난다! 아닌가요?

다음과 같은 재귀함수 w(a, b, c)가 있다.
---------------------------------------------------------------------------------------------------------
if a <= 0 or b <= 0 or c <= 0, then w(a, b, c) returns:
    1

if a > 20 or b > 20 or c > 20, then w(a, b, c) returns:
    w(20, 20, 20)

if a < b and b < c, then w(a, b, c) returns:
    w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)

otherwise it returns:
    w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1)
---------------------------------------------------------------------------------------------------------

위의 함수를 구현하는 것은 매우 쉽다.

하지만, 그대로 구현하면 값을 구하는데 매우 오랜 시간이 걸린다.

(예를 들면, a=15, b=15, c=15)

a, b, c가 주어졌을 때, w(a, b, c)를 출력하는 프로그램을 작성하시오.

입력
---
입력은 세 정수 a, b, c로 이루어져 있으며, 한 줄에 하나씩 주어진다.

입력의 마지막은 -1 -1 -1로 나타내며, 세 정수가 모두 -1인 경우는 입력의 마지막을 제외하면 없다.


출력
---
입력으로 주어진 각각의 a, b, c에 대해서, w(a, b, c)를 출력한다.

제한
---
-50 ≤ a, b, c ≤ 50

예제 입력 1
1 1 1
2 2 2
10 4 6
50 50 50
-1 7 18
-1 -1 -1
예제 출력 1
w(1, 1, 1) = 2
w(2, 2, 2) = 4
w(10, 4, 6) = 523
w(50, 50, 50) = 1048576
w(-1, 7, 18) = 1
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeArr(void** arr);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    int*** cube = (int***)malloc(sizeof(int**) * (21 + 1));
    *(cube + 21) = NULL;

    int i = 0;
    while(i <= 20) {
        *(cube + i) = (int**)malloc(sizeof(int*) * (21 + 1));

        int j = 0;
        while(j <= 20) {
            *(*(cube + i) + j) = (int*)malloc(sizeof(int) * (21 + 1));
            j++;
        }
        i++;
    }

    i = 0;
    while(i <= 20) {
        int j = 0;
        while(j <= 20) {
            int k = 0;
            while(k <= 20) {
                if(i <= 0 || j <= 0 || k <= 0) {
                    *(*(*(cube + i) + j) + k) = 1;
                } else if(i < j && j < k) {
                    *(*(*(cube + i) + j) + k)
                        = *(*(*(cube + i) + j) + k - 1)
                        + *(*(*(cube + i) + j - 1) + k - 1)
                        - *(*(*(cube + i) + j - 1) + k);
                } else {
                    *(*(*(cube + i) + j) + k)
                        = *(*(*(cube + i - 1) + j) + k)
                        + *(*(*(cube + i - 1) + j - 1) + k)
                        + *(*(*(cube + i - 1) + j) + k - 1)
                        - *(*(*(cube + i - 1) + j - 1) + k - 1);
                }

                k++;
            }
            j++;
        }
        i++;
    }

    char input[255];


    while(1) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = tokens;

        int originA = parseInt(*tokensPtr++);
        int originB = parseInt(*tokensPtr++);
        int originC = parseInt(*tokensPtr++);

        int a = originA; int b = originB; int c = originC;

        freeArr((void**)tokens);

        if(a == -1 && b == -1 && c == -1) {
            break;
        }

        if(a <= 0 || b <= 0 || c <= 0) {
            a = 0; b = 0; c = 0;
        }

        if(a > 20 || b > 20 || c > 20) {
            a = 20; b = 20; c = 20;
        }

        char* aStr = intToStr(originA);
        char* bStr = intToStr(originB);
        char* cStr = intToStr(originC);

        // w(1, 1, 1) = 2
        fputs("w(", stdout); fputs(aStr, stdout); fputs(", ", stdout); fputs(bStr, stdout); fputs(", ", stdout); fputs(cStr, stdout); fputs(") = ", stdout);
        free(aStr); free(bStr); free(cStr);

        char* result = intToStr(*(*(*(cube + a) + b) + c));
        fputs(result, stdout); fputc('\n', stdout);
        free(result);

    }

    int*** cubePtr = cube;
    while(*cubePtr) {
        freeArr((void**)*cubePtr++);
    }
    free(cube);

    return 0;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }
            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeArr(void** arr) {
    void** arrPtr = arr;
    while(*arrPtr) {
        free(*arrPtr++);
    }
    free(arr);

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
