/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com
*/

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	372370	282351	246621	76.620%
문제
두 정수 A와 B를 입력받은 다음, A×B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
첫째 줄에 A×B를 출력한다.

예제 입력 1
1 2
예제 출력 1
2
예제 입력 2
3 4
예제 출력 2
12
 */

#include<stdio.h>

extern void* malloc(size_t);
extern void* realloc(void*, size_t);
extern void free(void*);

char** tokenizer(const char* str);

int parseInt(const char* token);
int chToInt(char ch);
_Bool isBlank(char ch);

int main () {
    // 정적 배열 생성 (input 용)
    char inputs[255];

    // str 에 문장 시작 주소 입력됨.
    char *str = fgets(inputs, sizeof(inputs), stdin);

    // 결과값으로 하나의 문자 배열에서 나누어진 토큰(문자 배열) 을 가지는 주소의 배열을 반환한다.
    // 즉, 단순한 2차원 배열이 아니라, 각 문자 배열의 시작 주소를 가지는 1차원 주소 배열이라는 의미이다.
    char** tokens = tokenizer(str);

    // 첫 번째 수는 기본 수로 만든다.
    int baseNum = parseInt(*tokens);
    tokens++;

    // 모든 토큰 수를 곱한다. 끝날 때 까지
    while(*tokens != NULL) {
        int tempNum = parseInt(*tokens);

        baseNum *= tempNum;

        tokens++;
    }

    printf("%d\n", baseNum);
}

char** tokenizer(const char* str) {
    // 토큰의 기본 사이즈는 5 로 설정하고, 추후 찬다면 * 2 하면서 용량을 늘림.
    int size = 5;

    // 결과로 내보낼 토큰 동적 메모리 할당 - (+ 1 하여 마지막에 종료 처리를 한다.)
    char** tokens = (char**)malloc(sizeof(char*) * 5 + 1);
    // 마지막 요소에는 종료를 알림.
    tokens[size] = NULL;

    // 토큰을 넣을 장소를 알려줄 포인터.(순회용)
    char** tokensPtr = (char**) tokens;

    // 주어진 문장을 순회할 포인터를 따로 생성.
    char* strPtr = (char*) str;

    // 현재 탐색 인덱스
    int currIdx = 0;
    // 현재 토큰 시작 인덱스
    int startIdx = 0;

    // 이제부터 문자 순회 시작
    while(strPtr[currIdx]) {
        // 현재 탐색 문자를 추출한다.
        char currCh = strPtr[currIdx];

        // 만약에, 현재 문자가 빈 칸을 의미하는 문자에 해당한다면,
        if(isBlank(currCh) == 1) {

            // 토큰 시작 인덱스와, 탐색 인덱스가 동일하다면, 토큰이 시작할 수 없으므로, 둘 다 전진한다.
            if(currIdx == startIdx) {
                currIdx++; startIdx++;
                // 건너뛰기
                continue;
            }

            // 하나의 토큰이 어디부터 어디까지인지 파악이 된 상태이다. (토큰 시작 != 현재 인덱스)
            int newTokenSize = currIdx - startIdx;
            // 파악된 크기만큼 동적 할당
            char* newToken = (char*)malloc(sizeof(char) * newTokenSize + 1);
            char* newTokenPtr = (char*)newToken;
            // 마지막 인덱스에 종료를 알리는 문자를 넣는다.
            newToken[newTokenSize] = '\0';

            // 현재 토큰이 마무리 될 때 까지 진행
            while(startIdx != currIdx) {
                // 토큰 시작 인덱스가 현재 인덱스와 동일해 질 때 까지, 문자 단위로 추출하여 넣는다.
                *newTokenPtr = strPtr[startIdx];
                // 각 주소 이동
                startIdx++; newTokenPtr++;
            }

            // 생성된 토큰의 문자열이 완성되었으므로, 이를 토큰들을 담고 있는 배열에 넣는다.
            *tokensPtr = newToken;
            tokensPtr++;

            // 만약 토큰들을 담는 주소의 배열이 마지막에 다다랐다면,
            if(tokensPtr == NULL) {
                // 사이즈를 2 배로 키운다.
                size *= 2;
                // 다시 토큰들 주소에 재할당한다.
                tokens = (char**)realloc(tokens, size + 1);
                // 다시 마지막에 NULL 을 넣는다.
                tokens[size] = NULL;
            }

            // 현재 탐색 인덱스는 빈 칸이니, 그 다음 칸으로 이동.
            // 그리고 토큰 파싱을 마쳤으니, 토큰 시작 인덱스를 현재 탐색 인덱스와 동일화.
            currIdx++; startIdx = currIdx;

        } else { // 현재 문자가 정식 문자라면.(물론 숫자 문자)
            currIdx++;
        }
    }

    // 마지막 토큰이 추출되지 않은 상황
    if(startIdx != currIdx) {
        // 마지막 토큰에 대한 길이를 측정
        int byte = currIdx - startIdx;

        // 마지막 토큰을 담을 문자 배열 생성
        char* lastToken = (char*) malloc(sizeof(char) * byte + 1);
        // 끝을 알리기 위한 일종의 NULL 역할 문자 삽입
        lastToken[byte] = '\0';
        // 순회하기 위한 포인터 생성 - lastToken 은 return 될 결과값에 들어가야 함!
        char* lastTokenPtr = lastToken;

        // 마지막으로 생성된 문자 배열의 마지막까지 순회
        while(lastTokenPtr) {
            // 토큰 시작 인덱스를 중점으로, 마지막 문자 배열에 하나씩 넣기
            *lastTokenPtr = strPtr[startIdx];

            // 주소 이동
            lastTokenPtr++; startIdx++;
        }

        // 마지막 토큰을 결과값에 넣기
        *tokensPtr = lastToken;
        tokensPtr++;
    }

    *tokensPtr = NULL;

    return tokens;
}

int parseInt(const char* token) {
    // 결과값
    int result = 0;
    // + 인지, - 인지.
    unsigned short sign = 1;

    char* tokenPtr = (char*) token;

    char firstCh = *token;

    if(firstCh == '-') {
        sign = -1;
        tokenPtr++;
    } else if(firstCh == '+'){
        tokenPtr++;
    }

    // 토큰이 끝날 때 까지 계산
    while(*tokenPtr) {
        // 새로운 수를 넣기 위해 첫 번쨰 수 공간 창출
        result *= 10;

        // 현재 문자를 수로 변환
        int currDigit = chToInt(*tokenPtr);

        // 결과 수에 현재 문자수를 더함
        result += currDigit;

        // 포인터 다음으로 이동
        tokenPtr++;
    }

    return result * sign;
}

int chToInt(char ch) {
    if(ch >= '0' && ch <= '9') {
        return ch - '0';
    } else {
        return -1;
    }
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
