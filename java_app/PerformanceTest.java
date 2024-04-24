import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;

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

    public static void create_threads(){
        CountDownLatch latch = new CountDownLatch(3);
        try {
            new Thread(() -> hardWork(latch, 500)).start();
            new Thread(() -> hardWork(latch, 1000)).start();
            new Thread(() -> hardWork(latch, 1500)).start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        create_threads();
    }
}
