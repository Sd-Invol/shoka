import java.util.*;
import java.math.*;

public class Main {
    public static void main(String [] args) {
        Scanner cin = new Scanner(System.in);
        
        BigInteger n = cin.nextBigInteger();
        BigInteger res = BigInteger.ZERO; 
        while (n.compareTo(BigInteger.ZERO) > 0) {
            BigInteger x = n.subtract(BigInteger.valueOf(2)).divide(BigInteger.valueOf(2));
            res = res.add(n.subtract(x));
            n = x.subtract(BigInteger.valueOf(2)).divide(BigInteger.valueOf(2));
        }       
        System.out.println(res);
    }
}
