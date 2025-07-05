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
1 초	128 MB	41868	29794	26966	71.573%

문제
---
상근이는 친구들과 함께 SF영화를 찍으려고 한다.

이 영화는 외계 지형이 필요하다.

실제로 우주선을 타고 외계 행성에 가서 촬영을 할 수 없기 때문에, 컴퓨터 그래픽으로 CG처리를 하려고 한다.

외계 지형은 중앙 이동 알고리즘을 이용해서 만들려고 한다.

알고리즘을 시작하면서 상근이는 정사각형을 이루는 점 4개를 고른다.

그 후에는 다음과 같은 과정을 거쳐서 지형을 만든다.

정사각형의 각 변의 중앙에 점을 하나 추가한다.
정사각형의 중심에 점을 하나 추가한다.
초기 상태에서 위와 같은 과정을 한 번 거치면 총 4개의 정사각형이 새로 생긴다.

이와 같은 과정을 상근이가 만족할 때 까지 계속한다.

아래 그림은 과정을 총 2번 거쳤을 때까지의 모습이다.


- 초기 상태 - 점 4개
- 1번 - 점 9개
- 2번 - 25개


상근이는 어떤 점은 한 개 보다 많은 정사각형에 포함될 수 있다는 사실을 알았다.

메모리 소모량을 줄이기 위해서 중복하는 점을 한 번만 저장하려고 한다.

과정을 N번 거친 후 점 몇 개를 저장해야 하는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. (1 ≤ N ≤ 15)

출력
첫째 줄에 과정을 N번 거친 후 점의 수를 출력한다.

예제 입력 1
1
예제 출력 1
9
예제 입력 2
2
예제 출력 2
25
예제 입력 3
5
예제 출력 3
1089
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

    int width = 2;

    while(--N >= 0) {
        width += width - 1;
    }

    int result = width * width;

    char* resultStr = intToStr(result);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

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
