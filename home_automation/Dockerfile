FROM ubuntu
RUN apt-get update
RUN apt-get install -y \ 
    python3 \
    python3-pip \ 
    python3-setuptools \
    python3-wheel \ 
    ninja-build \
    pkg-config
RUN pip3 install meson
RUN apt-get install -y cpputest