import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.net.ServerSocket;
import java.io.IOException;

public class PerformanceTest {

    private static void hardWork(CountDownLatch latch, Integer complexity) {
        System.out.println("Start: " + System.currentTimeMillis());

        List<String> a = new ArrayList<>();
        try {
            while (true) {
                a.add("aaaa");
                List<String> b = new ArrayList<>(10000);
                long startTime = System.currentTimeMillis();
                while (System.currentTimeMillis() - startTime < complexity) {
                    double x = Math.random() * 1000;
                    double y = Math.random() * 1000;
                    double result = x * y;
                }
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            latch.countDown();
        }
    }

    // Off-CPU: long sleep loop
    private static void offCpuSleepLoop() {
        while (true) {
            try {
                Thread.sleep(1500); // long sleep -> off-CPU
            } catch (InterruptedException e) {
                // ignore
            }
        }
    }

    // Off-CPU: blocking accept() on a server socket
    private static void offCpuAcceptLoop() {
        try (ServerSocket server = new ServerSocket(5555)) { // no connections => blocks
            while (true) {
                server.accept(); // off-CPU in kernel accept wait
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void create_threads(){
        CountDownLatch latch = new CountDownLatch(3);
        try {
            new Thread(() -> hardWork(latch, 500)).start();
            new Thread(() -> hardWork(latch, 1000)).start();
            new Thread(() -> hardWork(latch, 1500)).start();

            // Off-CPU threads
            new Thread(PerformanceTest::offCpuSleepLoop, "offcpu-sleep-1").start();
            new Thread(PerformanceTest::offCpuSleepLoop, "offcpu-sleep-2").start();
            new Thread(PerformanceTest::offCpuAcceptLoop, "offcpu-accept").start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        create_threads();
    }
}
