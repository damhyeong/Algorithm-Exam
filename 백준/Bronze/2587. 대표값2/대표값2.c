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
1 초	128 MB	66128	40712	36970	61.916%
문제
어떤 수들이 있을 때, 그 수들을 대표하는 값으로 가장 흔하게 쓰이는 것은 평균이다. 평균은 주어진 모든 수의 합을 수의 개수로 나눈 것이다. 예를 들어 10, 40, 30, 60, 30의 평균은 (10 + 40 + 30 + 60 + 30) / 5 = 170 / 5 = 34가 된다.

평균 이외의 또 다른 대표값으로 중앙값이라는 것이 있다. 중앙값은 주어진 수를 크기 순서대로 늘어 놓았을 때 가장 중앙에 놓인 값이다. 예를 들어 10, 40, 30, 60, 30의 경우, 크기 순서대로 늘어 놓으면

10 30 30 40 60

이 되고 따라서 중앙값은 30이 된다.

다섯 개의 자연수가 주어질 때 이들의 평균과 중앙값을 구하는 프로그램을 작성하시오.

입력
첫째 줄부터 다섯 번째 줄까지 한 줄에 하나씩 자연수가 주어진다. 주어지는 자연수는 100 보다 작은 10의 배수이다.

출력
첫째 줄에는 평균을 출력하고, 둘째 줄에는 중앙값을 출력한다. 평균과 중앙값은 모두 자연수이다.

예제 입력 1
10
40
30
60
30
예제 출력 1
34
30
*/

/**
연습을 위해 quick 으로 푼다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void sort_quick(int* list, int start, int end);
void swap(int* list, int i, int j);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    int size = 5;
    int* arr = (int*)malloc(sizeof(int*) * (size + 1));
    int* arrPtr = (int*)arr;

    int total = 0;

    while(fgets(input, sizeof(input), stdin) != NULL) {
        *arrPtr = parseInt(input);

        total += *arrPtr;

        arrPtr++;
    }

    sort_quick(arr, 0, size - 1);

    int middle = *(arr + 2);
    int avg = total / size;

    char* middleStr = intToStr(middle);
    char* avgStr = intToStr(avg);

    fputs(avgStr, stdout); fputc('\n', stdout);
    fputs(middleStr, stdout); fputc('\n', stdout);

    free(middleStr); free(avgStr);

    return 0;
}

void sort_quick(int* list, int start, int end) {
    if(start >= end) {
        return;
    }

    int pivot = start;
    int i = start;
    int j = end;

    while(i < j) {
        while(*(list + pivot) < *(list + j)) {
            j--;
        }
        while(i < j && *(list + pivot) >= *(list + i)) {
            i++;
        }
        swap(list, i, j);
    }
    swap(list, pivot, i);

    sort_quick(list, start, i - 1);
    sort_quick(list, i + 1, end);
}

void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

    return;
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
