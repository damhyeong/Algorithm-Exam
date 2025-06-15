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
1 초	1024 MB	184930	101749	89108	55.503%

문제
---
준원이는 저번 주에 살면서 처음으로 코스트코를 가 봤다.

정말 멋졌다. 그런데, 몇 개 담지도 않았는데 수상하게 높은 금액이 나오는 것이다!

준원이는 영수증을 보면서 정확하게 계산된 것이 맞는지 확인해보려 한다.

영수증에 적힌,

* 구매한 각 물건의 가격과 개수
* 구매한 물건들의 총 금액
*
을 보고, 구매한 물건의 가격과 개수로 계산한 총 금액이 영수증에 적힌 총 금액과 일치하는지 검사해보자.

입력
---
첫째 줄에는 영수증에 적힌 총 금액
X 가 주어진다.

둘째 줄에는 영수증에 적힌 구매한 물건의 종류의 수
N 이 주어진다.

이후
N 개의 줄에는 각 물건의 가격
a 와 개수
b 가 공백을 사이에 두고 주어진다.

출력
구매한 물건의 가격과 개수로 계산한 총 금액이 영수증에 적힌 총 금액과 일치하면 Yes를 출력한다.

일치하지 않는다면 No를 출력한다.

제한
---
1 ≤ X ≤ 1,000,000,000
1 ≤ N ≤ 100
1 ≤ a ≤ 1,000,000
1 ≤ b ≤ 10

예제 입력 1
260000
4
20000 5
30000 2
10000 6
5000 8
예제 출력 1
Yes

영수증에 적힌 구매할 물건들의 목록으로 계산한 총 금액은

20000 × 5 + 30000 × 2 + 10000 × 6 + 5000 × 8 = 260000원이다.

이는 영수증에 적힌 총 금액인 260000원과 일치한다.

예제 입력 2
250000
4
20000 5
30000 2
10000 6
5000 8
예제 출력 2
No
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void* realloc(void*, size_t);
extern void free(void*);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int totalPrice = parseInt(input);

    fgets(input, sizeof(input), stdin);

    int loop = parseInt(input);

    int resultPrice = 0;

    while(--loop >= 0) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int price = parseInt(*tokensPtr++);
        int count = parseInt(*tokensPtr++);

        freeTokens(tokens);

        resultPrice += price * count;
    }

    if(totalPrice == resultPrice) {
        fputs("Yes\n", stdout);
    } else {
        fputs("No\n", stdout);
    }

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

            *tokensPtr++ = (char*)newTkn; currSize++;

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

    int size = (sign == 1) ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = (sign == 1) ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
        target /= 10;
    }
    if(sign == -1) {
        *result = '-';
    }

    return result;
}

int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

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
