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
1 초	128 MB	175874	70743	59468	39.916%

문제
---
자연수 M과 N이 주어질 때 M이상 N이하의 자연수 중

소수인 것을 모두 골라 이들 소수의 합과 최솟값을 찾는 프로그램을 작성하시오.

예를 들어 M=60, N=100인 경우 60이상 100이하의 자연수 중

소수는 61, 67, 71, 73, 79, 83, 89, 97 총 8개가 있으므로,

이들 소수의 합은 620이고, 최솟값은 61이 된다.


입력
---
입력의 첫째 줄에 M이, 둘째 줄에 N이 주어진다.

M과 N은 10,000이하의 자연수이며, M은 N보다 작거나 같다.


출력
---
M이상 N이하의 자연수 중 소수인 것을 모두 찾아

첫째 줄에 그 합을,

둘째 줄에 그 중 최솟값을 출력한다.

단, M이상 N이하의 자연수 중 소수가 없을 경우는 첫째 줄에 -1을 출력한다.


예제 입력 1
60
100
예제 출력 1
620
61
예제 입력 2
64
65
예제 출력 2
-1
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

_Bool isPrime(int target);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int M = parseInt(input);

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int minPrime = -1;
    int total = 0;

    int idx = M;
    while(idx <= N) {
        _Bool isPrimeNum = isPrime(idx);

        if(isPrimeNum == 1) {
            total += idx;

            minPrime = (minPrime == -1) ? idx : minPrime;
        }

        idx++;
    }

    char* result1 = intToStr(total);
    char* result2 = intToStr(minPrime);

    if(minPrime == -1) {
        fputs(result2, stdout); fputc('\n', stdout);
    } else {
        fputs(result1, stdout); fputc('\n', stdout); fputs(result2, stdout); fputc('\n' ,stdout);
    }

    free(result1); free(result2);

    return 0;
}


_Bool isPrime(int target) {
    if(target == 1) {
        return 0;
    }

    int idx = 2;

    _Bool isPrimeNum = 1;

    while((idx * idx) <= target) {
        if(target % idx == 0) {
            isPrimeNum = 0;
            break;
        }
        idx++;
    }

    return isPrimeNum;
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
