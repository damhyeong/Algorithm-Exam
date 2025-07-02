
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
2 초	128 MB	191847	103547	84712	54.200%

문제
---
그룹 단어란 단어에 존재하는 모든 문자에 대해서, 각 문자가 연속해서 나타나는 경우만을 말한다.

예를 들면, ccazzzzbb는 c, a, z, b가 모두 연속해서 나타나고,

kin도 k, i, n이 연속해서 나타나기 때문에 그룹 단어이지만,

aabbbccb는 b가 떨어져서 나타나기 때문에 그룹 단어가 아니다.


단어 N개를 입력으로 받아 그룹 단어의 개수를 출력하는 프로그램을 작성하시오.

입력
---
첫째 줄에 단어의 개수 N이 들어온다.

N은 100보다 작거나 같은 자연수이다.

둘째 줄부터 N개의 줄에 단어가 들어온다.

단어는 알파벳 소문자로만 되어있고 중복되지 않으며, 길이는 최대 100이다.


출력
---
첫째 줄에 그룹 단어의 개수를 출력한다.

예제 입력 1
3
happy
new
year
예제 출력 1
3

예제 입력 2
4
aba
abab
abcabc
a
예제 출력 2
1

예제 입력 3
5
ab
aa
aca
ba
bb
예제 출력 3
4

예제 입력 4
2
yzyzy
zyzyz
예제 출력 4
0

예제 입력 5
1
z
예제 출력 5
1

예제 입력 6
9
aaa
aaazbz
babb
aazz
azbz
aabbaa
abacc
aba
zzaz
예제 출력 6
2
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* calloc(size_t size, size_t byte);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int loop = parseInt(input);

    int groupNum = 0;

    while(--loop >= 0) {
        _Bool* isShown = (_Bool*)calloc('z' - 'a' + 1, sizeof(_Bool));

        fgets(input, sizeof(input), stdin);
        char* inputPtr = (char*)input;

        _Bool isGroup = 1;

        char currCh = -1;
        while(isBlank(*inputPtr) != 1) {
            char ch = *inputPtr++;

            if(currCh != ch && isShown[ch - 'a'] == 1) {
                isGroup = 0;
                break;
            } else if(currCh != ch && isShown[ch - 'a'] == 0) {
                currCh = ch;
                isShown[ch - 'a'] = 1;
            }
        }

        free(isShown);

        groupNum = isGroup == 1 ? groupNum + 1 : groupNum;
    }

    char* resultStr = intToStr(groupNum);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

    return 0;
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

    int size = (sign == 1) ? len : len + 1;
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
