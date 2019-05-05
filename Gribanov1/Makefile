COMPILER=gcc

all: default

#===============! Usual usage !==================#

default: zadacha1.c 
	$(COMPILER) zadacha1.c 

#===================! Test !=====================#

test: zadacha1.c
	$(COMPILER) zadacha1.c  -DTEST

#==================! Clean !=====================#

clean:
	rm ./a.out

