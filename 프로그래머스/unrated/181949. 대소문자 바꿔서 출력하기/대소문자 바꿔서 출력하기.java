import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        
        char[] chStr = br.readLine().toCharArray();
        for(int i = 0; i < chStr.length; i++){
            char ch = chStr[i];
            if('a' <= ch && ch <= 'z')
                ch = (char)('A' + ch - 'a');
            else if('A' <= ch && ch <= 'Z')
                ch = (char)('a' + ch - 'A');
            chStr[i] = ch;
        }
        String str = new String(chStr);
        bw.write(str);
        bw.flush();
        bw.close();
        br.close();
    }
}