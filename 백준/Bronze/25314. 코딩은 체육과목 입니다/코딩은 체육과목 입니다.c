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
0.5 초 (추가 시간 없음)	1024 MB (추가 메모리 없음)	125827	79272	70874	63.499%
문제


오늘은 혜아의 면접 날이다. 면접 준비를 열심히 해서 앞선 질문들을 잘 대답한 혜아는 이제 마지막으로 칠판에 직접 코딩하는 문제를 받았다. 혜아가 받은 문제는 두 수를 더하는 문제였다. C++ 책을 열심히 읽었던 혜아는 간단히 두 수를 더하는 코드를 칠판에 적었다. 코드를 본 면접관은 다음 질문을 했다. “만약, 입출력이
$N$바이트 크기의 정수라면 프로그램을 어떻게 구현해야 할까요?”

혜아는 책에 있는 정수 자료형과 관련된 내용을 기억해 냈다. 책에는 long int는
$4$바이트 정수까지 저장할 수 있는 정수 자료형이고 long long int는
$8$바이트 정수까지 저장할 수 있는 정수 자료형이라고 적혀 있었다. 혜아는 이런 생각이 들었다. “int 앞에 long을 하나씩 더 붙일 때마다
$4$바이트씩 저장할 수 있는 공간이 늘어나는 걸까? 분명 long long long int는
$12$바이트, long long long long int는
$16$바이트까지 저장할 수 있는 정수 자료형일 거야!” 그렇게 혜아는 당황하는 면접관의 얼굴을 뒤로한 채 칠판에 정수 자료형을 써 내려가기 시작했다.

혜아가
$N$바이트 정수까지 저장할 수 있다고 생각해서 칠판에 쓴 정수 자료형의 이름은 무엇일까?

입력
첫 번째 줄에는 문제의 정수
$N$이 주어진다.
$(4\le N\le 1\, 000$;
$N$은
$4$의 배수
$)$ 

출력
혜아가
$N$바이트 정수까지 저장할 수 있다고 생각하는 정수 자료형의 이름을 출력하여라.

예제 입력 1
4
예제 출력 1
long int
예제 입력 2
20
예제 출력 2
long long long long long int
노트
출력에서 long과 long, long과 int 사이에는 공백이 하나씩 들어간다.

실제로 C++에서 각 정수 자료형이 저장할 수 있는 수의 크기는 환경에 따라 달라질 수 있다. 덧붙여, 실제로 문제 내용과 같이 long long long int와 같은 자료형을 사용한 코드를 GCC의 C++ 컴파일러를 사용해 컴파일하려고 할 경우 'long long long' is too long for GCC라는 에러 메시지와 함께 컴파일되지 않는다.
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

StringBuilder* NewStringBuilder (void);
void DeleteStringBuilder(StringBuilder* this);
StringBuilder* append_sb(StringBuilder* this, const char* newStr);
char* to_string_sb(StringBuilder* this);

int parseInt(const char* str);
_Bool isBlank(char ch);

int main (void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int byte = parseInt(input);

    StringBuilder* sb = NewStringBuilder();

    while(byte > 0) {
        sb->append(sb, "long ");
        byte -= 4;
    }
    sb->append(sb, "int\n");

    fputs(sb->to_string(sb), stdout);

    DeleteStringBuilder(sb);

    return 0;
}

StringBuilder* NewStringBuilder (void) {
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

void DeleteStringBuilder(StringBuilder* this) {
    free(this->str);
    free(this);
}

StringBuilder* append_sb(StringBuilder* this, const char* newStr) {
    char* newStrPtr = (char*)newStr;

    while(*newStrPtr) {
        *this->strPtr++ = *newStrPtr++; this->currIdx++;

        if(this->size == this->currIdx) {
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

int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
