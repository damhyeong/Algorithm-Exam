
/**
쉬운 계단 수

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	171011	56297	41282	31.388%

문제
---
45656이란 수를 보자.

이 수는 인접한 모든 자리의 차이가 1이다.

이런 수를 계단 수라고 한다.

N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는지 구해보자.

0으로 시작하는 수는 계단수가 아니다.


입력
---
첫째 줄에 N이 주어진다.

N은 1보다 크거나 같고, 100보다 작거나 같은 자연수이다.

출력
---
첫째 줄에 정답을 1,000,000,000으로 나눈 나머지를 출력한다.

예제 입력 1
1
예제 출력 1
9
예제 입력 2
2
예제 출력 2
17
*/

/**

특정 문자열을 주고, N 만큼의 계단수를 구하라는 건줄 알았는데,

그냥 0 ~ 9 까지의 일 자리수가 "모두" 주어졌을 때, 나타날 수 있는 모든 계단수를 구하는 것이다.

참 신기한 아이디어 문제가 많다고 생각한다.

---

여기에는 신기한 조건이 존재하는데, "0" 으로 시작하는 계단수는 없다는 것이다. 다만, 0 으로 끝나는 것은 가능하다.

그리고, 10 진수를 사용하기 때문에, 0 ~ 9 까지의 수를 사용할 수 있다. (만약 16 진수라면, a -> b 이런 현상이 생겼을 것이다.)

그 다음 수는 + 그리고 - 1 으로 만들어질 수 있다. 그 외는 불가능

---

그렇다면, 먼저 예제로 만들어서 규칙을 보자.

--> 길이 : 1

1, 2, 3, 4, 5, 6, 7, 8, 9

결과 : 9

--> 길이 : 2

10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98

결과 : 17

---

위의 결과 중 "길이 2" 를 펼쳐놓고 보니, "길이 3" 은 너무나도 많이 작성할 것 같아, 여기서 규칙을 명시하려고 한다.

길이 N 을 충족하는 "계단수" 가 존재 할 때,

이 모든 계단수는 결과적으로 길이 N - 1 의 모든 계단수에서 종료된 "마지막 수" 인 0 ~ 9 까지의 모든 연속 계단을 충족시켜주는 수를 가지고 있다는 것이다.

마지막으로 끝난 수는 어떤 수를 다시 가질 수 있을까?

N - 1 이 특정 수로 끝났을 때, 나올 수 있는 수를 펼쳐보자.

| 0 | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9 |
| 1 | 0, 2  | 1, 3  | 2, 4  | 3, 5  | 4, 6  | 5, 7  | 6, 8  | 7, 9  | 8 |


위의 예시는 맨 윗줄이 "맨 처음이 아니다" 라는 가정 하에 "0" 을 포함시켰다.

"0" 을 제외하고 모든 조합을 완성시켜 보면, "길이 2" 에서 나올 수 있는 모든 경우의 수가 나온다는 것을 알 수 있다.

위에서 내가 작성해 본 예시는, 다시 정렬되어 사용할 수 있다.

| 0 | 1 x 2 | 2 x 2 | 3 x 2 | 4 x 2 | 5 x 2 | 6 x 2 | 7 x 2 | 8 x 2 | 9 |
| 1 | 0, 2  | 1, 3  | 2, 4  | 3, 5  | 4, 6  | 5, 7  | 6, 8  | 7, 9  | 8 |

윗줄은 N - 1 번째에서 마무리 된 수를 정리 해 놓은 것이고,

N 번째는 나올 수 있는 모든 종류의 수를 다시 나열했다.

여기서 "1 x 2" 와 같은 표시를 한 것은,

| 1     | 1     |
| 0, 2  | 0, 2  |

이 표식과 동일하다.

xxxx0 이라는 계단수가 존재할 때, 이 수가 그 다음 길이로도 계단수가 되기 위해서는

1 이 될 수 밖에 없다. --> xxxx01

그리고, 만약 이것이 1 이라면,

xxxx1 이라는 계단수가 존재 할 때, 이 수 또한 동일한 규칙을 적용한다면

0, 2 이 될 수 있다. --> xxxx10, xxxx12

0 과 마찬가지로, 9 또한 동일한 행동을 보인다.

xxxx9 라는 계단수가 존재 할 때, 이 수는 그 다음 --> xxxx98 이는 계단수로 진행된다.

---

그렇다면, "0" 은 시작할 수 없는 계단수라는 점을 적용하여 이러한 배열을 만든다.

길이 : 1

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | --> 배열 공간
| 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |


길이 : 2

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | --> 배열 공간
| 1 | 1 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 1 |


길이 : 3
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | --> 배열 공간
| 1 | 3 | 3 | 4 | 4 | 4 | 4 | 4 | 3 | 2 |

---

조금 헷갈린 면이 있었는데, 작성해 보니 규칙은 명확해 졌다.

N 길이의 계단수가 존재할 때, 0 ~ 9 로 끝난다.

각 수로 끝날 때, 만약 N 길이에서 3 으로 끝나는 모든 계단수를 구하기 위해서는,

N - 1 길이에서 2, 4 에서 끝난 모든 계단수를 합하면 된다.

즉, 2 차원 배열로 상정한다면,

dp[N][3] = dp[N - 1][2] + dp[N - 1][4] 이 된다.

그러나, 0 이나 9 의 경우 인덱스를 벗어나는데, 이 때는 해당 방향을 0 개 라고 상정한다.


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

    int N = parseInt(input);

    int* tempArr = (int*)malloc(sizeof(int) * (10 + 1));
    int* dp = (int*)malloc(sizeof(int) * (10 + 1));

    *tempArr = *dp = 0;

    int iter = 1;
    while(iter < 10) {
        *(tempArr + iter) = *(dp + iter) = 1;
        iter++;
    }

    int idx = 2;
    while(idx <= N) {

        int i = 0;
        while(i < 10) {
            int left = (i - 1) < 0 ? 0 : *(tempArr + i - 1);
            int right = (i + 1) >= 10 ? 0 : *(tempArr + i + 1);

            *(dp + i) = (left + right) % 1000000000;
            i++;
        }

        i = 0;
        while(i < 10) {
            *(tempArr + i) = *(dp + i);
            i++;
        }

        idx++;
    }

    int result = 0;
    idx = 0;
    while(idx < 10) {
        result = (result + (*(dp + idx++))) % 1000000000;
    }


    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    return 0;
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
