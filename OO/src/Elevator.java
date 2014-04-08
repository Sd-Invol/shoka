import java.util.*;
import java.lang.*;

public class Elevator {
    public static void main(String[] args) {
    	Query Q = new Query();
    	Schedule OO = new Schedule(Q);
    	Work XX = new Work(Q);
    	OO.start();
    	XX.start();
    } 
}

class Work extends Thread {
	public Query Q;
	Work (Query MuQ) {
		Q = MuQ;
	}
	public void run() {
		Scanner cin = new Scanner(System.in);
    	while (cin.hasNext()) {
    		Q.put(cin.nextLine());
    	}
	}
}

class Schedule extends Thread {
	public Query Q;
	public int time = 0;
	public int floor = 1;
	public int Dir = 0;
	Schedule (Query MuQ) {
		Q = MuQ;
	}
	public void run() {
		while (true) {
			Q.get();
			if (true == true)  {// F_R
				if (Q.n > floor) {
					for (int i = floor ; i < Q.n ; ++ i) {
						output res = new output(i , 1);
						res.print();
						try {
							sleep(1000);
							++ time;
						} catch (InterruptedException e) {}
					}
					output res = new output(Q.n , 0);
					res.print();
					try {
						sleep(1000);
						++ time;
					} catch (InterruptedException e) {}
				} else {
					for (int i = floor ; i > Q.n ; -- i) {
						output res = new output(i , -1);
						res.print();
						try {
							sleep(1000);
							++ time;
						} catch (InterruptedException e) {}
					}
					output res = new output(Q.n , 0);
					res.print();
					try {
						sleep(1000);
						++ time;
					} catch (InterruptedException e) {}	
				}
				floor = Q.n;
			} 
		}
	}
	
}

class output{
	private int floor;
	public int Dir = 0;
	output (int F , int D) {
		floor = F;
		Dir = D;
	}
	void print() {
		System.out.print('(');
		System.out.print(floor);
		System.out.print(',');
		if (Dir == 0)
			System.out.print("S");
		else {
			System.out.print("P");
			System.out.print(",");	
			if (Dir == -1)
				System.out.print("DOWN");
			else
				System.out.print("UP");		
		}
		System.out.println(')');
	}
}

class Query {
	public boolean type;
	public int n;
	public String direct;
	public int time;
	
	private boolean available = false;
	
	public synchronized Query get() {
		while (available == false) {
            try {  
            	wait();       
            } 
            catch (InterruptedException e) { }        
        }
        available = false;
        notifyAll(); 
        return this;
	}
	public synchronized void put(String str) {
		while (available == true) {
            try {
            	wait();   
            } catch (InterruptedException e) { }        
        }
        int i , j;
		for (i = 2 ; i < str.length() ; ++ i)
			if (str.charAt(i) == ',')
				break;
		type = (str.substring(1 , i).equals("F_R"));
		j = i + 1;
		for (++ i ; i < str.length() ; ++ i) 
			if (str.charAt(i) == ',')
				break;
		n = Integer.parseInt(str.substring(j , i));
		j = i + 1;
		if (type) {
			for (++ i ; i < str.length() ; ++ i) 
				if (str.charAt(i) == ',')
					break;
			direct = str.substring(j , i);
			j = i + 1;
		}
		for (++ i ; i < str.length() ; ++ i) 
			if (str.charAt(i) == '}')
				break;
		time = Integer.parseInt(str.substring(j , i));
		available = true;
		notifyAll();
	}
}

