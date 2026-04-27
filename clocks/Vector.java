import java.util.*;
public class Vector{
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int n,e;
		System.out.println("Enter no of process : ");
		n=sc.nextInt();
		System.out.println("Enter no of events : ");
		e=sc.nextInt();
		int[][] VC=new int[n][n];
		int[] msg=new int[n];
		for(int i=0;i<e;i++){
			int pid,type;
			System.out.println("For event "+(i+1));
			System.out.println("Enter process id : ");
			pid=sc.nextInt();
			System.out.println("Enter event type (1-send,2-recieve) : ");
			type=sc.nextInt();
			if(type==1){
				VC[pid][pid]++;
			}
			else{
				System.out.println("Enter reciever clock : ");
				for(int j=0;j<n;j++){
					msg[j]=sc.nextInt();
				}
				for(int j=0;j<n;j++){
					VC[pid][j]=Math.max(VC[pid][j],msg[j]);
				}
				VC[pid][pid]++;
			}
			for(int p=0;p<n;p++){
				System.out.print("For process : "+p+" [ ");
				for(int j=0;j<n;j++){
					System.out.print(VC[p][j]+" ");
				}
				System.out.print(" ] ");
			}
			
		}
	}
}
