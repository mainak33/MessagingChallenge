FROM alpine:latest

RUN set -ex && \
    apk add build-base && \
    apk add cmake

COPY . /usr/src/MessagingChallenge

WORKDIR /usr/src/MessagingChallenge

RUN set -ex; \
    cmake -S . -B build

WORKDIR /usr/src/MessagingChallenge/build/

RUN make

WORKDIR /usr/src/MessagingChallenge/build/apps

CMD ["./messagingchallenge"] 