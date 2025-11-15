FROM debian:bookworm-slim

RUN apt update && apt install -y \
    build-essential \
    && apt clean

RUN useradd -ms /bin/bash dev
RUN apt-get update && apt-get install -y git
USER dev
