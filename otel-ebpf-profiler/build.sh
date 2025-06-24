#!/bin/bash

# Clone and build the profiler
git clone https://github.com/open-telemetry/opentelemetry-ebpf-profiler.git
cd opentelemetry-ebpf-profiler

# Build using their Docker build process
docker build -t ebpf-otel-profiler:latest .

# Clean up
cd ..
rm -rf opentelemetry-ebpf-profiler
