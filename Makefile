GCC=gcc-4.7
CFLAGS=-Wall -Wextra

binlog: write_binlog.c
	$(GCC) -o $@ $^ $(CFLAGS)

test: binlog
	./binlog strings

