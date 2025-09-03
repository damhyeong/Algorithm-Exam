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
가장 긴 증가하는 부분 수열

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	202171	82753	54903	38.714%

문제
---
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에

가장 긴 증가하는 부분 수열은 A = {10, 20, 10, 30, 20, 50} 이고, 길이는 4이다.


입력
---
첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000)이 주어진다.

둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다.

(1 ≤ A_i ≤ 1,000)


출력
---
첫째 줄에 수열 A의 가장 긴 증가하는 부분 수열의 길이를 출력한다.


예제 입력 1
6
10 20 10 30 20 50
예제 출력 1
4
*/

/**

문제 풀이 :

이전에 풀어봤던 문제는 확실한데...

내가 지금 생각하는 방식은 N^2 방식으로,

현재 수를 기점으로 지나간 수들과, 누적 값을 조회하여 최대를 구하는 방식밖에 생각이 안난다.

이러한 방식으로 문제를 풀게 되면, 추후 길이 100,000 이 되었을 때 사용하지 못하게 된다.

---

생각을 좀 하다가, 이전에 Java 로 문제를 풀었을 때의 기억이 떠올라 버렸다..

리스트와 이진 탐색, 값 교체를 활용하면 된다.

정해진 길이의 배열이라기 보다는, 우리가 마지막에 존재할 최대 값을 발견한다면,

각자의 방식으로 길이를 늘려서 가장 큰 값을 마지막에 새로 넣어주고,

마지막 값, 즉 가장 큰 수에 해당하지 않는다면,

여태까지 기억하고 있는 리스트에 이진 탐색을 통해, 동일한 수가 있는지, 중간에 들어갈 수 있는 위치를 찾는다.

* 동일한 수가 존재할 경우 : 이진 탐색 이후, 어떠한 것도 하지 않는다.
* 동일한 수가 존재하지 않을 경우 : 사이에 들어갈 수 있는 수 x, x + 1 이 존재 할 때, x + 1 로 값을 넣는다. (참고로 리스트와 dp 에는 맨 처음 0 이 들어가 있다.)

여기서 동일한 수가 존재 할 때, 따로 리스트를 갱신 할 필요는 없어서 (동일하니) 변경점이 존재하지 않는다.

그렇다면 왜? 동일한 수가 존재하지 않을 때, 리스트에 이미 바로잡혀 있는 수들을 교체할까?

---

나도 이에 대해서 아주 완벽하게 이해하고 있는 것은 아니지만, 새로운 수를 리스트에 갱신한다는 것은 큰 의미가 있다.

우리는 주어지는 수많은 입력에 대해서 어떤 부분 수열이 제일 길게 될지 예측할 수 없다.

내부에는 동일한 길이의 부분 수열이 있을수도 있고,

이 부분 수열이 구성되어 최대 길이의 수열을 구성할 수도 있다.

또한, 이 수들은 예시로 10, 20, 30 등등 일정한 간격의 수로 구성되어 있지만,

실제로는 1, 7, 50, 23, 967 이러한 수들로 구성되어 있을 것이다.

---

한번 바로 위에 작성한 수로 예시를 구성 해 보자.

{1, 7, 50, 967}
{1, 7, 23, 967}

이렇게 2 개의 최대 길이를 가진 수열이 나온다.

가장 눈여겨 봐야 할 점은, 우리는 내부의 요소를 구하는 것이 아니라, "길이" 만을 구한다는 것이다.

이제 그 과정을 나열 해 보겠다.

---

현재 최대 길이 저장 배열 : {0} --> 길이 0

"1" --> 현재 마지막 요소인 len : 0 에 접근 해 보니, "1" 이 더 크다.

따라서, "1" 을 마지막에 추가한다.

==

현재 최대 길이 저장 배열 : {0, 1} --> 길이 1

"7" --> 현재 마지막 요소인 len : 1 에 접근 해 보니, "7" 이 더 크다.

따라서, "7" 을 마지막에 추가한다.

==

현재 최대 길이 저장 배열 : {0, 1, 7} --> 길이 2

"50" --> 현재 마지막 요소인 len : 2 에 접근 해 보니, "50" 이 더 크다.

따라서, "50" 을 마지막에 추가한다.

==

현재 최대 길이 저장 배열 : {0, 1, 7, 50} --> 길이 3

"23" --> 현재 마지막 요소인 len : 3 에 접근 해 보니, "23" 이 작다.

따라서, 이분 탐색을 통해 같은 요소가 있는지 찾는다.

같은 요소는 없으므로, 중간에 들어갈 수 있는 수 x, x + 1 이 구해진다.

x : 7, x + 1 : 50

x + 1 에 새로운 수로 교체하므로, "50" 은 "23" 으로 교체된다.

==

현재 최대 길이 저장 배열 : {0, 1, 7, 23} --> 길이 3

"967" --> 현재 마지막 요소인 len : 3 에 접근 해 보니, "967" 이 더 크다

따라서, 마지막에 "967" 을 추가 해 준다.

==

결과 : {0, 1, 7, 23, 967} --> 길이 4

---

**"왜 이런 방식으로 계산하는가?"**

처음 이 방식을 시도하면 직관적으로 이해하기 힘들다.

그 이유는, "특정 입력 상황" 에서는 마지막에 남는 가장 긴 수열을 출력 해 보면,

입력된 수에 따라 나열된 가장 긴 수열에 해당하지 않기 때문일 것이다.

다시 예를 들어서,

10, 20, 30, 40, 50, 60, 70, 1, 2, 3, 4

라는 입력이 주어진다고 가정 해 보자.

그렇다면, 위에서 계산했던 대로 모두 계산 한 뒤

기록한 배열을 출력해서 본다면, {1, 2, 3, 4, 50, 60, 70} 이 된다.

---

위의 수열은 도저히 입력 상에서 도출 될 수 없는 수열이다.

그러나, "길이" 만큼은 아주 정확하게 구해진다.

그럼에도 불구하고, 도출될 수 없는 부분 수열에 대한 부분은 머리에서 떠나지 않을 것이다.

내가 그랬기 때문이다.

---

이걸 어떻게 직관적으로 말해야 할까 고민이 되는데,

"최대 길이가 될 수 있는 경우를 저장한다" 라고 생각한다.

최대 길이가 될 수 있는 경우는,

우리가 생각하는 "입력의 앞부분" 에서 나올 수도 있고, "입력의 뒷부분" 에서 도출 될 수도 있다.

하지만, 우리는 인지할 수 없다. (길이가 막 10,000 정도로 생각해 본다면.)

따라서, 우리는 도출 될 수 있는 가장 긴 수열을 구하기 위해,

"가능성이 존재하는 부분 수열을 내부에 저장한다" 라고 이해할 수 있다.

---

이러한 방식으로 구하는 이유를 들기 위해, 다른 예시를 들 수도 있다.

{10, 20, 30, 40, 50, 1, 2, 3, 4, 5, 6, 7, 8, 9}

이건 결과적으로 [1, 2, 3, 4, 5, 6, 7, 8, 9] 가 나올 것이다.

---

그리고, x, x + 1 사이의 수에서 x + 1 의 자리로 새로운 수를 넣는 이유가 있다.

만약에, 현재 지정된 수가 15 인데, 리스트가 {10, 20} 이라고 가정 해 보자.

수는 10, 20 사이에 위치한다. 즉, (x : 10), (x + 1 : 20) 이다.

그렇다면, "20" 은 새로운 수인 "15" 로 교체된다.

---

마지막 수를 교체하면 의도가 틀려지지 않을까? 할 수도 있겠지만,

현재 중요한 것은 "길이" 이지 "정확한 부분 수열" 이 아니다.

현재 지정 수가 "15" 이고, 내부 수열이 [10, 20] 이라는 것은,

내부에 어떤 계산이 있었던 간에, 현재까지의 가장 긴 수열은 [10, 20] 이었다는 것이다.

여기서 "15" 가 새로운 수, 즉 마지막으로 대체되는 이유는, [10, 15]

어짜피 (10, 20) 이던, (10, 15) 이던 그 길이는 동일하며, 앞으로 맞이하게 될 수에 대해서도 동일한 조건으로 대하게 된다.

하지만, "20" 은 "15" 보다 더 큰 수이기 때문에, 추후 "17", 혹은 "19" 와 같은 수가 나왔을 때 마지막에 추가해 줄 수가 없다.

어짜피 현재까지 탐색했을 때, 가장 긴 수열이 (10, 20), (10, 15) 라면, 추후 더 긴 수열을 만들기 위해 "15" 를 선택하는 것이 합리적이다.

아니, "16, 19" 와 같은 수를 오히려 붙이지 못하게 하여 가장 긴 부분 수열을 만들지 못하게 하는 상황이 되어버린다.

따라서, 길이는 동일하지만, 더 작은 수가 있다면, 쌍수 들고 새로운 수로 편입해야 더 긴 수열을 만들 수 있는 상황이라는 것이다.

---

이제 중요한 것은, 이분 탐색(binary_search) 를 어떻게 다룰 것이냐에 대한 것이다.

만약, 중간 인덱스의 수와 새로운 수가 동일하다면, 어떠한 것도 하지 않는다.

그러나, 양 끝에서 시작한 인덱스가 갈라지는 순간과 그 조건을 잘 명시해야 겠다는 생각이 든다.





*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

int binary_and_insert(int* list, int start, int end, int newNum);

char** tokenizer(const char* input);
void freeArrs(void** arrs);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[10000];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = tokens;

    int* list = (int*)malloc(sizeof(int) * (N + 2));
    *list = 0;

    int idx = 1;
    while(idx <= N) {
        *(list + idx++) = parseInt(*tokensPtr++);
    }

    freeArrs((void**)tokens);


    int size = 5;
    int currSize = 1;
    int* flex = (int*)malloc(sizeof(int) * (size + 1));
    *flex = 0;

    idx = 1;
    while(idx <= N) {
        int num = *(list + idx++);

        if(num > *(flex + currSize - 1)) {
            *(flex + currSize++) = num;

            if(size == currSize - 1) {
                size *= 2;
                flex = (int*)realloc(flex, sizeof(int) * (size + 1));
            }
        } else {
            binary_and_insert(flex, 0, currSize - 1, num);
        }
    }

    char* resultStr = intToStr(currSize - 1);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    free(list); free(flex);

    return 0;
}

int binary_and_insert(int* list, int start, int end, int newNum) {
    int mid = (start + end) / 2;
    int midNum = *(list + mid);

    if(start > end) {
        *(list + end + 1) = newNum;

        return -1;
    }

    if(midNum == newNum){
        return mid;
    }else if(midNum > newNum) {
        return binary_and_insert(list, start, mid - 1, newNum);
    } else {
        return binary_and_insert(list, mid + 1, end, newNum);
    }


}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }
            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

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
