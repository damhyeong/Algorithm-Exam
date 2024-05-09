import java.util.*;
import java.io.*;

/**
회사에 있는 사람

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	54548	22439	17040	40.638%

문제
상근이는 세계적인 소프트웨어 회사 기글에서 일한다. 

이 회사의 가장 큰 특징은 자유로운 출퇴근 시간이다. 

따라서, 직원들은 반드시 9시부터 6시까지 회사에 있지 않아도 된다.

각 직원은 자기가 원할 때 출근할 수 있고, 아무때나 퇴근할 수 있다.

상근이는 모든 사람의 출입카드 시스템의 로그를 가지고 있다. 

이 로그는 어떤 사람이 회사에 들어왔는지, 나갔는지가 기록되어져 있다. 

로그가 주어졌을 때, 현재 회사에 있는 모든 사람을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 로그에 기록된 출입 기록의 수 n이 주어진다. 

(2 ≤ n ≤ 106) 다음 n개의 줄에는 출입 기록이 순서대로 주어지며, 
각 사람의 이름이 주어지고 "enter"나 "leave"가 주어진다. 

"enter"인 경우는 출근, "leave"인 경우는 퇴근이다.

회사에는 동명이인이 없으며, 대소문자가 다른 경우에는 다른 이름이다. 

사람들의 이름은 알파벳 대소문자로 구성된 5글자 이하의 문자열이다.

출력
현재 회사에 있는 사람의 이름을 사전 순의 역순으로 한 줄에 한 명씩 출력한다.

예제 입력 1 
4
Baha enter
Askar enter
Baha leave
Artem enter
예제 출력 1 
Askar
Artem
 */

public class Main {
	public static String[] strArr;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		PracStringHashMap map = new PracStringHashMap();
		
		Set<String> newSet = new HashSet<String>();
		
		for(int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			String name = st.nextToken();
			String doing = st.nextToken();
			
			if(doing.equals("enter")) {
//				map.put(name);
				newSet.add(name);
			} else if(doing.equals("leave")) {
//				map.delete(name);
				newSet.remove(name);
			}
		}
		// Complete Inserting.
		
//		strArr = map.getStrArr();
		Object[] tempObj = newSet.toArray();
		String[] tempStr = new String[tempObj.length];
		
		for(int i = 0; i < tempStr.length; i++)
			tempStr[i] = (String) tempObj[i];
		
//		List<String> strList = Arrays.asList(strArr);
		List<String> strList = Arrays.asList(tempStr);
		
		// ----------------------------------------------------------------------
		// using quickSort - Time Out.
		/**
		boolean isCompareLen = true;
		quickSort(strArr, 0, strArr.length - 1, isCompareLen);
		
		isCompareLen = false;
		int ridLen = strArr[0].length();
		int currIdx = 0;
		int count = 1;
		for(int i = 1; i < strArr.length; i++) {
			if(ridLen == strArr[i].length()) {
				count++;
				continue;
			}
			String[] tempStr = cutArr(strArr, currIdx, currIdx + count);
			quickSort(tempStr, 0, tempStr.length - 1, isCompareLen);
			pasteArr(tempStr, strArr, currIdx, currIdx + count);
			
			ridLen = strArr[i].length();
			currIdx = i;
			count = 1;
		}
		if(count > 1) {
			String[] tempStr = cutArr(strArr, currIdx, currIdx + count);
			quickSort(tempStr, 0, tempStr.length - 1, isCompareLen);
			pasteArr(tempStr, strArr, currIdx, currIdx + count);
		}
		*/
		// ----------------------------------------------------------------------
		// mergeSort
		
//		boolean isCompareLen = false;
//		mergeSort(strArr, isCompareLen);
		
		Collections.sort(strList, Collections.reverseOrder());
		
		// Printing Results reverse.
		StringBuilder sb = new StringBuilder();
//		for(int i = strArr.length - 1; i >= 0; i--)
//			sb.append(strArr[i] + "\n");
		
		for(int i = 0; i < strList.size(); i++)
			sb.append(strList.get(i) + "\n");
		
