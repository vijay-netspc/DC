import java.util.*;

class Process {
    int id;
    int replies = 0;
    boolean requesting = false;
    int reqtime = 0;

    List<Integer> deferred = new ArrayList<>();

    Process(int id) {
        this.id = id;
    }

    void requestCS() {
        requesting = true;
        reqtime = ++LogicalClock.time;
        System.out.println("Process " + id + " requesting CS at time " + reqtime);
    }

    boolean shouldreply(Process sender) {
        if (!requesting) return true;

        if (sender.reqtime < this.reqtime) return true;

        if (sender.reqtime == this.reqtime && sender.id < this.id) return true;

        return false;
    }

    void receiveRequest(Process sender) {
        if (shouldreply(sender)) {
            System.out.println("Process " + this.id + " reply to process " + sender.id);
            sender.reply_count();
        } else {
            System.out.println("Process " + this.id + " put in deferred for " + sender.id);
            deferred.add(sender.id);
        }
    }

    void reply_count() {
        replies++;
    }

    void tryenterCS(int n) {
        if (requesting && replies == n - 1) {
            enterCS(n);
        }
    }

    void enterCS(int n) {
        System.out.println("Process " + this.id + " entered CS");
        exitCS(n);
    }

    void exitCS(int n) {
        requesting = false;
        replies = 0;

        System.out.println("Process " + this.id + " exited CS");

        for (int pid : deferred) {
            System.out.println("Process " + this.id + " sends deferred reply to " + pid);
            Main.process[pid].reply_count();   // deliver reply
        }

        deferred.clear();
        System.out.println();
    }
}

class LogicalClock {
    static int time = 0;
}

public class Ricart {
    static Process[] process;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter no of processes: ");
        int n = sc.nextInt();

        process = new Process[n];

        for (int i = 0; i < n; i++) {
            process[i] = new Process(i);
        }

        System.out.print("Enter no of requests: ");
        int r = sc.nextInt();

        for (int i = 0; i < r; i++) {
            System.out.print("Enter process id requesting CS: ");
            int pid = sc.nextInt();
            process[pid].requestCS();
        }

        System.out.println("\n--- Processing Requests ---");

        for (Process p1 : process) {
            if (p1.requesting) {
                for (Process p2 : process) {
                    if (p1.id != p2.id) {
                        p2.receiveRequest(p1);
                    }
                }
            }
        }

        System.out.println("\n--- First CS Check ---");

        for (Process p : process) {
            p.tryenterCS(n);
        }

        System.out.println("\n--- Rechecking after deferred replies ---");

        for (Process p : process) {
            p.tryenterCS(n);
        }
    }
}
