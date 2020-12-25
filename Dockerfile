FROM gcc:latest AS builder

RUN apt update
RUN DEBIAN_FRONTEND=noninteractive apt install -y cmake

WORKDIR /opt/wazuh/build
COPY ./ ../

RUN cmake .. && make
RUN ctest

FROM ubuntu:latest

WORKDIR /opt/wazuh/challenge
COPY --from=builder /opt/wazuh/build/waz .

CMD [ "./waz" ]
