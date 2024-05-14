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
		// PracStringHashSet map = new PracStringHashSet();
		PHashSet map = new PHashSet();
		
		for(int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			String name = st.nextToken();
			String doing = st.nextToken();
			
			if(doing.equals("enter")) {
				map.add(name);
			} else if(doing.equals("leave")) {
				map.remove(name);
			}
		}
		
		strArr = map.toStringArray();
		
		// ----------------------------------------------------------------------
		// mergeSort
		
		boolean isCompareLen = false;
		mergeSort(strArr, isCompareLen);
		
		// ----------------------------------------------------------------------
		
//		dualPivotQuickSort(strArr, 0, strArr.length - 1);
		
		
		// Printing Results reverse.
		StringBuilder sb = new StringBuilder();
		for(int i = strArr.length - 1; i >= 0; i--)
			sb.append(strArr[i] + "\n");
		
//		for(int i = 0; i < strList.size(); i++)
//			sb.append(strList.get(i) + "\n");
		
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
	
	public static void dualPivotQuickSort(String[] strArr, int low, int high) {
		if(high < low)
			return;
		
		if(compareStr(strArr[low], strArr[high]) == -1)
			swap(strArr, low, high);
		
		int leftPivotIdx = low + 1;
		int rightPivotIdx = high - 1;
		int iter = low + 1;
		
		while(iter <= rightPivotIdx) {
			if(compareStr(strArr[iter], strArr[low]) == 1) {
				swap(strArr, iter++, leftPivotIdx++);
			}else if(compareStr(strArr[iter], strArr[high]) == -1) {
				swap(strArr, iter, rightPivotIdx--);
			} else 
				iter++;
			
		}
		
		swap(strArr, low, --leftPivotIdx);
		swap(strArr, high, ++rightPivotIdx);
		
		dualPivotQuickSort(strArr, low, leftPivotIdx - 1);
		dualPivotQuickSort(strArr, leftPivotIdx + 1, rightPivotIdx - 1);
		dualPivotQuickSort(strArr, rightPivotIdx + 1, high);
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

//--------------------------------------------------------------------------------------------------


class PHashSet {
    PSet[] set; // Hashing Arrays.
    private int size = 0;
    private int hashNum;

    public PHashSet() {
        this.hashNum = 200;
        set = new PSet[this.hashNum];

        for (int i = 0; i < this.hashNum; i++)
            set[i] = new PSet();
    }

    public boolean add(String name) {
        if (name == null)
            return false;

        int hash = Math.abs(name.hashCode()) % this.hashNum;

        if (set[hash] == null)
            set[hash] = new PSet();

        boolean isAdd = set[hash].add(name);

        if (isAdd)
            size++;
        return isAdd;
    }

    public boolean remove(String name) {
        if (name == null)
            return false;

        int hash = Math.abs(name.hashCode()) % this.hashNum;

        boolean isDelete = set[hash].remove(name);

        if (isDelete) {
            size--;
        }

        if (set[hash].getFirstNode() == null)
            set[hash] = new PSet();

        return isDelete;
    }

    public boolean contains(String name) {
        if (name == null)
            return false;

        int hash = Math.abs(name.hashCode()) % this.hashNum;

        return set[hash].isContain(name);
    }

    public int size() {
        return this.size;
    }

    private void setHashNum(int hashNum) { // 초기에만 사용 할 수 있게 만들어야 한다. - hash 배열 망가짐.
        this.hashNum = hashNum;
    }

    public int getHashNum() {
        return this.hashNum;
    }

    public void clear() {
        this.set = new PSet[this.hashNum];
        this.size = 0;

        for (int i = 0; i < this.hashNum; i++) {
            this.set[i] = new PSet();
        }
    }

    public String[] toStringArray() {
        List<String> strList = new ArrayList<>();

        for (int i = 0; i < this.hashNum; i++) {
            PSet tempSet = this.set[i];

            if (tempSet.getFirstNode() != null) {
                String[] tempStrArr = tempSet.toStringArray();

                for (String s : tempStrArr) {
                    strList.add(s);
                }
            }
        }
        return strList.toArray(new String[0]);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < this.hashNum; i++) {
            if (this.set[i].getFirstNode() == null)
                continue;

            String[] partStrArr = this.set[i].toStringArray();
            for (String s : partStrArr)
                sb.append(s).append(" ");
        }

        return sb.toString();
    }
}

