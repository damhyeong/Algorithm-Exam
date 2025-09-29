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
곱셈

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	128 MB	162952	47667	34478	28.175%

문제
---
자연수 A를 B번 곱한 수를 알고 싶다.

단 구하려는 수가 매우 커질 수 있으므로 이를 C로 나눈 나머지를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 A, B, C가 빈 칸을 사이에 두고 순서대로 주어진다.

A, B, C는 모두 2,147,483,647 이하의 자연수이다.


출력
---
첫째 줄에 A를 B번 곱한 수를 C로 나눈 나머지를 출력한다.

예제 입력 1
10 11 12
예제 출력 1
4
*/


/**
"분할 정복" 카테고리에 속한 문제라는 것을 보아 떠올리게 된 프로세스이다.

확실히 B 가 21 억에 가까운 수가 된다면, 단순 반복문으로는 시간 제한 0.5 초 만에 풀 수 없는 문제이다.

그렇다면, 어떻게 푸는가?

처음에는 DP 형식으로 풀이 형식을 떠올렸는데, 파스칼의 삼각형이 떠올랐다.

그리고, 설마 벌써 행렬이 사용되나? 하는 문제이기도 했다. (행렬 방식을 까먹어서)

다시 생각 해 보니까, '재귀' 방식을 이용하여 B 를 나누면 되는 문제이다.

재귀란 자기 자신을 "다시 호출" 하는 형태를 일컫기도 하지만,

가장 작은 계산 단위에서 직접적인 계산이 이루어지는 형태를 말하기도 한다.

그렇다면, B 를 기준으로, 절반으로 나누어 재귀를 이어가면 되는 것이다.

---

a^b % c 를 구하기 위해 재귀 기반의 분할 정복을 실시했으나, 시간 초과로 인해 통과하지 못했다.

재귀는 b 를 절반으로 나누며 밑에 하달하는 형식으로 진행했는데, b 가 21억에 도달 할 경우, 굉장한 시간이 걸렸다.

이는 재귀 시 생성되는 하위 함수의 수가 기하급수적으로 많아졌기 때문일 것이다. (N^2) 개로 많아 질 테니까...

즉, b 가 21 억이라면, 2^31 개 정도? 로 많아졌을 것이다.

이를 막기 위해 b 가 1000 이하일 시, 직접 루프로 계산하여 되돌려주는 형식을 만들었지만, 시간 초과를 피하지 못했다.

그렇다면, 근본적으로 재귀 함수의 개수를 줄일 수 있는 방식이 무엇일까... 생각을 해 보니,

b 를 "절반" 으로 똑 떼서 만드는 것이 아니라, 재귀 함수가 "일직선" 형식으로 재귀 되도록 만들면 되는 것이다.

먼저 a^b 에 집중해 보겠다.

a^b 의 구성은 a^(b / 2) * a^(b / 2) 로 이루어 진다.
이는 a^( (b / 2) + (b / 2) ) 로 이루어 진다.

내가 시간초과가 난 이유는, 양 쪽으로 생성되는 재귀 함수의 단위가 a^(b / 2) 였기 때문이다.

동일하지만, 수학적으로 조금 더 넓은 시야로 봐야한다는 것을 알게 되었다.

a^b 의 구성은, a^(b / 2)^2 로 이루어 질 수 있다.

a^(b / 2) 는, 스스로를 다시 제곱하여 이루어진다.

---

여기서 의문을 제기해야 하는 것이, 제곱인 b 를 절반으로 나누어 계산하는 과정에서 대부분의 수의 나눔 과정에서 "홀수" 는 나온다는 것이다.

예를 들어 6 도 나누면 "3" 이 나온다. 이 때는 어떻게 대처해야 할까?

예로 들어진 A : 10, B : 11, C : 12 로 계산 해 보자.

물론, 여기서 C 를 중점으로 다루진 않는다.

그렇다면, 10^11 을 계산해야 하는 것인데,

10 을 11 번 스스로 곱한다는 계산이다.

따라서, 11 을 컴퓨터 계산 상으로 단순 계산했을 때, 11 은 5 가 나온다.

10^5 * 10^5 * 10 을 하면 된다는 계산이 되었다.

여기서 10^5 는, 양 쪽으로 나누어 재귀한 결과가 아닌, 일직선상의 재귀의 결과를 의미한다.

따라서, 재귀 함수는 두 가지 경우에 따라 계산 과정이 달라지게 된다.

1. 홀수 일 때, 하위 재귀 계산 결과를 서로 곱한 후, a(기반 수) 를 곱한다.
2. 짝수 일 때, 하위 재귀 계산 결과를 서로 곱한 후, 바로 반환한다.
*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

long long recursiveConquer(long a, long b, long c);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(long target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {

    char** tokens = tokenizer(stdin);

    int A = parseInt(*tokens, NULL);
    int B = parseInt(*(tokens + 1), NULL);
    int C = parseInt(*(tokens + 2), NULL);

    freeArrs((void**)tokens);

    long result = recursiveConquer(A, B, C);

    char buf[32];
    char* resultStr = intToStr((int)result, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

long long recursiveConquer(long a, long b, long c) {
    if(b <= 1) {
        return b == 0 ? 1 : a % c;
    }

    long tmp = recursiveConquer(a, b / 2, c);
    tmp = (tmp * tmp) % c;

    // odd
    if(b % 2) {
        return (tmp * a) % c;
    } else { // even
        return tmp % c;
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
            if(!tknSize)
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
            *bufPtr++ = ch; tknSize++;
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
    temp = target < 0 ? -temp : temp;

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

        while(!isBlank(ch)) {
            result *= 10;
            result += ch - '0';
            ch = fgetc(stream);
        }
    }

    return result * sign;
}
_Bool isBlank(char ch) {
    if(ch == 32 || ch == 0)
        return 1;
    else if(ch >= 9 && ch <= 13)
        return 1;
    else
        return 0;
}
