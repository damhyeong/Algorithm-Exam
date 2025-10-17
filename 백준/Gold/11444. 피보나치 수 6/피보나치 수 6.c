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
피보나치 수 6

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	31082	14028	11628	47.671%

문제
---
피보나치 수는 0과 1로 시작한다.

0번째 피보나치 수는 0이고, 1번째 피보나치 수는 1이다.

그 다음 2번째 부터는 바로 앞 두 피보나치 수의 합이 된다.

이를 식으로 써보면 Fn = Fn-1 + Fn-2 (n ≥ 2)가 된다.

n=17일때 까지 피보나치 수를 써보면 다음과 같다.

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597

n이 주어졌을 때, n번째 피보나치 수를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 n이 주어진다.

n은 1,000,000,000,000,000,000 보다 작거나 같은 자연수이다.


출력
---
첫째 줄에 n번째 피보나치 수를 1,000,000,007으로 나눈 나머지를 출력한다.


예제 입력 1
1000
예제 출력 1
517691607
*/

/**

이번 문제는 정상적인 루프로는 정해진 시간 안에 피보나치 수를 구할 수 없다.

최대 1,000,000,000,000,000,000 "번째" 를 구하는 것이기 때문에, 루프로 프로그램을 가동시킨다면,

아마 1년이 걸리지 않을까 생각된다.

---

따라서, 이 문제는 주어진 규칙을 토대로 "분할 정복" 계산할 수 있는 환경을 만들어 주어야 한다는 것이다.

여기서 힌트를 주는게, 페르마의 소정리 { A^(P - 1) = 1 (mod P) } 를 남겨두었다.

즉, Fibonachi 점화식인 Fn = F_(n-1) + F_(n-2) 를 만족시키는 제곱 계산식의 형태를 만들어야 한다.

그런데, 위의 식을 아무리 보아도 "제곱 형태" 로 만들 수 있는 특정 수학식이 떠오르진 않는다.

내가 이 문제에 대한 강력한 힌트를 얻을 수 있는 것은, 이 문제가 "행렬" 문제에 속하기 때문에 알게 된 것이라는 거다.

어쩌면, "분할 정복" 이라는 항목은, 페르마의 소정리가 대부분 사용된다고 알려주는 일종의 힌트가 아닐까? With Matrix(행렬)

---

나는 행렬을 접할 때, 내가 알던 수학 규칙과는 사뭇 다른 무언가라고 생각했다.

뭐랄까, 너무 인간이 인위적으로 만든 도구같다고 해야하나?

수학 자체가 우주의 규칙을 이해하려는 일종의 단어라고 볼 수 있겠지만,

행렬도 비슷한 도구이지만, 좀 더 인위적이라고 생각했다.

이를 AI 에게 물어보고 행렬의 탄생 원리를 알게 되었다.

행렬을 잘 사용하면, 중첩된 벡터의 계산을 아주 빠르게 행할 수 있다는 것이었다.

즉, 우리가 할 계산 A ~ Z 가 존재한다고 가정하자.

일반적으로 A -> B -> ... -> Z 를 행하겠지만,

행렬은 아예 A ~ Z 의 결과를 미리 마치 "중첩" 시키는 듯한 과정과 비슷하다.

따라서, 아주 빠른 계산이 가능하다.

---

위의 배경을 보아하니, 아무래도 이번에는 주어진 행렬을 "제곱" 하시오 가 아닌,

행렬 규칙을 발견하거나 만들고, 이를 제곱하는 형태로 만드는 것이 이 문제의 핵심이라고 생각한다.

---

F_n = F_(n-1) + F_(n-2) 이다.

이를 어떻게 행렬 형태로 만들어야 할까?

먼저, 가로와 세로의 길이가 동일한 형태로 만들어야 한다고 판단했다. (그래야 제곱수를 만들 수 있으니)

F_(n-1) + F_(n-2) 가 그대로 나오는 형태를 다시 생각 해 보기로 했다.

문제는, 처음 형태는 1 * 2 이므로, 제곱이 불가하다. 따라서, 확장해야 한다.

{ F_(n-1), F_(n-2) }
{   ?    ,    ?    }

만약에 그렇게 하지 않는다면,

{ F_(n-1), F_(n-2) }
x
{ 1 }
{ 1 }

{ F_(n-1) * 1 + F_(n-2) * 1 } == { F_(n) }

결국 1 * 1 로 변한다.



==

---

그렇다면, 한번 실제 값을 넣어 보자.

n = 2 라면,

{ F_(1), F(0) }
{   ?  ,  ?   }

{ 1, 0 }
{ ?, ? }

n = 3 이라면,

{ F_(2), F_(1) }
{   ?  ,   ?   }

{ 1, 1 }
{ ?, ? }

n = 4 이라면,

{ F_(3), F_(2) }
{   ?  ,   ?   }

{ 2, 1 }
{ ?, ? }

n = 5 라면,

{ F_(4), F_(3) }
{   ?  ,   ?   }

{ 3, 2 }
{ ?, ? }

---

여기서 행렬의 "덧셈" 규칙을 이용해 각 행렬의 윗 부분을 확인 해 보면, 일치한다는 것을 볼 수 있다.

그러나, 중요 한 것은 "곱셈" 이다.

그러기 위해, 각 n 에서 "어떤" ? 가 나오는지 확인 해 보기로 했다.
(n = 0 부터.)
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597

{ 2, 1 }
{ ?, ? } ==> n = 4
=
{ 1, 1 }
{ ?, ? } ==> n = 3
+
{ 1, 0 }
{ ?, ? } ==> n = 2

위에서 크게 F(4) 와, F(3), F(2) 로 나누면, (x y z 로 해보기.)

이는 크게 F(4) ==> x = y + z 이다.

그런데, 여기서 하나의 계산으로 취급된 y, z 또한,

이전의 결과로 인해 x = y + z 처럼 취급된다는 것이다.

즉, 위에 작성된 ? 들은, 전부 F(x) = F(x-1) + F(x-2) 를 만족한다.

---

그러나, 이것이 n 과 얼마나 떨어져있는지, 일치하는지는 알 수 없다.

즉, F(n) 에 만들어 진 4 개의 "모든" 요소는 이전 요소로 인해 F(n) = F(n-1) + F(n-2) 를 만족한다는 것을 기억해야 한다.

---

그렇다면, N = 5 일 때, N = 4 일 때, 어떤 행렬 곱으로 규칙을 만족 할 수 있을지 보자.

{   3   ,    2     } = {     2   ,     1    }   { ?, ? }
{ F(p)  , F(p - 1) } = { F(p - 1), F(p - 2) } x { ?, ? }

또 이것을 이렇게 변경 할 수 있다.

{ F(N)  , F(N - 1) } = { F(N - 1), F(N - 2) }   { a, b }
{ F(p)  , F(p - 1) } = { F(p - 1), F(p - 2) } x { c, d }

{ a * F(N - 1) + c * F(N - 2), b * F(N - 1) + d * F(N - 2) }    { F(N)  , F(N - 1) }
{ a * F(p - 1) + c * F(p - 2), b * F(p - 1) + d * F(p - 2) } == { F(p)  , F(p - 1) }

한번 위의 규칙을 이용하여, a, b, c, d 를 알아보려고 한다.

- a * F(N - 1) + c * F(N - 2) == F(N)

- b * F(N - 1) + d * F(N - 2) == F(N - 1)

- a * F(p - 1) + c * F(p - 2) == F(p)

- b * F(p - 1) + d * F(p - 2) == F(p - 1)

위에서, F(N) 이던, F(p) 이던, F_x = F_x-1 + F_x-2 를 만족한다.

즉, 이는 이렇게 만들 수 있다.

- a * F(N - 1) + c * F(N - 2) == F(N - 1) + F(N - 2)
==> a = 1, c = 1

- b * F(N - 1) + d * F(N - 2) == F(N - 1)
==> b = 1, d = 0

- a * F(p - 1) + c * F(p - 2) == F(p - 1) + F(p - 2)
==> a = 1, c = 1

- b * F(p - 1) + d * F(p - 2) == F(p - 1)
==> b = 1, d = 0

==> a = 1, b = 1, c = 1, d = 0;

{ 1, 1 }
{ 1, 0 }

==> 즉, F(n) 행렬 = F(n-1) 행렬 x 위의 행렬

위의 간단한 행렬은, 우리가 분할 정복(재귀) 도중, 제곱수가 홀수 일 때, 사용하게 될 행렬이라는 것이다.

---

그렇다면, 우리에게는 아직 문제가 있다.

F(N) 과 F(p) 는 동일한 피보나치 시스템을 공유한다.

그러나, N 과 p 는 얼마나 떨어져 있는지 알 수 없다.

그러나, 우리는 이제 F(N)행렬 = F(N - 1)행렬 * 위에서 도출한 1, 1, 1, 0 행렬을 통해 밑의 값을 알아 낼 수 있다.

(n = 0 부터.)
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597

N = 4 일 때,

{ F(3), F(2)     }   { F(2)    , F(1)     }   { 1, 1 }
{ F(p), F(p - 1) } = { F(p - 1), F(p - 2) } x { 1, 0 }

{  2  ,     1    }   { 1       , 1        }   { 1, 1 }
{ F(p), F(p - 1) } = { F(p - 1), F(p - 2) } x { 1, 0 }

{ (1 * 1) + (1 * 1) , (1 * 0) + (1 * 1)  }
{ (1 * F(p - 1) + (1 * F(p - 2)), (1 * F(p - 1)) + (0 * F(p - 2)) }
==>
{ 2, 1 }
{ F(p - 1) + F(p - 2), F(p - 1) }

큰일이다. 이 방식으로는 다시 원점에 도달한다.

그런데, 이런 생각이 들었다.

제곱을 하기 위해, 나는 도출하려는 행렬의 형태를

{ F_(n), F_(n-1) }    { F_(n-1), F_(n-2) }   { 1, 1 }
{ F_(p), F_(p-1) } == { F_(p-1), F_(p-2) } x { 1, 0 }

으로 만들었다.

이러한 식은, F(..) 자체가 동일한 계산식 위에서 동작하기 때문이다.

그리고, { 1, 1 / 1, 0 } 행렬을 곱할 때,

정확하게 n 과 p 는 서로에게 영향을 미치지 않았다.

생각 해 보니, n 과 p 가 서로에게 영향을 미치지 않는데, 나는 F(n) 을 구해야만 한다.

그렇다면, p 가 어떤 값으로 설정되든 상관이 없지 않은가?

따라서,

{ 1, 1 }
{ 1, 0 }
x
{ F_(n), F_(n-1) }
{   0  ,   0     }

이 되어도 상관없는 것이다.

F_n 행렬 = F_(n-1) 행렬 x { 1, 1 / 1, 0 } 이므로,

즉, 이 문제는 { 1, 1 / 1, 0 } 이 몇 번이나 곱해졌는가로 정해질 수 있다.

따라서,

만약 n = 3 이라면,

 F_1 , F_0
{  1 , 0 }   { 1, 1 }^2
{  0 , 0 } x { 1, 0 }

가 결과가 된다.

---

혹시 몰라서, 위에 작성한 모든 판단과 추측을 Gemini 2.5 pro 에게 맡겨봤는데,

다행히도 이 추측은 완벽하게 핵심을 짚었다고 한다.

하지만, 앞의 행렬의 { .... / 0, 0 } 의 0, 0 은 딱히 필요가 없다는 지적을 받았다.

있어도 그만, 없어도 그만이지만,

확실히 행렬의 곱셈 법칙 상, 이는 틀림이 없고, 깔끔했다.

따라서, 나는 위에 작성한 규칙대로 문제의 답을 알려주면 된다.

---

그러나, 아직 "페르마의 소정리" 에 관한 구간이 남아있다.

A^(P-1) = 1 (mod P)  {A 는 P 의 배수가 아닐 때.}

여기서 주어진 P 는, 문제에서 준 1,000,000,007 (10억 7) 이라고 할 수 있다.

이는 큰 소수로서, 충분히 페르마 소정리를 적용할 수 있을만한 수이다.

---

문제는 여기서 생긴다.

어떻게 세야 할 지 조차 모르는

1,000,000,000,000,000,000 의 지수를 (100경)

어떻게 계산 할 것인가?

---

여기서 하나 알게 되었는데,

딱히 페르마의 소정리를 이용해서

풀 필요가 없다는 것이다. 그 이유는, "나눗셈" 이 필요없기 때문이다.

오로지 "곱셈" 만이 필요하다.

---

따라서, 이 문제는 {1, 1 / 1, 0} 의 제곱 과정 중,

제곱수의 홀짝 조건에 집중하면 된다.




*/

