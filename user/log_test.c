#include "kernel/types.h"
#include "user/user.h"

#define NCHILD 4
#define MSG_MAX_LEN 64
#define BUF_SIZE 4096
#define HEADER_SIZE 4


uint32 make_header(uint16 child_idx, uint16 msg_len) {
  return ((uint32)child_idx << 16) | msg_len;
}

uint16 get_child_idx(uint32 header) {
  return (header >> 16) & 0xFFFF;
}

uint16 get_msg_len(uint32 header) {
  return header & 0xFFFF;
}

int main() {
  char *shmem_base = (char *)sbrk(BUF_SIZE);
  int parentPid = getpid();
  if ((uint64)shmem_base == 0xffffffffffffffff) {
    printf("sbrk failed\n");
    exit(1);
  }

  for (int i = 0; i < NCHILD; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }

    if (pid == 0) {
      sleep(1);
      // Child process
      uint64 mapped_addr = map_shared_pages(parentPid, (uint64)shmem_base, BUF_SIZE);
      if (mapped_addr == (uint64)-1) {
        printf("Child %d: map_shared_pages failed\n", i);
        exit(1);
      }

      char *child_buf = (char *)mapped_addr;

      char msg[MSG_MAX_LEN];
      int len = 0;

      const char *prefix = "Hello from child ";
      for (int j = 0; prefix[j] != '\0'; j++)
        msg[len++] = prefix[j];
      msg[len++] = '0' + i;
      msg[len++] = '\n';

      char *cur = child_buf;
      while ((cur + HEADER_SIZE + len) < (child_buf + BUF_SIZE)) {
        cur = (char *)((uint64)((char*)cur + 3) & ~3);  // align to 4
        uint32 *hdr = (uint32 *)cur;
        uint32 old = __sync_val_compare_and_swap(hdr, 0, make_header(i, len));
        if (old == 0) {
          memmove(cur + HEADER_SIZE, msg, len);
          sleep(0);
        } else {
          uint16 skip_len = get_msg_len(old);
          cur += HEADER_SIZE + skip_len;
        }
      }
      cur = (char *)((uint64)((char*)cur + 3) & ~3);  // align to 4
      uint32 *hdr = (uint32 *)cur;
      __sync_val_compare_and_swap(hdr, 0, make_header(i, len));
      exit(0);
    }
  }

  // Parent reads from the buffer
  char *reader = shmem_base;
  while ((reader + HEADER_SIZE) < (shmem_base + BUF_SIZE)) {
    reader = (char *)((uint64)((char*)reader + 3) & ~3);  // align to 4
    uint32 header = *(uint32 *)reader;
    // there isn't a message yet, wait for one (not actually waiting)
    if (header == 0) {
      continue;
    }

    uint16 child_id = get_child_idx(header);
    uint16 len = get_msg_len(header);
    if (reader + HEADER_SIZE + len >= shmem_base + BUF_SIZE)
      break;

    char buf[MSG_MAX_LEN + 1];
    memmove(buf, reader + HEADER_SIZE, len); 
    buf[len] = '\0';

    printf("Parent received from child %d: %s", child_id, buf);
    reader += HEADER_SIZE + len;
  }

  unmap_shared_pages((uint64)shmem_base, BUF_SIZE);

  exit(0);
}