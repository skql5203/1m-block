all:
	g++ -o 1m-blcok 1m-block.cpp -lnetfilter_queue

clean:
	rm -f nfqnl_test *.o

