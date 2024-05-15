all:
	g++ -o 1m-block 1m-block.cpp -lnetfilter_queue

clean:
	rm -f nfqnl_test *.o
	rm -f 1m-block

