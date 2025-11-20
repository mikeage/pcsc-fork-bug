# PCSC is not fork safe

## Compilation

```bash
make
```

## Execution
```bash
./pcsc_fork_test  # Basic execution
./pcsc_fork_test_child_delayed  # Show that delaying the child until after the parent ran doesn't help
./pcsc_fork_test_parent_delayed  # Show that delaying the parent doesn't help either
```

## Expected behavior:

Calls to `SCardEstablishContext()` (and then `SCardListReaders()` or any other API) work whether they're called from the parent process or a child process after `fork()`. 

## Actual Behavior

Only the calls before the `fork()` and after the fork that run in the parent work. Calls from the child return `0x8010001D`. As seen from the _foo_delayed versions, it makes no difference which order the calls are made, nor is it a thread-safe issue if they're called simultaneously.

## Background

Inspired by a bug seen in OSCam (https://git.streamboard.tv/common/oscam) when running on a Mac. Works on Linux with pcsclite.
