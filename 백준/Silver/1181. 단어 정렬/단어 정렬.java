import java.util.*;
import java.io.*;

/**
단어 정렬

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	185155	77798	58336	40.435%

문제
알파벳 소문자로 이루어진 N개의 단어가 들어오면 아래와 같은 조건에 따라 정렬하는 프로그램을 작성하시오.

길이가 짧은 것부터
길이가 같으면 사전 순으로
단, 중복된 단어는 하나만 남기고 제거해야 한다.

입력
첫째 줄에 단어의 개수 N이 주어진다. 

(1 ≤ N ≤ 20,000) 둘째 줄부터 N개의 줄에 걸쳐 알파벳 소문자로 이루어진 단어가 한 줄에 하나씩 주어진다. 

주어지는 문자열의 길이는 50을 넘지 않는다.

출력
조건에 따라 정렬하여 단어들을 출력한다.

예제 입력 1 
13
but
i
wont
hesitate
no
more
no
more
it
cannot
wait
im
yours
예제 출력 1 
i
im
it
no
but
more
wait
wont
yours
cannot
hesitate
 */

public class Main {
	public static String[] strArr;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		strArr = new String[N];
		
		for(int i = 0; i < N; i++)
			strArr[i] = br.readLine().trim();
		
		// Sorting using diffrent ways for my Skills.
		// ------------------------------------------------------------------------------------
		/**
		// quickSort - 길이 정렬 
		
		boolean isCompareLen = true;
		quickSort(0, strArr.length - 1, isCompareLen);
		
		
		// quickSort - 사전순 정렬 
		isCompareLen = false;
		int currIdx = 0;
		int ridLen = strArr[0].length();
		int count = 1;
		for(int i = 1; i < strArr.length; i++) {
			if(ridLen == strArr[i].length()) {
				count++;
				continue;
			}
			quickSort(currIdx, currIdx + count - 1, isCompareLen);
			currIdx = i;
			ridLen = strArr[i].length();
			count = 1;
		}
		
		if(count > 1) {
			quickSort(currIdx, currIdx + count - 1, isCompareLen);
		}
		*/
		//------------------------------------------------------------------------------------
		/**
		// mergeSort - 길이 정렬 
		boolean isCompareLen = true;
		mergeSort(strArr, isCompareLen);
		
		// mergeSort - 사전 정렬 
		isCompareLen = false;
		int ridLen = strArr[0].length();
		int currIdx = 0;
		int count = 1;
		for(int i = 1; i < strArr.length; i++) {
			if(ridLen == strArr[i].length())
				count++;
			else {
				String[] tempStr = new String[count];
				for(int j = currIdx; j < currIdx + count; j++) 
					tempStr[j - currIdx] = strArr[j];
				
				mergeSort(tempStr, isCompareLen);
				for(int j = currIdx; j < currIdx + count; j++)
					strArr[j] = tempStr[j - currIdx];
				
				ridLen = strArr[i].length();
				currIdx = i;
				count = 1;
			}
		}
		if(count > 1) {
			String[] tempStr = new String[count];
			for(int j = currIdx; j < currIdx + count; j++) 
				tempStr[j - currIdx] = strArr[j];
			
			mergeSort(tempStr, isCompareLen);
			for(int j = currIdx; j < currIdx + count; j++)
				strArr[j] = tempStr[j - currIdx];
		}
		*/
		//------------------------------------------------------------------------------------
		
		// heapSort - 문자열 길이에 따라 정렬 - Sorting by Length of String.
		boolean isCompareLen = true;
		heapSort(strArr, isCompareLen);
		
		// heapSort - 같은 문자열 길이끼리 사전 순 정렬 - Sorting Part of Origin String Array by str Dictionary order.
		isCompareLen = false;
		int ridLen = strArr[0].length();
		int currIdx = 0;
		int count = 1;
		for(int i = 1; i < strArr.length; i++) {
			if(ridLen == strArr[i].length()) {
				count++;
				continue;
			}
			String[] tempStr = new String[count];
			
			// tempStr로 정렬 할 부분 복사 
			for(int j = currIdx; j < currIdx + count; j++)
				tempStr[j - currIdx] = strArr[j];
			// 정렬 실시 
			heapSort(tempStr, isCompareLen);
			
			// 원본 strArr로 정렬 된 부분 다시 복사 
			for(int j = currIdx; j < currIdx + count; j++)
				strArr[j] = tempStr[j - currIdx];
			
			ridLen = strArr[i].length();
			currIdx = i;
			count = 1;
		}
		
		if(count > 1) {
			String[] tempStr = new String[count];
			
			// tempStr로 정렬 할 부분 복사 
			for(int j = currIdx; j < currIdx + count; j++)
				tempStr[j - currIdx] = strArr[j];
			// 정렬 실시 
			heapSort(tempStr, isCompareLen);
			
			// 원본 strArr로 정렬 된 부분 다시 복사 
			for(int j = currIdx; j < currIdx + count; j++)
				strArr[j] = tempStr[j - currIdx];
		}
		
		//------------------------------------------------------------------------------------
		