class PSet {
    private PNode treeNode;
    private int size = 0;

    public PSet() {
        treeNode = null;
    }

    public boolean add(String name) {
        if (name == null)
            return false;

        if (treeNode == null) {
            treeNode = new PNode(name);
            size++;
            return true;
        }

        PNode currNode = treeNode;
        PNode tempNode = currNode;
        boolean isLeft = true;

        while (currNode != null) {
            String currName = currNode.getName();

            if (currName.compareTo(name) == 0)
                return false;
            else if (currName.compareTo(name) > 0) {
                tempNode = currNode;
                isLeft = true;
                currNode = currNode.getLeftNode();
            } else {
                tempNode = currNode;
                isLeft = false;
                currNode = currNode.getRightNode();
            }
        }

        if (isLeft) {
            tempNode.setLeftNode(new PNode(name));
        } else {
            tempNode.setRightNode(new PNode(name));
        }
        size++;
        return true;
    }

    public boolean remove(String name) {
        if (name == null || treeNode == null)
            return false;

        PNode currNode = treeNode;
        PNode tempNode = treeNode;
        boolean isLeft = true;

        while (currNode != null) {
            if (currNode.getName().compareTo(name) == 0) {
                break;
            } else if (currNode.getName().compareTo(name) > 0) {
                tempNode = currNode;
                currNode = currNode.getLeftNode();
                isLeft = true;
            } else {
                tempNode = currNode;
                currNode = currNode.getRightNode();
                isLeft = false;
            }
        }

        if (currNode == null) {
            return false;
        }

        if (currNode.getLeftNode() == null && currNode.getRightNode() == null) {
            if (currNode == treeNode) {
                treeNode = null;
            } else if (isLeft) {
                tempNode.setLeftNode(null);
            } else {
                tempNode.setRightNode(null);
            }
        } else if (currNode.getRightNode() == null) {
            if (currNode == treeNode) {
                treeNode = currNode.getLeftNode();
            } else if (isLeft) {
                tempNode.setLeftNode(currNode.getLeftNode());
            } else {
                tempNode.setRightNode(currNode.getLeftNode());
            }
        } else if (currNode.getLeftNode() == null) {
            if (currNode == treeNode) {
                treeNode = currNode.getRightNode();
            } else if (isLeft) {
                tempNode.setLeftNode(currNode.getRightNode());
            } else {
                tempNode.setRightNode(currNode.getRightNode());
            }
        } else {
            PNode successor = getSuccessor(currNode);
            if (currNode == treeNode) {
                treeNode = successor;
            } else if (isLeft) {
                tempNode.setLeftNode(successor);
            } else {
                tempNode.setRightNode(successor);
            }
            successor.setLeftNode(currNode.getLeftNode());
        }

        size--;
        return true;
    }

    private PNode getSuccessor(PNode delNode) {
        PNode successorParent = delNode;
        PNode successor = delNode;
        PNode currNode = delNode.getRightNode();

        while (currNode != null) {
            successorParent = successor;
            successor = currNode;
            currNode = currNode.getLeftNode();
        }

        if (successor != delNode.getRightNode()) {
            successorParent.setLeftNode(successor.getRightNode());
            successor.setRightNode(delNode.getRightNode());
        }

        return successor;
    }

    public boolean isContain(String name) {
        PNode currNode = treeNode;

        while (currNode != null) {
            String currName = currNode.getName();

            if (currName.compareTo(name) == 0)
                return true;
            else if (currName.compareTo(name) > 0) {
                currNode = currNode.getLeftNode();
            } else {
                currNode = currNode.getRightNode();
            }
        }

        return false;
    }

