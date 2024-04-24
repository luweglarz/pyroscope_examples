FROM gcc:latest

WORKDIR /app

COPY PerformanceTest.cpp .

RUN g++ -std=c++11 -fno-omit-frame-pointer -g -o PerformanceTest PerformanceTest.cpp

CMD ["./PerformanceTest"]