#include<stdio.h>
#include <string.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

long long** makeArr(int row, int col);
long long** copyArr(long long** dest, int row, int col);
long long getCellResult(long long** arrs1, long long** arrs2, int y, int x, int len, long long C);
long long** mulMatrix(long long** arrs1, long long** arrs2, int i, int j, int k , long long C);
long long** divideConquer(long long** A, long long B, long long C);

void freeArrs(void** arrs);

char* longToStr(long long target, int bufSize, char* buf);
long long parseLongLong(const char* str, FILE* stream);
_Bool isBlank(char ch);


int main(void) {
    long long n = parseLongLong(NULL, stdin);

    if(n == 0) {
        fputs("0\n", stdout);
        return 0;
    }

    long long** A = makeArr(2, 2);
    *(*(A)) = 1;
    *(*(A) + 1) = 1;
    *(*(A + 1)) = 1;
    *(*(A + 1) + 1) = 0;

    long long** tmpResult = divideConquer(A, n - 1, 1000000007);

    freeArrs((void**)A);


    char buf[100];
    char* charResult = longToStr(*(*(tmpResult)), sizeof(buf), buf);
    fputs(charResult, stdout); fputc('\n', stdout);

    return 0;
}

long long** makeArr(int row, int col) {
    long long** result = (long long**)malloc(sizeof(long long*) * (row + 1));
    *(result + row) = NULL;

    int idx = 0;
    while(idx < row)
        *(result + idx++) = (long long*)calloc(col + 1, sizeof(long long));

    return result;
}
long long** copyArr(long long** dest, int row, int col) {
    long long** target = makeArr(row, col);

    int idx = 0;
    while(idx < row) {
        int jdx = 0;
        while(jdx < col) {
            *(*(target + idx) + jdx) = *(*(dest + idx) + jdx);
            jdx++;
        }
        idx++;
    }

    return target;
}
long long getCellResult(long long** arrs1, long long** arrs2, int y, int x, int len, long long C) {
    long long result = 0;

    int idx = 0;
    while(idx < len) {
        result += *(*(arrs1 + y) + idx) * *(*(arrs2 + idx) + x);
        result %= C;
        idx++;
    }

    return result;
}
long long** mulMatrix(long long** arrs1, long long** arrs2, int i, int j, int k, long long C) {
    long long** result = makeArr(i, k);

    int idx = 0;
    while(idx < i) {
        int jdx = 0;
        while(jdx < k) {
            *(*(result + idx) + jdx) = getCellResult(arrs1, arrs2, idx, jdx, j, C);
            jdx++;
        }
        idx++;
    }

    return result;
}
long long** divideConquer(long long** A, long long B, long long C) {
    if(B == 0) {
        long long** oneArr = makeArr(2, 2);
        *(*(oneArr)) = 1;
        *(*(oneArr + 1) + 1) = 1;

        return oneArr;
    } else if(B == 1) {
        long long** copiedArr = copyArr(A, 2, 2);
        return copiedArr;
    }

    long long** halfResult = divideConquer(A, B / 2, C);

    long long** tmpResult = mulMatrix(halfResult, halfResult, 2, 2, 2, C);
    free((void**)halfResult);

    long long** result;
    if(B % 2) {
        result = mulMatrix(tmpResult, A, 2, 2, 2, C);
        freeArrs((void**)tmpResult);
    } else {
        result = tmpResult;
    }

    return result;
}

void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr)
        free(*arrsPtr++);
    free(arrs);

    return;
}

char* longToStr(long long target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long long temp = target;
    temp = target < 0 ? -temp : temp;

    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0)
        *--bufPtr = '-';

    return bufPtr;
}
long long parseLongLong(const char* str, FILE* stream) {
    long long sign = 1;
    long long result = 0;

    if(!stream) {
        char* strPtr = (char*)str;
        if(*strPtr == '-') {
            sign = -1;
            strPtr++;
        }

        while(!isBlank(*strPtr)) {
            result *= 10;
            result += *strPtr++ - '0';
        }
    } else {
        char ch = fgetc(stream);
        if(ch == '-') {
            sign = -1;
            ch = fgetc(stream);
        }

        while(!isBlank(ch)) {
            result *= 10;
            result += ch - '0';
            ch = fgetc(stream);
        }
    }

    return result * sign;
}
_Bool isBlank(char ch) {
    if(ch == 32 || ch == 0)
        return 1;
    else if(ch >= 9 && ch <= 13)
        return 1;
    else
        return 0;
}
