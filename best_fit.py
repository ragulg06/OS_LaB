
# Step 1: Input memory blocks and processes
memory_blocks = [100, 500, 200, 300, 600]
processes = [212, 417, 112, 426]

# Step 2: Create an allocation list and copy block sizes
allocation = [-1] * len(processes)
block_sizes = memory_blocks.copy()

# Step 3: Loop through each process
for i in range(len(processes)):
    process = processes[i]
    best_fit_index = -1

    # Step 4: Find the best (smallest suitable) block for this process
    for j in range(len(block_sizes)):
        block = block_sizes[j]
        if block >= process:
            if best_fit_index == -1 or block < block_sizes[best_fit_index]:
                best_fit_index = j

    # Step 5: Allocate the process if a block is found
    if best_fit_index != -1:
        allocation[i] = best_fit_index
        block_sizes[best_fit_index] -= process

# Step 6: Print the result
print("Process No.\tProcess Size\tBlock No.")
for i in range(len(processes)):
    if allocation[i] != -1:
        print(f"{i + 1}\t\t{processes[i]}\t\t{allocation[i] + 1}")
    else:
        print(f"{i + 1}\t\t{processes[i]}\t\tNot Allocated")
