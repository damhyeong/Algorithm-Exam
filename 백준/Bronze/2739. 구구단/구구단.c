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
1 초	128 MB	507849	254565	210618	50.498%

문제
---
N을 입력받은 뒤, 구구단 N단을 출력하는 프로그램을 작성하시오. 출력 형식에 맞춰서 출력하면 된다.

입력
---
첫째 줄에 N이 주어진다. N은 1보다 크거나 같고, 9보다 작거나 같다.

출력
---
출력형식과 같게 N*1부터 N*9까지 출력한다.

예제 입력 1
2
예제 출력 1
2 * 1 = 2
2 * 2 = 4
2 * 3 = 6
2 * 4 = 8
2 * 5 = 10
2 * 6 = 12
2 * 7 = 14
2 * 8 = 16
2 * 9 = 18
*/

/**
C 에서의 최소 라이브러리를 이용한

프로그램 입출력,
입력 문자열 토큰화,
문자열 숫자화,
수 문자화,
메모리 관리 등등을 직접 다루었다.

그러나, 조금 아쉬운 것이 바로 출력 부분이다.

현재는 fputs, fputc 를 이용하여 직접 출력하고 있지만,

Java 의 StringBuilder 처럼 사용 할 수 있는 방법은 없나 생각하고 있었다.

마침, 구구단을 출력하는 문제가 나왔으니, 이번에 문자열 빌더 struct 를 만들어 보면서 struct 를 익힐 계획이다.
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

typedef struct StringBuilder {
    // this 포인터를 의미
    struct StringBuilder* this;

    // 보유 문자열
    char* str;
    // 현재 가르키는 문자열 인덱스
    char* strPtr;
    // 현재 할당한 사이즈
    int size;
    // 현재 인덱스
    int currIdx;
    // 내부 문자열 추가
    void (*append)(struct StringBuilder* this, char* newStr);

    char* (*to_string)(struct StringBuilder* this);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
void append_sb(struct StringBuilder *this, char* newStr);
char* to_string_sb(struct StringBuilder* this);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int num = parseInt(input);

    StringBuilder *sb = NewStringBuilder();

    for(int i = 1; i < 10; i++) {

        sb->append(sb, intToStr(num));
        sb->append(sb, " * ");
        sb->append(sb, intToStr(i));
        sb->append(sb, " = ");
        sb->append(sb, intToStr(num * i));
        sb->append(sb, "\n");
    }

    char* result = sb->to_string(sb);

    fputs(result, stdout);

    free(sb->str);
    free(sb);

    return 0;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));
    sb->this = sb;

    sb->size = 2;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    sb->str[sb->size] = '\0';

    sb->strPtr = (char*)sb->str;

    sb->append = append_sb;

    sb->to_string = to_string_sb;

    return sb;
}

void append_sb(struct StringBuilder *this, char* newStr) {
    while(*newStr) {
        *this->strPtr++ = *newStr++;

        this->currIdx++;

        if(this->currIdx == this->size) {
            this->size *= 2;
            this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
            this->str[this->size] = '\0';
            this->strPtr = (char*)(this->str + this->currIdx);
        }
    }
    *this->strPtr = '\0';
}

char* to_string_sb(struct StringBuilder* this) {
    // 마지막 표시는 해 주고 반환
    *this->strPtr = '\0';
    return this->str;
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
        len++;
        temp /= 10;
    } while(temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;
    char* result = (char*)malloc(size + 1);
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
        target /= 10;
    }
    if(sign == -1) {
        result[0] = '-';
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
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
