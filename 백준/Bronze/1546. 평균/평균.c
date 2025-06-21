/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.

    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!
*/

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	334720	170712	137483	50.423%

문제
---
세준이는 기말고사를 망쳤다.

세준이는 점수를 조작해서 집에 가져가기로 했다.

일단 세준이는 자기 점수 중에 최댓값을 골랐다.

이 값을 M이라고 한다.

그리고 나서 모든 점수를 점수/M*100으로 고쳤다.


예를 들어, 세준이의 최고점이 70이고, 수학점수가 50이었으면

수학점수는 50/70*100 이 되어 71.43점이 된다.

세준이의 성적을 위의 방법대로 새로 계산했을 때, 새로운 평균을 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 시험 본 과목의 개수 N이 주어진다.

이 값은 1000보다 작거나 같다.

둘째 줄에 세준이의 현재 성적이 주어진다.

이 값은 100보다 작거나 같은 음이 아닌 정수이고, 적어도 하나의 값은 0보다 크다.

출력
---
첫째 줄에 새로운 평균을 출력한다.

실제 정답과 출력값의 절대오차 또는 상대오차가 10^-2 이하이면 정답이다.

예제 입력 1
3
40 80 60
예제 출력 1
75.0

예제 입력 2
3
10 20 30
예제 출력 2
66.666667

10-2 이하의 오차를 허용한다는 말은 정확히 소수 2번째 자리까지 출력하라는 뜻이 아니다.

예제 입력 3
4
1 100 100 100
예제 출력 3
75.25

예제 입력 4
5
1 2 4 8 16
예제 출력 4
38.75

예제 입력 5
2
3 10
예제 출력 5
65.0

예제 입력 6
4
10 20 0 100
예제 출력 6
32.5

예제 입력 7
1
50
예제 출력 7
100.0

예제 입력 8
9
10 20 30 40 50 60 70 80 90
예제 출력 8
55.55555555555556

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
char* intToStr(int target);
int parseInt(const char* str);
char* doubleToStr(double target);
double parseDouble(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[10000];

    fgets(input, sizeof(input), stdin);

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int biggest = parseInt(*tokensPtr++);

    while(*tokensPtr) {
        int score = parseInt(*tokensPtr++);

        if(biggest <= score) {
            biggest = score;
        }
    }

    tokensPtr = (char**)tokens;

    double total = 0;
    int count = 0;
    while(*tokensPtr) {
        int score = parseInt(*tokensPtr++);

        double aftScore = (double)score * 100 / (double)(biggest);

        total += aftScore; count++;
    }

    double avg = total / (double)count;

    char* result = doubleToStr(avg);

    fputs(result, stdout); fputc('\n', stdout);

    free(result);

    return 0;
}

char** tokenizer(const char* input) {
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
            newTkn[tknSize] = '\0';
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

// 개인적으로 너무 지저분하게 작성했다. 다음에 작성 할 땐 깔끔하게 작성하자.
char* doubleToStr(double target) {
    int sign = 1;
    // int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    long longPart = (long)target;
    int longLen = 0;

    long tempLong = longPart;
    do {
        tempLong /= 10;
        longLen++;
    } while (tempLong != 0);

    int tempInt = (int)longPart;

    char* longStr = intToStr(tempInt);

    double doublePart = target - (double)longPart;

    char* doubleStr = (char*)malloc(sizeof(char) * (9 + 1));
    doubleStr[9] = '\0';

    int idx = 0;
    while(idx < 3) {
        doublePart *= 10.0;
        int n = (int)doublePart;

        doubleStr[idx++] = n + '0';
        doublePart = doublePart - (int)doublePart;

    }

    int resultLen = longLen + 1 + 3;
    char* resultStr = (char*)malloc(sizeof(char) * (resultLen + 1));
    resultStr[resultLen] = '\0';
    // char* resultStrPtr = (char*)resultStr;

    idx = 0;
    char* longStrPtr = (char*)longStr;
    while(*longStrPtr) {
        resultStr[idx++] = *longStrPtr++;
    }
    free(longStr);

    resultStr[idx++] = '.';

    char* doubleStrPtr = (char*)doubleStr;
    while(*doubleStrPtr) {
        resultStr[idx++] = *doubleStrPtr++;
    }

    return resultStr;
}
double parseDouble(const char* str) {
    double sign = 1;
    int intPart = 0;
    double doublePart = 0;

    char* strPtr = (char*)str;
    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    // 정수 부분을 떼어낸다.
    while(*strPtr != '.') {
        intPart *= 10;
        intPart += *strPtr++ - '0';
    }

    strPtr++;

    double div = 0.1;

    while(isBlank(*strPtr) != 1) {
        int doubleNum = *strPtr++ - '0';

        doublePart += div * doubleNum;

        div /= 10;
    }

    double result = (double)intPart + doublePart;

    return result * (double)sign;
}
char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= sign;
    }

    int temp = target;
    do {
        temp /= 10;
        len++;
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    int idx = endIdx;
    while(idx >= startIdx) {
        *(result + idx--) = target % 10 + '0';
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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
