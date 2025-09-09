/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "코드를 보다가 궁금하시면 EMAIL 로 연락 주셔도 괜찮습니다!"

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.


    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
LCS

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.1 초 (하단 참고)	256 MB	108706	46709	34196	42.204%

문제
---
LCS(Longest Common Subsequence, 최장 공통 부분 수열)문제는 두 수열이 주어졌을 때,

모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾는 문제이다.

예를 들어, ACAYKP와 CAPCAK의 LCS는 ACAK가 된다.

입력
---
첫째 줄과 둘째 줄에 두 문자열이 주어진다.

문자열은 알파벳 대문자로만 이루어져 있으며, 최대 1000글자로 이루어져 있다.


출력
---
첫째 줄에 입력으로 주어진 두 문자열의 LCS의 길이를 출력한다.

예제 입력 1
ACAYKP
CAPCAK
예제 출력 1
4
*/

/**
문제를 클릭하기 전, 나오는 설명으로는 LCS, (Longest Common Sequence) 라고 한다.

그런데, 이 문제에서 요구하는 것은, "최대 길이" 이다.

즉, "최대 길이인 정확한 부분 문장" 을 요구하는 것은 아니다.

이도 LIS 처럼 접근 방식을 택하면, 보이는 길이 있을 것이라 믿는다.

---

특이한 것은, 여기서 요구하는 것이 일치하는 문장 중 가장 긴 것이 아니라,

두 문장 간 알파벳 하나씩을 오름차순으로 선택하여, 가장 긴 "부분 수열" 을 요구한다는 것이다.

ACAYKP
CAPCAK

이 두 문장의 최장 공통 수열은, "ACAK" 이다.

---

문제를 보고, 최장 공통 수열과 입력을 대조해 보았을 때,

이에 대한 누적을 어떻게 진행해야 하는지 감이 오지 않는다.

먼저, 주어진 조건을 보자면,

1. 정렬을 따지지 않는다.
2. 두 문장 간의 공통적인 부분 수열이 이루어져야 한다.

---

두 문장 간의 공통적인 부분 수열 이라는 것을 어떻게 해석해야 하는가?

알파벳은 char 타입으로, 그대로 수로 변형 할 수 있는 특성을 가지므로,

ABCDE 는, { 1, 2, 3, 4, 5 } 로 생각할 수 있다.

그렇다면, 문제의 의미는 이렇게 변환할 수 있다.

---

첫째, 둘째 줄에 30 이하의 자연수 배열이 주어진다. (길이는 서로 다를 수 있음.)

첫째, 둘째 줄에 공통적으로 형성될 수 있는 가장 긴 공통 부분 수열의 길이는 얼마인가?

이렇게 해석이 가능하다.

정렬은 필요가 없으며, 단순히 두 수열 간의 최대 공통 부분을 구해야 한다는 것이 LIS 와는 사뭇 다르다고 느껴진다.

---

나는 이런 생각이 든다.

두 문장 간의 "최대 공통 부분" 을 구해야 한다면, 어쨋든 다른 하나의 문장이 기준이 되어야 할 것이다.

문제는, 정렬이 없으므로 1 ~ 최대 길이, 그리고 나올 수 있는 모든 경우의 수가 부분 수열이 될 수 있다.

그러나 우리가 참조할 수 있는 것은, 인덱스이다.

혹시 모를 가능성이나 단서를 찾기 위해 두 문장을 인덱스와 함께 펼쳐보기로 했다.

---

| 1  | 2  | 3  | 4  | 5  | 6  |
| A  | C  | A  | Y  | K  | P  |

| 1  | 2  | 3  | 4  | 5  | 6  |
| C  | A  | P  | C  | A  | K  |

와 이럴수가..

펼쳐놓고 보니까, 이건 완전 "전선" 문제와 거의 동일하다.

물론 전선 문제는 연결된 전선이 있다고 가정 할 때, 교차되지 않는 최대 전선의 갯수를 구한 후, 최소로 잘라야 하는 전선 개수를 구하는 것이었다.

이 두 문장 간 하나의 알파벳은 다른 문장에 동일한 알파벳으로 전선을 잇는다고 가정했을 때,

교차되지 않으며, 형성할 수 있는 최대 개수의 전선을 구한다고 가정하면 알맞는다.

조금 시야를 바꿔 보자.

1 번째 'A' 가 연결될 수 있는 인덱스

[1, 2], [1, 5]

2 번째 'C' 가 연결 될 수 있는 인덱스

[2, 1], [2, 4]

3 번째 'A' 가 연결 될 수 있는 인덱스

[3, 2], [3, 5]

4 번째 'Y' 가 연결 될 수 있는 인덱스

None

5 번째 'K' 가 연결 될 수 있는 인덱스

[5, 6]

6 번째 'P' 가 연결 될 수 있는 인덱스

[6, 3]


---

| 1  | 2  | 3  | 4  | 5  | 6  |
| A  | C  | A  | Y  | K  | P  |

| 1  | 2  | 3  | 4  | 5  | 6  |
| C  | A  | P  | C  | A  | K  |

### -모든 경우의 수를 적용하는 버전- (x1 <= x2) && (y1 <= y2)

1 2 --> { [0, 0], [1, 2] }
1 5 --> { [0, 0], [1, 2], [1, 5] }

2 1 --> { [0, 0], [2, 1], [1, 5] }
2 4 --> { [0, 0], [2, 1], [2, 4] }

3 2 --> { [0, 0], [2, 1], [3, 2] }
3 5 --> { [0, 0], [2, 1], [3, 2], [3, 5] }

5 6 --> { [0, 0], [2, 1], [3, 2], [3, 5], [5, 6] }

6 3 --> { [0, 0], [2, 1], [3, 2], [6, 3], [5, 6] } --> 결과 4 와 동일.

### 지정될 수 있는 알파벳 중 가장 앞의 것을 고르고, 그 이후는 고르지 못하는 버전

1 2 --> { [0, 0], [1, 2] }

2 1 --> { [0, 0], [2, 1] }

3 5 --> { [0, 0], [2, 1], {3, 5} }

5 6 --> { [0, 0], [2, 1], [3, 5], [5, 6] }

6 3 --> { [0, 0], [2, 1], [6, 3], [5, 6] }

---

...

---

...

---

그런데, 문제가 발생했다.

백준에서 틀리고, 테스트케이스 사이트에서도 틀린 예제 및 "시간 초과" 에러가 난 것이다.

위의 추리와 추상화는 틀렸다는 의미이다. (모든 경우의 전선을 입력으로 넣었을 경우.)

아....

처음부터 다시 분석해야 한다.

위에 약 120 줄이 넘는 분석 글을 적었고, 그 방법론으로 문제를 풀어봤다.

그런데, 절반 정도의 예제가 맞고? 절반 정도의 예제가 틀린 것이다!

도대체 무엇이 문제였을까?

---

결국 과정을 찾질 못하겠어서, GPT-5 Think 버전에게 물어보았다.

놀라웠던 것은, 생각의 전환이었다.

나는 이전의 전선 문제를 풀면서, 이 방식에 대해 갇혀 있었다.

그러나, 이를 "조합론" DP 풀이식 처럼 본다면 이야기가 달라진다.

즉,

수열 1 의 2 번째까지와, (j 라고 가정)
수열 2 의 1 번째까지의  (i 라고 가정)

최장 공통 부분 수열을 구할 수 있으며,

이 값은 더 긴 길이의 부분 수열의 최장 길이를 구하기 위한 "밑거름" 으로 사용하는 것이다.

---

두 수열의 총 길이가 N, M 이라고 칭해질 수 있을 때,

총 길이 N + 1, M + 1 의 정수 2차원 배열을 만들어서,

최대값을 구하는 용도로 사용할 수 있다.

수열 1 과 수열 2 가 있을 때, 현재 각각 i, j 라는 인덱스를 가지고

iterable 하게 될 텐데, 1번 수열의 j, 2번 수열의 i 의 문자가 같을 때, 다를 때를 구분하여 누적해야 한다.

이를 알기 위해, 직접 2 차원 그래프를 만들어서 누적시키며 규칙을 알아내 보자.


---

만약에 인덱스 i, j 의 문자가 서로 같지 않다면, 위와 왼쪽 중 더 큰 값을 가져온다.

idx      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | --> j
    char | 0 | A | C | A | Y | K | P |
--------------------------------------------
| 0 | 0 |  0 : 0 : 0 : 0 : 0 : 0 : 0 --> 공집합을 의미.
| 1 | C |  0 : 0 : 1 : 1 : 1 : 1 : 1 --> 수열 1 의 IDX:2 와 'C' 가 일치한다. 이 때, +1 을 행하는 인덱스는, (i - 1, j - 1) 이다. -1 된 각 수열에서, 일치하는 문자로 인해 최대 길이가 늘어났기 때문이다.
| 2 | A |  0 : 1 : 1 : 2 : 2 : 2 : 2 --> A 가 2 번 나왔음에도, 동일하게 +1 시킨다.
| 3 | P |  0 : 1 : 1 : 2 : 2 : 2 : 3 --> P 가 같으므로, (i-1, j-1) 인 (2, 5) 에서 +1 한 값을 저장한다.
| 4 | C |  0 : 1 : 2 : 2 : 2 : 2 : 3 --> 마지막은, 위(i-1, j) 과 왼쪽 (i, j-1) 중에서 더 큰 값을 저장한 것이다.
| 5 | A |  0 : 1 : 2 : 3 : 3 : 3 : 3
| 6 | K |  0 : 1 : 2 : 3 : 3 : 4 : 4 --> 결과적으로, (i, j) 에서 최대값인 "4" 가 담기게 된다.
  |        |
  v        v
  i       공집합

---

서로 가장 작은 엘리먼트 수부터 시작해서, 각 엘리먼트를 덧붙이며 그 이상의 집합이 되었을 때, 최대 길이가 얼마인지 도출한다.

여기서, iteration 도중 i, j 가 동일한 문자를 지녔을 때, (i - 1, j - 1) + 1 의 길이를 가지는 이유를 알아보자.

맨 처음 이러한 계산이 일어나는 집합을 구해 보자면,

i : {'C'}
j : {'A', 'C'}

이렇게 구성되어 있다.

그렇다면, 문자가 동일한 이 상황에서 +1 하기 위한 집합은 무엇일까?

i : {} --> 공집합
j : {'A'}

이 상황이다. --> 각각의 마지막 엘리먼트를 지운 집합에서, 정확히 하나의 길이가 늘어나기 위한 '이전의 상황' 이라고 볼 수 있다.

i 집합에만 'C' 를 붙이면, 공통 부분이 성립되지 않는다.

그렇다면, j 집합의 마지막에 'C' 를 넣더라도, 공통 부분이 성립되지 않는다.

즉, 각 집합의 마지막에 공통적으로 'C' 가 들어가야, 공통 엘리먼트가 성립되고,

공통 부분 수열의 길이가 1 이 늘어날 수 있는 것이다.

각자 일치하는 마지막 문자인 'C' 가 없는 상황에서 +1 한 것이므로, 0 + 1 == 1 이 된다.

---

이러한 방식으로, i, j 의 반복문이 끝이 났을 때, 조회하면 곧바로 최대 값을 구할 수 있다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void freeArrs(void** arrs);

char* parseStr(const char* input);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[1500];

    fgets(input, sizeof(input), stdin);

    char* str1 = parseStr(input);
    char* str1Ptr = str1;
    int j = 0;

    fgets(input, sizeof(input), stdin);

    char* str2 = parseStr(input);
    char* str2Ptr = str2;
    int i = 0;

    int idx = 0;
    while(!isBlank(*str1Ptr++)) {
        j++;
    }

    idx = 0;
    while(!isBlank(*str2Ptr++)) {
        i++;
    }

    int** dps = (int**)malloc(sizeof(int*) * (i + 2));
    int iter = 0;
    while(iter <= i) {
        *(dps + iter++) = (int*)calloc(j + 2, sizeof(int));
    }

    idx = 1;
    while(idx <= i) {
        char iCh = *(str2 + idx - 1);

        int jdx = 1;
        while(jdx <= j) {
            char jCh = *(str1 + jdx - 1);

            if(iCh == jCh) {
                *(*(dps + idx) + jdx) = *(*(dps + idx - 1) + jdx - 1) + 1;
            } else {
                int up = *(*(dps + idx - 1) + jdx);
                int left = *(*(dps + idx) + jdx - 1);

                *(*(dps + idx) + jdx) = up > left ? up : left;
            }

            jdx++;
        }
        idx++;
    }

    char* resultStr = intToStr(*(*(dps + i) + j));
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    freeArrs((void**)dps); free(str1); free(str2);

    return 0;
}

void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

    return;
}

char* parseStr(const char* input) {
    int size = 5;
    int curr = 0;

    char* flex = (char*)malloc(sizeof(char) * (size + 1));
    *(flex + size) = 0;

    char* flexPtr = flex;
    char* inputPtr = (char*)input;

    while(!isBlank(*inputPtr)) {
        curr++;
        *flexPtr++ = *inputPtr++;

        if(size == curr) {
            size *= 2;
            flex = (char*)realloc(flex, sizeof(char) * (size + 1));
            flexPtr = (char*)(flex + curr);
        }
    }
    *flexPtr = 0;

    return flex;
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
