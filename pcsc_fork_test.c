// gcc -framework PCSC pcsc-fork-test.c -o pcsc-fork-test
// Add -DDELAY_CHILD or -DDELAY_PARENT to introduce delays after fork, to prove that it's not an ordering, or simultaneous access, issue.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>

static void test_pcsc(const char *tag) {
  SCARDCONTEXT ctx = 0;
  LONG rv;
  char readers[2048];
  DWORD len = sizeof(readers);

  printf("[%s] PID=%d: calling SCardEstablishContext()\n", tag, getpid());

  rv = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ctx);
  if (rv != SCARD_S_SUCCESS) {
    printf("[%s] SCardEstablishContext failed: 0x%08X\n", tag, rv);
    return;
  }

  printf("[%s] SCardEstablishContext OK, ctx=%x\n", tag, ctx);

  rv = SCardListReaders(ctx, NULL, readers, &len);
  if (rv != SCARD_S_SUCCESS) {
    printf("[%s] SCardListReaders failed: 0x%08X\n", tag, rv);
    SCardReleaseContext(ctx);
    return;
  }

  printf("[%s] Readers (%u bytes): \"%s\"\n", tag, len, readers);

  rv = SCardReleaseContext(ctx);
  if (rv != SCARD_S_SUCCESS) {
    printf("[%s] SCardReleaseContext failed: 0x%08X\n", tag, rv);
  } else {
    printf("[%s] SCardReleaseContext OK\n", tag);
  }
}

int main(void) {
  test_pcsc("before fork");

  printf("calling fork()\n");

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
#ifdef DELAY_CHILD
	sleep(1);
#endif /* DELAY_CHILD */
    test_pcsc("child after fork");
  } else {
#ifdef DELAY_PARENT
	sleep(1);
#endif /* DELAY_PARENT */
    test_pcsc("parent after fork");

    int status = 0;
    waitpid(pid, &status, 0);
    printf("[parent]: child exited with status %d\n", status);
  }

  return 0;
}
