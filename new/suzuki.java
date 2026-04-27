import java.util.*;
class Process{
	int[] RN;
	int id;
	Process(int id,int n){
		this.id=id;
		RN=new int[n];
	}
	void requestCS(Process[] process){
		RN[id]++;
		System.out.println("process :"+id+" requesting CS and RN="+Arrays.toString(RN));
		for(Process p:process){
			if(p.id!=this.id){
				p.recieverequest(id,RN[id]);
			}
		}
	}
	void recieverequest(int senderid,int senderRN){
		RN[senderid]=Math.max(RN[senderid],senderRN);
	}
}
class Token{
	int[] LN;
	Queue<Integer> queue=new LinkedList<>();
	Token(int n){
		LN=new int[n];
	}
}
class suzuki{
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int n;
		System.out.println("Enter no of process : ");
		n=sc.nextInt();
		Process[] p=new Process[n];
		for(int i=0;i<n;i++){
			p[i]=new Process(i,n);
		}
		Token token=new Token(n);
		System.out.println("Enter initial LN values : ");
		for(int i=0;i<n;i++){
			token.LN[i]=sc.nextInt();
		}
		System.out.println("Enter token holder id : ");
		int tokenholder=sc.nextInt();
		System.out.println("Intially token holder : "+tokenholder);
		System.out.println("Enter no of requests : ");
		int r=sc.nextInt();
		for(int i=0;i<r;i++){
			System.out.println("Enter process id requesting CS : ");
			int pid=sc.nextInt();		
			p[pid].requestCS(p);
		}		
		for(int i=0;i<n;i++){
			if(i!=tokenholder){
				if(p[tokenholder].RN[i]==token.LN[i]+1){
					token.queue.add(i);
				}
			}
		}
		System.out.println("Token holder enters CS...");
		System.out.println("process : "+tokenholder+"enters CS");
		token.LN[tokenholder]=p[tokenholder].RN[tokenholder];
		System.out.println("Updated LN :"+Arrays.toString(token.LN));
		while(!token.queue.isEmpty()){
			int next=token.queue.poll();
			System.out.println("Token passed to "+next);
			System.out.println("process : "+next+"enters CS");
			token.LN[next]=p[next].RN[next];
			System.out.println("Updated LN : "+Arrays.toString(token.LN));
		}
	}
}
