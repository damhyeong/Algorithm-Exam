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
1 초	128 MB	50517	13627	10937	25.458%

문제
---
정수 n(0 ≤ n ≤ 4*10^9)가 주어졌을 때, n보다 크거나 같은 소수 중 가장 작은 소수 찾는 프로그램을 작성하시오.

4 * 1_000_000_000 --> long 으로 풀어야 함.

입력
---
첫째 줄에 테스트 케이스의 개수가 주어진다. 각 테스트 케이스는 한 줄로 이루어져 있고, 정수 n이 주어진다.

출력
---
각각의 테스트 케이스에 대해서 n보다 크거나 같은 소수 중 가장 작은 소수를 한 줄에 하나씩 출력한다.

예제 입력 1
3
6
20
100
예제 출력 1
7
23
101
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

long get_min_prime(long start);

char* longToStr(long target);
long parseLong(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int n = (int)parseLong(input);

    int idx = 0;
    while(idx < n) {
        fgets(input, sizeof(input), stdin);

        long inputNum = parseLong(input);

        long result = get_min_prime(inputNum);

        char* resultStr = longToStr(result);
        fputs(resultStr, stdout); fputc('\n', stdout);
        free(resultStr);

        idx++;
    }


    return 0;
}

long get_min_prime(long start) {

    if(start == 0 || start == 1){
        return 2;
    } else if(start == 2 || start == 3) {
        return start;
    }

    long iterNum = start;

    while(1) {
        long idx = 2;
        _Bool isPrime = 1;

        while(idx * idx <= iterNum) {
            if(iterNum % idx == 0) {
                isPrime = 0;
                break;
            }

            idx++;
        }

        if(isPrime == 1) {
            break;
        }

        iterNum++;
    }

    return iterNum;
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
    int sign = 1;
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
