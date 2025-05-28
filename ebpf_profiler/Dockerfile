# Runtime stage
FROM debian:bookworm-slim

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libbpf1 \
    libelf1 \
    && rm -rf /var/lib/apt/lists/*

# Copy compiled binaries
COPY ./ebpf-profiler ./ebpf-profiler

ENTRYPOINT ["./ebpf-profiler"]

