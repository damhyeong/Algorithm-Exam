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
2 초 (추가 시간 없음)	1024 MB (추가 메모리 없음)	34069	18738	16193	55.919%
문제
정휘는 후배들이 재귀 함수를 잘 다루는 재귀의 귀재인지 알아보기 위해 재귀 함수와 관련된 문제를 출제하기로 했다.

팰린드롬이란, 앞에서부터 읽었을 때와 뒤에서부터 읽었을 때가 같은 문자열을 말한다. 팰린드롬의 예시로 AAA, ABBA, ABABA 등이 있고, 팰린드롬이 아닌 문자열의 예시로 ABCA, PALINDROME 등이 있다.

어떤 문자열이 팰린드롬인지 판별하는 문제는 재귀 함수를 이용해 쉽게 해결할 수 있다. 아래 코드의 isPalindrome 함수는 주어진 문자열이 팰린드롬이면 1, 팰린드롬이 아니면 0을 반환하는 함수다.

#include <stdio.h>
#include <string.h>

int recursion(const char *s, int l, int r){
    if(l >= r) return 1;
    else if(s[l] != s[r]) return 0;
    else return recursion(s, l+1, r-1);
}

int isPalindrome(const char *s){
    return recursion(s, 0, strlen(s)-1);
}

int main(){
    printf("ABBA: %d\n", isPalindrome("ABBA")); // 1
    printf("ABC: %d\n", isPalindrome("ABC"));   // 0
}

정휘는 위에 작성된 isPalindrome 함수를 이용하여 어떤 문자열이 팰린드롬인지 여부를 판단하려고 한다.

구체적으로는, 문자열 S 를 isPalindrome 함수의 인자로 전달하여 팰린드롬 여부를 반환값으로 알아낼 것이다.

더불어 판별하는 과정에서 recursion 함수를 몇 번 호출하는지 셀 것이다.

정휘를 따라 여러분도 함수의 반환값과 recursion 함수의 호출 횟수를 구해보자.

입력
---
첫째 줄에 테스트케이스 개수 T 가 주어진다.

(1 <= T <= 1_000)

둘째 주 부터 T 개의 줄에 알파벳 대문자로 구성된 문자열 S 가 주어진다.

(1 <= |S| <= 1_000)

출력
---
각 테스트케이스마다, isPalindrome 함수의 반환값과 recursion 함수의 호출 횟수를 한 줄에 공백으로 구분하여 출력한다.

예제 입력 1
5
AAA
ABBA
ABABA
ABCA
PALINDROME
예제 출력 1
1 2
1 3
1 3
0 2
0 1
*/
/**
좋은 생각이 났는데,

전역 변수를 통해 호출 횟수를 아는 방식이 있다.

그러나, 나는 조금 더 생각해 보기로 했다.

만약에 팰린드롬이 형성되지 않는다면, "음수" 로 전달해 주면 알지 않나?

덕분에 작성할 코드가 줄었다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

int recursive(const char* str, int i, int j, int times);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[1200];

    fgets(input, sizeof(input), stdin);

    int T = parseInt(input);

    while(--T >= 0) {
        fgets(input, sizeof(input), stdin);

        int len = 0;

        char* inputPtr = input;
        while(!isBlank(*inputPtr++)) {
            len++;
        }

        int result = recursive(input, 0, len - 1, 1);

        char* timesStr;
        if(result < 0) {
            result *= -1;

            timesStr = intToStr(result);
            fputs("0 ", stdout); fputs(timesStr, stdout); fputc('\n', stdout);
            free(timesStr);
        } else {
            timesStr = intToStr(result);
            fputs("1 ", stdout); fputs(timesStr, stdout); fputc('\n', stdout);
            free(timesStr);
        }
    }

    return 0;
}

int recursive(const char* str, int i, int j, int times) {
    if(i >= j) {
        return times;
    }

    char ch1 = *(str + i);
    char ch2 = *(str + j);

    if(ch1 == ch2) {
        return recursive(str, i + 1, j - 1, times + 1);
    } else {
        return -1 * times;
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
