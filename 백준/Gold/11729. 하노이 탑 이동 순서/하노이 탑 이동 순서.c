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
하노이 탑 이동 순서

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	103268	53838	40888	51.637%

문제
---
세 개의 장대가 있고 첫 번째 장대에는 반경이 서로 다른 n개의 원판이 쌓여 있다.

각 원판은 반경이 큰 순서대로 쌓여있다.

이제 수도승들이 다음 규칙에 따라 첫 번째 장대에서 세 번째 장대로 옮기려 한다.

1. 한 번에 한 개의 원판만을 다른 탑으로 옮길 수 있다.
2. 쌓아 놓은 원판은 항상 위의 것이 아래의 것보다 작아야 한다.

이 작업을 수행하는데 필요한 이동 순서를 출력하는 프로그램을 작성하라.

단, 이동 횟수는 최소가 되어야 한다.

아래 그림은 원판이 5개인 경우의 예시이다.

입력
---
첫째 줄에 첫 번째 장대에 쌓인 원판의 개수 N (1 ≤ N ≤ 20)이 주어진다.

출력
---
첫째 줄에 옮긴 횟수 K를 출력한다.

두 번째 줄부터 수행 과정을 출력한다.

두 번째 줄부터 K개의 줄에 걸쳐 두 정수 A B를 빈칸을 사이에 두고 출력하는데, 이는 A번째 탑의 가장 위에 있는 원판을 B번째 탑의 가장 위로 옮긴다는 뜻이다.

예제 입력 1
3
예제 출력 1
7
1 3
1 2
3 2
1 3
2 1
2 3
1 3
*/

