GCC=gcc-4.7
CFLAGS=-Wall -Wextra

indexer: binlog_indexer.c ngx_crc32.c
	$(GCC) -o $@ $^ $(CFLAGS)

binlog: write_binlog.c
	$(GCC) -o $@ $^ $(CFLAGS)

test: binlog
	./binlog strings

