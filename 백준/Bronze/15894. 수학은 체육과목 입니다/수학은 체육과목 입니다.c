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
1 초 (추가 시간 없음)	512 MB	55533	30150	28039	54.589%

문제
---
성원이는 수학을 정말 못 하는 고등학생이다.

수학을 못하는 대신 근성과 팔 힘이 뛰어난 성원이는 수학 시험에서 수학 지식을 사용하지 않고 근성과 체력을 사용해 문제를 푼다.

지난 시험에서는 아래 사진에 나와있는 문제를 근성과 체력을 사용해 열심히 풀었지만 사진에서 볼 수 있듯이 틀려버리고 말았다!

결국 이 문제는 틀려버렸지만 성원이는 여전히 자신의 체력에 강한 자신감을 갖고 있다.

어떤 어려운 문제가 나와도 이런 식으로 근성과 체력을 사용하면 다 풀 수 있으니 이 방법은 최고의 방법이라고 생각하고 있다.

성원이의 친구 형석이는 근성과 체력으로 수학 문제를 푸는 것은 굉장히 무식한 방법이라고 생각한다.

형석이는 수학을 공부하면 문제를 훨씬 빨리 풀 수 있다는 것을 알려주기 위해 위 사진에 나와있는 문제를 갖고 성원이와 퀴즈 내기를 하기로 했다.

위 사진의 문제를 다시 정리하면 아래와 같다.

"한 변의 길이가 1인 정사각형을 아래 그림과 같이 겹치지 않게 빈틈없이 계속 붙여 나간다.

가장 아랫부분의 정사각형이 n개가 되었을 때, 실선으로 이루어진 도형의 둘레의 길이를 구하시오."

가장 아랫부분의 정사각형 개수가 주어지면 그에 해당하는 답을 출력하는 프로그램을 만들어 형석이를 도와주자!

입력
---
첫 번째 줄에 가장 아랫부분의 정사각형 개수 n이 주어진다. (1 ≤ n ≤ 10^9) (1_000_000_000)

출력
---
첫 번째 줄에 형석이가 말해야 하는 답을 출력한다.

예제 입력 1
1
예제 출력 1
4
예제 입력 2
3
예제 출력 2
12
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* longToStr(long target);
long parseLong(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    long n = parseLong(input);

    long result = n * 4;

    char* resultStr = longToStr(result);

    fputs(resultStr, stdout);

    free(resultStr);

    return 0;
}


char* longToStr(long target) {
    long sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    long temp = target;
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
long parseLong(const char* str) {
    long sign = 1;
    long result = 0;

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
