CC      = cc
CFLAGS  = -Wall -Wextra -g
LDFLAGS = -framework PCSC

all: pcsc_fork_test pcsc_fork_test_child_delayed pcsc_fork_test_parent_delayed

pcsc_fork_test: pcsc_fork_test.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

pcsc_fork_test_parent_delayed: pcsc_fork_test.c
	$(CC) $(CFLAGS) -DDELAY_PARENT -o $@ $< $(LDFLAGS)

pcsc_fork_test_child_delayed: pcsc_fork_test.c
	$(CC) $(CFLAGS) -DDELAY_CHILD -o $@ $< $(LDFLAGS)

clean:
	rm -rf pcsc_fork_test{,.dSYM/} pcsc_fork_test_parent_delayed{,.dSYM/} pcsc_fork_test_child_delayed{,.dSYM/}{,.dSYM/}
