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
통계학

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	193901	50952	40761	27.822%

문제
---
수를 처리하는 것은 통계학에서 상당히 중요한 일이다.

통계학에서 N개의 수를 대표하는 기본 통계값에는 다음과 같은 것들이 있다. 단, N은 홀수라고 가정하자.

산술평균 : N개의 수들의 합을 N으로 나눈 값
중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
최빈값 : N개의 수들 중 가장 많이 나타나는 값
범위 : N개의 수들 중 최댓값과 최솟값의 차이

N개의 수가 주어졌을 때, 네 가지 기본 통계값을 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에 수의 개수 N(1 ≤ N ≤ 500,000)이 주어진다.

단, N은 홀수이다.

그 다음 N개의 줄에는 정수들이 주어진다.

입력되는 정수의 절댓값은 4,000을 넘지 않는다.


출력
---
첫째 줄에는 산술평균을 출력한다.

소수점 이하 첫째 자리에서 반올림한 값을 출력한다.

둘째 줄에는 중앙값을 출력한다.

셋째 줄에는 최빈값을 출력한다. 여러 개 있을 때에는 최빈값 중 두 번째로 작은 값을 출력한다.

넷째 줄에는 범위를 출력한다.

예제 입력 1
5
1
3
8
-2
2
예제 출력 1
2
2
1
10
예제 입력 2
1
4000
예제 출력 2
4000
4000
4000
0
예제 입력 3
5
-1
-2
-3
-1
-2
예제 출력 3
-2
-2
-1
2
예제 입력 4
3
0
0
-1
예제 출력 4
0
0
0
1
(0 + 0 + (-1)) / 3 = -0.333333... 이고 이를 첫째 자리에서 반올림하면 0이다. -0으로 출력하면 안된다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);


void sort_merge(int* list, int length);

int divideToRound(int origin, int divide);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));

    int idx = 0;
    int result1 = 0; // 1. 산술평균을 위한 총량 계산
    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        int newNum = parseInt(input);

        result1 += newNum;

        *(list + idx++) = newNum;
    }

    result1 = divideToRound(result1, N);

    sort_merge(list, N);

    int result2 = *(list + (N / 2)); // 중앙값 - 홀수라서 그냥 반절 나누면 됨.(0.5는 무시)

    int result4 = *(list + N - 1) - *list; // 최고 값과 최소 값 간의 크기

    // 최빈 값 구하기 - 중복된다면, 두 번째로 작은 값을 출력한다. - 현재 list 는 오름차순 정렬 상태이다.

    int* timesList = (int*)calloc(N + 1, sizeof(int));

    idx = 1;
    int currNum = *list;
    int times = 1;
    int maxTimes = 1;
    while(idx < N) {
        int num = *(list + idx);

        if(num == currNum) {
            times++;
            maxTimes = maxTimes < times ? times : maxTimes;
        } else {
            *(timesList + idx - 1) = times;
            currNum = num;
            times = 1;
        }

        idx++;
    }
    *(timesList + N - 1) = times;

    int size = 5;
    int currSize = 0;

    int* maxList = (int*)malloc(sizeof(int) * (size + 1));
    int* maxListPtr = maxList;

    idx = 0;
    while(idx < N) {
        int time = *(timesList + idx);

        if(time == maxTimes) {
            currSize++;
            *maxListPtr++ = *(list + idx);

            if(size == currSize) {
                size *= 2;
                maxList = (int*)realloc(maxList, sizeof(int) * (size + 1));
                maxListPtr = (int*)(maxList + currSize);
            }
        }

        idx++;
    }

    sort_merge(maxList, currSize);

    int result3;

    if(currSize == 1) {
        result3 = *maxList;
    } else {
        result3 = *(maxList + 1);
    }

    char* result1Str = intToStr(result1);
    char* result2Str = intToStr(result2);
    char* result3Str = intToStr(result3);
    char* result4Str = intToStr(result4);

    fputs(result1Str, stdout); fputc('\n', stdout);
    fputs(result2Str, stdout); fputc('\n', stdout);
    fputs(result3Str, stdout); fputc('\n', stdout);
    fputs(result4Str, stdout); fputc('\n', stdout);

    free(result1Str); free(result2Str); free(result3Str); free(result4Str);

    free(list);
    free(maxList);
    free(timesList);

    return 0;
}

void sort_merge(int* list, int length) {
    if(length <= 1) {
        return;
    }

    int mid = length / 2;
    int left = mid;
    int right = length - mid;

    int* leftList = (int*)malloc(sizeof(int) * (left + 1));
    int* rightList = (int*)malloc(sizeof(int) * (right + 1));

    int i = 0, idx = 0;
    while(i < left) {
        *(leftList + i++) = *(list + idx++);
    }

    i = 0;
    while(i < right) {
        *(rightList + i++) = *(list + idx++);
    }

    sort_merge(leftList, left); sort_merge(rightList, right);

    i = 0, idx = 0;
    int j = 0;

    while(i < left && j < right) {
        int left = *(leftList + i);
        int right = *(rightList + j);
        if(left <= right) {
            *(list + idx++) = *(leftList + i++);
        } else {
            *(list + idx++) = *(rightList + j++);
        }
    }

    while(i < left) {
        *(list + idx++) = *(leftList + i++);
    }

    while(j < right) {
        *(list + idx++) = *(rightList + j++);
    }

    free(leftList); free(rightList);

    return;
}

int divideToRound(int origin, int divide) {
    // double d1 = (double)origin;
    // double d2 = (double)divide;

    // double doubleResult = d1 / d2;
    // int intPart = (int)doubleResult;
    // doubleResult -= (double)intPart;

    // intPart = (int)(doubleResult * 10);

    int tmp = origin % divide;
    tmp *= 10;

    int intPart = tmp / divide;

    if(intPart >= 5) {
        return (origin / divide) + 1;
    } else if (intPart <= -5) {
        return (origin / divide) - 1;
    } else {
        return origin / divide;
    }
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
