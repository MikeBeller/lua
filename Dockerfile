# syntax=docker/dockerfile:1
FROM alpine AS build
WORKDIR /app
RUN apk add build-base git
RUN git clone https://luajit.org/git/luajit.git
RUN cd luajit; make

FROM alpine
COPY --from=build /app/luajit/src/luajit /usr/local/bin/luajit
