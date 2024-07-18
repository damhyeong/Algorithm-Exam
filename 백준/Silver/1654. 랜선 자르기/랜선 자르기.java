import java.util.*;
import java.io.*;

/**
랜선 자르기

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	232784	55349	37418	21.434%

문제
---
집에서 시간을 보내던 오영식은 박성원의 부름을 받고 급히 달려왔다. 

박성원이 캠프 때 쓸 N개의 랜선을 만들어야 하는데 너무 바빠서 영식이에게 도움을 청했다.

이미 오영식은 자체적으로 K개의 랜선을 가지고 있다. 

그러나 K개의 랜선은 길이가 제각각이다. 

박성원은 랜선을 모두 N개의 같은 길이의 랜선으로 만들고 싶었기 때문에 K개의 랜선을 잘라서 만들어야 한다. 

예를 들어 300cm 짜리 랜선에서 140cm 짜리 랜선을 두 개 잘라내면 20cm는 버려야 한다. 

(이미 자른 랜선은 붙일 수 없다.)

편의를 위해 랜선을 자르거나 만들 때 손실되는 길이는 없다고 가정하며, 
기존의 K개의 랜선으로 N개의 랜선을 만들 수 없는 경우는 없다고 가정하자. 

그리고 자를 때는 항상 센티미터 단위로 정수길이만큼 자른다고 가정하자.

N개보다 많이 만드는 것도 N개를 만드는 것에 포함된다. 

이때 만들 수 있는 최대 랜선의 길이를 구하는 프로그램을 작성하시오.

입력
---
첫째 줄에는 오영식이 이미 가지고 있는 랜선의 개수 K, 그리고 필요한 랜선의 개수 N이 입력된다. 

K는 1이상 10,000이하의 정수이고, N은 1이상 1,000,000이하의 정수이다. 

그리고 항상 K ≦ N 이다. 

그 후 K줄에 걸쳐 이미 가지고 있는 각 랜선의 길이가 센티미터 단위의 정수로 입력된다. 

랜선의 길이는 (2^31)-1보다 작거나 같은 자연수이다.

출력
---
첫째 줄에 N개를 만들 수 있는 랜선의 최대 길이를 센티미터 단위의 정수로 출력한다.

예제 입력 1 
4 11
802
743
457
539
예제 출력 1 
200

힌트
----
802cm 랜선에서 4개, 
743cm 랜선에서 3개, 
457cm 랜선에서 2개, 
539cm 랜선에서 2개를 잘라내 

모두 11개를 만들 수 있다.
 */

/**
 * 시작 파라미터 : 0, longeger.MAX_VALUE == 21억쯤
 * 
 * 이분 탐색 프로세스는 랜선의 길이를 이분탐색으로 나누어 lines[K] 배열의 엘리먼트들을 전부 랜선의 길이로 나누고, 그 결과들을 합해 sum으로 도출.
 * 만약 sum 변수가 N 미만이라면 중간값을 최상위 값으로 배치하여 (최하위 값, 중간값) 으로 재귀.
 * 만약 sum 변수가 N 초과라면, 중간값을 최하위 값으로 배치하여 (중간값, 최상위 값) 으로 재귀.
 * 
 * 만약 sum 변수가 N 과 일치한다면, sum을 반환한다.
 * 
 * 반환된 sum 길이가 N 과 일치하더라도, 최대의 sum 길이는 아니므로, sum + 1 증가문을 만들어 다른 N이 나올 때 까지 증가시킨다.
 * 
 */

public class Main {
	public static long result = -1;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		int K = Integer.parseInt(st.nextToken()); int N = Integer.parseInt(st.nextToken());
		
		long[] lines = new long[K];
		for(int i = 0; i < lines.length; i++)
			lines[i] = Long.parseLong(br.readLine());
		
		System.out.println(getMaxLength(N, lines));
	}

	public static long getMaxLength(long N, long[] lines) {
		// getReachedLength 재귀 메서드를 사용하여 일단 답 도출 - 0, longeger.MAX_VALUE
		long tempMaxLen = getReachedLength(N, lines, 0, Integer.MAX_VALUE);
		
		// tempMax 부터 시작하여 다른 값이 나올 때 까지 tempMax + 1 한다.
		long maxLen = tempMaxLen;
		
//		while(maxLen > 0 && getLineNum(lines, maxLen) != N)
//			maxLen--;
		
		return maxLen;
	}
	
	public static long getReachedLength(long N, long[] lines, long sLen, long eLen) {
		long mLen = (sLen + eLen) / 2;
		
		if(sLen > eLen)
			return -1;
		
//		System.out.println("mLen : " + mLen + ", start : " + sLen + ", end : " + eLen);
		
		long lineNum = getLineNum(lines, mLen);
		
		if(lineNum < N) {
			return getReachedLength(N, lines, sLen, mLen - 1);
		} else {
			long tempResult = getReachedLength(N, lines, mLen + 1, eLen);
			
			if(tempResult == -1) {
				return mLen;
			}else {
				return tempResult;
			}
		}
	}
	
	public static long getLineNum(long[] lines, long length) {
		long sum = 0;
		
		for(int i = 0; i < lines.length; i++) {
			sum += lines[i] / length;
		}
		
		return sum;
	}
}
