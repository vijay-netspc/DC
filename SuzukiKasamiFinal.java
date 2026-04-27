import java.util.*; 
class Token { 
    int[] LN; 
    Queue<Integer> Q; 
 
    public Token(int n) { 
        LN = new int[n]; 
        Q = new LinkedList<>(); 
    } 
 
    public void printToken(int siteId) { 
        System.out.println("TOKEN at Site " + siteId); 
        System.out.println("LN: " + Arrays.toString(LN)); 
        System.out.println("Queue: " + Q); 
    } 
} 
 
class Site extends Thread { 
 
    int id; 
    int n; 
    int[] RN; 
    boolean hasToken = false; 
 
    static Token token; 
    static Site[] sites; 
 
    public Site(int id, int n) { 
        this.id = id; 
        this.n = n; 
        RN = new int[n]; 
    } 
 
    // Print RN 
    public void printRN() { 
        System.out.println("Site " + id + " RN: " + Arrays.toString(RN)); 
    } 
 
    // ================= REQUEST CS ================= 
    public void requestCS() { 
        synchronized (Site.class) { 
            RN[id]++; 
            System.out.println("\n[REQUEST] Site " + id); 
            printRN(); 
 
            for (int i = 0; i < n; i++) { 
                if (i != id) { 
                    sites[i].receiveRequest(id, RN[id]); 
                } 
            } 
 
            if (hasToken) { 
                executeCS(); 
            } 
        } 
    } 
 
    // ================= RECEIVE REQUEST ================= 
    public synchronized void receiveRequest(int i, int sn) { 
        RN[i] = Math.max(RN[i], sn); 
 
        System.out.println("[RECEIVE REQUEST] Site " + id + " from " + i); 
        printRN(); 
 
        if (hasToken && RN[i] == token.LN[i] + 1) { 
            hasToken = false; 
            System.out.println("[TOKEN SENT] " + id + " → " + i); 
            sites[i].receiveToken(token); 
        } 
    } 
 
    // ================= RECEIVE TOKEN ================= 
    public synchronized void receiveToken(Token t) { 
        token = t; 
        hasToken = true; 
 
        System.out.println("\n[RECEIVE TOKEN] Site " + id); 
        token.printToken(id);   
 
        executeCS(); 
    } 
 
    // ================= EXECUTE CS ================= 
    public void executeCS() { 
        System.out.println("\n>>> Site " + id + " ENTERING CS"); 
 
        try { 
            Thread.sleep(1000); 
        } catch (Exception e) {} 
 
        releaseCS(); 
    } 
 
    // ================= RELEASE CS ================= 
    public synchronized void releaseCS() { 
        System.out.println("<<< Site " + id + " EXITING CS"); 
 
        // Update LN 
        token.LN[id] = RN[id]; 
        System.out.println("[LN UPDATED]"); 
        token.printToken(id);   
 
        // Update Queue 
        for (int j = 0; j < n; j++) { 
            if (j != id && !token.Q.contains(j) && RN[j] == token.LN[j] + 1) { 
                token.Q.add(j); 
                System.out.println("[QUEUE ADD] " + j); 
                token.printToken(id);  
            } 
        } 
 
        // Send token 
        if (!token.Q.isEmpty()) { 
            int next = token.Q.poll(); 
            hasToken = false; 
 
            System.out.println("[TOKEN TRANSFER] " + id + " → " + next); 
            sites[next].receiveToken(token); 
        } else { 
            System.out.println("[TOKEN IDLE at Site " + id + "]"); 
        } 
    } 
 
    public void run() { 
        requestCS(); 
    } 
} 
 
public class SuzukiKasamiFinal { 
 
    public static void main(String[] args) { 
 
        Scanner sc = new Scanner(System.in); 
 
        System.out.print("Enter number of sites: "); 
        int n = sc.nextInt(); 
 
        Site.sites = new Site[n]; 
 
        for (int i = 0; i < n; i++) { 
            Site.sites[i] = new Site(i, n); 
        } 
 
        // Initial token at Site 0 
        Site.token = new Token(n); 
        Site.sites[0].hasToken = true; 
 
        System.out.println("\nInitial token at Site 0"); 
        Site.token.printToken(0);   
 
        System.out.print("\nEnter number of requests: "); 
        int r = sc.nextInt(); 
 
        System.out.println("Enter site IDs:"); 
 
        List<Thread> threads = new ArrayList<>(); 
 
        for (int i = 0; i < r; i++) { 
            int id = sc.nextInt(); 
            threads.add(new Thread(Site.sites[id])); 
        } 
 
        // Start all threads (parallel requests) 
        for (Thread t : threads) { 
            t.start(); 
        } 
 
        // Wait 
        for (Thread t : threads) { 
            try { 
                t.join(); 
            } catch (Exception e) {} 
        } 
 
        sc.close(); 
    } 
}
