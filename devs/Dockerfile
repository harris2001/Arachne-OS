FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install all required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    nasm \
    xorriso \
    grub-pc-bin \
    grub-common \
    qemu-system-x86 \
    wget \
    curl \
    git \
    gcc-multilib \
    g++-multilib \
    && rm -rf /var/lib/apt/lists/*

# Download and install x86_64 cross-compiler toolchain from kernel.org
# Using GCC 15.2.0 (biarch - supports both 32-bit and 64-bit x86)
RUN cd /tmp && \
    wget -q https://www.kernel.org/pub/tools/crosstool/files/bin/x86_64/15.2.0/x86_64-gcc-15.2.0-nolibc-aarch64-linux.tar.gz && \
    tar -xf x86_64-gcc-15.2.0-nolibc-aarch64-linux.tar.gz -C /usr/local --strip-components=1 && \
    rm x86_64-gcc-15.2.0-nolibc-aarch64-linux.tar.gz 

# Set working directory
WORKDIR /root/env

ENV PATH="/usr/local/bin:${PATH}"

CMD ["/bin/bash"]