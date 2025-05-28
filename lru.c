#include <stdio.h>

int main() {
    int frames, pages, i, j, k, page_faults = 0;
    int ref[50], mem[10], recent[10], time = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter reference string: ");
    for (i = 0; i < pages; i++)
        scanf("%d", &ref[i]);

    for (i = 0; i < frames; i++) {
        mem[i] = -1;
        recent[i] = 0;
    }

    for (i = 0; i < pages; i++) {
        int found = 0;

        // Check if page is already in memory
        for (j = 0; j < frames; j++) {
            if (mem[j] == ref[i]) {
                found = 1;
                recent[j] = ++time; // Update time for LRU
                break;
            }
        }

        if (!found) {
            int min = 0;
            // Find empty slot or least recently used
            for (j = 1; j < frames; j++) {
                if (recent[j] < recent[min]) min = j;
            }
            mem[min] = ref[i];
            recent[min] = ++time;
            page_faults++;
        }

        // Print memory state
        for (k = 0; k < frames; k++) {
            if (mem[k] == -1) printf("- ");
            else printf("%d ", mem[k]);
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", page_faults);
    return 0;
}
