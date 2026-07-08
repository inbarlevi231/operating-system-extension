#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main(int argc, char **argv)
{
  int pid;
  int size = PGSIZE*3*sizeof(char);
  char* shared_data = (char*)malloc(size);
  int parent_id = getpid();

  // Flag: 1 = do unmap; 0 = skip unmap
  int do_unmap = 1;
  if(argc == 2 && strcmp(argv[1], "--skip") == 0){
    do_unmap = 0;
  }
  
  if ((pid = fork()) == 0) { // child process
    printf("Size before mapping is %x\n", sbrk(0));

    uint64 new_va = map_shared_pages(parent_id, (uint64)shared_data, size); 
    if (new_va == (uint64)-1) {
      printf("map_shared_pages failed\n");
      exit(1);
    }

    printf("Size after mapping is %x\n", sbrk(0));

    strcpy((char*)new_va, "Hello daddy");

    if (do_unmap) {
      if (unmap_shared_pages(new_va, size) == (uint64)-1) {
        printf("unmap_shared_pages failed\n");
        exit(1);
      }
      printf("Size after unmapping is %x\n", sbrk(0));
    } else {
      printf("Skipping unmap as per flag\n");
    }

    void* ptr = malloc(70000);
    if(ptr == 0){
      printf("malloc failed\n");
    }
    printf("Size after allocating is %x\n", sbrk(0));
    free(ptr);
    printf("Size after freeing allocated memory is %x\n", sbrk(0));
    exit(0);
  } else { // parent process
    wait(0); // wait until child writes
    printf("Parent read: %s\n", shared_data);
  }

  exit(0);
}
