FROM ubuntu:22.04
ARG DEBIAN_FRONTEND=noninteractive

USER root

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y --no-install-recommends install \
        build-essential \
        git \
        git-core \
        git-lfs \
        python3-dbg \
        python3-dev \
        python3-pip \
        python3-pexpect \
        python3-git \
        python3-jinja2 \
        python3-subunit \
        vim \
        cmake \
        gcc-multilib \
        g++-multilib \
        software-properties-common \
        language-pack-en-base \
        wget \
        flex \
        bison \
        gperf \
        doxygen \
        ninja-build \
        ccache \
        libffi-dev \
        libssl-dev \
        dfu-util \
        python3.10-venv \
        unzip && \
    apt-get -y clean

RUN git config --global --add safe.directory /workspace

RUN cd / && \
    git clone -b v5.3.2 --recursive https://github.com/espressif/esp-idf.git esp-idf && \
    cd esp-idf && \
    ./install.sh esp32,esp32s2,esp32s3 && \
    . ./export.sh && \
    git clone https://github.com/espressif/esp32-camera.git && \
    idf.py add-dependency "espressif/esp32-camera"

CMD ["/bin/bash"]

WORKDIR /workspace/
