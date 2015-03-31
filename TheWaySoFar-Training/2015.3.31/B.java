import java.util.*;
import java.math.*;

public class Main {
    public static void main(String [] args) {
        Scanner cin = new Scanner(System.in);
        int n ;
        int bo[] = new int [2005];
        BigInteger p[] = new BigInteger [2005];
        p[0] = BigInteger.ONE;
        n = cin.nextInt();
        for (int i = 1 ; i <= n ; ++ i)
            p[i] = p[i - 1].multiply(BigInteger.valueOf(2));
        for (int i = n ; i > 0 ; -- i) {
            int x , y;
            x = cin.nextInt();
            y = cin.nextInt();
            if (x > y)
                bo[i] = 1;
            else
                bo[i] = 0;
		
        }
        BigInteger ans = BigInteger.ZERO;
        for (int i = n ; i > 0 ; -- i) {
            if (bo[i] == 1) {
                if (i == 1) {
                    ans = ans.add(BigInteger.valueOf(3));
                } else {
                    ans = ans.add(BigInteger.valueOf(4));
                    ans = ans.add(p[i - 1].subtract(BigInteger.ONE).multiply(BigInteger.valueOf(4)));
                }
				
            } else {
                ans = ans.add(BigInteger.valueOf(2));
                ans = ans.add(p[i - 1].subtract(BigInteger.ONE).multiply(BigInteger.valueOf(2)));
                bo[i - 1] ^= 1;				
            }
        }
        System.out.println(ans);
		
    }

}
