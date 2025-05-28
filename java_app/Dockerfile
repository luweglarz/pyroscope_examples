FROM openjdk:17-jdk-slim

ADD ./PerformanceTest.java /PerformanceTest.java
RUN javac  PerformanceTest.java

CMD ["java","-XX:+PreserveFramePointer", "PerformanceTest"]