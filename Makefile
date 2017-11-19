GCC=gcc-4.7
CFLAGS = -Wall -Wextra -fno-builtin

BINS = binlog indexer hash_engine
OBJS = main.o hash_table.o

hash_engine: main.o hash_table.o ngx_crc32.c
	$(GCC) -o $@ $^ $(CFLAGS)

hash_table.o: hash_table.c
	$(GCC) $< -c -o $@ $(CFLAGS)

main.o: main.c
	$(GCC) $< -c -o $@ $(CFLAGS)

indexer: binlog_indexer.c ngx_crc32.c
	$(GCC) -o $@ $^ $(CFLAGS)

binlog: write_binlog.c
	$(GCC) -o $@ $^ $(CFLAGS)

test: binlog
	./binlog strings

clean:
	rm -f $(OBJS) $(BINS)

.PHONY: clean test
