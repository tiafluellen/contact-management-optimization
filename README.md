# Contact Management Optimization

## Project Description

This project compares two implementations of a contact management search system written in C.

- `baseline.c` uses a dynamically allocated array and linear search.
- `optimized.c` uses a hash table with linked lists for collision handling.

Both programs generate contacts, search for the last contact, and measure the time required to repeat the search 100,000 times.

## Requirements

- GCC or a compatible C compiler
- Terminal or command line

## Compile the Programs

Compile the baseline version:

```bash
gcc -Wall baseline.c -o baseline
```

Compile the optimized version:

```bash
gcc -Wall optimized.c -o optimized
```

## Run the Programs

Run the baseline version with 1,000 contacts:

```bash
./baseline 1000
```

Run the optimized version with 1,000 contacts:

```bash
./optimized 1000
```

You can replace `1000` with another positive contact count, such as `5000`, `10000`, or `50000`.

## Benchmarking

Each program performs 100,000 searches during a run. To compare performance, run both programs with the same contact counts and repeat each test three times.

Example:

```bash
./baseline 1000
./baseline 1000
./baseline 1000

./optimized 1000
./optimized 1000
./optimized 1000
```

Repeat the tests with 5,000, 10,000, and 50,000 contacts. Record the total search time from each run and use the median of the three times.

## Expected Output

The output should identify the contact, display its phone number, show the number of contacts and search repetitions, and report the total and average search times.

Example:

```text
Found: Contact999
Phone: 555-0999
Contacts: 1000
Search repetitions: 100000
Total search time: [measured time]
Average search time: [measured time]
```

The exact timing results will vary depending on the computer and system activity.

## Project Comparison

The baseline version uses O(n) linear search. The optimized version uses a hash table with an average expected search time of O(1). The benchmark results are used to compare the performance of both approaches.