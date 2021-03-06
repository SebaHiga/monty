FROM alpine:latest AS builder

RUN apk update
RUN apk add cmake gcc make g++

WORKDIR /opt/monty/build
COPY ./ ../

RUN cmake .. && make

FROM alpine:latest

WORKDIR /opt/monty

COPY --from=builder /opt/monty/build/monty .

CMD ["./monty", "--interactive", "1", "--doors", "3", "--reveal", "1"]