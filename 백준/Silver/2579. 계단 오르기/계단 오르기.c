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
계단 오르기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	236355	84037	60631	34.817%

문제
---
계단 오르기 게임은 계단 아래 시작점부터 계단 꼭대기에 위치한 도착점까지 가는 게임이다.

<그림 1>과 같이 각각의 계단에는 일정한 점수가 쓰여 있는데 계단을 밟으면 그 계단에 쓰여 있는 점수를 얻게 된다.

<그림 1>



예를 들어 <그림 2>와 같이 시작점에서부터 첫 번째, 두 번째, 네 번째, 여섯 번째 계단을 밟아 도착점에 도달하면 총 점수는 10 + 20 + 25 + 20 = 75점이 된다.

<그림 2>



계단 오르는 데는 다음과 같은 규칙이 있다.

1. 계단은 한 번에 한 계단씩 또는 두 계단씩 오를 수 있다. 즉, 한 계단을 밟으면서 이어서 다음 계단이나, 다음 다음 계단으로 오를 수 있다.
2. 연속된 세 개의 계단을 모두 밟아서는 안 된다. 단, 시작점은 계단에 포함되지 않는다.
3. 마지막 도착 계단은 반드시 밟아야 한다.


따라서 첫 번째 계단을 밟고 이어 두 번째 계단이나, 세 번째 계단으로 오를 수 있다.

하지만, 첫 번째 계단을 밟고 이어 네 번째 계단으로 올라가거나, 첫 번째, 두 번째, 세 번째 계단을 연속해서 모두 밟을 수는 없다.

각 계단에 쓰여 있는 점수가 주어질 때 이 게임에서 얻을 수 있는 총 점수의 최댓값을 구하는 프로그램을 작성하시오.

입력
---
입력의 첫째 줄에 계단의 개수가 주어진다.

둘째 줄부터 한 줄에 하나씩 제일 아래에 놓인 계단부터 순서대로 각 계단에 쓰여 있는 점수가 주어진다.

계단의 개수는 300이하의 자연수이고, 계단에 쓰여 있는 점수는 10,000이하의 자연수이다.


출력
---
첫째 줄에 계단 오르기 게임에서 얻을 수 있는 총 점수의 최댓값을 출력한다.

예제 입력 1
6
10
20
15
25
10
20
예제 출력 1
75
*/

/**

같은 수가 나오지 않는 환경이기 때문에, 단순히 피보나치 함수처럼 일정하게 정해진 점화식을 가질 수는 없다.

EX - 피보나치 : f(n - 1) + f(n - 2)

그 이유는 주어진 규칙이 까다롭기 때문이다.

1. 계단은 하나만 위로 가거나, 2 칸을 한번에 점프할 수 있다.
2. 연속된 계단 3 개를 밣을 수 없다. 1, 1, 1 불가능.

누적된 값이 필요하므로(최대 값을 구하기 위해) dp 를 사용하겠지만,

결국 이는 위에서 제시한 2 가지 규칙을 통해,

어떤 상황에서든 최대 값을 구해내야 한다는 것을 의미한다.

----

일단, 처음 위치를 제외하고 1 번째, 2 번째, 3 번째 계단까지는 명확하게 바로 풀이 할 수 있다.

그리고, 처음 위치, 즉, 몇 번째가 아닌 계단인 "0 번째" 라는 것도 정의해야 한다고 판단했다.

즉, 0, 1 번째 까지는 그대로 값을 넣는다. (0 은 점수가 없기 때문.)

하지만, 2 번째 부터는 추상적으로 떠오르는 점화식을 넣을 수 있다고 판단했다.

당연히 직관적으로 보았을 때, 1, 2 번째를 연속적으로 밣을 수 있으므로,

계단 2 번째는 1 번째를 더한 값으로 dp 배열을 누적하면 된다.

---

그렇다면, 점화식을 어떻게 나누어야 할까?

가장 중요한 것은, 연속으로 계단을 3 번 밣을 수 없다는 것이다.

그 다음 조건에 대한 힌트를 주는 것은, 계단을 이어서 밣거나(1칸), 건너뛰어(2칸) 밣을 수 있다는 것이다.

그렇다면, 현재 dp[N] 은,

* dp[N - 1]
* dp[N - 2]

이 두 값 중에서 선택할 수 있다는 것일까?

만약에 이러한 조건이 성립된다면, 당연히 dp[N] 은 dp[N - 1] + list[N] 으로,

모든 계단을 한 칸씩 밣았을 때의 결과와 다르지 않다.

심지어 이런 계산은 딱히 dp 누적 배열이 필요하지도 않다.

여기서 가장 중요한 조건, 연속으로 계단을 3 번 밣을 수 없다는 것을 적용해야 한다.

즉, 계단을 연속으로 밣았지만, 마지막 2 번째 연속 계단이거나,

계단을 연속으로 밣지 않고, N - 2 계단을 밣고 곧바로 N 계단을 밣은 경우로 나눌 수 있다.

---

그렇다는 것은, dp[N] = dp[N - 2] + list[N]; 이라는 점화식 하나는 정확하게 나온다.

그리고 마지막으로, 계단을 연속으로 밣았지만, 마지막 2 번째 연속 계단일 때의 점화식을 구해야 한다.

dp[N] = dp[N - 2] + dp[N - 1] + list[N] 이라는 것은 성립하지 않는다. 연속으로 3 번 밣을 수 없기 때문이다.

마지막 N 번째 계단을 연속으로 밣아, 최댓값을 만들 수 있는 형태를 생각해야 한다.

dp[N] = dp[N - 3] + list[N - 1] + list[N]

위의 점화식은, N 번째 계단에 도달하기 직전, 마지막 계단을 밣고 연속으로 올라갔을 때의 점수(max) 를 보여주는 점화식이다.

계단은 3 번 연속으로 밣을 수 없다.

따라서, N 번째는 연속으로 밣았을 때를 상정하기 위해, N - 1 번째를 밣는다고 가정한다면, N - 2 번째는 밣지 못한다.

따라서, 2 칸 떨어져 있는 N - 3 을 밣아야 한다는 결론에 도달하게 되었다.

---

결국, dp[N] = MAX{ "(dp[N - 2] + list[N])" or "(dp[N - 3] + list[N - 1] + list[N])" }

이러한 점화식이 나오게 된다.

즉, "연속으로 밣기" 혹은 "연속으로 밣지 않기" 라는 항목이 이 2 가지 점화식 중 하나를 고르게 되는 선택지를 만들어 낸 것이다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 2));
    *(list) = 0;
    int* dp = (int*)malloc(sizeof(int) * (N + 2));
    *(dp) = 0;

    int idx = 1;
    while(idx <= N) {
        fgets(input, sizeof(input), stdin);

        int temp = parseInt(input);

        *(list + idx++) = temp;
    }

    int result = 0;

    if(N == 1 || N == 2) {
        int idx = 1;
        while(idx <= N) {
            result += *(list + idx++);
        }
    } else {
        *(dp + 1) = *(list + 1);
        *(dp + 2) = *(list + 1) + *(list + 2);

        int idx = 3;
        while(idx <= N) {
            int result1 = *(dp + idx - 3) + *(list + idx - 1) + *(list + idx);
            int result2 = *(dp + idx - 2) + *(list + idx);

            *(dp + idx++) = result1 > result2 ? result1 : result2;
        }

        result = *(dp + N);
    }

    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);
    free(list); free(dp);

    return 0;
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