/**
다른 문제들은 재귀를 어떻게 사용해야 할 지 바로 계획이 세워지는데,

솔직히 이 문제는 계획이 세워지지 않는다.

도대체 어떻게 이 문제를 재귀로 푼다는 것인가?

차라리 Stack 문제에 가깝겠다고 생각이 들지만,

이 문제를 보며 "재귀 파트에 들어가 있으니, 재귀 사용이 가능하겠지" 라는 안일한 생각 또한 든다.

도대체 하노이 탑을 어떻게 재귀로 푼다는 것인가... 심지어 실행 횟수를 먼저 출력하면서까지.


만약에 직접 하노이 탑 놀이를 하라고 한다면 하지,

이 하노이 탑에 대한 최소한의 횟수와 이동 과정을 상세히 풀어낼 수 있으리라고는 생각해 보지 않았다.

역시 모르는 문제의 경우, 각 입력 값에 따라 어떤 결과가 나오는지 풀어 봐야 이해가 될 것 같다.

---------

예시 - 1 개

가장 최소이므로,

1 3

라는 과정을 겪을 것이고,

최소 횟수는 1 번이다.

이다.

예시 - 2 개

과정 :
1 2
1 3
2 3
횟수 : 3

예시 - 3 개

과정 :
1 3
1 2
3 2
1 3
2 1
2 3
1 3
횟수 : 7

예시 - 4 개

과정 :
1 2 - {2, 3, 4}, {1}, {}
1 3 - {3, 4}, {1}, {2}
2 3 - {3, 4}, {}, {1, 2}
1 2 - {4}, {3}, {1, 2}
3 1 - {1, 4}, {3}, {2}
3 2 - {1, 4}, {2, 3}, {}
1 2 - {4}, {1, 2, 3}, {}
1 3 - {}, {1, 2, 3}, {4}
2 3 - {}, {2, 3}, {1, 4}
2 1 - {2}, {3}, {1, 4}
3 1 - {1, 2}, {3}, {4}
2 3 - {1, 2}, {}, {3, 4}
1 2 - {2}, {1}, {3, 4}
1 3 - {}, {1}, {2, 3, 4}
2 3 - {}, {}, {1, 2, 3, 4}
횟수 : 15

나는 맨 위의 판을 3 번쨰로 옮기지 않고, 2 번째로 시작한 예시를 만들었다. 그러나, 처음 판을 3 번째로 옮겨야 할 수도 있다.

따라서 예시를 하나 더 만든다.

과정 :
1 3 - {2, 3, 4}, {}, {1}
1 2 - {3, 4}, {2}, {1}
3 2 - {3, 4}, {1, 2}, {}
1 3 - {4}, {1, 2}, {3}
2 1 - {1, 4}, {2}, {3}
2 3 - {1, 4}, {}, {2, 3}
1 3 - {4}, {}, {1, 2, 3}
1 2 - {}, {4}, {1, 2, 3} ===> 짝수일 경우, 첫 번째 행동으로 판을 3 번째로 가져다 놓는 것은 틀린 행위이다. (최적 X)

그렇다면,
* 홀수 일 경우, 첫 번째 행동으로 3 번째 판으로 옮기고
* 짝수 일 경우, 첫 번째 행동으로 2 번째 판으로 옮긴다.

-----

이제 관점을 바꿔, 재귀로 돌아온다.

재귀는 결국 구성될 수 있는 최소한의 "길이" 혹은 "크기" 혹은 "수"가 되었을 때,

정확한 값을 전달한다.

결국 재귀 호출한 상위 메서드는, 하위 메서드의 반환값을 구성하여 결과값을 전달하는 매개라고 칭할 수 있다.

그렇다는 것은, 위의 과정을 통해, 각 재귀 메서드가 반환값, 혹은 최소 값을 통해 2 개의 수를 출력해야 한다는 것을 알 수 있다.

먼저, 도달 가능한 최소 값을 선정 해 보자.

* 1 개
    - 1 3   {}, {}, {1}
* 2 개
    - 1 2   {2}, {1}, {}
    - 1 3   {}, {1}, {2} => N 번째의 판이 목표에 도달
    - 2 3   {}, {}, {1, 2}
* 3 개
    - 1 3   {2, 3}, {}, {1}
    - 1 2   {3}, {2}, {1}
    - 3 2   {3}, {1, 2}, {}
    - 1 3   {}, {1, 2}, {3} => N 번째의 판이 목표에 도달
    - 2 1   {1}, {2}, {3}
    - 2 3   {1}, {}, {2, 3}
    - 1 3   {}, {}, {1, 2, 3}
* 4 개
    - 1 2 - {2, 3, 4}, {1}, {}
    - 1 3 - {3, 4}, {1}, {2}
    - 2 3 - {3, 4}, {}, {1, 2}
    - 1 2 - {4}, {3}, {1, 2}
    - 3 1 - {1, 4}, {3}, {2}
    - 3 2 - {1, 4}, {2, 3}, {}
    - 1 2 - {4}, {1, 2, 3}, {}
    - 1 3 - {}, {1, 2, 3}, {4} => N 번째의 판이 목표에 도달
    - 2 3 - {}, {2, 3}, {1, 4}
    - 2 1 - {2}, {3}, {1, 4}
    - 3 1 - {1, 2}, {3}, {4}
    - 2 3 - {1, 2}, {}, {3, 4}
    - 1 2 - {2}, {1}, {3, 4}
    - 1 3 - {}, {1}, {2, 3, 4}
    - 2 3 - {}, {}, {1, 2, 3, 4}

이러한 과정을 살펴보았을 때, 각 개수마다 공통점이 존재한다.

가장 밑에 존재하는 N 번째의 판을 곧바로 3 번째로 옮기기 위해, 2 번째 판으로 모두 옮긴다는 것이다.

즉, N 번째 판을 목표인 3 번째 판으로 옮기기 위한 과정, (1 3) 은 모두 공통적으로 가지고 있다.\

----

문제는 하나 더 있다.

이건 단순히 횟수를 구하지 않는다.

정확하게 최소 횟수를 구하는 과정에서 옮겨진 행동을 실제로 출력해야 한다.

위의 과정을 복사하여, N - 1, N - 2, ..., N - (N - 1) 까지의 판이 "어디로" 이동하는지 풀어보기로 했다.

* 1 개
    - 1 3   {}, {}, {1} --> 목표인 N 번째 판을 목표에 옮김.
* 2 개
    - 1 2   {2}, {1}, {} --> N - 1 번째 판까지 전부 2 번째로 옮김.
    - 1 3   {}, {1}, {2}
    - 2 3   {}, {}, {1, 2} --> N 번째 판 까지 전부 3 번째로 옮김.
* 3 개
    - 1 3   {2, 3}, {}, {1} --> N - 2 번째 판까지 전부 3 번째로 옮김.
    - 1 2   {3}, {2}, {1}
    - 3 2   {3}, {1, 2}, {} --> N - 1 번째 판까지 전부 2 번쨰로 옮김.
    - 1 3   {}, {1, 2}, {3}
    - 2 1   {1}, {2}, {3}
    - 2 3   {1}, {}, {2, 3}
    - 1 3   {}, {}, {1, 2, 3} --> N 번째 판을 전부 3 번쨰로 옮김.
* 4 개
    - 1 2 - {2, 3, 4}, {1}, {} --> N - 3 번째 판까지 전부 2 번째로 옮김.
    - 1 3 - {3, 4}, {1}, {2}
    - 2 3 - {3, 4}, {}, {1, 2} --> N - 2 번째 판까지 전부 3 번째 옮김.
    - 1 2 - {4}, {3}, {1, 2}
    - 3 1 - {1, 4}, {3}, {2}
    - 3 2 - {1, 4}, {2, 3}, {}
    - 1 2 - {4}, {1, 2, 3}, {} --> N - 1 번째 판 까지 전부 2 번째로 옮김.
    - 1 3 - {}, {1, 2, 3}, {4}
    - 2 3 - {}, {2, 3}, {1, 4}
    - 2 1 - {2}, {3}, {1, 4}
    - 3 1 - {1, 2}, {3}, {4}
    - 2 3 - {1, 2}, {}, {3, 4}
    - 1 2 - {2}, {1}, {3, 4}
    - 1 3 - {}, {1}, {2, 3, 4}
    - 2 3 - {}, {}, {1, 2, 3, 4} --> N 번째 판 까지 전부 3 번째로 옮김.

1. 홀수 일 경우, 첫 번째 행동은 3 번째로 옮긴다. 짝수 일 경우, 2 번째로 옮긴다.
2. 처음 입력이 N 일 경우, 하위 재귀의 목표는 전부 N - 1 개의 판을 2 번째로 옮기기 위한 행동이다.
3. 2 번째에 N - 1 까지 정렬이 완료 되며, N 번째가 목표에 도달했을 경우, N - 1 을 3 번째로 옮기기 위한 행동에 돌입한다.
4. 예시에서 가장 밑의 행동은 처음 재귀 메서드를 실행했을 때의 행동이며, 마지막 행동을 의미한다.
5. 역으로, 가장 위의 행동은 재귀 메서드가 마지막에 도달했을 때의 행동을 의미한다.

---

지금 위에 선언한 트리거는 재귀에 걸맞는지는 잘 알 수 없다.

하지만, 확실한 것은, 현재 재귀의 깊이, N 이 동일하다면, 곧바로 return 하여 어떠한 행동도 하지 않는다.

* 1 개

1 3

* 2 개

2 3 --> 1 2
    --> 1 3

현재 깊이, 깊이 제한, 옮겨야 하는 판 개수, 목적지(1 ~ 3)
int N, int front, int back

recursive(1, 1, 3);

recursive(2, 1, 3) --> recursive(2 - 1, 1, 2)
                   --> recursive(2 - 1, 1, 3)
                   --> recursive(2 - 1, 2, 3)

recursive(3, 1, 3) --> recursive(2, 1, 2) --> recursive(1, 1, 3)
                                          --> recursive(1, 1, 2)
                                          --> recursive(1, 3, 2)
                   --> recursive(1, 1, 3)
                   --> recursive(2, 2, 3) --> recursive(1, 2, 1)
                                          --> recursive(1, 2, 3)
                                          --> recursive(1, 1, 3)




if(N == 0) {
    return;
}

if(N == 1) {
    fputs(front, ' ', back)
} else {
    int idx = 1;
    while(true) {
        if(start != idx && end != idx){
            break;
        }

        idx++;
    }

    recursive(N - 1, front, idx)
    recursive(1, front, end);
    recursive(N - 1, idx, end)
}
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct StringBuilder {
    int size;
    int currSize;

    char* str;
    char* strPtr;

    struct StringBuilder* (*append)(struct StringBuilder* this, char ch);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
StringBuilder* append_char(StringBuilder* this, char ch);

void recursive(int N, int start, int end, StringBuilder* sb, int* result);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    StringBuilder* sb = NewStringBuilder();

    int* result = (int*)malloc(sizeof(int) * (2));
    *result = 0;

    recursive(N, 1, 3, sb, result);

    char* numResult = intToStr(*result);
    fputs(numResult, stdout); fputc('\n', stdout);
    free(numResult);
    fputs(sb->str, stdout);

    free(result);
    free(sb->str);
    free(sb);

    return 0;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));

    sb->size = 5;
    sb->currSize = 0;

    sb->append = append_char;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    *(sb->str + sb->size) = 0;
    sb->strPtr = sb->str;

    return sb;
}

StringBuilder* append_char(StringBuilder* this, char ch) {
    *this->strPtr++ = ch; this->currSize++; *this->strPtr = 0;

    if(this->size == this->currSize) {
        this->size *= 2;
        this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
        *(this->str + this->size) = 0;
        this->strPtr = (char*)(this->str + this->currSize);
    }

    return this;
}

void recursive(int N, int start, int end, StringBuilder* sb, int* result) {

    if(N == 1) {
        int tmpResult = *result;
        *result = tmpResult + 1;
        sb->append(sb, start + '0')->append(sb, ' ')->append(sb, end + '0')->append(sb, '\n');
    } else {
        int idx = 1;
        while(1) {
            if(start != idx && end != idx){
                break;
            }

            idx++;
        }

        recursive(N - 1, start, idx, sb, result);
        recursive(1, start, end, sb, result);
        recursive(N - 1, idx, end, sb, result);
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
    *result = sign == 1 ? *result : '-';

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
