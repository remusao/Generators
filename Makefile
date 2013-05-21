CXX=clang++
FLAGS=-std=c++11 -g -Wall -Wextra

all:
	${CXX} ${FLAGS} -Isrc main.cc
