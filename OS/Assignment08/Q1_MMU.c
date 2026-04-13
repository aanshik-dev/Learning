#include <stdio.h>

int main() {
  int num_frames, num_pages;

  printf("Enter number of frames: ");
  scanf("%d", &num_frames);

  int frames[num_frames];
  int last_used[num_frames];

  for (int i = 0; i < num_frames; i++) {
    frames[i] = -1;
    last_used[i] = 0;
  }

  printf("Enter number of page requests: ");
  scanf("%d", &num_pages);

  int pages[num_pages];
  printf("Enter the reference string: ");
  for (int i = 0; i < num_pages; i++) {
    scanf("%d", &pages[i]);
  }

  int page_faults = 0;
  int counter = 0;

  for (int i = 0; i < num_pages; i++) {
    int current_page = pages[i];
    int found = 0;
    counter++;

    for (int j = 0; j < num_frames; j++) {
      if (frames[j] == current_page) {
        found = 1;
        last_used[j] = counter;
        printf("Page %d: HIT\n", current_page);
        break;
      }
    }

    if (!found) {
      page_faults++;
      int victim_index = -1;

      for (int j = 0; j < num_frames; j++) {
        if (frames[j] == -1) {
          victim_index = j;
          break;
        }
      }

      if (victim_index == -1) {
        int min_time = last_used[0];
        victim_index = 0;
        for (int j = 1; j < num_frames; j++) {
          if (last_used[j] < min_time) {
            min_time = last_used[j];
            victim_index = j;
          }
        }
      }

      frames[victim_index] = current_page;
      last_used[victim_index] = counter;
      printf("Page %d: FAULT\n", current_page);
    }
  }

  printf("\nTotal Page Faults: %d\n", page_faults);

  return 0;
}