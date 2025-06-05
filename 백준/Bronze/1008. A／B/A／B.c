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
2 초	128 MB	872353	296109	244527	34.468%
문제
두 정수 A와 B를 입력받은 다음, A/B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
첫째 줄에 A/B를 출력한다. 실제 정답과 출력값의 절대오차 또는 상대오차가 10-9 이하이면 정답이다.

예제 입력 1
1 3
예제 출력 1
0.33333333333333333333333333333333
10-9 이하의 오차를 허용한다는 말은 꼭 소수 9번째 자리까지만 출력하라는 뜻이 아니다.

예제 입력 2
4 5
예제 출력 2
0.8
 */

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

int parseInt(const char* str); // 주어진 문자열을 정수로 만든다. - 입력 파싱
char* doubleToString(double target); // 결과로 출력해야 하는 double 타입을 문자열로 만든다.

char** tokenizer(const char* str); // 입력으로 주어진 한 줄 입력을 토큰으로 만들어 주소값 배열을 반환한다.
int chToInt(char ch); // 단순한 숫자 문자 하나를 정수로 바꿔 전달한다.
_Bool isBlank(char ch); // 현재 문자가 빈 칸에 해당하는 문자인지 알려준다.


int main () {
    char chList[255];

    char* str = fgets(chList, sizeof(chList), stdin);

    char** tokens = tokenizer(str);
    char** tokensPtr = (char**)tokens;

    double baseNum = (double)parseInt(*tokensPtr);
    tokensPtr++;

    while(*tokensPtr) {
        baseNum /= (double)parseInt(*tokensPtr);
        free(*tokensPtr);
        tokensPtr++;
    }
    free(*tokens);

    char* result = doubleToString(baseNum);

    fputs(result, stdout);

    // 결과 출력으로 사용한 문자열 풀어주기
    free(result);

    // free 작업
}

int parseInt(const char* str) {
    int result = 0;
    short sign = 1;

    char* strPtr = (char*)str;

    // 음수 문자가 올 경우, 이를 따로 처리 및 저장.
    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    // 숫자 문자 앞에서부터 파싱하여 넣는다.
    while(*strPtr) {
        // 이미 계산된 수는 이번 수를 넣기 위해 공간을 창출한다.
        result *= 10;

        int currNum = chToInt(*strPtr);

        // 빈 공간에 수 넣기
        result += currNum;

        // 다음 문자로 이동
        strPtr++;
    }

    return result * (int)sign;
}



char* doubleToString(double target) {
    int sign = 1;

    if(target < 0) {
        sign = -1; target *= -1;
    }

    // 소수부를 무시한 값으로 정수 값을 추출
    int intPart = (int)target;

    // 정수부를 다시 소수부로 만들어서 정수만 빼고, 소수부만 남기기
    double doublePart = target - (double)intPart;


    // 정수 문자가 들어갈 사이즈
    int intSize = 0;
    // 정수 길이를 구하기 위한 임시 정수
    int tempInt = intPart;

    // 정수 길이를 구하기
    while(tempInt != 0) {
        tempInt /= 10;
        intSize++;
    }

    char* intStr = (char*)malloc(sizeof(char) * intSize + 1);
    intStr[intSize] = '\0';

    // 생성된 문자 배열의 마지막부터 시작하여 수를 넣는다.
    for(int i = intSize - 1; i >= 0; i--) {
        // 항상 첫 번째 자리수를 추출한다.
        int number = intPart % 10;
        // 추출한 자리수의 문자는 '0' 을 더해주면 된다.
        intStr[i] = (char)(number + '0');
        // 그리고, 모든 자리수를 하나씩 이동한다.
        intPart /= 10;
    }

    // 문제에서는 9 자리까지 맞으면 된다고 하니, 10 자리까지 정확도를 올림.
    const int MAX_SIZE = 10;

    char* doubleStr = (char*)malloc(sizeof(char) * MAX_SIZE + 1);
    doubleStr[MAX_SIZE] = '\0';


    int currDeep = 0;

    // 10 개를 넣을 예정.
    while(currDeep < MAX_SIZE) {
        // 지속적으로 각 소수부를 위로 한 칸씩 올림
        doublePart *= 10;

        // 정수가 된 소수부를 추출
        int extractNum = (int)doublePart;

        doublePart -= extractNum;

        // 이를 가지고 문자열로 형성
        doubleStr[currDeep++] = (char)(extractNum + '0');
    }

    // 정수 문자열, 소수 문자열이 전부 완료 된 상황.

    // 만약에, 정수가 애초에 0 이라서 제대로 할당이 되지 못했을 경우 (".33333" 으로 나옴)
    if(intSize == 0) {
        // 0 을 위한 공간으로 재할당
        intStr = (char*)realloc(intStr, 2);
        intStr[0] = '0';
        intStr[1] = '\0';
        // 0 이 들어갔으므로.
        intSize = 1;
    }

    // .(점) 을 넣을 공간까지 고려한 사이즈. and 마이너스 일 경우 대비
    int totalStrSize = intSize + MAX_SIZE + (sign == 1 ? 0 : 1);

    char* resultStr = (char*)malloc(sizeof(char) * totalStrSize + 1);
    resultStr[totalStrSize] = '\0';

    // 반환할 결과 문자 배열 인덱스 순회용
    int resultIdx = 0;

    // 만약 음수라면, 맨 앞에 '-' 를 붙여 음수임을 알린다.
    if(sign == -1) {
        resultStr[resultIdx] = '-';
        resultIdx++;
    }

    // 정수 문자열 순회 포인터 가져오기
    char* intStrPtr = (char*)intStr;
    char* doubleStrPtr = (char*)doubleStr;

    // 정수 문자열을 이용하여 순회
    while(*intStrPtr) {
        char ch = *intStrPtr;
        resultStr[resultIdx++] = ch;
        intStrPtr++;
    }
    // 정수 끝났으면 '.' 넣어서 소수부 준비하기
    resultStr[resultIdx++] = '.';

    // 소수 문자열을 이용하여 순회
    while(*doubleStrPtr) {
        char ch = *doubleStrPtr;
        resultStr[resultIdx++] = ch;
        doubleStrPtr++;
    }

    // 사용이 끝난 문자 배열 할당은 풀어주기
    free(intStr);
    free(doubleStr);

    return resultStr;
}

