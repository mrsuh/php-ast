FROM debian:buster-slim

RUN set -eux; \
	apt-get update; \
	apt-get install -y --no-install-recommends \
		autoconf \
		dpkg-dev \
		file \
		gcc \
		libc-dev \
		make \
		pkg-config \
		re2c \
		build-essential \
		bison \
		libxml2-dev \
		libffi-dev \
		libsqlite3-dev \
		strace \
        gdb

COPY . /code

WORKDIR /code/php-src

RUN ./buildconf --force
RUN ./configure --with-ffi
RUN make
RUN make install

RUN ./buildconf --force
RUN ./configure

WORKDIR /code
