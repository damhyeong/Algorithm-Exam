
/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초	512 MB	42916	15910	12327	34.930%

문제
---
골드바흐의 추측: 2보다 큰 짝수는 두 소수의 합으로 나타낼 수 있다.

짝수 N을 두 소수의 합으로 나타내는 표현을 골드바흐 파티션이라고 한다.

짝수 N이 주어졌을 때, 골드바흐 파티션의 개수를 구해보자.

두 소수의 순서만 다른 것은 같은 파티션이다.


입력
---
첫째 줄에 테스트 케이스의 개수 T (1 ≤ T ≤ 100)가 주어진다.

각 테스트 케이스는 한 줄로 이루어져 있고, 정수 N은 짝수이고, 2 < N ≤ 1,000,000을 만족한다.


출력
---
각각의 테스트 케이스마다 골드바흐 파티션의 수를 출력한다.

예제 입력 1
5
6
8
10
12
100
예제 출력 1
1
1
2
1
6
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

_Bool isPrime(int target);

int euclidean_algorithm(int n1, int n2);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    const int MAX_SIZE = 1000000;
    _Bool* isPrimeArr = (_Bool*)malloc(sizeof(_Bool) * (MAX_SIZE + 1));

    int idx = 0;
    while(idx <= MAX_SIZE) {
        *(isPrimeArr + idx) = isPrime(idx) == 1 ? 1 : 0;

        idx++;
    }

    char input[255];

    fgets(input, sizeof(input), stdin);

    int T = parseInt(input);

    idx = 0;
    while(idx++ < T) {
        fgets(input, sizeof(input), stdin);

        int N = parseInt(input);

        int tmpTotal = 0;

        int jdx = 2;
        while(jdx <= N / 2) {
            int n1 = jdx;
            int n2 = N - jdx;

            _Bool n1Prime = *(isPrimeArr + n1);
            _Bool n2Prime = *(isPrimeArr + n2);

            if(n1Prime == 1 && n2Prime == 1) {
                tmpTotal++;
            }
            jdx++;
        }

        char* tmpResult = intToStr(tmpTotal);
        fputs(tmpResult, stdout); fputc('\n', stdout);
        free(tmpResult);
    }

    return 0;
}

_Bool isPrime(int target) {
    if(target == 0 || target == 1) {
        return 0;
    } else if(target == 2 || target == 3) {
        return 1;
    }

    _Bool isPrime = 1;

    int idx = 2;
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
