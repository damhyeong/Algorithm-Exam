import java.util.*;
import java.io.*;

/**
나이순 정렬

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
3 초	256 MB	144596	65121	49981	43.618%

문제
온라인 저지에 가입한 사람들의 나이와 이름이 가입한 순서대로 주어진다. 

이때, 회원들을 나이가 증가하는 순으로, 나이가 같으면 먼저 가입한 사람이 앞에 오는 순서로 정렬하는 프로그램을 작성하시오.

입력
첫째 줄에 온라인 저지 회원의 수 N이 주어진다. 
(1 ≤ N ≤ 100,000)

둘째 줄부터 N개의 줄에는 각 회원의 나이와 이름이 공백으로 구분되어 주어진다. 

나이는 1보다 크거나 같으며, 200보다 작거나 같은 정수이고, 
이름은 알파벳 대소문자로 이루어져 있고, 
길이가 100보다 작거나 같은 문자열이다. 

입력은 가입한 순서로 주어진다.

출력
첫째 줄부터 총 N개의 줄에 걸쳐 온라인 저지 회원을 

나이 순, 
나이가 같으면 가입한 순으로 

한 줄에 한 명씩 나이와 이름을 공백으로 구분해 출력한다.

예제 입력 1 
3
21 Junkyu
21 Dohyun
20 Sunyoung
예제 출력 1 
20 Sunyoung
21 Junkyu
21 Dohyun
 */

public class Main {
	public static int[] ageList; 
	public static String[] nameList;
	public static int[] ordList;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		ageList = new int[N];
		nameList = new String[N];
		ordList = new int[N]; // 숫자가 낮을수록 위에 와야 한다. 
		
