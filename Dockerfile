FROM ubuntu:20.04

RUN ln -fs /usr/share/zoneinfo/UTC /etc/localtime

RUN apt-get update

RUN apt install -y software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test

RUN apt-get update
RUN apt-get install -y g++-9 libboost-all-dev wget make

RUN wget https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.sh
RUN sh cmake-3.12.0-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9

RUN apt-get install -y libavcodec-dev libavformat-dev libavdevice-dev libavfilter-dev

COPY . /code/

# build && install
RUN mkdir -p /code/build/
WORKDIR /code/build/
RUN cmake .. && \
    make -j$(nproc) && \
    make test && \
    make install

#RUN rm -r /code

CMD /usr/local/kirpich_writer

