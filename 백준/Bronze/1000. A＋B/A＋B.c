#include<stdio.h>

extern void *malloc(size_t);
extern void free(void *);

// C 시스템을 위해 미리 함수 선언
int parseInt(char* origin);
int parseDigit(char ch);
int isDigit(char ch);
char** tokenizer(char* str);
int isSpace(char ch);
char* trim(char* str);

int main () {
    char str[255];

    int result = 0;

    // str 배열에 한 줄의 입력을 전부 담음.
    fgets(str, sizeof(str), stdin);

    char* newStr = trim(str);

    char** tokens = tokenizer(newStr);
    char** tokenPtr = tokens;

    while(*tokenPtr) {
        result += parseInt(*tokenPtr);
        tokenPtr++;
    }

    printf("%d\n", result);

    char** p = tokens;
    while(*p) {
        free(*p);
        p++;
    }
    free(tokens);

    return 0;
}

/**
origin 의 시작은 빈칸이 아니라, 토큰에 해당하는 문자열이 와야 한다.
*/
int parseInt(char* origin) {
    // 리턴하게 될 결과
    int target = 0;
    // - or +
    int sign = 1;

    // 만약 첫 번째 부분에 - 가 있다면, 부호를 바꾼다.
    if(*origin == '-'){
        sign = -1;
        origin++;
    } else if(*origin == '+') { // '+' 는 있을 수도, 없을 수도 있다.
        sign = 1;
        origin++;
    }

    /**
    문자열 배열이 끝나지 않으며, *origin != '\0'
    현재 문자 배열 하나가 숫자를 의미할 경우 반복한다.
    isDigit 에 숫자가 아닌 것이 들어간다면, NULL 이 반환된다.
    */
    while(*origin && isDigit(*origin)) {
        // 현재 지정된 문자열을 숫자로 바꾼다.
        int currNum = parseDigit(*origin);

        // 새로운 수를 넣어야 하므로, 기존의 값을 10 곱해 공간을 만들고, 현재 수를 더한다.
        target = (target * 10) + currNum;

        // 그 다음 문자로 이동
        origin++;
    }

    return target * sign;
}

int parseDigit(char ch) {
    // 만약 숫자가 아니라면 NULL 을 반환한다. - 다양한 용도로 사용 가능할듯 (EX - Token)
    if(isDigit(ch) == 0) {
        return -1;
    }

    return ch - '0';
}

/**
    @Param : 숫자로 예상되는 문자를 입력한다.
    @Return :  '0' 과 '9' 아스키 코드 사이에 있는지 판별한다.
*/
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9') ? 1 : 0;
}

/**
    @Param
        - str : 나눌 문장
    @Return
        - char** : 토큰들이 담겨 있는 char** 2차원 배열
*/
char** tokenizer(char* str) {
    // 초기 사이즈 5로 지정
    int size = 5;

    // 5 개의 문자열 주소를 가지는 tokens 2 차원 배열 선언.
    char** tokens = malloc(sizeof(char*) * size);
    char** tokensAddr = tokens;

    // 현재 문자 주소를 처음 받은 문자열 변수로부터 할당 (복사)
    char* currCh = str;

    // 현재 가르키는 문자열이 끝나지 않을 때 까지 진행
    while(*currCh) {

        // 만약 현재 문자가 빈 칸을 의미한다면. (ASCII 32 or 9 ~ 13)
        if(isSpace(*currCh) == 1) {

            // 직전에 토큰화가 끝났거나, 처음 시작 시에 분리자가 나왔다면, 이는 건너 뛰어야 한다.
            if(str == currCh) {
                str++; currCh++;
                continue;
            }

            // "바이트" 가 반환된다.
            int byte = currCh - str;
            // byte 와 size 가 결국 같긴 하지만, 가독성을 위해 추가함
            int size = byte / sizeof(char);


            // 현재 시작 문자로부터 delim 까지의 거리를 계산하여 문자열 배열 생성
            char* newToken = malloc(sizeof(char) * size + 1);
            char* token = newToken;

            // str 이 delim 위치인 currCh 도달 할 때 까지 진행
            while(str != currCh) {
                // 주소 복사 자체를 방지하기 위해 복사 후 insert 진행
                char ch = *str;
                *newToken = ch;

                str++; newToken++;
            }
            // 마지막에 종료 알림
            *newToken = '\0';

            // 현재 토큰 주소에 newToken 문자열 시작 주소 배치
            *tokens = token;

            // 토큰 주소 1칸 이동.
            tokens++;

            // 현재 문자 인덱스를 한 칸 이동한 후, 시작 str 인덱스를 동일화.
            currCh++; str = currCh;
        } else {
            currCh++;
        }
    }


    // 만약 모든 것이 끝난 후, 문자열 토큰 시작 idx 인 str 과, 모든 문자를 훑는 currCh 의 주소가 다르다면,
    // 이는 마지막 토큰이 추출되지 않음을 의미한다. EX - "Hello World" 가 있다면, "World" 가 파싱이 되지 않은 것.
    if(str != currCh) {
        // 마지막 토큰의 길이
        size_t byte = currCh - str;

        int size = byte / sizeof(char);

        // 마지막에 '\0' 을 넣기 위해 size + 1 을 수행
        char* lastToken = malloc(sizeof(char) * size + 1);
        // lastToken 은 문자열 순회를 위한 포인터로서 작용
        char* tempAddr = lastToken;

        while(str != currCh) {
            char ch = *str;
            *lastToken = ch;
            str++; lastToken++;
        }
        *lastToken = '\0';

        *tokens = tempAddr;
    }

    tokens++;

    *tokens = NULL;

    return tokensAddr;
}

/**
    @Param
        - str : 앞뒤 공백을 제거하고자 하는 문자열 배열
    @Return
        - char* : 공백 없는 시작 지점 주소, 그리고 뒷 부분은 '\0' 으로 초기화되어 마지막이라고 인식함.
*/
char* trim(char* str) {
    // 현재 주어진 str 문자열이 빈 칸이라면 지속적으로 앞으로 주소를 이동한다.
    while(isSpace(*str) == 1) {
        // 메모리 잔여물 없도록 초기화.
        *str = '\0';
        str++;
    }

    // 앞 부분 trim 완료.

    // 마지막까지 순회하기 위한 문자 포인터 생성 및 copy
    char* end = str + 1;


    // 배열의 끝에 도달 할 때 까지 이동 - string.h 의 strlen 과 비용이 동일
    while(*end != '\0') {
        end++;
    }

    // 현재 *end 는 마지막인 '\0' 을 가르키고 있다. 따라서, 바로 이전 문자인 *end - 1 로 주소를 이동
    end -= 1;

    // 마지막 포인터가 다시 앞으로 오면서, 공백 문자를 '\0' = NULL 로 바꿔버린다.
    while(isSpace(*end) == 1) {
        *end = '\0';
        end--;
    }

    // 이 상태에서는 앞뒤 공백이 모두 삭제됨.

    // 공백없는 시작점이며, 뒷 부분도 다듬어져 있는 결과물 전달
    return str;
}

int isSpace(char ch) {
    // 단순 빈칸 - 아스키 32 라고 한다.
    if(ch == ' '){
        return 1;
    } else if(ch >= 9 && ch <= 13) { // 기존 라이브러리는 9 에서 13 에 해당하는 빈칸 아스키 코드들을 감지한다. \n, \b, .... 등등
        return 1;
    } else {
        return 0;
    }
}
