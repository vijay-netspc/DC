import java.util.*;
public class Scalar{
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int n,e;
		System.out.println("Enter no of process : ");
		n=sc.nextInt();
		System.out.println("Enter no of events : ");
		e=sc.nextInt();
		int[] clock=new int[n];
		for(int i=0;i<e;i++){
			int pid,type,recv_clock=0;
			System.out.println("For event "+(i+1));
			System.out.println("Enter process id : ");
			pid=sc.nextInt();
			System.out.println("Enter event type (1-send,2-recieve) : ");
			type=sc.nextInt();
			if(type==1){
				clock[pid]++;
			}
			else{
				System.out.println("Enter sender clock value : ");
				recv_clock=sc.nextInt();
				clock[pid]=Math.max(recv_clock,clock[pid])+1;
			}
			for(int j=0;j<n;j++){
				System.out.println("For process :"+j + "=" +clock[j]);
			}
			System.out.println();
		}
	}
}
