#include <stdio.h>
#include <string.h>

void reset(int temp_blocks[], int blocks[], int n) {
  for (int i = 0; i < n; i++)
    temp_blocks[i] = blocks[i];
}

void solve(int blocks[], int b_count, int processes[], int p_count, int mode) {
  int allocation[p_count];
  int temp_blocks[b_count];
  int total_frag = 0;

  for (int i = 0; i < p_count; i++)
    allocation[i] = -1;
  for (int i = 0; i < b_count; i++)
    temp_blocks[i] = blocks[i];

  for (int i = 0; i < p_count; i++) {
    int target_idx = -1;

    for (int j = 0; j < b_count; j++) {
      if (temp_blocks[j] >= processes[i]) {
        if (mode == 1) { // First Fit
          target_idx = j;
          break;
        } else if (mode == 2) { // Best Fit
          if (target_idx == -1 || temp_blocks[j] < temp_blocks[target_idx])
            target_idx = j;
        } else if (mode == 3) { // Worst Fit
          if (target_idx == -1 || temp_blocks[j] > temp_blocks[target_idx])
            target_idx = j;
        }
      }
    }

    if (target_idx != -1) {
      allocation[i] = target_idx;
      temp_blocks[target_idx] -= processes[i];
    }
  }

  printf("\nProcess No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < p_count; i++) {
    printf("%d\t\t%dK\t\t", i + 1, processes[i]);
    if (allocation[i] != -1)
      printf("%d\n", allocation[i] + 1);
    else
      printf("Not Allocated\n");
  }

  for (int i = 0; i < b_count; i++)
    total_frag += temp_blocks[i];
  printf("Total Fragmentation: %dK\n", total_frag);
}

int main() {
  int b_count, p_count;

  printf("Enter number of memory blocks: ");
  scanf("%d", &b_count);
  int blocks[b_count];
  printf("Enter sizes of %d blocks: ", b_count);
  for (int i = 0; i < b_count; i++)
    scanf("%d", &blocks[i]);

  printf("Enter number of processes: ");
  scanf("%d", &p_count);
  int processes[p_count];
  printf("Enter sizes of %d processes: ", p_count);
  for (int i = 0; i < p_count; i++)
    scanf("%d", &processes[i]);

  printf("\n--- FIRST FIT ---");
  solve(blocks, b_count, processes, p_count, 1);

  printf("\n--- BEST FIT ---");
  solve(blocks, b_count, processes, p_count, 2);

  printf("\n--- WORST FIT ---");
  solve(blocks, b_count, processes, p_count, 3);

  return 0;
}