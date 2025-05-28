FROM gcc:latest

WORKDIR /app

COPY PerformanceTest.cpp .

RUN g++ -std=c++11 -O2 -m64 -pipe -fdiagnostics-color=always -fno-pic -fno-pie -fno-strict-aliasing  -fno-semantic-interposition -fno-strict-aliasing -fno-plt -ffat-lto-objects -fPIC -fno-PIE -g -g -o PerformanceTest PerformanceTest.cpp

CMD ["./PerformanceTest"]
