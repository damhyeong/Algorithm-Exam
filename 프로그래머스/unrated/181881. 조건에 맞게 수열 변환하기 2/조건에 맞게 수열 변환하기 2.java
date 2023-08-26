class Solution {
    public int solution(int[] arr) {
        int answer = 0;
        
        int[] preArr = arr;
        while(true){
            int[] newArr = new int[arr.length];
            for(int i = 0; i < arr.length; i++){
                int num = preArr[i];
                if(num >= 50 && num % 2 == 0){
                    newArr[i] = preArr[i] / 2;
                } else if(num < 50 && num % 2 == 1){
                    newArr[i] = preArr[i] * 2 + 1;
                } else {
                    newArr[i] = preArr[i];
                }
            }
            if(isSame(preArr, newArr))
                break;
            preArr = newArr;
            answer++;
        }
        return answer;
    }
    public static boolean isSame(int[] preArr, int[] newArr){
        for(int i = 0; i < preArr.length; i++){
            if(preArr[i] != newArr[i])
                return false;
        }
        return true;
    }
}