#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "mmanager.h"

// Allocate memory
int allocate(mmgr_action *action, int strategy, FILE *outputfp) {
    mmgr_action *current = headChunk, *best = NULL, *worst = NULL;
	
	// Check which algorithm user picked
    while (current) {
        if (current->isFree && current->size >= action->size) {
            if (strategy == STRAT_FIRST) {
                best = current; 
                break; 
            }
            if (strategy == STRAT_BEST) {
                if (!best || current->size < best->size) {
                    best = current; 
                }
            }
            if (strategy == STRAT_WORST) {
                if (!worst || current->size > worst->size) {
                    worst = current; 
                }
            }
        }
        current = current->next;
    }

    // Select the chunk based on algorithm
    mmgr_action *selected = NULL;
    if (strategy == STRAT_FIRST || strategy == STRAT_BEST) {
        selected = best;
    } else if (strategy == STRAT_WORST) {
        selected = worst;
    }

    // Allocate the selected chunk
    if (selected) {
        // Split the chunk if there's extra space
        if (selected->size > action->size + sizeof(mmgr_action)) {
            mmgr_action *newChunk = (mmgr_action *)((char *)selected + sizeof(mmgr_action) + action->size);
            newChunk->id = -1;
            newChunk->size = selected->size - action->size;
            newChunk->isFree = 1;
            newChunk->paint = '\0';
            newChunk->next = selected->next;
            newChunk->offset = selected->offset + action->size;
            selected->next = newChunk;
            selected->size = action->size;
        }
        // Mark the selected chunk as allocated
        selected->id = action->id;
        selected->isFree = 0;
        selected->paint = action->paint;

        fprintf(outputfp, "alloc %d bytes : SUCCESS - return location %ld\n", action->size, selected->offset);
        return 1;
    }

    fprintf(outputfp, "alloc %d bytes : FAIL\n", action->size);
    return 0;
}



// Release memory
int release(int id, FILE *outputfp) {
    mmgr_action *current = headChunk;

    while (current) {
        if (current->id == id && !current->isFree) {
            current->isFree = 1;
            current->paint = '\0';

            fprintf(outputfp, "free location %ld\n", current->offset);
            return 1;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Invalid free request for chunk ID %d\n", id);
    return 0;
}

// Summary report
void printSummary(FILE *outputfp) {
    mmgr_action *current = headChunk;
    int allocated = 0, free = 0;

    fprintf(outputfp, "SUMMARY:\n");

    while (current) {
        if (current->isFree) {
            free += current->size;
        } else {
            allocated += current->size;
        }
        fprintf(outputfp, "chunk %ld location : %d bytes - %s\n", current->offset, current->size,
                current->isFree ? "free" : "allocated");
        current = current->next;
    }

    fprintf(outputfp, "%d bytes allocated\n%d bytes free\n", allocated, free);
}

int runModel(FILE *outputfp, FILE *inputfp, 
long totalMemorySize, int fitStrategy, int verbosity) {
    
	char *memoryBlock = NULL;
    int nSuccessfulActions = 0;
	mmgr_action action;

	fprintf(outputfp,
            "Running a %s-fit model in %ld (0x%lx) bytes of memory.\n",
            (fitStrategy == STRAT_FIRST ? "first" :
             fitStrategy == STRAT_BEST ? "best" :
             fitStrategy == STRAT_WORST ? "worst" : "unknown"),
            totalMemorySize, totalMemorySize);
	/**
	 * this is the only allocation you should need -- all requests
	 * from your model should come from this allocated block
	 */
	memoryBlock = (char *)malloc(totalMemorySize);
    if (memoryBlock == NULL) {
        perror("allocation failed!");
        return -1;
    }
    // Initialize memory chunk
    headChunk = (mmgr_action *)memoryBlock;
    headChunk->id = -1;
    headChunk->size = totalMemorySize - sizeof(mmgr_action); // Remaining space for allocation
    headChunk->isFree = 1;
    headChunk->paint = '\0';
    headChunk->next = NULL;
    headChunk->offset = 0;
	/**
	 *	+++ Set up anything else you will need for your memory management
	 */
    while (getAction(&action, inputfp, outputfp, verbosity)) {
        if (action.type == ACTION_ALLOCATE) {
            allocate(&action, fitStrategy, outputfp);
        } else if (action.type == ACTION_RELEASE) {
            release(action.id, outputfp);
        }
		/** increment our count of work we did */
		nSuccessfulActions++;
    }

    printSummary(outputfp);

    /** +++ Clean up your memory management */
    free(memoryBlock);
    
    return nSuccessfulActions;
}





