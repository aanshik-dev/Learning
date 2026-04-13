#include <stdio.h>

#define MAX_FRAMES 10

struct Frame {
  int page_id;
  int reference_bit;
};

int main() {
  int num_frames, num_pages;
  struct Frame frames[MAX_FRAMES];
  int hand = 0;
  int page_faults = 0;

  printf("Enter number of frames: ");
  scanf("%d", &num_frames);

  for (int i = 0; i < num_frames; i++) {
    frames[i].page_id = -1;
    frames[i].reference_bit = 0;
  }

  printf("Enter number of page requests: ");
  scanf("%d", &num_pages);

  int requests[num_pages];
  printf("Enter the page requests: ");
  for (int i = 0; i < num_pages; i++) {
    scanf("%d", &requests[i]);
  }

  for (int i = 0; i < num_pages; i++) {
    int current_page = requests[i];
    int found = 0;

    for (int j = 0; j < num_frames; j++) {
      if (frames[j].page_id == current_page) {
        frames[j].reference_bit = 1;
        found = 1;
        printf("Page %d: HIT\n", current_page);
        break;
      }
    }

    if (!found) {
      page_faults++;
      while (1) {
        if (frames[hand].page_id == -1) {
          frames[hand].page_id = current_page;
          frames[hand].reference_bit = 1;
          hand = (hand + 1) % num_frames;
          break;
        }

        if (frames[hand].reference_bit == 1) {
          frames[hand].reference_bit = 0;
          hand = (hand + 1) % num_frames;
        } else {
          frames[hand].page_id = current_page;
          frames[hand].reference_bit = 1;
          hand = (hand + 1) % num_frames;
          break;
        }
      }
      printf("Page %d: FAULT\n", current_page);
    }
  }

  printf("\nTotal Page Faults: %d\n", page_faults);

  return 0;
}