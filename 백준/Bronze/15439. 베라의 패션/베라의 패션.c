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
2 초	256 MB	20569	17661	16735	86.298%

문제
---
베라는 상의 N 벌과 하의 N 벌이 있다.

i 번째 상의와 i 번째 하의는 모두 색상 i를 가진다.

N 개의 색상은 모두 서로 다르다.

상의와 하의가 서로 다른 색상인 조합은 총 몇 가지일까?

입력
---
입력은 아래와 같이 주어진다.

N


출력
---
상의와 하의가 서로 다른 색상인 조합의 가짓수를 출력한다.

제한
---
1 ≤ N ≤ 2017

N은 정수이다.


예제 입력 1
1
예제 출력 1
0
예제 입력 2
2
예제 출력 2
2
예제 입력 3
5
예제 출력 3
20
*/

/**
이 문제는 조합론의 식을 이용하여 풀거나,

제한(2017) 덕분에 루프문으로 돌려도 풀려지는 문제다. (2 초나 주어짐.)

이전에도 수학 문제를 증명하여 풀었었는데, 이번에도 한번 해석해서 수학식을 만들어서 적용해보려고 한다.

---

상의와 하의는 별개의 변수이며,

상의와 하의는 동일한 색상들을 참조한다.

그리고, 상의와 하의는 동일한 색상을 가지지 않아야 한다.

---

다행이라고 생각이 드는 것은, 정말 생각보다 쉽게 나와서 정말로 다행이라는 것이다.

색상의 수는 결국 상의, 하의 의 개수이다.

단순히 상의, 하의만 일치하지 않는 경우를 구하라 했으니,

만약에 색상이 3 개라면, 상 하의는 각각 3 개씩이다.

---

&& 예제 1. 색상 3개 &&

1   1   1   2   2   2   3   3   3 - 상의
1   2   3   1   2   3   1   2   3 - 하의

곧바로 특정할 수 있는 규칙은, 한 번의 루프를 돌 때, "하나만" 색상이 같은 경우가 존재한다는 것이다.

이게 최소, 최대의 개념이 아니라, 무조건 "하나만" 색상이 같다는 것이다.

그렇다면, N 개의 색상이 존재할 때, 상의와 하의는 각각 N 개의 색상을 가지며, 번호가 같다면 같은 색상이다.

즉, N * (N - 1) 의 공통 식이 성립될 것이다.

증명으로, N 이 5 일 때를 가정 해 보자.

&& 예제 2. 색상 5개 &&

1   1   1   1   1   2   2   2   2   2   3   3   3   3   3   4   4   4   4   4   5   5   5   5   5
1   2   3   4   5   1   2   3   4   5   1   2   3   4   5   1   2   3   4   5   1   2   3   4   5

이 경우에도, 하나의 루프 당 무조건 "하나만" 위아래 색상이 동일한 것을 확인 할 수 있다.

따라서, 모든 루프 횟수 : 5 (N) 이며, 하나의 루프 당 상 하의 색상이 다른 것은 : 4 (N - 1) 이다.

따라서, 5 * 4 == (N) * (N - 1) 이 공통 식이라는 것을 확인 할 수 있다.

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

    int result = N * (N - 1);

    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

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
