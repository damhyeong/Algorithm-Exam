import java.util.*;

class Solution {
    public String[] solution(String[] strings, int n) {
        String[] answer = {};
        List<String> ansList = new ArrayList<>();
        
        List<ArrayList<String>> list = new ArrayList<>();
        
        for(int i = 'a'; i <= 'z'; i++)
            list.add(new ArrayList<String>());
        
        for(int i = 0; i < strings.length; i++){
            char ch = strings[i].charAt(n);
            list.get(ch - 'a').add(strings[i]);
        }
        
        for(int i = 0; i < list.size(); i++)
            Collections.sort(list.get(i));
        
        for(int i = 0; i < list.size(); i++){
            if(!list.get(i).isEmpty()){
                for(int j = 0; j < list.get(i).size(); j++){
                    ansList.add(list.get(i).get(j));
                }
            }
        }
        
        answer = ansList.toArray(new String[ansList.size()]);
        
        return answer;
    }
}