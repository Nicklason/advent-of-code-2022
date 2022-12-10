FROM gcc:12.2.0

WORKDIR /usr/app

COPY main.cpp input.txt ./

RUN g++ -o main -static main.cpp

CMD ["./main"]
