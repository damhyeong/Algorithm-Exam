
import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		Integer notKorea = Integer.parseInt(br.readLine());
		
		Integer koreaYear = notKorea - (2541 - 1998);
		
		System.out.println(koreaYear);
	}

}