    public int getSize() {
        return this.size;
    }

    public PNode getFirstNode() {
        return this.treeNode;
    }

    public void clear() {
        treeNode = null;
        size = 0;
    }

    public String[] toStringArray() {
        List<String> strList = new ArrayList<>();
        inorder(treeNode, strList);
        return strList.toArray(new String[0]);
    }

    private void inorder(PNode node, List<String> strList) {
        if (node != null) {
            inorder(node.getLeftNode(), strList);
            strList.add(node.getName());
            inorder(node.getRightNode(), strList);
        }
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        Queue<PNode> queue = new LinkedList<>();

        if (treeNode == null)
            return "Empty";

        queue.add(treeNode);

        while (!queue.isEmpty()) {
            PNode popNode = queue.poll();
            sb.append(popNode.getName()).append(" ");

            PNode leftNode = popNode.getLeftNode();
            PNode rightNode = popNode.getRightNode();

            if (leftNode != null)
                queue.add(leftNode);
            if (rightNode != null)
                queue.add(rightNode);
        }

        return sb.toString();
    }
}

/** 
 * PNode is Practical Node.
 * This node exisiting for Practice.
 * Based on String value, and Binary Search Tree.
 */
class PNode {
    private String name;
    private PNode leftNode;
    private PNode rightNode;

    public PNode() {
        this.name = null;
        this.leftNode = null;
        this.rightNode = null;
    }

