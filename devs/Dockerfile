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

# Set working directory
WORKDIR /root/env

ENV PATH="/usr/local/bin:${PATH}"

CMD ["/bin/bash"]