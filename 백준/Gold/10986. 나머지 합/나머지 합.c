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
나머지 합

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	71156	20102	14345	26.691%

문제
---
수 N개 A_1, A_2, ..., A_N이 주어진다.

이때, 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수를 구하는 프로그램을 작성하시오.

즉, A_i + ... + A_j (i ≤ j) 의 합이 M으로 나누어 떨어지는 (i, j) 쌍의 개수를 구해야 한다.

입력
---
첫째 줄에 N과 M이 주어진다.

(1 ≤ N ≤ 10^6, 2 ≤ M ≤ 10^3)

둘째 줄에 N개의 수 A_1, A_2, ..., A_N이 주어진다.

(0 ≤ A_i ≤ 10^9)


출력
---
첫째 줄에 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수를 출력한다.

예제 입력 1
5 3
1 2 3 1 2
예제 출력 1
7
*/

/**
처음에는 DP 방법론 중 하나인, 최대값, 최소값 구하기 같은 최대, 최소 조건 방식을 적용해야 하는 줄 알았는데,

최대 입력 횟수를 계산해 보니 나의 방식으로는 DP 테이블을 펼치기 위해 10억 개의 int 자리가 필요하단 것을 알게 되었다.

즉, 테이블 생성만으로도 시간 초과가 난다.

---

바로 생각을 고쳐먹고, 문제의 제약에 집중했다.

1. 연속적이어야 한다.
2. 주어진 수에 정확히 나누어 떨어져야 한다.
3. 나누어질 수 있는 모든 구간의 쌍을 구해야 한다. --> 이걸 "최대값" 이라고 해석할 수가 있을까?

---

여기서 "연속적" 이라는 키워드로 인해 정답에 가까운 생각이 들게 되었는데,

만약에 "연속적" 이어야 한다면, 굳이 나올 수 있는 모든 수의 조합을 생각할 필요가 없다는 것이다.

위의 입력, (1, 2, 3, 1, 2) 를 통해 원리를 보자 :

여기서 DP 1차원 배열(누적) 을 생성해 놓고,

각 값을 더하며 주어진 M(3) 으로 나눈 값을 저장한다.

| 1 | 2 | 3 | 4 | 5 |
---------------------
| 1 | 2 | 3 | 1 | 2 |

누적 and 나머지 연산 :

| 1 | 0 | 0 | 1 | 0 |

여기서 "연속적" 이면서, 이루어질 수 있는 "최소 길이로 나누어지는" 부분 구간이 총 3 개이다.

이걸 한번 집합으로 생각 해 보자.

집합 1 : (1 ~ 2)
집합 2 : (3)
집합 3 : (4 ~ 5)

---

위의 집합들은,

개별 집합으로 충족될 수도 있지만,

1, 2 집합, 2, 3 집합, 이렇게 연속적인 집합도 정확히 M 으로 나누어 떨어진다.

그렇다면, 나올 수 있는 모든 집합의 경우를 구해보자 :

(길이 1의 경우) : 1, 2, 3

(길이 2의 경우) : (1, 2), (2, 3)

(길이 3의 경우) : (1, 2, 3)

---

그런데, 정답이 "6" 이 아니다. "7" 이다.

다시 보니, (2 ~ 4) 까지의 집합도 나머지 0 을 충족한다.

그렇다면,

| 1 | 2 | 3 | 4 | 5 | --> Index
---------------------
| 1 | 2 | 3 | 1 | 2 | --> A_i

누적 and 나머지 연산 :

| 1 | 0 | 0 | 1 | 0 |

위의 상황에서 정확히 나올 수 있는 "모든" 구간 의 경우는

길이 1 : (3)

길이 2 : (1 ~ 2), (4 ~ 5)

길이 3 : (1 ~ 3), (2 ~ 4), (3 ~ 5)

길이 4 : X

길이 5 : (1 ~ 5)

이며,

| 1 | 2 | 3 | 4 | 5 | --> Index
---------------------
| 1 | 2 | 3 | 1 | 2 | --> A_i

누적 and 나머지 연산 :

| 1 | 0 | 0 | 1 | 0 |

마지막 구간을 인덱스로 나누어서 본다면,

IDX 1 : X

IDX 2 : (1 ~ 2)

IDX 3 : (3), (1 ~ 3)

IDX 4 : (2 ~ 4)

IDX 5 : (4 ~ 5), (3 ~ 5), (1 ~ 5)

---

인덱스 기반의 조합에 중점을 더 놓고 보니, 더 깊은 이해가 가능했다.

여기서 이해가 된 것은, 0 을 발견했을 때의 조합들과,

(2 ~ 4) 가 어떻게 규칙적으로 조건에 들어맞을 수 있는지에 대한 것이었다.

그러나, 0 이 아닌 상황에서 집합을 형성하는 조건을 더 명확히 이해하기 위해서

직접 예제를 만들어서 위의 IDX 기준 집합을 만들어 보기로 했다 :

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | --> Index
-----------------------------
| 1 | 2 | 3 | 1 | 2 | 1 | 0 | --> A_i

누적 and 나머지 연산 :

| 1 | 0 | 0 | 1 | 0 | 1 | 1 |

IDX 1 : X

IDX 2 : (1 ~ 2)

IDX 3 : (3), (1 ~ 3)

IDX 4 : (2 ~ 4)

IDX 5 : (4 ~ 5), (3 ~ 5), (1 ~ 5)

IDX 6 : (5 ~ 6), (2 ~ 6)

IDX 7 : (7), (5 ~ 7), (2 ~ 7)

---

위의 예제에서 확신하게 되는 것이 있었다.

"정확하게 나누어지는" 0 에 집중하는 것이 아니라,

될 수 있는 "모든 나머지 수" 에 집중해야 하는 것이다.

---

0 ~ M - 1(나누는 수) 길이만큼의 정수 배열을 생성하고,

각 나머지가 나올 때 마다, 해당 배열 주소의 정수를 + 1 한다.

모든 구간을 순회하며 위의 동작을 실행한다.

여기서 0 은 그 자체로 완성된 구간이기 때문에,

만약 0 이 3 번 나타났다면, 3 + 2 + 1 개의 구간이 존재한다. --> { N = 3 이며, N > 0 까지 곱한다. }

그러나, 0 을 제외한 모든 나머지 수들은, 이전에 나타났던 동일한 나머지 수를 필요로 한다.

나머지 1 이 5 번 나타났다면, 4 + 3 + 2 + 1 개의 구간이 존재한다. --> { N - 1 부터 시작하여 마이너스 순회, && N > 0 }

나머지 2 가 1 번 나타났다면, 그대로 0 개 이다. --> 나머지 2 는 홀로 0 이 될 수 없기 때문이다.

---

그렇다면, 이제 N + (N - 1) + (N - 2) + ... + 2 + 1 형태의 수학식을 알아내야 할 차례다.

N = 4 일 경우를 상정 해 보자.

O   O   O   O --> 4
O   O   O --> 3
O   O --> 2
O --> 1

4 + 3 + 2 + 1 은, 위의 'O' 개수와 동일하다.

하지만, 위의 형식은 정확히 내부의 엘리먼트 개수의 수학식을 알아낼 수는 없다.

이유는, 그 모양이 "삼각형" 이기 때문이다.

"사각형" 일 경우, 엘리먼트 개수는 정확히 풀이된다. x * y 이기 때문이다.

하지만, 위의 경우, 결과적으로 엘리먼트는 "10" 개 이지만, 삼각형 내부 영역 풀이식 (x * y) / 2 로는 정확히 구할 수 없다.

직사각형의 x, y 를 덧입혀 (4 * 4) / 2 를 해본다면, 이는 "8" 을 도출한다. 즉, 이는 정확한 풀이법이 아니다.

---

N = 5 일 때를 가정 해 보자.

O   O   O   O   O --> 5
O   O   O   O --> 4
O   O   O --> 3
O   O --> 2
O --> 1

5 + 4 + 3 + 2 + 1 은 15 이다. 그러나, 일반적인 "삼각형 공식" (5 * 5) / 2 = 12.5 로,

이는 정수배로서 나타낼 수도 없다.

그렇다면, 어떻게 해석해야 하는가?

---

물론, 우리는 N = 5 일 때, (5 * 4) / 2 라는 공식을 알고 있다.

N * (N - 1) / 2 * 1 이라는 공식 말이다.

그러나, 이는 다른 공식으로도 도출이 가능하다.

---

N = 4 일 때, --> 짝수

O   O   O   O
O   O   O
O   O
O

이다.

내부 엘리먼트의 개수를 올바로 세기 위해서, 이 모양을 직사각형 형태로 변형할 수 있다.

맨 위부터 1 번째라고 가정할 때,

3, 4 번째 삼각형을 정확히 180 도 돌려서, 오른쪽에 붙인다고 생각 해 보자.

그렇다면,

O   O   O   O   O
O   O   O   O   O

이 된다. --> {짝수 일 때, (N / 2) * (N + 1) 이 결과가 된다. || (N / 2) 는 나머지 부분을 버리는 컴퓨터의 형식을 따른다.}

N = 5 일 때, --> 홀수

O   O   O   O   O
O   O   O   O
O   O   O
O   O
O

위의 모양을 정확히 직사각형으로 만들기 위해서,

4, 5 번째 를 똑 떼서 180도 돌리고, 오른쪽에 붙인다면,

O   O   O   O   O
O   O   O   O   O
O   O   O   O   O

가 되므로, --> {홀수 일 때, (N / 2 + 1) * (N) 이 결과가 된다. || (N / 2) 는 나머지 부분을 버리는 컴퓨터의 형식을 따른다.}

이러한 풀이식은 단순한 ( ∑(N) && N > 0 까지 N-- ) 에 적용할 수 있으며,

차원이 더해진다면, 풀이식은 완벽히 달라진다.

3차원으로 풀이 될 시, 이는 큐브처럼 해석해야 하지 않을까?

---

이제 모든 로직을 완성했으므로, 문제에 적용할 시간이다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

char** tokenzier(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(long target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {

    char** tokens = tokenzier(stdin);

    int N = parseInt(*tokens, NULL);
    int M = parseInt(*(tokens + 1), NULL);

    int* accumulate = (int*)calloc(M + 1, sizeof(int));

    freeArrs((void**)tokens);

    tokens = tokenzier(stdin);

    int idx = 0;
    int temp = 0; // 누적
    while(idx < N) {
        temp = (temp + parseInt(*(tokens + idx), NULL)) % M;

        *(accumulate + temp) = *(accumulate + temp) + 1;

        idx++;
    }

    long total = 0;
    idx = 0;
    while(idx < M) {
        int n = *(accumulate + idx);

        if(idx != 0) {
            --n;
        }

        if(n <= 0) {
            idx++;
            continue;
        }
        if(n == 1) {
            total++;
        } else {
            int y = (n % 2 == 0) ? n / 2 : (n / 2) + 1;
            int x = (n % 2 == 0) ? n + 1 : n;

            total += (long)y * (long)x;
        }

        idx++;
    }

    char buf[32];
    char* resultStr = intToStr(total, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

char** tokenzier(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    char ch;

    char* buf = (char*)malloc(sizeof(char) * (100 + 1));
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0) {
                continue;
            }

            buf = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            *(buf + tknSize) = 0;
            *tokensPtr++ = buf; curr++;

            buf = (char*)malloc(sizeof(char) * (100 + 1));
            bufPtr = buf;
            tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch;
            tknSize++;
        }


        if(ch == '\n') {
            break;
        }
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
