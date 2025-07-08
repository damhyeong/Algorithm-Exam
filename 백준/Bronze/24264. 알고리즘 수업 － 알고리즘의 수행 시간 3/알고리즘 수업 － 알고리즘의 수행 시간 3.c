
/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	35940	18381	17574	51.227%

문제
---
오늘도 서준이는 알고리즘의 수행시간 수업 조교를 하고 있다.

아빠가 수업한 내용을 학생들이 잘 이해했는지 문제를 통해서 확인해보자.

입력의 크기 n이 주어지면 MenOfPassion 알고리즘 수행 시간을 예제 출력과 같은 방식으로 출력해보자.

MenOfPassion 알고리즘은 다음과 같다.
------------------------------------------------------------
MenOfPassion(A[], n) {
    sum <- 0;
    for i <- 1 to n
        for j <- 1 to n
            sum <- sum + A[i] × A[j]; # 코드1
    return sum;
}
------------------------------------------------------------

입력
---
첫째 줄에 입력의 크기 n(1 ≤ n ≤ 500,000)이 주어진다.

출력
---
첫째 줄에 코드1 의 수행 횟수를 출력한다.

둘째 줄에 코드1의 수행 횟수를 다항식으로 나타내었을 때, 최고차항의 차수를 출력한다.

단, 다항식으로 나타낼 수 없거나 최고차항의 차수가 3보다 크면 4를 출력한다.

예제 입력 1
7
예제 출력 1
49
2
코드1 이 49회 수행되고 알고리즘의 수행 시간이 n2에 비례한다.
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

    char* resultStr = longToStr(n * n);

    fputs(resultStr, stdout); fputc('\n', stdout);

    fputs("2\n", stdout);

    free(resultStr);

    return 0;
}

char* longToStr(long target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        target *= -1;
        sign = -1;
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
