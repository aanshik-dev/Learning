#include <stdio.h>

int main() {
  int n, f;

  printf("Enter number of pages: ");
  scanf("%d", &n);

  int pages[n];
  printf("Enter reference string:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &pages[i]);
  }

  printf("Enter number of frames: ");
  scanf("%d", &f);

  int frame[f], time[f];
  for (int i = 0; i < f; i++) {
    frame[i] = -1;
    time[i] = 0;
  }

  int clock = 0, faults = 0;

  for (int i = 0; i < n; i++) {
    clock++;
    int hit = 0;

    for (int j = 0; j < f; j++) {
      if (frame[j] == pages[i]) {
        time[j] = clock;
        hit = 1;
        break;
      }
    }

    if (!hit) {
      int pos = -1;

      for (int j = 0; j < f; j++) {
        if (frame[j] == -1) {
          pos = j;
          break;
        }
      }

      if (pos == -1) {
        int min = time[0];
        pos = 0;
        for (int j = 1; j < f; j++) {
          if (time[j] < min) {
            min = time[j];
            pos = j;
          }
        }
      }

      frame[pos] = pages[i];
      time[pos] = clock;
      faults++;
    }

    printf("Frames: ");
    for (int j = 0; j < f; j++) {
      if (frame[j] == -1)
        printf("- ");
      else
        printf("%d ", frame[j]);
    }
    printf("\n");
  }

  printf("Total Page Faults = %d\n", faults);

  return 0;
}








// You are designing a memory management unit (MMU). The system has a fixed
// number of Physical Frames (e.g., 3 or 4). A process generates a Reference
// String (a sequence of integers representing page requests). Your job is to
// determine which pages are in memory at any given time and count the total
// number of Page Faults.
// Logical Clock: Maintain a global integer counter that starts at 0. Every time a
// page is accessed (whether it's a hit or a fault), increment the counter.
// Page Hit: If the requested page is already in a frame, update that frame’s "Last
// Used Time" to the current counter.
// Page Fault (Empty Frame): If the page is not in memory and there is an empty
// frame (indicated by -1), load the page and set its "Last Used Time" to the
// current counter.
// Page Fault (Eviction): If memory is full, find the frame that has the smallest
// (oldest) "Last Used Time." Replace that page with the new one and update its
// "Last Used Time" to the current counter.
// Write the c code in such a way that is is not detected for plagiarism, do not write comments, keep it simple, take user input where required.


