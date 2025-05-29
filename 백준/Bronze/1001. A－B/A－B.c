/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com
*/

/**
문제
두 정수 A와 B를 입력받은 다음, A-B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
첫째 줄에 A-B를 출력한다.

예제 입력 1
3 2
예제 출력 1
1
 */
#include <stdio.h>

extern void *malloc(size_t);
extern void *realloc(void*, size_t);
extern void free(void *);

char **tokenizer(const char *str);
int isBlank(char ch);
int parseInt(const char *ch);
int charToInt(char ch);


// 메인 로직을 수행함. (Main)
int main() {
  char str[255];

  // str 문자 배열 안에 입력 한 줄을 "통째로" 넣는다.
  fgets(str, sizeof(str), stdin);

  // tokenizer 메서드를 통해 문자열들을 담은 주소 포인터들을 가져온다. (2차원 배열)
  char **tokens = tokenizer(str);

  char **tokensPtr = tokens;

  // 처음 주어지는 수는 그대로 받아서 저장
  int baseNum = parseInt(*tokensPtr);


  tokensPtr++;

  // 이후 주어지는 수는 baseNum 에서 차감하며, 끝날 때 까지 진행한다.
  while(*tokensPtr) {
      int tempNum = parseInt(*tokensPtr);

      baseNum = baseNum - tempNum;

      tokensPtr++;
  }

  printf("%d\n", baseNum);

  char** tokensFreePtr = tokens;

  while(*tokensFreePtr) {
      char* freeToken = *tokensFreePtr;
      free(freeToken);
      tokensFreePtr++;
  }

  free(tokens);

  return 0;
}

/**
@Param : 토큰화를 수행 할 문자열 (앞뒤 빈칸 가능)
@Return : 각 토큰 문자열 시작 주소를 가지고 있는 2 차원 배열
*/
char **tokenizer(const char *str) { // const 선언을 통해, str 을 변경 할 수 없게 만든다.
    // 초기 토큰 용량은 5 로 설정한다.
    int capacity = 5;
    int count = 0;

    // 5 개의 문자열 배열을 생성
    char **resultTokens = (char**) malloc(sizeof(char *) * (capacity + 1));

    int startIdx = 0; // 읽기 시작 할 문자 인덱스
    int currIdx = 0; // 빈칸을 의미하는 문자 인덱스

    // 읽은 문자열에서 끝을 의미하는 '\0' 이 나올 때 까지 진행
    while(str[currIdx] != '\0') {
        // 현재 순회 문자 추출
        char ch = str[currIdx];

        // 현재 문자가 빈 칸에 해당한다면,
        if(isBlank(ch) == 1) {
            // 만약 토큰 시작 인덱스와 빈칸 인덱스가 동일하다면, 토큰화 하지 않고, 둘 다 앞으로 전진한다.
            if(startIdx == currIdx) {
                startIdx++; currIdx++;
                continue; // 다음 문자 검색으로 바로 이동
            }

            // 토큰 시작 인덱스와, 토큰 마지막 인덱스가 정해 진 상황이다.
            // 이 때, 토큰의 길이에 따라 동적 할당을 진행하고, 이를 resultToken 에 할당한다.
            int len = currIdx - startIdx;
            char* token = (char*) malloc(sizeof(char) * (len + 1)); // 끝은 '\0' 으로 마무리 해 주어야 한다.
            token[len] = '\0';

            char* tokenPtr = token;

            while(startIdx != currIdx) {
                // 토큰 시작부터 마지막까지 단어 추출하여 *token 문자열 배열에 삽입
                char ch = str[startIdx];
                *tokenPtr = ch;
                tokenPtr++; startIdx++;
            }

            // 완성된 토큰을 2차원 resultTokens 현재 위치에 배치
            resultTokens[count++] = token;

            // 만약 토큰 컨테이너의 용량이 다 찼다면,
            if(count == capacity) {
                // char** 타입인 resultTokens 에 "realloc" 메서드를 통해 2 배로 용량을 늘리고,
                resultTokens = realloc(resultTokens, (sizeof(char*) * (capacity * 2 + 1)));
                // 정해진 용량을 다시 2 배로 기록한다. (추후 10 개가 들어오면, 다시 차서 더 늘려야 하기 때문.)
                capacity *= 2;
            }

            // 현재 빈 칸을 가르키는 currIdx 를 한 칸 앞으로 당기고,
            currIdx++;
            // 토큰 시작 인덱스와 현재 인덱스를 일치시킨다.
            startIdx = currIdx;

        } else { // 정상적으로 문자라면.
            // 탐색 현재 인덱스 이동.
            currIdx++;
        }
    }

    // 맨 마지막 부분이 토큰화 되지 않았을 경우 (대부분)
    if(startIdx != currIdx) {
        // 마지막에 닿은 currIdx 와 현재 토큰 시작인 startIdx 간의 차이 계산
        int len = currIdx - startIdx;
        // 마지막 단어(토큰) 배열 생성
        char* lastToken = (char*) malloc(sizeof(char) * (len + 1));
        // 끝 선언(필수)
        lastToken[len] = '\0';

        char* tokenPtr = lastToken;

        // 마지막으로 토큰 시작이 마지막 인덱스까지 갈 때 까지 반복
        while(startIdx != currIdx) {
            // 단어 추출 및 마지막 토큰 문자열 배열에 삽입.
            char ch = str[startIdx];
            *tokenPtr = ch;
            tokenPtr++; startIdx++;
        }

        // count 후위 연산자로 "resultTokens" 에는 1 더해진 값이 들어가지 않음.
        resultTokens[count++] = lastToken;
    }

    // 2 차원 배열에서 마지막을 선언.
    resultTokens[count] = NULL;

    return resultTokens;
}

/**
@Param : 빈 칸에 해당하는지 알아야 하는 문자 하나
@Return : 빈 칸일 시 == 1, 아닐 시 == 0
*/
int isBlank(char ch) {
    if (ch == 32) { // ' ' 일 경우
        return 1;
    } else if (ch >= 9 && ch <= 13) { // 여러 가지 빈 칸 종류일 경우
        return 1;
    } else {
        return 0;
    }
}

/**
@Param : 파싱하게 될 숫자 문자열을 의미 (빈칸 불가능)
@Return : 파싱된 숫자 문자열의 진짜 정수를 반환
*/
int parseInt(const char* ch) {
    // 반환 될 값
    int result = 0;
    int sign = 1;

    char* chPtr = (char*) ch;

    if(*chPtr == '-') {
        chPtr++;
        sign *= -1;
    }

    // 문자열의 끝이 도달 할 때 까지 루프
    while (*chPtr != '\0') {
        // 기존 수 올림
        result *= 10;

        int num = charToInt(*chPtr);

        // 새로운 수 삽입
        result += num;

        chPtr++;
    }

    return result * sign;
}

/**
@Param : 단일 숫자로 변환 할 문자
@Return : 단일 문자에서 숫자로.
*/
int charToInt(char ch) {
    // 정상적인 숫자 문자가 들어왔다면, 수행
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else { // 아니라면, 잘못됨을 의미하는 -1 반환
        return -1;
    }
}