/**
 * @Param : 토큰화 할 입력 문자 배열
 *  - 앞뒤 빈칸 인식하여 파싱
 * @Return : 토큰 문자 배열의 주소들을 가지고 있는 배열 반환
 *  - 각 토큰의 시작 주소를 배열로 가지고 있음
 */
char** tokenizer(const char* str) {
    int size = 5;
    int currSize = 0;

    // 문자 순회용
    char* strPtr = (char*)str;

    // 현재 마지막에 NULL 처리를 하지 않고, 이 메서드의 마지막에 NULL 처리 한다.
    char** tokens = (char**) malloc(sizeof(char*) * size + 1);

    // 토큰 주소 순회용 포인터
    char** tokensPtr = (char**)tokens;

    int tknStartIdx = 0;
    int currIdx = 0;

    // 입력 문자 마지막까지 진행
    while(*strPtr) {
        // 현재 문자 추출
        char ch = *strPtr;

        // 바로 다음 입력 문자 인덱스로 이동
        strPtr++;

        // 만약 현재 문자가 빈칸에 해당한다면.
        if(isBlank(ch) == 1) {
            // 아직 토큰 시작점도 정해지지 않았다 ==> 토큰 시작 인덱스와 현재 탐색 인덱스가 동일.
            // 따라서, 둘 다 올리고 건너뛴다.
            if(tknStartIdx == currIdx) {
                tknStartIdx++; currIdx++;
                continue;
            }

            // 토큰 시작 위치와 탐색 위치 간의 차이를 계산.
            int tokenSize = currIdx - tknStartIdx;
            // 그 크기만큼 배열을 동적 생성
            char* newToken = (char*) malloc(sizeof(char) * tokenSize + 1);
            // 마지막에 미리 END 알림
            newToken[tokenSize] = '\0';

            // 새로 생성된 토큰 순회용
            char* newTknPtr = newToken;

            // 토큰 시작 인덱스와 현재 탐색 인덱스가 동일하지 않을 때 까지 진행 : 토큰 시작 인덱스가 하나씩 오름
            while(currIdx != tknStartIdx) {
                // 문자열의 토큰 시작 인덱스를 이동시키며, 생성된 토큰에 넣을 거임
                char ch = str[tknStartIdx];
                // 새로 생성된 토큰 인덱스에 문자 삽입
                *newTknPtr = ch;

                newTknPtr++; tknStartIdx++;
            }

            // 새로 만들어진 토큰을 토큰 배열에 넣기
            *tokensPtr = newToken;
            // 토큰 주소 배열 이동하고, 현재 토큰 주소 배열 엘리먼트 개수 표시 증가
            tokensPtr++; currSize++;

            // 토큰화를 끝냈으니, 다음 탐색 인덱스로 이동
            currIdx++;

            // 다시 토큰 시작 인덱스와 탐색 인덱스를 동일시 한다 - 토큰화가 끝났으므로
            tknStartIdx = currIdx;

            // 만약에, 현재 토큰 주소 배열이 꽉 찼다면, 2 배로 길이를 늘려서 다시 할당한다.
            if(currSize == size) {
                // 2 배로 길이를 늘린 토큰 주소 배열 할당
                tokens = (char**)realloc(tokens, sizeof(char*) * (size * 2) + 1);
                // tokensPtr 은 이전 주소를 가르키므로, 곧 토큰을 넣어야 하는 주소로 다시 할당 해 준다.

                size *= 2;

                tokensPtr = (char**) tokens[currSize];
            }
        } else { // 빈 칸이 아니라면, 탐색 인덱스는 진행한다.
            currIdx++;
        }
    }

    // 1 개의 토큰만 존재하거나, 문자열 마지막에 정확히 마지막 토큰이 존재한다면, 실행된다.
    if(tknStartIdx != currIdx) {
        int newTknSize = currIdx - tknStartIdx;
        char* lastToken = (char*)malloc(sizeof(char) * newTknSize + 1);
        lastToken[newTknSize] = '\0';

        // 순회용Ptr
        char* lastTokenPtr = lastToken;

        while(currIdx != tknStartIdx) {
            char ch = *strPtr;
            *lastTokenPtr = ch;
            lastTokenPtr++; strPtr++;
        }

        *tokensPtr = lastToken;
        tokensPtr++;
    }

    *tokensPtr = NULL;

    return tokens;
}

/**
 * @Param : 숫자 문자만을 타겟으로 한다.
 *  - 만약 숫자 문자가 아니라면, -1 을 반환한다.
 * @Return : 0 ~ 9 or -1
 */
int chToInt(char ch) {
    if(ch >= '0' && ch <= '9') {
        return ch - '0';
    } else {
        return -1;
    }
}

/**
 * @Param : 빈 칸에 해당하는 문자인지 확인하려는 문자
 *  - 빈 칸, 혹은 끝('\0') 이면, 1 (True) 반환
 * @Return : 1 or 0 (True or False)
 */
_Bool isBlank(char ch) {
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
