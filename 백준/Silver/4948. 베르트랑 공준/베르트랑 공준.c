
/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	118561	47721	38050	39.569%

문제
---
베르트랑 공준은 임의의 자연수 n에 대하여, n보다 크고, 2n보다 작거나 같은 소수는 적어도 하나 존재한다는 내용을 담고 있다.

이 명제는 조제프 베르트랑이 1845년에 추측했고, 파프누티 체비쇼프가 1850년에 증명했다.

예를 들어, 10보다 크고, 20보다 작거나 같은 소수는 4개가 있다.
(11, 13, 17, 19)

또, 14보다 크고, 28보다 작거나 같은 소수는 3개가 있다.
(17,19, 23)

자연수 n이 주어졌을 때, n보다 크고, 2n보다 작거나 같은 소수의 개수를 구하는 프로그램을 작성하시오.

입력
---
입력은 여러 개의 테스트 케이스로 이루어져 있다.

각 케이스는 n을 포함하는 한 줄로 이루어져 있다.

입력의 마지막에는 0이 주어진다.

출력
---
각 테스트 케이스에 대해서, n보다 크고, 2n보다 작거나 같은 소수의 개수를 출력한다.

제한
---
1 ≤ n ≤ 123,456


예제 입력 1
1
10
13
100
1000
10000
100000
0
예제 출력 1
1
4
3
21
135
1033
8392
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

_Bool isPrimeNum(int target);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    int currNum;
    while((currNum = parseInt(fgets(input, sizeof(input), stdin))) != 0) {
        int idx = currNum + 1;
        int endIdx = currNum * 2;

        int tmpTotal = 0;
        while(idx <= endIdx) {
            tmpTotal = isPrimeNum(idx) == 1 ? tmpTotal + 1 : tmpTotal;
            idx++;
        }

        char* tmpResult = intToStr(tmpTotal);
        fputs(tmpResult, stdout); fputc('\n', stdout);
        free(tmpResult);
    }

    return 0;
}

_Bool isPrimeNum(int target) {
    if(target == 1) {
        return 0;
    } else if(target == 2 || target == 3) {
        return 1;
    }

    int idx = 2;
    _Bool isPrime = 1;
    while(idx * idx <= target) {
        if(target % idx == 0) {
            isPrime = 0;
            break;
        }
        idx++;
    }

    return isPrime;
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
