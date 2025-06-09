/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.

    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!
*/

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	477828	243880	209193	51.179%
문제
(A+B)%C는 ((A%C) + (B%C))%C 와 같을까?

(A×B)%C는 ((A%C) × (B%C))%C 와 같을까?

세 수 A, B, C가 주어졌을 때, 위의 네 가지 값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 A, B, C가 순서대로 주어진다. (2 ≤ A, B, C ≤ 10000)

출력
첫째 줄에 (A+B)%C, 둘째 줄에 ((A%C) + (B%C))%C, 셋째 줄에 (A×B)%C, 넷째 줄에 ((A%C) × (B%C))%C를 출력한다.

예제 입력 1
5 8 4
예제 출력 1
1
1
0
0
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

char* intToStr(int target);
char** tokenizer(const char* input);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main() {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int A = parseInt(*tokensPtr);
    tokensPtr++;
    int B = parseInt(*tokensPtr);
    tokensPtr++;
    int C = parseInt(*tokensPtr);

    char** freeTokens = (char**)tokens;
    while(*freeTokens) {
        free(*freeTokens);
        freeTokens++;
    }
    free(tokens);

    // 첫째 줄에 (A+B)%C, 둘째 줄에 ((A%C) + (B%C))%C, 셋째 줄에 (A×B)%C, 넷째 줄에 ((A%C) × (B%C))%C를 출력한다.
    int num1 = (A + B) % C;
    int num2 = ((A % C) + (B % C)) % C;
    int num3 = (A * B) % C;
    int num4 = ((A % C) * (B % C)) % C;

    char* result1 = intToStr(num1);
    char* result2 = intToStr(num2);
    char* result3 = intToStr(num3);
    char* result4 = intToStr(num4);

    fputs(result1, stdout);
    fputc('\n', stdout);
    fputs(result2, stdout);
    fputc('\n', stdout);
    fputs(result3, stdout);
    fputc('\n', stdout);
    fputs(result4, stdout);
    fputc('\n', stdout);

    free(result1); free(result2); free(result3); free(result4);

    return 0;
}

char* intToStr(int target){
    int len = 0;
    int sign = 1;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    int temp = target;

    do {
        temp /= 10;
        len++;
    } while(temp != 0);

    char* result;

    int size = 0;
    int endIdx = 0;
    int startIdx = 0;

    if(sign == -1) {
        size = len + 1;
        result = (char*)malloc(sizeof(char) * (size + 1));

        result[0] = '-';
        startIdx = 1; endIdx = size;
    } else {
        size = len;
        result = (char*)malloc(sizeof(char) * (size + 1));

        startIdx = 0; endIdx = size;
    }
    result[endIdx] = '\0';

    for(int i = endIdx - 1; i >= startIdx; i--) {
        int extract = target % 10;
        target /= 10;

        result[i] = extract + '0';
    }

    return result;
}

char** tokenizer(const char* input){
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;

    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr;

        inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            newTkn[tknSize] = '\0';
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr = input[tknIdx++];
                newTknPtr++;
            }

            *tokensPtr = newTkn;
            tokensPtr++; currSize++;

            tknIdx = ++currIdx;

            if(currSize == size) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)tokens[currSize];
            }
        } else {
            currIdx++;
        }
    }

    tokens[currSize] = NULL;

    return tokens;
}

int parseInt(const char* str){
    int result = 0;
    int sign = 1;

    char* strPtr = (char*)str;
    while(*strPtr) {
        result *= 10;
        result += *strPtr - '0';
        strPtr++;
    }

    return result * sign;
}

_Bool isBlank(char ch){
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
