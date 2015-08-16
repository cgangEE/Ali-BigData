import java.io.*;
import java.util.*;
import net.sf.chineseutils.*;

public class TransWord{

	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		while (in.hasNext()){
			String s=in.next();
			try{
				s = ChineseUtils.big5ToGb(s);
			} catch(Exception e){}
			System.out.println(s);
		}
	}
};
