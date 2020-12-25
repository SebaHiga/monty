FROM ubuntu:latest

RUN apt update
RUN DEBIAN_FRONTEND=noninteractive apt install -y cmake gcc make g++

WORKDIR /opt/wazuh/build
COPY ./ ../

RUN cmake .. && make