		// 입력 받기 
		StringTokenizer st;
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			ageList[i] = Integer.parseInt(st.nextToken());
			nameList[i] = st.nextToken().trim();
			ordList[i] = i;
		}
		
		// ----------------------------------------------------------------------------------------------------
		/**
		// quickSort - 나이 순 정렬 
		boolean isSortAge = true;
		quickSort(0, N - 1, ageList, nameList, ordList, isSortAge);
		
		// quickSort - 먼저 온 사람 위로. 정렬 
		isSortAge = false;
		int ridAge = ageList[0];
		int currIdx = 0;
		int count = 1;
		
		for(int i = 1; i < N; i++) {
			if(ridAge == ageList[i]) {
				count++;
				continue;
			}
			
			quickSort(currIdx, currIdx + count - 1, ageList, nameList, ordList, isSortAge);
			
			ridAge = ageList[i];
			currIdx = i;
			count = 1;
		}
		if(count > 1) {
			quickSort(currIdx, currIdx + count - 1, ageList, nameList, ordList, isSortAge);
		}
		*/
		// ----------------------------------------------------------------------------------------------------
		/**
		// mergeSort - 나이순 정렬 
		boolean isSortAge = true;
		mergeSort(ageList, nameList, ordList, isSortAge);
		
		// mergeSort - 온 순서대로 정렬 
		isSortAge = false;
		int ridAge = ageList[0];
		int currIdx = 0;
		int count = 1;
		
		for(int i = 1; i < ageList.length; i++) {
			if(ridAge == ageList[i]) {
				count++;
				continue;
			}
			int[] tempAgeList = cutIntArr(ageList, currIdx, currIdx + count);
			String[] tempNameList = cutStrArr(nameList, currIdx, currIdx + count);
			int[] tempOrdList = cutIntArr(ordList, currIdx, currIdx + count);
			
			mergeSort(tempAgeList, tempNameList, tempOrdList, isSortAge);
			
			insertIntArr(tempAgeList, ageList, currIdx);
			insertStrArr(tempNameList, nameList, currIdx);
			insertIntArr(tempOrdList, ordList, currIdx);
			
			ridAge = ageList[i];
			currIdx = i;
			count = 1;
			
		}
		if(count > 1) {
			int[] tempAgeList = cutIntArr(ageList, currIdx, currIdx + count);
			String[] tempNameList = cutStrArr(nameList, currIdx, currIdx + count);
			int[] tempOrdList = cutIntArr(ordList, currIdx, currIdx + count);
			
			mergeSort(tempAgeList, tempNameList, tempOrdList, isSortAge);
			
			insertIntArr(tempAgeList, ageList, currIdx);
			insertStrArr(tempNameList, nameList, currIdx);
			insertIntArr(tempOrdList, ordList, currIdx);
		}
		*/
		// ----------------------------------------------------------------------------------------------------
		
		// heapSort - 나이 순 정렬 
		boolean isSortAge = true;
		heapSort(ageList, nameList, ordList, isSortAge);
		
		isSortAge = false;
		int ridAge = ageList[0];
		int currIdx = 0;
		int count = 1;
		for(int i = 1; i < ageList.length; i++) {
			if(ridAge == ageList[i]) {
				count++;
				continue;
			}
			int[] tmpAgeList = cutIntArr(ageList, currIdx, currIdx + count);
			String[] tmpNameList = cutStrArr(nameList, currIdx, currIdx + count);
			int[] tmpOrdList = cutIntArr(ordList, currIdx, currIdx + count);
			
			heapSort(tmpAgeList, tmpNameList, tmpOrdList, isSortAge);
			
			insertIntArr(tmpAgeList, ageList, currIdx);
			insertStrArr(tmpNameList, nameList, currIdx);
			insertIntArr(tmpOrdList, ordList, currIdx);
			
			ridAge = ageList[i];
			currIdx = i;
			count = 1;
		}
		if(count > 1) {
			int[] tmpAgeList = cutIntArr(ageList, currIdx, currIdx + count);
			String[] tmpNameList = cutStrArr(nameList, currIdx, currIdx + count);
			int[] tmpOrdList = cutIntArr(ordList, currIdx, currIdx + count);
			
			heapSort(tmpAgeList, tmpNameList, tmpOrdList, isSortAge);
			
			insertIntArr(tmpAgeList, ageList, currIdx);
			insertStrArr(tmpNameList, nameList, currIdx);
			insertIntArr(tmpOrdList, ordList, currIdx);
		}
		
		
		// ----------------------------------------------------------------------------------------------------
		
		// 출력하기 
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < ageList.length; i++) {
			sb.append(ageList[i]); sb.append(" "); sb.append(nameList[i] + "\n");
		}
		
		System.out.println(sb.toString());
		
	}
	
	public static void heapSort(int[] aL, String[] nL, int[] oL, boolean isSortAge) {
		int len = aL.length;
		
		for(int i = len / 2 - 1; i >= 0; i--)
			heapify(len, i, isSortAge, aL, nL, oL);
		
		for(int i = len - 1; i > 0; i--) {
			swapTwoArr(0, i, aL, nL, oL);
			
			heapify(i, 0, isSortAge, aL, nL, oL);
		}
	}
	public static void heapify(int end, int index, boolean isSortAge, int[] aL, String[] nL, int[] oL) {
		int parent = index;
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		
		if(isSortAge) {
			if(left < end && aL[parent] < aL[left])
				parent = left;
			if(right < end && aL[parent] < aL[right])
				parent = right;
		} else {
			if(left < end && oL[parent] < oL[left])
				parent = left;
			if(right < end && oL[parent] < oL[right])
				parent = right;
		}
		
		if(parent != index) {
			swapTwoArr(parent, index, aL, nL, oL);
			
			heapify(end, parent, isSortAge, aL, nL, oL);
		}
	}
	
	public static void mergeSort(int[] aL, String[] nL, int[] oL, boolean isSortAge) {
		if(aL.length <= 1)
			return;
		
		int middle = aL.length / 2;
		
		// age or order 로 나뉠듯. 
		int[] lAL = cutIntArr(aL, 0, middle);
		String[] lNL = cutStrArr(nL, 0, middle);
		int[] lOL = cutIntArr(oL, 0, middle);
		
		int len = aL.length;
	
		int[] rAL = cutIntArr(aL, middle, len);
		String[] rNL = cutStrArr(nL, middle, len);
		int[] rOL = cutIntArr(oL, middle, len);
		
		mergeSort(lAL, lNL, lOL, isSortAge); mergeSort(rAL, rNL, rOL, isSortAge);
		
		int i = 0, j = 0, index = 0;
		if(isSortAge) {
			while(i < lAL.length && j < rAL.length) {
				if(lAL[i] <= rAL[j]) {
					aL[index] = lAL[i];
					nL[index] = lNL[i];
					oL[index++] = lOL[i++];
				} else {
					aL[index] = rAL[j];
					nL[index] = rNL[j];
					oL[index++] = rOL[j++];
				}
			}
		} else {
			while(i < lAL.length && j < rAL.length) {
				if(lOL[i] <= rOL[j]) {
					aL[index] = lAL[i];
					nL[index] = lNL[i];
					oL[index++] = lOL[i++];
				} else {
					aL[index] = rAL[j];
					nL[index] = rNL[j];
					oL[index++] = rOL[j++];
				}
			}
		}
		
		while(i < lAL.length) {
			aL[index] = lAL[i];
			nL[index] = lNL[i];
			oL[index++] = lOL[i++];
		}
		while(j < rAL.length) {
			aL[index] = rAL[j];
			nL[index] = rNL[j];
			oL[index++] = rOL[j++];
		}
	}
	
	public static void quickSort(int start, int end, int[] aL, String[] nL, int[] oL, boolean isSortAge) {
		if(end - start <= 0)
			return;
		
		int pivot = start;
		int i = start;
		int j = end;
		
		if(isSortAge) {
			while(i < j) {
				while(aL[pivot] < aL[j])
					j--;
				while(i < j && aL[pivot] >= aL[i])
					i++;
				
				swapTwoArr(i, j, aL, nL, oL);
			}
		} else {
			while(i < j) {
				while(oL[pivot] < oL[j])
					j--;
				while(i < j && oL[pivot] >= oL[i])
					i++;
				
				swapTwoArr(i, j, aL, nL, oL);
			}
		}
		
		swapTwoArr(i, pivot, aL, nL, oL);
		
		quickSort(start, i - 1, aL, nL, oL, isSortAge); quickSort(i + 1, end, aL, nL, oL, isSortAge);
	}
	
	public static boolean isFront(int order1, int order2) {
		// 온 순서는 똑같을 수 없다 - There's Not Possible to equal order1 with order2.
		if(order1 < order2)
			return true;
		else
			return false;
	}
	
	/**
	 * This Method Made for swap two Array, ageList and nameList. <br/>
	 * if we want to swap index i with j, ageList, nameList and orderList swapping same time. <br/>
	 * 
	 * @param i - Index for first swap point.
	 * @param j - Index for second swap point.
	 * @param aL - What we want to swap int array.
	 * @param nL - What we want to swap String array.
	 * @param oL = What we want to swap int array.
	 */
	public static void swapTwoArr(int i, int j, int[] aL, String[] nL, int[] oL) {
		int tempAge = aL[i]; String tempName = nL[i]; int tempOrder = oL[i];
		aL[i] = aL[j]; nL[i] = nL[j]; oL[i] = oL[j];
		aL[j] = tempAge; nL[j] = tempName; oL[j] = tempOrder;
	}
	
	
	public static int[] cutIntArr(int[] numArr, int i, int j){
		int[] tempArr = new int[j - i];
		
		for(int x = i; x < j; x++)
			tempArr[x - i] = numArr[x];
		
		return tempArr;
	}
	public static void insertIntArr(int[] tmpArr, int[] orgArr, int start) {
		for(int i = start; i < start + tmpArr.length; i++) {
			orgArr[i] = tmpArr[i - start];
		}
	}
	
	public static String[] cutStrArr(String[] strArr, int i, int j) {
		String[] tempArr = new String[j - i];
		
		for(int x = i; x < j; x++)
			tempArr[x - i] = strArr[x];
		
		return tempArr;
	}
	public static void insertStrArr(String[] tmpArr, String[] orgArr, int start) {
		for(int i = start; i < start + tmpArr.length; i++) {
			orgArr[i] = tmpArr[i - start];
		}
	}
}
