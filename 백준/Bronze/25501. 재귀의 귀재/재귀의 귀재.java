import java.util.*;
import java.io.*;

/**
재귀의 귀재

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초 (추가 시간 없음)	1024 MB (추가 메모리 없음)	24324	13150	11369	55.157%

문제
---
정휘는 후배들이 재귀 함수를 잘 다루는 재귀의 귀재인지 알아보기 위해 재귀 함수와 관련된 문제를 출제하기로 했다.

팰린드롬이란, 앞에서부터 읽었을 때와 뒤에서부터 읽었을 때가 같은 문자열을 말한다. 

팰린드롬의 예시로 AAA, ABBA, ABABA 등이 있고, 팰린드롬이 아닌 문자열의 예시로 ABCA, PALINDROME 등이 있다.

어떤 문자열이 팰린드롬인지 판별하는 문제는 재귀 함수를 이용해 쉽게 해결할 수 있다. 

아래 코드의 isPalindrome 함수는 주어진 문자열이 

팰린드롬이면 1, 팰린드롬이 아니면 0을 반환하는 함수다.
------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

int recursion(const char *s, int l, int r){
    if(l >= r) return 1;
    else if(s[l] != s[r]) return 0;
    else return recursion(s, l+1, r-1);
}

int isPalindrome(const char *s){
    return recursion(s, 0, strlen(s)-1);
}

int main(){
    printf("ABBA: %d\n", isPalindrome("ABBA")); // 1
    printf("ABC: %d\n", isPalindrome("ABC"));   // 0
}
------------------------------------------------------------------------------------

정휘는 위에 작성된 isPalindrome 함수를 이용하여 어떤 문자열이 팰린드롬인지 여부를 판단하려고 한다.

구체적으로는, 문자열 S 를 isPalindrome 함수의 인자로 전달하여 팰린드롬 여부를 반환값으로 알아낼 것이다. 

더불어 판별하는 과정에서 recursion 함수를 몇 번 호출하는지 셀 것이다.

정휘를 따라 여러분도 함수의 반환값과 recursion 함수의 호출 횟수를 구해보자.

입력
첫째 줄에 테스트케이스의 개수 T가 주어진다. (1 <= T <= 1_000)

둘째 줄부터 T개의 줄에 알파벳 대문자로 구성된 문자열 S 가 주어진다. (1 <= |S| <= 1_000)

출력
---
각 테스트케이스마다, 
isPalindrome 함수의 반환값과 recursion 함수의 호출 횟수를 한 줄에 공백으로 구분하여 출력한다.

예제 입력 1 
5
AAA
ABBA
ABABA
ABCA
PALINDROME
예제 출력 1 
1 2
1 3
1 3
0 2
0 1

힌트
---
Python 3
------------------------------------------------------------------------------------
def recursion(s, l, r):
    if l >= r: return 1
    elif s[l] != s[r]: return 0
    else: return recursion(s, l+1, r-1)

def isPalindrome(s):
    return recursion(s, 0, len(s)-1)

print('ABBA:', isPalindrome('ABBA'))
print('ABC:', isPalindrome('ABC'))
------------------------------------------------------------------------------------


Java 15
------------------------------------------------------------------------------------
public class Main{
    public static int recursion(String s, int l, int r){
        if(l >= r) return 1;
        else if(s.charAt(l) != s.charAt(r)) return 0;
        else return recursion(s, l+1, r-1);
    }
    public static int isPalindrome(String s){
        return recursion(s, 0, s.length()-1);
    }
    public static void main(String[] args){
        System.out.println("ABBA: " + isPalindrome("ABBA"));
        System.out.println("ABC: " + isPalindrome("ABC"));
    }
}
------------------------------------------------------------------------------------
 */

public class Main {
	public static int count = 0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		StringBuilder sb = new StringBuilder();
		while(T-- > 0) {
			String str = br.readLine().trim();
			sb.append(recursion(str, 0, str.length() - 1)).append(" ");
			sb.append(count).append("\n");
			count = 0;
		}
		System.out.println(sb.toString());
	}
	
	public static int recursion(String str, int start, int end) {
		count++;
		if(start >= end) {
			return 1;
		}
		
		char ch1 = str.charAt(start);
		char ch2 = str.charAt(end);
		if(ch1 == ch2) {
			return recursion(str, start + 1, end - 1);
		} else 
			return 0;
	}
}
