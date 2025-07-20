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
5 초 (하단 참고)	8 MB (하단 참고)	357400	86119	65925	23.990%

N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.

입력
---
첫째 줄에 수의 개수 N(1 ≤ N ≤ 10,000,000)이 주어진다.

둘째 줄부터 N개의 줄에는 수가 주어진다.

이 수는 10,000보다 작거나 같은 자연수이다.

출력
---
첫째 줄부터 N개의 줄에 오름차순으로 정렬한 결과를 한 줄에 하나씩 출력한다.

예제 입력 1
10
5
2
3
1
4
2
3
5
1
7
예제 출력 1
1
1
2
2
3
3
4
5
5
7
*/

/**
이 문제는 Counting Sort 를 이용하여 풀기를 권장하고 있다.

그 이유는, 이 문제에 대한 컴퓨팅 리소스 제한 중, Ram 제한이 8 MB 이기 때문이다.

그리고, 주어지는 수는 최대 천만, (10,000,000) 개가 주어진다.

당연히 선택정렬, 버블정렬, 삽입정렬 은 n^2 의 시간복잡도이기에 불가능하다. (1억 회의 계산은 1 초로 간주한다.)

그리고, "수를 저장하는 행위" 도 불가능하다. 만약 천만의 "수" 를 저장한다고 가정한다면, (int 가정)

40,000,000 바이트를 차지하게 되는데,

이것은 40MB 이기 때문이다. 따라서, 수를 저장하는 행위부터가 최대 램 용량의 5 배이다.

카운팅 정렬로 푸는 방법밖에 없다는 것을 알게 되었다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* storeNum = (int*)calloc(10001, sizeof(int));

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        int num = parseInt(input);

        *(storeNum + num) = *(storeNum + num) + 1;
    }

    idx = 0;
    while(idx++ < 10001) {
        int loop = *(storeNum + idx);

        char* tempStr = intToStr(idx);
        int i = 0;
        while(i++ < loop) {
            fputs(tempStr, stdout); fputc('\n', stdout);
        }
    }

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
