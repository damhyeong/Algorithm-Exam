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
1 초	128 MB	213987	96271	80730	44.792%

문제
---
예전에는 운영체제에서 크로아티아 알파벳을 입력할 수가 없었다.

따라서, 다음과 같이 크로아티아 알파벳을 변경해서 입력했다.

크로아티아 알파벳 | 변경
č	c=
ć	c-
dž	dz=
đ	d-
lj	lj
nj	nj
š	s=
ž	z=

예를 들어, ljes=njak은 크로아티아 알파벳 6개(lj, e, š, nj, a, k)로 이루어져 있다.

단어가 주어졌을 때, 몇 개의 크로아티아 알파벳으로 이루어져 있는지 출력한다.

dž는 무조건 하나의 알파벳으로 쓰이고, d와 ž가 분리된 것으로 보지 않는다.

lj 와 nj 도 마찬가지이다.

위 목록에 없는 알파벳은 한 글자씩 센다.

입력
---
첫째 줄에 최대 100글자의 단어가 주어진다.

알파벳 소문자와 '-', '='로만 이루어져 있다.

단어는 크로아티아 알파벳으로 이루어져 있다.

문제 설명의 표에 나와있는 알파벳은 변경된 형태로 입력된다.


출력
---
입력으로 주어진 단어가 몇 개의 크로아티아 알파벳으로 이루어져 있는지 출력한다.

예제 입력 1
ljes=njak
예제 출력 1
6

예제 입력 2
ddz=z=
예제 출력 2
3

예제 입력 3
nljj
예제 출력 3
3

예제 입력 4
c=c=
예제 출력 4
2

예제 입력 5
dz=ak
예제 출력 5
3
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

char* intToStr(int target);
_Bool isSame(char* str, char* word);
int getLength(char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    char* words[] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=", NULL};
    char** wordsPtr = (char**)words;

    fgets(input, sizeof(input), stdin);

    // 각 단어마다 체크 될 시 1 로 변경
    while(*wordsPtr) {
        char* word = *wordsPtr++;

        char* inputPtr = (char*)input;

        // 인덱스 하나마다, 이를 보내서 확인한다.
        while(*inputPtr) {
            _Bool isChanging = isSame(inputPtr, word);

            // 현재 inputPtr 인덱스 수준에서 단어가 매칭된다면.
            if(isChanging == 1) {
                char* startPtr = inputPtr;
                char* endPtr = inputPtr + getLength(word);

                *startPtr++ = '1';

                while(*endPtr) {
                    *startPtr++ = (char)*endPtr++;
                }
                *endPtr = '\0';
            }

            inputPtr++;
        }
    }

    int resultLength = getLength(input);

    char* resultStr = intToStr(resultLength);

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

_Bool isSame(char* str, char* word) {
    _Bool isSame = 1;

    while(*str && *word) {
        char ch1 = *str++;
        char ch2 = *word++;
        if(ch1 != ch2) {
            isSame = 0;
            break;
        }
    }

    return isSame;
}

int getLength(char* str) {
    int len = 0;
    while(isBlank(*str++) != 1) {
        len++;
    }

    return len;
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
