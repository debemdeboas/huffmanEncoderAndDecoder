# Huffman-based Text Encoder and Decoder 
Home of a simple Huffman-based encoder and decoder.

## Why?
This project was requested by a Professor in my BCompSc university course.

## Technologies used:
- C++20
- Makefile
- Microsoft Visual Studio and VSCode

## The project
I used a [Priority Queue](https://en.cppreference.com/w/cpp/container/priority_queue) for the final version, but I also made a version that uses a [Vector](https://en.cppreference.com/w/cpp/container/vector).
This was done to emphasize the difference in execution time between the two data structures.

Using a priority queue, I hope to see something close to O(nlog(n)) in complexity.
Using a vector, I'm aiming at a O(n^2) complexity.

Execution times:

|  n  | Expected | Elapsed |
| --- | :------: | ------: |
| 50  | 30       | 29      |

> These values are purely fictional.

Fila de prioridade O(nlog(n))
Lista O(n^2)
