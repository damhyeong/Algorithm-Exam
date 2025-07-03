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
1 초	1024 MB	92064	40546	35348	44.149%
문제
인하대학교 컴퓨터공학과를 졸업하기 위해서는, 전공평점이 3.3 이상이거나 졸업고사를 통과해야 한다. 그런데 아뿔싸, 치훈이는 깜빡하고 졸업고사를 응시하지 않았다는 사실을 깨달았다!

치훈이의 전공평점을 계산해주는 프로그램을 작성해보자.

전공평점은 전공과목별 (학점 × 과목평점)의 합을 학점의 총합으로 나눈 값이다.

인하대학교 컴퓨터공학과의 등급에 따른 과목평점은 다음 표와 같다.

A+	4.5
A0	4.0
B+	3.5
B0	3.0
C+	2.5
C0	2.0
D+	1.5
D0	1.0
F	0.0
P/F 과목의 경우 등급이 P또는 F로 표시되는데, 등급이 P인 과목은 계산에서 제외해야 한다.

과연 치훈이는 무사히 졸업할 수 있을까?

입력
20줄에 걸쳐 치훈이가 수강한 전공과목의 과목명, 학점, 등급이 공백으로 구분되어 주어진다.

출력
치훈이의 전공평점을 출력한다.

정답과의 절대오차 또는 상대오차가
\(10^{-4}\) 이하이면 정답으로 인정한다.

제한
1 ≤ 과목명의 길이 ≤ 50
과목명은 알파벳 대소문자 또는 숫자로만 이루어져 있으며, 띄어쓰기 없이 주어진다. 입력으로 주어지는 모든 과목명은 서로 다르다.
학점은 1.0,2.0,3.0,4.0중 하나이다.
등급은 A+,A0,B+,B0,C+,C0,D+,D0,F,P중 하나이다.
적어도 한 과목은 등급이 P가 아님이 보장된다.
예제 입력 1
ObjectOrientedProgramming1 3.0 A+
IntroductiontoComputerEngineering 3.0 A+
ObjectOrientedProgramming2 3.0 A0
CreativeComputerEngineeringDesign 3.0 A+
AssemblyLanguage 3.0 A+
InternetProgramming 3.0 B0
ApplicationProgramminginJava 3.0 A0
SystemProgramming 3.0 B0
OperatingSystem 3.0 B0
WirelessCommunicationsandNetworking 3.0 C+
LogicCircuits 3.0 B0
DataStructure 4.0 A+
MicroprocessorApplication 3.0 B+
EmbeddedSoftware 3.0 C0
ComputerSecurity 3.0 D+
Database 3.0 C+
Algorithm 3.0 B0
CapstoneDesigninCSE 3.0 B+
CompilerDesign 3.0 D0
ProblemSolving 4.0 P
예제 출력 1
3.284483

예제 입력 2
BruteForce 3.0 F
Greedy 1.0 F
DivideandConquer 2.0 F
DynamicProgramming 3.0 F
DepthFirstSearch 4.0 F
BreadthFirstSearch 3.0 F
ShortestPath 4.0 F
DisjointSet 2.0 F
MinimumSpanningTree 2.0 F
TopologicalSorting 1.0 F
LeastCommonAncestor 2.0 F
SegmentTree 4.0 F
EulerTourTechnique 3.0 F
StronglyConnectedComponent 2.0 F
BipartiteMatching 2.0 F
MaximumFlowProblem 3.0 F
SuffixArray 1.0 F
HeavyLightDecomposition 4.0 F
CentroidDecomposition 3.0 F
SplayTree 1.0 F
예제 출력 2
0.000000
*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

double toGradeNum(char* grade);
char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* doubleToStr(double target, int size);
double parseDouble(const char* str);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main(void) {
    int loop = 20;

    char input[255];

    double div = 0;
    double total = 0;

    while(loop-- > 0) {
        fgets(input, sizeof(input), stdin);
        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        tokensPtr++;

        double score = parseDouble(*tokensPtr++);

        char* grd = *tokensPtr;

        double grade = toGradeNum(grd);

        if(*grd == 'P') {
            continue;
        }

        div += score;
        total += (score * grade);

        freeTokens(tokens);
    }

    double result = 0;

    if(div != 0) {
        result = total / div;
    }

    char* resultStr = doubleToStr(result, 6);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

    return 0;
}
/**
A+	4.5
A0	4.0
B+	3.5
B0	3.0
C+	2.5
C0	2.0
D+	1.5
D0	1.0
F	0.0
 */
double toGradeNum(char* grade) {
    char g1 = *grade;
    char g2 = *(grade + 1);

    double result = 0.0;

    switch(g1) {
        case 'A':
            result = g2 == '+' ? 4.5 : 4.0;
            break;
        case 'B':
            result = g2 == '+' ? 3.5 : 3.0;
            break;
        case 'C':
            result = g2 == '+' ? 2.5 : 2.0;
            break;
        case 'D':
            result = g2 == '+' ? 1.5 : 1.0;
            break;
        case 'F':
            result = 0;
            break;
        default:
            result = 0;
            break;
    }

    return result;
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
            *(newTkn + tknSize) = 0;
            char* newTknPtr = (char*)newTkn;

            while(tknIdx != currIdx) {
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
}

char* doubleToStr(double target, int size) {
    double sign = 1;

    if(target < 0) {
        sign = -1;
    }

    int intPart = (int)target;
    double doublePart = target - (double)intPart;

    // freee required
    char* intStr = intToStr(intPart);

    // freee required
    char* doubleStr = (char*)malloc(sizeof(char) * (size + 1));
    *(doubleStr + size) = 0;

    int idx = 0;
    while(idx < size) {
        doublePart *= 10;

        int tempInt = (int)doublePart;

        *(doubleStr + idx++) = tempInt + '0';

        doublePart -= (double)tempInt;
    }


    // free required
    char* result = (char*)malloc(sizeof(char) * (51));
    *(result + 50) = 0;
    char* resultPtr = (char*)result;

    if(sign == -1) {
        *resultPtr++ = '-';
    }

    char* intStrPtr = intStr;
    char* doubleStrPtr = doubleStr;

    while(isBlank(*intStrPtr) != 1) {
        *resultPtr++ = *intStrPtr++;
    }
    *resultPtr++ = '.';

    while(isBlank(*doubleStrPtr) != 1) {
        *resultPtr++ = *doubleStrPtr++;
    }
    *resultPtr = 0;

    free(intStr); free(doubleStr);

    return result;
}
double parseDouble(const char* str) {
    double sign = 1;

    char intStr[30];
    char* intStrPtr = (char*)intStr;

    char doubleStr[10];
    char* doubleStrPtr = (char*)doubleStr;

    char* strPtr = (char*)str;

    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(*strPtr != '.') {
        *intStrPtr++ = *strPtr++;
    }
    *intStrPtr = 0;
    strPtr++;

    double intPart = (double)parseInt(intStr);

    while(isBlank(*strPtr) != 1 && isBlank(*doubleStrPtr) != 1) {
        *doubleStrPtr++ = *strPtr++;
    }
    *doubleStrPtr = 0;

    double doublePart = parseInt(doubleStr);

    while(doublePart >= 1.0) {
        doublePart /= 10.0;
    }

    return (intPart + doublePart) * sign;
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
