#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
pid_t pids[10];
int i;
int n = 10;

/* Start children. */
for (i = 0; i < n; ++i) {
  if ((pids[i] = fork()) < 0) {
    perror("fork");
    abort();
  } else if (pids[i] == 0) {
    printf("Hello from Child %d",i);
    //DoWorkInChild();
    exit(0);
  }else{
	printf("\nCHILD CREATED %d\n",i);	
	}
}

/* Wait for children to exit. */
int status;
pid_t pid;
while (n > 0) {
  pid = wait(&status);
  printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
  --n;  // TODO(pts): Remove pid from the pids array.
}
}
