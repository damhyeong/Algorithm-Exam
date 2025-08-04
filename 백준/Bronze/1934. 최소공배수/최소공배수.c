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
1 초	128 MB	96770	52491	44537	55.028%
---
문제
---
두 자연수 A와 B에 대해서, A의 배수이면서 B의 배수인 자연수를 A와 B의 공배수라고 한다.

이런 공배수 중에서 가장 작은 수를 최소공배수라고 한다.

예를 들어,

6과 15의 공배수는 30, 60, 90등이 있으며, 최소 공배수는 30이다.


두 자연수 A와 B가 주어졌을 때, A와 B의 최소공배수를 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 테스트 케이스의 개수 T(1 ≤ T ≤ 1,000)가 주어진다.

둘째 줄부터 T개의 줄에 걸쳐서 A와 B가 주어진다.
(1 ≤ A, B ≤ 45,000)

출력
---
첫째 줄부터 T개의 줄에 A와 B의 최소공배수를 입력받은 순서대로 한 줄에 하나씩 출력한다.

예제 입력 1
3
1 45000
6 10
13 17
예제 출력 1
45000
30
221
*/

/**
오랜만에 순수 수학 문제로서 만나게 된 백준 문제이다.

최대공약수는 개념이 쉽지만 (두 수 를 정확히 나눌 수 있는 최대 수)

최소공배수는 약간의 개념이 추가될 것이다.

최소공배수란, 두 수가 정수배로 곱해졌을 때 교차되는 최소 값을 의미한다.

만약에, 소수이거나, 아주아주 큰 수일 경우, 단순 숫자 루프로는 시간이 걸릴 것이다.

그렇다면 우리는 이 문제를 수학적으로 접근해야 한다.

A 와 B 라는 수가 있다고 가정한다.

1. A, B 는 누가 더 큰지 모른다.
2. A, B 는 서로의 약수가 될 수 있다.
3. 혹은, 서로소가 될 수 있다. --> 1 을 제외하고 공유되는 약수가 없다.

그렇다면, 최소공배수는 어떻게 구해야 할까?

만약에 컴퓨팅 파워를 믿는다면, 이러한 접근도 가능하다.

변수 A, B 를 만들고, 이들의 최소공배수가 나타 날 때 까지 각각의 수를 상황에 맞게 곱하는 것이다.

예를 들면, A : 10, B : 15 라는 수가 주어졌을 때, A 와 B 를 곱하는 정수 변수를 1 로 각각 초기화한다. (EX aMul, bMul)

A 는 B 보다 작다. 따라서, aMul == 1 에서 aMul++ 한다.

그렇다면, A : 20, b : 15 일 것이다.

그렇다면, 이전 상황은 A < B 였지만, 지금은 A > B 가 되었다.

따라서, 이번에는 bMul 을 하나 올린다.

그렇다면, A : 20, B : 30 이 될 것이다.

이번에도 상황이 역전되었다. A < B, A > B, 그리고 현재는 A < B 로 돌아왔다.

A 가 작으므로, aMul++ 한다.

그렇다면, A : 30, B : 30 으로, A == B 인 상황에 도달했다.

이 결과로 인해, 우리는 A, B 서로의 최소공배수가 "30" 이라는 것을 알 수 있을 것이다.

그러나, 이 방식은 A : 1, B : 10_000_000 이러한 입력이 주어질 때, 굉장히 비효율적이라는 것을 알 수 있다.

단순한 최소 공배수를 구하는 문제에서 시간 초과가 날 수도 있다는 것이다.

그렇다면, 어떻게 수학적으로 접근할까?

&& 수학적 접근 &&

"최소"공배수 라는 것은, A 와 B 가 이 "최소공배수" 를 나눴을 때, 나머지가 없다는 것을 의미한다.

그리고, "가장 작은" 공배수를 구하는 작업이라는 것이다. 그리고 "최소공배수" 는, "최대공약수" 와 연관이 깊다.

우리가 A : 10, B : 15 라는 가정을 도입했을 때, 최소공배수는 "30" 이 나왔다.

이를 각각 A 와 B 로 나눠보자. (30 / A == 3) 이며, (30 / B == 2) 이다.

A 와 B 각각 몫이 다르다는 것을 알 수 있다.

여기서 수가 작은 A 는 3 이며, B 는 2 라는 것을 기억해 두자.

---

10 과 15 의 최대공약수는 얼마일까?

직관적으로 알겠지만, 바로 "5" 이다.

그렇다면, 이 5 를 A : 10, B : 15 를 각각 나눌 수 있다는 얘기가 되는데,

만약 각각의 수를 최대공약수인 "5" 로 나눈다면, (A / 5 == 2) , (B / 5 == 3) 이 된다.

어? 그렇다면, 우리는 위에서 최소공배수 / A or B 했었던 수와 동일하게 결과가 나온다는 것을 알 수 있다.

즉, 최대공약수로 A 를 나눴다면, 그 몫을 연결된 수인 B 에 곱한다면, 이는 최소공배수의 값이 나온다.

그리고, 반대의 상황도 동일하다.

이렇기 때문에, 최대공약수와 최소공배수의 연관관계는 깊다. 그리고, 계산적으로도 편리하다.

따라서,

1. A, B 중 작은 수를 선택한다. 또한, 큰 수 또한 미리 저장 해 놓는다.
2. 작은 수까지만 나눠 최대공약수를 구한다.
3. 작은 수 / 최대공약수 몫을 저장한다.
4. 이 몫을 큰 수에 곱해버리면, 최소공배수가 나온다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

int getMinDivisor(int n1, int n2);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int T = parseInt(input);

    int idx = 0;
    while(idx++ < T) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = tokens;

        int A = parseInt(*tokensPtr++);
        int B = parseInt(*tokensPtr++);

        freeTokens(tokens);

        int small = A > B ? B : A;
        int big = A > B ? A : B;

        int maxDiv = getMinDivisor(small, big);

        int tempMul = small / maxDiv;

        int result = big * tempMul;

        char* tempResult = (char*)intToStr(result);
        fputs(tempResult, stdout); fputc('\n', stdout);
        free(tempResult);
    }


    return 0;
}

int getMinDivisor(int n1, int n2) {
    int tempDivisor = 1;

    int maxDivisor = -1;

    while(tempDivisor <= n1 && tempDivisor <= n2) {
        maxDivisor = n1 % tempDivisor == 0 && n2 % tempDivisor == 0 ? tempDivisor : maxDivisor;
        tempDivisor++;
    }

    return maxDivisor;
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