    public PNode(String name) {
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void setLeftNode(PNode node) {
        this.leftNode = node;
    }

    public PNode getLeftNode() {
        return this.leftNode;
    }

    public void setRightNode(PNode node) {
        this.rightNode = node;
    }

    public PNode getRightNode() {
        return this.rightNode;
    }
}

/**
class PHashSet{
	PSet[] set; // Hashing Arrays.
	private int size = 0;
	private int hashNum;
	
	public PHashSet() {
		this.hashNum = 200;
		set = new PSet[this.hashNum];
		
		for(int i = 0; i < this.hashNum; i++)
			set[i] = new PSet();
	}
	
	public boolean add(String name) {
		if(name == null)
			return false;
		
		int hash = 0;
		for(int i = 0; i < name.length(); i++)
			hash = (hash + name.charAt(i)) % this.hashNum;
		
		if(set[hash] == null) 
			set[hash] = new PSet();
		
		boolean isAdd = set[hash].add(name);
		
		if(isAdd)
			size++;
		return isAdd;
	}
	
	public boolean remove(String name) {
		if(name == null)
			return false;
		
		int hash = 0;
		for(int i = 0; i < name.length(); i++)
			hash = (hash + name.charAt(i)) % this.hashNum;
		
//		if(set[hash] == null)
//			return false;
		
		boolean isDelete = set[hash].remove(name);
		
		if(isDelete) {
			size--;
		}
		
		if(set[hash].getFirstNode() == null)
			set[hash] = new PSet();
		
		return isDelete;
	}
	
	public boolean contains(String name) {
		if(name == null)
			return false;
		
		int hash = 0;
		
		for(int i = 0; i < name.length(); i++)
			hash = (hash + name.charAt(i)) % this.hashNum;
		
//		if(set[hash] == null)
//			return false;
		
		return set[hash].isContain(name);
	}
	
	public int size() {
		return this.size;
	}
	
	private void setHashNum(int hashNum) { // 초기에만 사용 할 수 있게 만들어야 한다. - hash 배열 망가짐.
		this.hashNum = hashNum;
	}
	public int getHashNum() {
		return this.hashNum;
	}
	
	public void clear() {
		this.set = new PSet[this.hashNum];
		this.size = 0;
		
		for(int i = 0; i < this.hashNum; i++) {
			this.set[i] = new PSet();
		}
	}
	
	public String[] toStringArray() {
//		String[] strArr = new String[this.size];
		List<String> strList = new ArrayList<>();
		
		int index = 0;
		for(int i = 0; i < this.hashNum; i++) {
			PSet tempSet = this.set[i];
			
			if(tempSet.getFirstNode() != null) {
				String[] tempStrArr = tempSet.toStringArray();
				
				for(int j = 0; j < tempStrArr.length; j++) {
//					strArr[index++] = tempStrArr[j];
					strList.add(tempStrArr[j]);
				}
			}
		}
		String[] strArr = new String[strList.size()];
		for(int i = 0; i < strArr.length; i++)
			strArr[i] = strList.get(i);
		
		return strArr;
	}
	
	public String toString() {
		
		StringBuilder sb = new StringBuilder();
		
		for(int i = 0; i < this.hashNum; i++) {
			if(this.set[i].getFirstNode() == null)
				continue;
			
			String[] partStrArr = this.set[i].toStringArray();
			for(int j = 0; j < partStrArr.length; j++)
				sb.append(partStrArr[j] + " ");
		}
		
		return sb.toString();
	}
}


class PSet {
	private PNode treeNode;
	private int size = 0;
	
	public PSet(){
		treeNode = null;
	}
	
	public boolean add(String name) {
		if(name == null)
			return false;
		
		if(treeNode == null) {
			treeNode = new PNode(name);
			size++;
			return true;
		}
		
		PNode currNode = treeNode;
		PNode tempNode = currNode;
		boolean isLeft = true;
		
		while(currNode != null) {
			String currName = currNode.getName();
			
			if(compareStr(currName, name) == 0)
				return false;
			else if(compareStr(currName, name) == -1) {
				tempNode = currNode;
				isLeft = true;
				currNode = currNode.getLeftNode();
			} else { // compareStr(currName, name) == 1 
				tempNode = currNode;
				isLeft = false;
				currNode = currNode.getRightNode();
			}
		}
		
		// 같은 요소가 존재하지 않음.
		if(isLeft) {
			tempNode.setLeftNode(new PNode(name));
		} else {
			tempNode.setRightNode(new PNode(name));
		}
		size++;
		return true;
	}
	
	public boolean remove(String name) {
		// 내부에 요소가 없거나, 입력값이 null로 잘못됨. 
		if(name == null || treeNode == null)
			return false;
		
		PNode currNode = treeNode;
		PNode tempNode = treeNode;
		
		boolean isLeft = true;
		
		
		while(currNode != null) {
			if(compareStr(currNode.getName(), name) == 0) {
				break;
			} else if(compareStr(currNode.getName(), name) == -1) {
				tempNode = currNode;
				currNode = currNode.getLeftNode();
				isLeft = true;
			} else {
				tempNode = currNode;
				currNode = currNode.getRightNode();
				isLeft = false;
			}
		}
		
		// 바로 탐색 첫 번째에서 삭제 할 노드를 찾았을 경우, 루트 노드를 삭제하기 때문에 골아프다..
		boolean isFirstElement = (currNode == treeNode) ? true : false;
		
		//삭제 할 노드를 찾았을 경우 
		if(currNode != null) {
			
			PNode leftNode = currNode.getLeftNode();
			PNode rightNode = currNode.getRightNode();
			
			// 마지막 노드일 경우 - 차수 0
			if(leftNode == null && rightNode == null) {
				if(isFirstElement) {
					treeNode = null;
					size = 0;
					return true;
				}
				if(isLeft)
					tempNode.setLeftNode(null);
				else
					tempNode.setRightNode(null);
				size--;
				return true;
			}
			
			// 한 개의 노드를 가지고 있을 경우 - 차수 1
			if(leftNode == null || rightNode == null) {
				PNode sideNode = (leftNode == null) ? rightNode : leftNode;
				
				if(isFirstElement) {
					treeNode = sideNode;
					size--;
					return true;
				}
				
				if(isLeft)
					tempNode.setLeftNode(sideNode);
				else
					tempNode.setRightNode(sideNode);
				
				size--;
				return true;
			}
			
			// 두 개의 노드(모두 가진 상태)를 가지고 있을 경우 - 차수 2 - 오른쪽 트리를 선택함. (왼쪽 트리로도 가능)
			PNode rightCurrNode = currNode.getRightNode();
			PNode rightTempNode = rightCurrNode;
			
			// 오른쪽 트리에서 계속해서 왼쪽을 선택하여 비교 할 노드와 가장 가까우며 큰 값을 선택한다.
			while(rightCurrNode.getLeftNode() != null) {
				rightTempNode = rightCurrNode;
				rightCurrNode = rightCurrNode.getLeftNode();
			}
			
			// rightCurrNode가 마지막 left 노드이며, rightTempNode에 가장 가까운 노드가 저장되어 있다.
			
			// 1. 먼저 가장 가까운 값을 삭제하는 곳에 값으로 저장한다.
			currNode.setName(rightCurrNode.getName());
			
			if(treeNode.getRightNode() == rightCurrNode) {
				treeNode.setRightNode(null);
				size--;
				return true;
			}
			// 2. 찾은 가장 가까운 값의 노드를 없앤다.
			rightTempNode.setLeftNode(null);
			size--; 
			return true;
		}
		
		
		// 삭제 할 노드를 찾지 못함. 
		return false;
	}
	
	public boolean isContain(String name) {
		// Algorithm for find something. - base on treeNode.
		// needs some values for contain information.
		PNode currNode = treeNode;
		
		while(currNode != null) {
			String currName = currNode.getName();
			
			if(compareStr(currName, name) == 0)
				return true;
			else if(compareStr(currName, name) == -1) {
				currNode = currNode.getLeftNode();
			} else {
				currNode = currNode.getRightNode();
			}
		}
		
		return false;
	}
	
	public boolean swapNode(PNode node1, PNode node2) {
		// 작성하지 않아도 될 듯. 일단.
		
		return false;
	}
	
	public int getSize() {
		return this.size;
	}
	
	public PNode getFirstNode() {
		return this.treeNode;
	}
	
	public int compareStr(String str1, String str2) {
		int len = (str1.length() <= str2.length()) ? str1.length() : str2.length();
		
		int result = 0;
		
		for(int i = 0; i < len; i++) {
			char ch1 = str1.charAt(i);
			char ch2 = str2.charAt(i);
			
			if(ch1 == ch2)
				continue;
			else if(ch1 < ch2)
				return 1;
			else
				return -1;
		}
		
		if(str1.length() < str2.length())
			return 1;
		else if(str1.length() > str2.length())
			return -1;
		
		return result;
	}
	
	public void clear() {
		treeNode = null;
		size = 0;
	}
	
	public String[] toStringArray() {
		Queue<PNode> queue = new LinkedList<>();
//		String[] strArr = new String[size];
		List<String> strList = new ArrayList<>();
		
//		int index = 0;
		
		// 시작 
		queue.add(treeNode);
		
		
		while(!queue.isEmpty()) {
			PNode popNode = queue.poll();
			
			String getName = popNode.getName();
			
//			strArr[index++] = getName;
			strList.add(getName);
			
			PNode leftNode = popNode.getLeftNode();
			PNode rightNode = popNode.getRightNode();
			
			if(leftNode != null)
				queue.add(leftNode);
			else if(rightNode != null)
				queue.add(rightNode);
			
			
		}
		
		String[] strArr = new String[strList.size()];
		for(int i = 0; i < strArr.length; i++)
			strArr[i] = strList.get(i);
		
		return strArr;
	}
	
	
	public String toString() {
		Queue<PNode> queue = new LinkedList<>();
		String str = "";
		
		int index = 0;
		
		// 시작 
		
		if(size == 0)
			return "Empty";
		
		queue.add(treeNode);
		
		while(!queue.isEmpty()) {
			PNode popNode = queue.poll();
			
			str += popNode.getName() + " ";
			
			PNode leftNode = popNode.getLeftNode();
			PNode rightNode = popNode.getRightNode();
			
			if(leftNode.getName() != null)
				queue.add(leftNode);
			else if(rightNode.getName() != null)
				queue.add(rightNode);
		}
		
		return str;
		
	}
}


class PNode {
	private String name;
	private PNode leftNode;
	private PNode rightNode;
	
	public PNode() {
		this.name = null; this.leftNode = null; this.rightNode = null;
	}
	
	public PNode(String name) {
		this.name = name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	public String getName() {
		return this.name;
	}
	
	public void setLeftNode(PNode node) {
		this.leftNode = node;
	}
	public PNode getLeftNode() {
		return this.leftNode;
	}
	
	public void setRightNode(PNode node) {
		this.rightNode = node;
	}
	public PNode getRightNode() {
		return this.rightNode;
	}
}*/

// --------------------------------------------------------------------------------------------------
/**
class PracStringHashSet{
	PracStringSet[] setArr;
	public static int bucket = 200;
	int count = 0;
	
	public PracStringHashSet() {
		// 디폴트로 50개 잡아보자 
		setArr = new PracStringSet[bucket];
	}
	
	public void add(String name) {
		if(name == null)
			return;
		
		int hash = 0;
		
//		for(int i = 0; i < name.length(); i++)
//			hash = (hash + name.charAt(i)) % bucket;
		
		hash = name.charAt(0) % 200;
		
		if(setArr[hash] == null)
			setArr[hash] = new PracStringSet();
		
		if(setArr[hash].isContain(name))
			return;
		
		setArr[hash].put(name);
		count++;
	}
	
	public boolean remove(String name) {
		if(name == null)
			return false;
		
		int hash = 0;
		
//		for(int i = 0; i < name.length(); i++)
//			hash = (hash + name.charAt(i)) % bucket;
		
		hash = name.charAt(0) % 200;
		
		if(setArr[hash] == null)
			return false;
		
		boolean isDelete = setArr[hash].delete(name);
		
		count = isDelete ? count - 1 : count;
		
		if(setArr[hash].getSize() == 0)
			setArr[hash] = null;
		
		return isDelete;
	}
	
	public boolean contains(String name) {
		if(name == null)
			return false;
		
		int hash = 0;
		
//		for(int i = 0; i < name.length(); i++)
//			hash = (hash + name.charAt(i)) % bucket;
		
		hash = name.charAt(0) % 200;
		
		if(setArr[hash] == null)
			return false;
		
		return setArr[hash].isContain(name);
	}
	
	public String[] getStrArr() {
		String[] strArr = new String[count];
		
		int index = 0;
		
		for(int i = 0; i < setArr.length; i++) {
			if(setArr[i] == null)
				continue;
			
			String[] tempArr = setArr[i].getStrArr();
			
			for(int j = 0; j < tempArr.length; j++) 
				strArr[index++] = tempArr[j];
		}
		
		return strArr;
	}
	
	public String toString() {
		String[] strArr;
		
		strArr = this.getStrArr();
		
		String returnStr = "";
		
		for(int i = 0; i < strArr.length; i++)
			returnStr += strArr[i] + " ";
		
		return returnStr;
	}
	
	public void clear() {
		setArr = new PracStringSet[bucket];
		count = 0;
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
	
	public boolean put(String name) {
		if(name == null)
			return false;
		
		if(size == 0) { // setting my personal Set Class.
			startPerson = new Person(name);
			currentPerson = this.startPerson; // set address to start.
		} else {
			// Person newPerson = new Person(name);
			currentPerson.setNextPerson(new Person(name));
			currentPerson = currentPerson.getNextPerson(); // Move to Next Address.
		}
		size++;
		return true;
	}
	
	public boolean delete(String name) {
		if(name == null)
			return false;
		
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
	
	public boolean isContain(String name) {
		if(name == null)
			return false;
		
		Person tempPerson = startPerson;
		Person currPerson = tempPerson;
		
		boolean isContain = false;
		while(tempPerson != null) {
			if(name.equals(tempPerson.getName())) {
				isContain = true;
				break;
			}
			currPerson = tempPerson;
			tempPerson = tempPerson.getNextPerson();
		}
		
		if(tempPerson == null || !isContain)
			return false;
		
		return isContain;
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
*/