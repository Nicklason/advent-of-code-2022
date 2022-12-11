FROM rust:1.65.0-alpine

WORKDIR /usr/app

COPY main.rs input.txt ./

# CMD ["rustc", "--explain", "E0689"]

RUN rustc main.rs

CMD ["./main"]