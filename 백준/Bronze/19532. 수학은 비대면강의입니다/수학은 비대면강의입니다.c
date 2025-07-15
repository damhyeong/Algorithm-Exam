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
1 초 (추가 시간 없음)	1024 MB	57029	28985	25165	51.137%

문제
---
수현이는 4차 산업혁명 시대에 살고 있는 중학생이다.

코로나 19로 인해, 수현이는 버추얼 학교로 버추얼 출석해 버추얼 강의를 듣고 있다.

수현이의 버추얼 선생님은 문자가 2개인 연립방정식을 해결하는 방법에 대해 강의하고, 다음과 같은 문제를 숙제로 냈다.

다음 연립방정식에서 x 와 y 의 값을 계산하시오.

{ ax + by = c
{ dx + ey = f


4차 산업혁명 시대에 숙제나 하고 앉아있는 것보다 버추얼 친구들을 만나러 가는 게 더 가치있는 일이라고 생각했던 수현이는 이런 연립방정식을 풀 시간이 없었다.

다행히도, 버추얼 강의의 숙제 제출은 인터넷 창의 빈 칸에 수들을 입력하는 식이다.

각 칸에는 -999 이상 999 이하의 정수만 입력할 수 있다.

수현이가 버추얼 친구들을 만나러 버추얼 세계로 떠날 수 있게 도와주자.

입력
---
정수 a, b, c, d, e, f 가 공백으로 구분되어 차례대로 주어진다.

(-999 <= a, b, c, d, e, f <= 999)

문제에서 언급한 방정식을 만족하는 (x, y) 가 유일하게 존재하고,

이 때 x 와 y 가 각각 -999 이상 999 이하의 정수인 경우만 입력으로 주어짐이 보장된다.


출력
---
문제의 답인 x 와 y 를 공백으로 구분해 출력한다.

예제 입력 1
1 3 -1 4 1 7
예제 출력 1
2 -1
예제 입력 2
2 5 8 3 -4 -11
예제 출력 2
-1 2
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int a = parseInt(*tokensPtr++);
    int b = parseInt(*tokensPtr++);
    int c = parseInt(*tokensPtr++);
    int d = parseInt(*tokensPtr++);
    int e = parseInt(*tokensPtr++);
    int f = parseInt(*tokensPtr++);

    freeTokens(tokens);

    int resultX = -10001;
    int resultY = -10001;

    int x = -999;
    while(x <= 999) {
        int y = -999;
        while(y <= 999) {

            _Bool condition1 = ((a * x) + (b * y)) == c ? 1 : 0;
            _Bool condition2 = ((d * x) + (e * y)) == f ? 1 : 0;

            if(condition1 == 1 && condition2 == 1) {
                resultX = x; resultY = y;
                break;
            }

            y++;
        }
        if(resultX != -10001) {
            break;
        }

        x++;
    }

    char* resultStrX = intToStr(resultX);
    char* resultStrY = intToStr(resultY);

    fputs(resultStrX, stdout); fputc(' ', stdout); fputs(resultStrY, stdout); fputc('\n', stdout);

    free(resultStrX); free(resultStrY);

    return 0;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;

    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            char* newTknPtr = (char*)newTkn;
            *(newTknPtr + tknSize) = 0;

            while(tknIdx != currIdx){
                *newTknPtr++ = input[tknIdx++];
            }

            *tokensPtr++ = newTkn; currSize++;

            tknIdx = ++currIdx;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            currIdx++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        free(*tokensPtr++);
    }
    free(tokens);

    return;
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
