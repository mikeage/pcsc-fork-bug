CC      = cc
CFLAGS  = -Wall -Wextra -g

CFLAGS_PCSCLITE = -I/opt/homebrew/opt/pcsc-lite/include/PCSC

LDFLAGS_APPLE = -framework PCSC
LDFLAGS_PCSCLITE = -lpcsclite -L/opt/homebrew/opt/pcsc-lite/lib

all: pcsc_fork_test_apple pcsc_fork_test_pcsclite

pcsc_fork_test_apple: pcsc_fork_test.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDFLAGS_APPLE)

pcsc_fork_test_pcsclite: pcsc_fork_test.c
	$(CC) $(CFLAGS) $(CFLAGS_APPLE) -o $@ $< $(LDFLAGS) $(LDFLAGS_PCSCLITE) 

clean:
	rm -f pcsc_fork_test_apple pcsc_fork_test_pcsclite
