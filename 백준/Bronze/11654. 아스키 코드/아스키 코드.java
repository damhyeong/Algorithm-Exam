import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        String inputData = br.readLine();
        
        char character = inputData.charAt(0);
        
        int ASCII_DATA = (int)character;
        
        System.out.println(ASCII_DATA);
    }
}