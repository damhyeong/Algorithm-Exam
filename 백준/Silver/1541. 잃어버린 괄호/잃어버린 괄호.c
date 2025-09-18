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
잃어버린 괄호

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	109122	61244	47578	55.402%

문제
---
세준이는 양수와 +, -, 그리고 괄호를 가지고 식을 만들었다.

그리고 나서 세준이는 괄호를 모두 지웠다.

그리고 나서 세준이는 괄호를 적절히 쳐서 이 식의 값을 최소로 만들려고 한다.

괄호를 적절히 쳐서 이 식의 값을 최소로 만드는 프로그램을 작성하시오.

입력
---
첫째 줄에 식이 주어진다. 식은 ‘0’~‘9’, ‘+’, 그리고 ‘-’만으로 이루어져 있고, 가장 처음과 마지막 문자는 숫자이다.

그리고 연속해서 두 개 이상의 연산자가 나타나지 않고, 5자리보다 많이 연속되는 숫자는 없다.

수는 0으로 시작할 수 있다.

입력으로 주어지는 식의 길이는 50보다 작거나 같다.


출력
---
첫째 줄에 정답을 출력한다.

예제 입력 1
55-50+40
예제 출력 1
-35

예제 입력 2
10+20+30+40
예제 출력 2
100

예제 입력 3
00009-00009
예제 출력 3
0
*/

/**

*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void* realloc(void* memory, size_t byte);
extern void free(void* memory);

char** tokenizer(FILE* stream, char* delim);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);


int main(void) {

    char delim[] = {'-', '+'};
    char** tokens = tokenizer(stdin, delim);
    char** tokensPtr = tokens;

    int sign = 1;
    int result = 0;
    while(*tokensPtr) {
        int currNum = parseInt(*tokensPtr++, NULL);

        if(currNum < 0) {
            sign = -1;
        }

        if(sign > 0) {
            result += currNum;
        } else {
            currNum = currNum > 0 ? -1 * currNum : currNum;
            result += currNum;
        }
    }

    freeArrs((void**)tokens);

    char buf[32];
    char* resultStr = intToStr(result, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

char** tokenizer(FILE* stream, char* delim) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    int bufSize = 100;
    int tknSize = 0;
    char ch = fgetc(stream);
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    char* bufPtr = buf;

    if(ch == '-') {
        *bufPtr++ = '-'; tknSize++;
        ch = fgetc(stream);
    }

    while(ch != -1) {
        // 빈칸이거나, '-' 혹은 '+'
        if(isBlank(ch) || ch == *delim || ch == *(delim + 1)) {
            if(tknSize == 0) {
                continue;
            }

            *bufPtr = 0;
            buf = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            *tokensPtr++ = buf; curr++;

            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            bufPtr = buf;
            tknSize = 0;

            if(ch == *delim) {
                *bufPtr++ = *delim;
                tknSize++;
            } else if(ch == *(delim + 1)) {
                *bufPtr++ = *(delim + 1);
                tknSize++;
            }

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch; tknSize++;
        }



        if(ch == '\n') {
            break;
        }

        ch = fgetc(stream);
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
        } else if(*strPtr == '+') {
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
            fgetc(stream);
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
