
/**
이항 계수 3 성공
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	36086	13438	9911	40.091%

문제
---
자연수 N 과 정수 K 가 주어졌을 때, 이항 계수 ( N ) 를 1,000,007 로 나눈 나머지를 구하는 프로그램을 작성하시오.
                                    ( K )


입력
---
첫째 줄에 N 과 K 가 주어진다.

( 1 <= N <= 4,000,000,  0 <= K <= N )


출력
---
( N ) 를 1,000,000,007 로 나눈 나머지를 출력한다.
( K )


예제 입력 1
5 2
예제 출력 1
10
*/

/**

이항 계수는 식으로 외우거나, DP 의 형태로 풀이 할 수 있다.

신기하게도, 손으로 푸는 이항 계수의 풀이법은 컴퓨터에서 동작하면 오류가 날 확률이 크다. (저장할 수 있는 수의 한계를 손쉽게 넘기 때문)

따라서, 이는 "파스칼의 삼각형" 을 2 차원 배열로 펼쳐서 계산하는 것이 컴퓨터 알고리즘 상의 일반적인 풀이법이다.

그러나, 나는 또 다른 파스칼의 삼각형 혹은 이항 계수의 풀이법을 배울 것 같은데,

그 이유는 수의 제한 자체가 너무나도 크기 때문이다.

나열되어 있는 제품 400 만개가 존재 할 때, 순서 상관없는 200 만개를 고르는 경우의 수를 구한다고 가정해 보자.

아무리 생각 해 봐도, 이건 내가 여태까지 풀어온 이항 계수 풀이법과는 궤를 달리하는 경우의 수라고 말할 수 있다..

---

일단 나는 이항 계수의 dp 식 풀이법을 다시 돌아보기로 했다.

 N -->  0   1   2   3   4   5   6
    K
    0   1   1   1   1   1   1   1
    1   0   1   2   3   4   5   6
    2   0   0   1   3   6   10  15
    3   0   0   0   1   4   10  20
    4   0   0   0   0   1   5   15
    5   0   0   0   0   0   1   6
    6   0   0   0   0   0   0   1
---
K -->  0   1   2   3   4   5   6
   N
   0   1   0   0   0   0   0   0
   1   1   1   0   0   0   0   0
   2   1   2   1   0   0   0   0
   3   1   3   3   1   0   0   0
   4   1   4   6   4   1   0   0
   5   1   5   10  10  5   1   0
   6   1   6   15  20  15  6   1
---

정확히 파스칼의 삼각형, 혹은 이항계수의 특성이 나타나는 것을 볼 수 있다.

6 개를 고를 수 있고, 6 개 까지 모두 고르는 형태의 그래프를 나타냈다.

이 중에서, 가장 큰 수를 가지고 있는, N = 6, K = 3 을 알아보자.

---

N = 6, K = 3 은 어떤 수로 형성되었을까?

바로 (N = 5, K = 3) + (N = 5, K = 2) 의 결과물이다.

즉, (N, K) 이항계수는 (N - 1, K) + (N - 1, K - 1) 의 결과물이다.

마지막에 다시 작성한 2 차원 그래프를 살펴본다면,

(N- 1, K) 의 재귀는 결국 지속적인 "위쪽" 참조를 이어가고 있다.

그러나, (N - 1, K - 1) 은 "대각선 참조" 를 수행하므로, 굉장히 길어진다.

---

그런데, 이러한 방식으로 "재귀" 를 만든다고 가정한다면, N = 400만, K = 200 만 의 경우로 입력 최대가 되었을 때,

최종적인 재귀의 개수는 몇백만 개가 아니며, 몇 천만 ~ 몇 억 개로 늘어 날 수 있음을 알게 되었다.

동일한 구간의 계산을, 또 다시 계산하게 되기 때문이다.

---

그렇다면, 어떻게 계산해야 할까? 이항계수의 규칙에 또 다른 것이 있나?

---

방금 (N - 1, K), (N - 1, K - 1) 재귀를 테스트삼아 해 봤는데,

50 25 에서 멈춘듯이 계산을 하고 있는 것을 보았다...

차라리 DP 방식이 훨씬 더 빠르다는 것이며,

위의 계산은 DP 에만 해당한다는 것이다.

---

그리고 또 문제가 있다.

2 차원 배열의 생성은 불가하다.

400 만 * 400 만을 생각 해 보자.

적어도 배열 생성 시에만 시간이 너무 많이 소요된다. (메모리도 미친듯이..)

즉, 정말 재귀를 통해서만 풀어야 한다는 것이다.

---

결국 Gemini 의 도움을 받게 되었는데,

"정수론" 을 알아야 "분할 정복 재귀" 를 실시 할 수 있는 문제였다.

문제는 페르마의 소정리 라는 항목이다.

---

모듈러 세상에서는 나눗셈을 적용할 수 없다.

곱셈만이 적용 될 수 있다. (같은 나머지가 지속적으로 남기 위해서는)

페르마의 소정리에 따르면, A^(P - 1) == 1 (mod P) {P 는 소수이며, A 는 P 의 배수가 아닌 상황.} 항상 성립한다.

그리고, A * (1 / A) == 1 은 성립한다.

이를 이용하여 푸는 문제이다.

N! / K! * (N - K)! 에서, (N!) 은 이미 계산이 되어 있는 상태라고 가정한다. (400 만 개의 배열에 미리 나머지 계산 놓은 상태라고 가정)

문제는 바로 K! 와, (N - K)! 이다.

---

K! 를 A 로 간주한다. (소수인 P 의 배수가 되지 못한다 애초에)

A * A^-1 = A^(P - 2) * A 로 만들 수 있다. (두 항은 1 로 동일하다.)

그렇다면, A^-1 = A^(P - 2) (mod P) 가 된다.

우리가 원하는 것은 A^-1, 즉, (K!)^-1 이다.

그런데, 이 값을 정확히 (K!)^(P - 2) (mod P) 로 구할 수 있다는 것이다.

동일하게, 1 / (N - K)! 또한 (N - K)!^(P - 2) (mod P)로 구하게 된다.

그렇다면, { N! (mod P) } * { (K!)^(P - 2) (mod P) } * { (N - K)!^(P - 2) (mod P) } 가 결과가 된다.

여기서 미리 계산된 400 만 까지의 팩토리얼 계산은 미리 준비되어 있는 상태이기 때문에, N! (mod P) 부분은 그대로 가져온다.

그러나, (K!)^(P - 2) 와, (N - K)^(P - 2) 는 지수를 분할하여 계산해야 한다.

즉, 이 문제는 (K!)^(1000000005) 와, (N - K)!^(1000000005) 를 구하면 되는 문제이다.

두 수를 구한 뒤, N! 에 곱해주고, 다시 나머지 계산하고, 또 곱하고 나머지 계산하면 된다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

long long divAndConquer(long long A, long long B, long long C);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(long target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {
    char** tokens = tokenizer(stdin);

    long N = parseInt(*tokens, NULL);
    long K = parseInt(*(tokens + 1), NULL);

    long long p = 1000000007;

    long long* factorials = (long long*)malloc(sizeof(long long) * (N + 2));
    *(factorials) = 1;
    long long idx = 0;
    long long temp = 1;
    while(idx++ <= N) {
        temp *= idx;
        temp %= p;

        *(factorials + idx) = temp;

    }

    long long nFac = *(factorials + N);
    long long kFac = *(factorials + K);
    long long nkFac = *(factorials + (N - K));

    long long kFacMod = divAndConquer(kFac, p - 2, p);
    long long nkFacMod = divAndConquer(nkFac, p - 2, p);

    long long result = nFac;
    result = (result * kFacMod) % p;
    result = (result * nkFacMod) % p;

    char buf[32];
    char* resultStr = intToStr(result, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    free(factorials);

    return 0;
}

long long divAndConquer(long long A, long long B, long long C) {
    if(B <= 1) {
        return B == 1 ? A : 1;
    }

    // odd
    if(B % 2) {
        long long temp = divAndConquer(A, B / 2, C);
        temp = (temp * temp) % C;
        temp = (temp * A) % C;
        return temp;
    } else { // even
        long long temp = divAndConquer(A, B / 2, C);
        temp = (temp * temp) % C;
        return temp;
    }
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char ch;
    int tknSize = 0;
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

            tknSize = 0;
            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            *(buf + bufSize) = 0;
            bufPtr = buf;

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
    temp = target < 0 ? -temp : temp;

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
    if(ch == 32 || ch == 0)
        return 1;
    else if(ch >= 9 && ch <= 13)
        return 1;
    else
        return 0;
}
