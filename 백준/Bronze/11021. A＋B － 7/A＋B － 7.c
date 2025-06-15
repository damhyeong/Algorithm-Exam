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
 *
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	346734	171149	147064	49.176%

문제
---
두 정수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.

입력
---
첫째 줄에 테스트 케이스의 개수 T가 주어진다.

각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
---
각 테스트 케이스마다 "Case #x: "를 출력한 다음, A+B를 출력한다.

테스트 케이스 번호는 1부터 시작한다.

예제 입력 1
5
1 1
2 3
3 4
9 8
5 2
예제 출력 1
Case #1: 2
Case #2: 5
Case #3: 7
Case #4: 17
Case #5: 7
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

typedef struct StringBuilder {
    struct StringBuilder* this;

    int size;
    int currIdx;

    char* str;
    char* strPtr;

    struct StringBuilder* (*append)(struct StringBuilder* this, const char* newStr);
    char* (*to_string)(struct StringBuilder* this);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
void DelStringBuilder(StringBuilder* this);

StringBuilder* append_sb(StringBuilder* this, const char* newStr);
char* to_string_sb(StringBuilder* this);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main (void) {
    char input[255];

    StringBuilder* sb = NewStringBuilder();

    fgets(input, sizeof(input), stdin);

    int loop = parseInt(input);

    int currLoop = 0;

    while(++currLoop <= loop) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int numResult = 0;

        while(*tokensPtr) {
            numResult += parseInt(*tokensPtr++);
        }
        freeTokens(tokens);

        sb->append(sb, "Case #")
            ->append(sb, intToStr(currLoop))
            ->append(sb, ": ")
            ->append(sb, intToStr(numResult))
            ->append(sb, "\n");
    }

    fputs(sb->to_string(sb), stdout); fputc('\n', stdout);

    DelStringBuilder(sb);

    return 0;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));

    sb->this= sb;

    sb->size = 2;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    sb->str[sb->size] = '\0';

    sb->strPtr = (char*)sb->str;

    sb->append = append_sb;
    sb->to_string = to_string_sb;

    return sb;
}

void DelStringBuilder(StringBuilder* this) {
    free(this->str);
    free(this);
}

StringBuilder* append_sb(StringBuilder* this, const char* newStr) {
    char* newStrPtr = (char*)newStr;

    while(*newStrPtr) {
        *this->strPtr++ = *newStrPtr++;
        this->currIdx++;

        if(this->currIdx == this->size) {
            this->size *= 2;

            this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
            this->str[this->size] = '\0';
            this->strPtr = (char*)(this->str + this->currIdx);
        }
    }
    *this->strPtr = '\0';

    return this;
}

char* to_string_sb(StringBuilder* this) {
    *this->strPtr = '\0';
    return this->str;
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
            newTkn[tknSize] = '\0';
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr = input[tknIdx++];
            }

            *tokensPtr++ = (char*)newTkn; currSize++;

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
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
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
    if(ch == 32 || ch == '\0'){
        return 1;
    } else if( ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
