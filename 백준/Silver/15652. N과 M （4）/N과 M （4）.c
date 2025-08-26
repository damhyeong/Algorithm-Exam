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
N과 M (4)

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	512 MB	72286	56935	45040	78.641%

문제
---
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

* 1부터 N까지 자연수 중에서 M개를 고른 수열

* 같은 수를 여러 번 골라도 된다.

* 고른 수열은 비내림차순이어야 한다. --> 오름차순이라는 말.

* 길이가 K인 수열 A가 A1 ≤ A2 ≤ ... ≤ AK-1 ≤ AK를 만족하면, 비내림차순이라고 한다.

입력
---
첫째 줄에 자연수 N과 M이 주어진다.

(1 ≤ M ≤ N ≤ 8)

출력
---
한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다.

중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.

수열은 사전 순으로 증가하는 순서로 출력해야 한다.

예제 입력 1
3 1
예제 출력 1
1
2
3
예제 입력 2
4 2
예제 출력 2
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4
예제 입력 3
3 3
예제 출력 3
1 1 1
1 1 2
1 1 3
1 2 2
1 2 3
1 3 3
2 2 2
2 2 3
2 3 3
3 3 3
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void recursive(int curr, int deep, int prev, int len, int* list);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = *input - '0';
    int M = *(input + 2) - '0';

    int* list = (int*)malloc(sizeof(int) * (M + 1));

    recursive(0, M, 1, N, list);

    free(list);

    return 0;
}

void recursive(int curr, int deep, int prev, int len, int* list) {
    if(curr == deep) {
        int idx = 0;
        while(idx < deep) {
            fputc(*(list + idx) + '0', stdout); fputc(' ', stdout);

            idx++;
        }
        fputc('\n', stdout);
        return;
    }

    int idx = prev;
    while(idx <= len) {
        *(list + curr) = idx;

        recursive(curr + 1, deep, idx, len, list);

        idx++;
    }
}
