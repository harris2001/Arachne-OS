FROM randomdude/gcc-cross-x86_64-elf

# Install all dependencies in a single layer and clean up
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
        nasm \
        xorriso \
        grub-pc-bin \
        grub-common \
        qemu-system-x86 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

VOLUME /root/env
WORKDIR /root/env
