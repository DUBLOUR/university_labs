FROM ubuntu:bionic

RUN apt-get update && apt-get install -y build-essential git cmake autoconf libtool pkg-config

FROM cpp-build-base:0.1.0 AS build

WORKDIR /src

COPY CMakeLists.txt ./

COPY src/main.cpp src/tests.cpp src/drafts.h src/measure.cpp src/measures.h src/codegen.cpp ./src/

RUN cmake . && make

FROM ubuntu:bionic

WORKDIR /opt/benchmarking-bin

COPY --from=build /src/bin/benchmarking ./

CMD ["./benchmarking"]