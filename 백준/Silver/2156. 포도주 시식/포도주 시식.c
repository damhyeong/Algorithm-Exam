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
포도주 시식

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	166253	57614	41882	33.068%

문제
---
효주는 포도주 시식회에 갔다.

그 곳에 갔더니, 테이블 위에 다양한 포도주가 들어있는 포도주 잔이 일렬로 놓여 있었다.

효주는 포도주 시식을 하려고 하는데, 여기에는 다음과 같은 두 가지 규칙이 있다.

1. 포도주 잔을 선택하면 그 잔에 들어있는 포도주는 모두 마셔야 하고, 마신 후에는 원래 위치에 다시 놓아야 한다.
2. 연속으로 놓여 있는 3잔을 모두 마실 수는 없다.

효주는 될 수 있는 대로 많은 양의 포도주를 맛보기 위해서 어떤 포도주 잔을 선택해야 할지 고민하고 있다.

1부터 n까지의 번호가 붙어 있는 n개의 포도주 잔이 순서대로 테이블 위에 놓여 있고,

각 포도주 잔에 들어있는 포도주의 양이 주어졌을 때,

효주를 도와 가장 많은 양의 포도주를 마실 수 있도록 하는 프로그램을 작성하시오.


예를 들어 6개의 포도주 잔이 있고, 각각의 잔에 순서대로 6, 10, 13, 9, 8, 1 만큼의 포도주가 들어 있을 때,

첫 번째, 두 번째, 네 번째, 다섯 번째 포도주 잔을 선택하면 총 포도주 양이 33으로 최대로 마실 수 있다.


입력
---
첫째 줄에 포도주 잔의 개수 n이 주어진다.

(1 ≤ n ≤ 10,000)

둘째 줄부터 n+1번째 줄까지 포도주 잔에 들어있는 포도주의 양이 순서대로 주어진다.

포도주의 양은 1,000 이하의 음이 아닌 정수이다.


출력
---
첫째 줄에 최대로 마실 수 있는 포도주의 양을 출력한다.

예제 입력 1
6
6
10
13
9
8
1
예제 출력 1
33
*/

/**

문제 해석 :

다이나믹 프로그래밍의 단골 문제인가 싶다.

이전 문제 중 1 칸, 2 칸 올라갈 수 있으며,

연속 3 칸을 밣을 수 없다는 문제가 떠오른다.

이번 문제 또한, 동일하다고 생각한다.

이번에는 한칸, 두칸 띄어서 누적할 수 있다고 작성되어 있지 않을 뿐,

본질은 결국 "계단 오르기" 와 동일하다고 생각한다.

---

1. 연속 3 칸을 마실 수 없다.
2. 최대로 마셔야 한다.

결국, 이 문제는 하나의 누적 칸을 채우기 위해,

현재 칸이 연속된 마지막 2 번째 칸을 의미하는지,

혹은 한 칸을 무시하여 건너뛰었는지,

이 2 가지 조건 중 제일 큰 것을 선택하고, 현재 포도주 양을 누적하면 된다.

DP[N] 을 구해야 할 때,

DP[N] = { DP[N - 2] + list[N] } or { DP[N - 3] + list[N - 1] + list[N] }

위의 2 개 중 더 큰 하나를 골라서 채우면 된다.

---

그런데, 로직 실행 후 "32" 가 뜨길래, 뭐지 싶었다.

이번 문제에는, 꼭 "마지막" 을 선택 할 필요가 없다.

따라서, 모든 누적합을 순회하며 최대 값을 구하거나,

누적을 하는 과정에서 나온 산출물의 최대 값을 지속적으로 비교하여 구하거나 하면 된다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int n = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (n + 2));
    int* dp = (int*)malloc(sizeof(int) * (n + 2));
    *list = *dp = 0;

    int idx = 1;
    while(idx <= n) {
        fgets(input, sizeof(input), stdin);

        *(list + idx) = parseInt(input);

        idx++;
    }

    int result = 0;
    if(n <= 2) {
        int i = 0;
        while(i <= n) {
            result += *(list + i++);
        }
    } else {
        int max = -1;

        *(dp + 1) = *(list + 1);
        max = max < *(dp + 1) ? *(dp + 1) : max;
        *(dp + 2) = *(list + 1) + *(list + 2);
        max = max < *(dp + 2) ? *(dp + 2) : max;

        int i = 3;
        while(i <= n) {
            int result1 = *(dp + i - 2) + *(list + i);
            int result2 = *(dp + i - 3) + *(list + i - 1) + *(list + i);
            int result3 = *(dp + i - 1);

            *(dp + i) = result1 > result2 ? result1 : result2;
            *(dp + i) = *(dp + i) > result3 ? *(dp + i) : result3;

            max = max < *(dp + i) ? *(dp + i) : max;

            i++;
        }

        result = max;
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