		// 결과값 만들기 - 중복이 있어서는 안된다는 요청이 존재함. 
		StringBuilder sb = new StringBuilder();
		
		String preStr = strArr[0];
		sb.append(strArr[0] + "\n");
		
		for(int i = 1; i < strArr.length; i++) {
			if(strArr[i].equals(preStr))
				continue;
			
			sb.append(strArr[i] + "\n");
			preStr = strArr[i];
		}
		System.out.println(sb.toString());
	}
	public static void heapSort(String[] strArr, boolean isCompareLen) {
		int len = strArr.length;
		
		for(int i = len / 2 - 1; i >= 0; i--)
			heapify(strArr, len, i, isCompareLen);
		
		for(int i = len - 1; i > 0; i--) {
			swapIndex(strArr, 0, i);
			heapify(strArr, i, 0, isCompareLen);
		}
	}
	
	public static void heapify(String[] strArr, int end, int index, boolean isCompareLen) {
		int parent = index;
		int left = parent * 2 + 1;
		int right = parent * 2 + 2;
		
		if(isCompareLen) {
			if(left < end && strArr[parent].length() < strArr[left].length())
				parent = left;
			if(right < end && strArr[parent].length() < strArr[right].length())
				parent = right;
		} else {
			if(left < end && isFront(strArr[parent], strArr[left]))
				parent = left;
			if(right < end && isFront(strArr[parent], strArr[right]))
				parent = right;
		}
		
		if(parent != index) {
			swapIndex(strArr, parent, index);
			heapify(strArr, end, parent, isCompareLen);
		}
			
	}
	
	
	public static void mergeSort(String[] strArr, boolean isCompareLen) {
		if(strArr.length <= 1)
			return;
		
		int middle = strArr.length / 2;
		
		String[] LStrArr = new String[middle];
		String[] RStrArr = new String[strArr.length - middle];
		
		int count = 0;
		for(int i = 0; i < LStrArr.length; i++)
			LStrArr[i] = strArr[count++];
		for(int i = 0; i < RStrArr.length; i++)
			RStrArr[i] = strArr[count++];
		
		mergeSort(LStrArr, isCompareLen); mergeSort(RStrArr, isCompareLen);
		
		int i = 0, j = 0, index = 0;
		if(isCompareLen) {
			while(i < LStrArr.length && j < RStrArr.length) {
				if(LStrArr[i].length() <= RStrArr[j].length()) 
					strArr[index++] = LStrArr[i++];
				else
					strArr[index++] = RStrArr[j++];
			}
		} else {
			while(i < LStrArr.length && j < RStrArr.length) {
				if(isFront(LStrArr[i], RStrArr[j]) || LStrArr[i].equals(RStrArr[j]))
					strArr[index++] = LStrArr[i++];
				else
					strArr[index++] = RStrArr[j++];
			}
		}
		
		while(i < LStrArr.length) {
			strArr[index++] = LStrArr[i++];
		}
		while(j < RStrArr.length) {
			strArr[index++] = RStrArr[j++];
		}
	}
	
	
	public static void quickSort(int start, int end, boolean isCompareLen) {
		if(end - start <= 0)
			return;
		
		int pivot = start;
		int i = start;
		int j = end;
		
		if(isCompareLen) { // 길이 정렬 버전 
			while(i < j) {
				while(strArr[pivot].length() < strArr[j].length())
					j--;
				while(i < j && strArr[pivot].length() >= strArr[i].length())
					i++;
				
				swapIndex(strArr, i, j);
			}
		} else { // 사전적 정렬 버전 
			while(i < j) {
				while(isFront(strArr[pivot], strArr[j]))
					j--;
				while(i < j && (strArr[pivot].equals(strArr[i]) || !isFront(strArr[pivot], strArr[i])))
					i++;
				
				swapIndex(strArr, i, j);
			}
		}
		
		swapIndex(strArr, i, pivot);
		
		quickSort(start, i - 1, isCompareLen); quickSort(i + 1, end, isCompareLen);
	}
	
	/**
	 * before using this method, str1 And str2 of Length must be equal. <br/>
	 * isFront method would be decide what word will be front. <br/>
	 * if str1 is front, return true.
	 * if str2 is front, return false.
	 * 
	 * @param str1 length equal to str2
	 * @param str2 length equal to str1
	 * @return boolean values for sorting.
	 */
	public static boolean isFront(String str1, String str2) {
		int len = str1.length();
		
		for(int i = 0; i < len; i++) {
			char ch1 = str1.charAt(i);
			char ch2 = str2.charAt(i);
			
			if(ch1 == ch2)
				continue;
			else if(ch1 < ch2)
				return true;
			else
				return false;
		}
		// if looping logic is end, both of word is equal.
		// so It is not Important that which word would be front, so decide str1 is front.
		return false;
	}
	
	/**
	 * using method for swapping Index i and j <br/>
	 * created for comfortable swap index.
	 * 
	 * @param strArr
	 * @param i
	 * @param j
	 */
	public static void swapIndex(String[] strArr, int i, int j) {
		String temp;
		temp = strArr[i];
		strArr[i] = strArr[j];
		strArr[j] = temp;
	}
}
