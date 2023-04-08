FROM alpine:latest

RUN set -ex && \
    #apk add --no-cache gcc musl-dev && \
    apk add build-base && \
    apk add cmake

# RUN set -ex && \
#     rm -f /usr/libexec/gcc/x86_64-alpine-linux-musl/6.4.0/cc1obj && \
#     rm -f /usr/libexec/gcc/x86_64-alpine-linux-musl/6.4.0/lto1 && \
#     rm -f /usr/libexec/gcc/x86_64-alpine-linux-musl/6.4.0/lto-wrapper && \
#     rm -f /usr/bin/x86_64-alpine-linux-musl-gcj

COPY . /usr/src/MessagingChallenge

WORKDIR /usr/src/MessagingChallenge

RUN set -ex; \
    cmake -S . -B build

WORKDIR /usr/src/MessagingChallenge/build/

RUN make

WORKDIR /usr/src/MessagingChallenge/build/apps

CMD ["./messagingchallenge"] 