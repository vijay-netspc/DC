import java.util.*; 
enum ProcessState { 
RELEASED, WANTED, HELD 
} 
class Process extends Thread { 
int id; 
int clock = 0; 
int requestTime; 
ProcessState state = ProcessState.RELEASED; 
int totalProcesses; 
int replyCount = 0; 
List<Integer> deferred = new ArrayList<>(); 
static Process[] processes; 
Random rand = new Random(); 
Process(int id, int totalProcesses) { 
this.id = id; 
this.totalProcesses = totalProcesses; 
} 
void requestCS() { 
synchronized (this) { 
clock++; 
state = ProcessState.WANTED; 
requestTime = clock; 
replyCount = 0; 
System.out.println("\nProcess " + id + " requesting CS at time " + requestTime); 
} 
for (Process p : processes) { 
if (p.id != this.id) { 
new Thread(() -> { 
try { Thread.sleep(rand.nextInt(500)); } catch (Exception e) {} 
p.receiveRequest(this.id, this.requestTime); 
}).start(); 
} 
} 
} 
synchronized void receiveRequest(int senderId, int senderTime) { 
clock = Math.max(clock, senderTime) + 1; 
boolean sendReplyNow = false; 
if (state == ProcessState.RELEASED) { 
sendReplyNow = true; 
} 
else if (state == ProcessState.WANTED) { 
if (senderTime < requestTime || 
(senderTime == requestTime && senderId < id)) { 
sendReplyNow = true; 
} 
} 
if (sendReplyNow) { 
sendReply(senderId); 
} else { 
deferred.add(senderId); 
} 
} 
void sendReply(int receiverId) { 
new Thread(() -> { 
try { Thread.sleep(rand.nextInt(500)); } catch (Exception e) {} 
System.out.println("Process " + id + " sending REPLY to " + receiverId); 
processes[receiverId].receiveReply(this.id); 
}).start(); 
} 
synchronized void receiveReply(int senderId) { 
replyCount++; 
System.out.println("Process " + id + " received REPLY from " + senderId); 
if (replyCount == totalProcesses - 1) { 
enterCS(); 
} 
} 
void enterCS() { 
synchronized (this) { 
state = ProcessState.HELD; 
System.out.println("Process " + id + " ENTERING Critical Section"); 
} 
try { Thread.sleep(1000); } catch (Exception e) {} 
exitCS(); 
} 
void exitCS() { 
synchronized (this) { 
state = ProcessState.RELEASED; 
System.out.println("Process " + id + " EXITING Critical Section"); 
for (int pid : deferred) { 
sendReply(pid); 
} 
deferred.clear(); 
} 
} 
public void run() { 
try { 
Thread.sleep(rand.nextInt(1000)); 
} catch (Exception e) {} 
requestCS(); 
} 
} 
public class RicartAgarwalaDemo { 
public static void main(String[] args) { 
Scanner sc = new Scanner(System.in); 
System.out.print("Enter number of processes: "); 
int n = sc.nextInt(); 
Process.processes = new Process[n]; 
for (int i = 0; i < n; i++) { 
Process.processes[i] = new Process(i, n); 
} 
System.out.print("Enter number of processes requesting CS simultaneously: "); 
int requests = sc.nextInt(); 
Set<Integer> selected = new HashSet<>(); 
for (int i = 0; i < requests; i++) { 
System.out.print("Enter process ID (0 to " + (n-1) + "): "); 
int pid = sc.nextInt(); 
if (pid >= 0 && pid < n) { 
selected.add(pid); 
} else { 
System.out.println("Invalid ID"); 
i--; 
} 
} 
for (int pid : selected) { 
Process.processes[pid].start(); 
} 
sc.close(); 
} 
} 
