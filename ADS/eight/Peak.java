import java.util.Scanner;
public class Peak {
	final static int maxn = 30004;  
	final static int M = 10001;  
	static int a[] = new int[maxn], c[] = new int[maxn];
	static int up[] = new int[maxn], down[] = new int[maxn];
	static int n, idx, len, offset;  
	static int lowbit(int x) { return x &-x; }
	  
	static void add(int x, int y) {
		for (int i = x; i <= maxn; i += lowbit(i))
			c[i] = c[i]>y?c[i]:y;
	}   
	static int sum(int x) {
		int res = 0;
		for (int i = x; i != 0; i -= lowbit(i))
			res = res>c[i]?res:c[i];
		return res;
	} 
	static int abs(int x){
		if(x>0)return x;
		else return -x;
	}
	@SuppressWarnings("resource")
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		n = s.nextInt();
		for(int i = 1; i <= n; i++) {
			a[i] = s.nextInt();
			a[i]+=M;
		}
		for(int i = 1; i <= n; i++) {  
	        up[i] = sum(a[i] - 1) + 1;  
	        add(a[i], up[i]);  
	    }
		for(int i = 0; i < maxn; i++)c[i] = 0;
	    for(int i = n; i >= 1; i--) {  
	        down[i] = sum(a[i] - 1) + 1;  
	        add(a[i], down[i]);  
	    }  
	    offset = n + 1;  
	    idx = len = 1;  
	    for(int i = 1; i <= n; i++) {  
	        if (up[i] == 1 || down[i] == 1) continue;  
	        if (up[i] + down[i] - 1 >len)  
	        {  
	            len = up[i] + down[i] - 1;  
	            idx = i;  
	            offset = abs(up[i] - down[i]);  
	        }  
	        else if (up[i] + down[i] - 1 == len && offset > abs(up[i] - down[i]))  
	        {  
	            idx = i;  
	            offset = abs(up[i] - down[i]);  
	        }  
	    }  
	    if (len > 1) {
	    	System.out.print(len);
	    	System.out.print(' ');
	    	System.out.print(idx);
	    	System.out.print(' ');
	    	System.out.println(a[idx]-M);  
	    }
	    else System.out.println("No peak shape");  
	}
}