		System.out.println(sb.toString());
	}
	public static void mergeSort(String[] strArr, boolean isCompareLen) {
		if(strArr.length <= 1)
			return;
		
		int middle = strArr.length / 2;
		
		
		String[] LArr = new String[middle];
		String[] RArr = new String[strArr.length - middle];
		
		int count = 0;
		for(int i = 0; i < LArr.length; i++)
			LArr[i] = strArr[count++];
		for(int i = 0; i < RArr.length; i++)
			RArr[i] = strArr[count++];
		
		mergeSort(LArr, isCompareLen); mergeSort(RArr, isCompareLen);
		
		int i = 0, j = 0, index = 0;
		if(isCompareLen) {
			while(i < LArr.length && j < RArr.length) {
				if(LArr[i].length() <= RArr[j].length()) 
					strArr[index++] = LArr[i++];
				else
					strArr[index++] = RArr[j++];
			}
		} else {
			while(i < LArr.length && j < RArr.length) {
				if(compareStr(LArr[i], RArr[j]) == 0 || compareStr(LArr[i], RArr[j]) == 1)
					strArr[index++] = LArr[i++];
				else
					strArr[index++] = RArr[j++];
			}
		}
		

		while(i < LArr.length) 
			strArr[index++] = LArr[i++];
		while(j < RArr.length)
			strArr[index++] = RArr[j++];
	}
	
	public static void quickSort(String[] strArr, int start, int end, boolean isCompareLen) {
		if(end - start <= 0)
			return;
		
		int pivot = (start + end) / 2;
		int i = start;
		int j = end;
		
		if(isCompareLen) {
			while(i < j) {
				while(strArr[pivot].length() < strArr[j].length())
					j--;
				while(i < j && strArr[pivot].length() >= strArr[i].length())
					i++;
				
				swap(strArr, i, j);
			}
		} else {
			while(i < j) {
				while(compareStr(strArr[pivot], strArr[j]) == 1)
					j--;
				while(i < j && (compareStr(strArr[pivot], strArr[i]) == 0 || compareStr(strArr[pivot], strArr[i]) == -1))
					i++;
				swap(strArr, i, j);
			}
		}
		swap(strArr, i, pivot);
		
		quickSort(strArr, start, i - 1, isCompareLen); quickSort(strArr, i + 1, end, isCompareLen); 
	}
	
	// str1 is front of str2, return 1. | equals, return 0. |  Other else, return -1.
	public static int compareStr(String str1, String str2) {
		
		int len = (str1.length() <= str2.length()) ? str1.length() : str2.length();
		int result = 0;
		
		for(int i = 0; i < len; i++) {
			char ch1 = str1.charAt(i);
			char ch2 = str2.charAt(i);
			
			if(ch1 == ch2) {
				continue;
			}else if(ch1 < ch2) {
				return 1;
			}else {
				return -1;
			}
		}
		// 여기까지 왔으면, 주어진 길이까지는 문자열이 동일하다. 
		
		if(str1.length() < str2.length())
			result = 1;
		else if(str1.length() > str2.length())
			result = -1;
		
		return result;
	}
	
	public static <T> void pasteArr(T[] tempArr, T[] orgArr, int i, int j) {
		for(int x = i; x < j; x++) {
			orgArr[x] = tempArr[x - i];
		}
	}
	
	public static String[] cutArr(String[] arr, int i, int j) {
		String[] tempArr = new String[j - i];
		
		for(int x = i; x < j; x++) {
			tempArr[x - i] = arr[x];
		}
		
		return tempArr;
	}
	
	public static <T> void swap(T[] arr, int i, int j){
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
}

class PracStringHashMap{
	PracStringSet[] setArr;
	int count = 0;
	
	public PracStringHashMap() {
		// 디폴트로 50개 잡아보자 
		setArr = new PracStringSet[50];
		
		for(int i = 0; i < setArr.length; i++) {
			setArr[i] = new PracStringSet();
		}
	}
	
	public void put(String name) {
		int hash = 0;
		
		for(int i = 0; i < name.length(); i++)
			hash = (hash + name.charAt(i)) % 50;
		
		setArr[hash].put(name);
		count++;
	}
	
	public void delete(String name) {
		int hash = 0;
		
		for(int i = 0; i < name.length(); i++)
			hash = (hash + name.charAt(i)) % 50;
		
		boolean isDelete = setArr[hash].delete(name);
		
		count = isDelete ? count - 1 : count;
	}
	
	public String[] getStrArr() {
		String[] strArr = new String[count];
		
		int index = 0;
		
		for(int i = 0; i < setArr.length; i++) {
			String[] tempArr = setArr[i].getStrArr();
			
			for(int j = 0; j < tempArr.length; j++) 
				strArr[index++] = tempArr[j];
		}
		
		return strArr;
	}
}


class PracStringSet {
	Person startPerson;
	Person currentPerson;
	int size = 0;
	
	public PracStringSet() {
		startPerson = null;
		currentPerson = null;
	}
	
	public void put(String name) {
		if(size == 0) { // setting my personal Set Class.
			startPerson = new Person(name);
			currentPerson = this.startPerson; // set address to start.
		} else {
			// Person newPerson = new Person(name);
			currentPerson.setNextPerson(new Person(name));
			currentPerson = currentPerson.getNextPerson(); // Move to Next Address.
		}
		size++;
		
	}
	
	public boolean delete(String name) {
		Person tempPerson = startPerson; // Checking for value
		Person currPerson = tempPerson; // Connecting Link with Delete.
		
		boolean isDelete = false;
		while(tempPerson != null) {
			if(name.equals(tempPerson.getName())) {
				isDelete = true;
				break;
			}
			currPerson = tempPerson;
			tempPerson = tempPerson.getNextPerson();
		}
		
		if(tempPerson == null || !isDelete) {
			return false;
		}
		
		if(tempPerson == startPerson) {
			startPerson = tempPerson.getNextPerson();
		} else {
			currPerson = tempPerson.getNextPerson();
		}
		
		size--;
		return true;
	}
	
	public String[] getStrArr() {
		String[] strList = new String[size];
		Person currPerson = startPerson;
		
		for(int i = 0; i < size; i++) {
			strList[i] = currPerson.getName();
			currPerson = currPerson.getNextPerson();
		}
		
		return strList;
	}
	
	public int getSize() {
		return this.size;
	}
}

class Person{
	String name;
	Person nextPerson;
	
	public Person(){
		this.name = null;
		this.nextPerson = null;
	}
	public Person(String name) {
		this.name = name;
		nextPerson = null;
	}
	
	public String getName() {
		return name;
	}
	public Person getNextPerson() {
		return nextPerson;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	public void setNextPerson(Person nextPerson) {
		this.nextPerson = nextPerson;
	}
}
