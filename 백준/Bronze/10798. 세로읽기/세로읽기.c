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
1 초	256 MB	109479	52253	44256	47.918%

문제
---
아직 글을 모르는 영석이가 벽에 걸린 칠판에 자석이 붙어있는 글자들을 붙이는 장난감을 가지고 놀고 있다.

이 장난감에 있는 글자들은 영어 대문자 ‘A’부터 ‘Z’, 영어 소문자 ‘a’부터 ‘z’, 숫자 ‘0’부터 ‘9’이다.

영석이는 칠판에 글자들을 수평으로 일렬로 붙여서 단어를 만든다.

다시 그 아래쪽에 글자들을 붙여서 또 다른 단어를 만든다.

이런 식으로 다섯 개의 단어를 만든다.

아래 그림 1은 영석이가 칠판에 붙여 만든 단어들의 예이다.

A A B C D D
a f z z
0 9 1 2 1
a 8 E W g 6
P 5 h 3 k x
<그림 1>

한 줄의 단어는 글자들을 빈칸 없이 연속으로 나열해서 최대 15개의 글자들로 이루어진다.

또한 만들어진 다섯 개의 단어들의 글자 개수는 서로 다를 수 있다.

심심해진 영석이는 칠판에 만들어진 다섯 개의 단어를 세로로 읽으려 한다.

세로로 읽을 때, 각 단어의 첫 번째 글자들을 위에서 아래로 세로로 읽는다.

다음에 두 번째 글자들을 세로로 읽는다.

이런 식으로 왼쪽에서 오른쪽으로 한 자리씩 이동 하면서 동일한 자리의 글자들을 세로로 읽어 나간다.

위의 그림 1의 다섯 번째 자리를 보면 두 번째 줄의 다섯 번째 자리의 글자는 없다.

이런 경우처럼 세로로 읽을 때 해당 자리의 글자가 없으면, 읽지 않고 그 다음 글자를 계속 읽는다.

그림 1의 다섯 번째 자리를 세로로 읽으면 D1gk로 읽는다.

그림 1에서 영석이가 세로로 읽은 순서대로 글자들을 공백 없이 출력하면 다음과 같다:

Aa0aPAf985Bz1EhCz2W3D1gkD6x

칠판에 붙여진 단어들이 주어질 때, 영석이가 세로로 읽은 순서대로 글자들을 출력하는 프로그램을 작성하시오.

입력
---
총 다섯줄의 입력이 주어진다. 각 줄에는 최소 1개, 최대 15개의 글자들이 빈칸 없이 연속으로 주어진다. 주어지는 글자는 영어 대문자 ‘A’부터 ‘Z’, 영어 소문자 ‘a’부터 ‘z’, 숫자 ‘0’부터 ‘9’ 중 하나이다. 각 줄의 시작과 마지막에 빈칸은 없다.

출력
---
영석이가 세로로 읽은 순서대로 글자들을 출력한다. 이때, 글자들을 공백 없이 연속해서 출력한다.

예제 입력 1
ABCDE
abcde
01234
FGHIJ
fghij
예제 출력 1
Aa0FfBb1GgCc2HhDd3IiEe4Jj
예제 입력 2
AABCDD
afzz
09121
a8EWg6
P5h3kx
예제 출력 2
Aa0aPAf985Bz1EhCz2W3D1gkD6x
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct String {
    int size;
    int length;

    char* str;

    char* (*to_string)(struct String* this);
} String;

String* NewString(const char* initStr);
void DeleteStrings(String** strings);
char* to_string_str(String* this);

typedef struct StringBuilder {
    int size;
    int currIdx;

    char* str;
    char* strPtr;

    struct StringBuilder* (*append_ch)(struct StringBuilder* this, char newCh);
    char* (*to_string)(struct StringBuilder* this);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
void DeleteStringBuilder(StringBuilder* this);
StringBuilder* append_ch_sb(StringBuilder* this, char newCh);
char* to_string_sb(StringBuilder* this);

_Bool isBlank(char ch);


int main(void) {
    char input[255];

    String** stringList = (String**)malloc(sizeof(String*) * (5 + 1));
    *(stringList + 5) = NULL;
    String** stringListPtr = (String**)stringList;

    while(fgets(input, sizeof(input), stdin) != NULL) {
        *stringListPtr++ = NewString(input);
    }

    StringBuilder* sb = NewStringBuilder();

    int avaliable = 0;
    int index = 0;
    do {
        stringListPtr = (String**)stringList;
        avaliable = 0;

        while(*stringListPtr != NULL) {
            String* currString = *stringListPtr++;

            if(currString->length <= index) {
                continue;
            }
            char addCh = *(currString->str + index);

            sb->append_ch(sb, addCh);
            avaliable++;
        }
        ++index;
    } while(avaliable != 0);

    fputs(sb->to_string(sb), stdout); fputc('\n', stdout);

    DeleteStrings(stringList);
    DeleteStringBuilder(sb);

    return 0;
}

String* NewString(const char* initStr) {
    String* string = (String*)malloc(sizeof(String));

    char* initStrPtr = (char*)initStr;

    int size = 0;
    while(isBlank(*initStrPtr++) != 1) {
        size++;
    }

    char* str = (char*)malloc(sizeof(char) * (size + 1));
    *(str + size) = 0;

    initStrPtr = (char*)initStr;
    int idx = 0;
    while(idx < size) {
        *(str + idx++) = *initStrPtr++;
    }

    string->str = str;
    string->length = size;
    string->to_string = to_string_str;

    return string;
}

void DeleteStrings(String** strings) {
    String** stringsPtr = (String**)strings;
    while(*stringsPtr) {
        String* currString = *stringsPtr++;
        free(currString->str);
        free(currString);
    }
    free(strings);

    return;
}
char* to_string_str(String* this) {
    return this->str;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));

    sb->size = 2;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    *(sb->str + sb->size) = 0;
    sb->strPtr = (char*)sb->str;

    sb->append_ch = append_ch_sb;
    sb->to_string = to_string_sb;

    return sb;
}
void DeleteStringBuilder(StringBuilder* this) {
    free(this->str);
    free(this);
}

StringBuilder* append_ch_sb(StringBuilder* this, char newCh) {
    *this->strPtr++ = newCh; this->currIdx++;

    if(this->currIdx == this->size) {
        this->size *= 2;
        this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
        *(this->str + this->size) = 0;
        this->strPtr = (char*)(this->str + this->currIdx);
    }

    return this;
}
char* to_string_sb(StringBuilder* this) {
    *this->strPtr = 0;
    return this->str;
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
