FROM mcr.microsoft.com/devcontainers/base:jammy

# Install xv6 related packages
RUN apt-get update; echo Ignore any update errors
RUN apt-get install -y git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu