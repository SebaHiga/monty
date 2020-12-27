FROM ubuntu:latest AS builder

RUN apt update
RUN DEBIAN_FRONTEND=noninteractive apt install -y cmake gcc make g++

WORKDIR /opt/wazuh/build
COPY ./ ../

RUN cmake .. && make

FROM ubuntu:latest AS runtime

WORKDIR /opt/monty

COPY --from=builder /opt/wazuh/build/monty .

CMD ["./monty", "--interactive", "1", "--doors", "3", "--reveal", "1"]