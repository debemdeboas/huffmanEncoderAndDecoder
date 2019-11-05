[//]: # (vim README.md && pandoc README.md > a.html)

# Huffman-based Text Encoder and Decoder  

Home of a simple Huffman-based encoder and decoder.

## Why

This project was requested by a Professor in my BCompSc university course.

## Technologies used

- C++20
- Makefile
- Microsoft Visual Studio

## The project

Given a text file encoded in ASCII, run the encoder.  
The encoder will create a new file, <code>filename_ENC</code> (no extension), with a one-line header containing the character decoding table and the encoded text.
The decoder reads this file and uses the decoding table to decode the contents of the encoded file, saving it in <code>filename.txt</code>.

I used a [Priority Queue](https://en.cppreference.com/w/cpp/container/priority_queue) for the final version, but I also made a version that uses a [Vector](https://en.cppreference.com/w/cpp/container/vector).
This was done to emphasize the difference in execution time between the two data structures.

Using a priority queue, we have close to $O(nlog(n))$ in complexity.
Using a vector, we have $O(n^2)$ complexity.

## Execution times

The program was executed 20 times, half of which used vectors and the other half used a priority queue to build the Huffman Tree.  

### Executing using a vector


| Execution no. | Elapsed time |
| :-----------: | :----------: |
|       1       |     194      |
|       2       |     188      |
|       3       |     188      |
|       4       |     186      |
|       5       |     189      |
|       6       |     188      |
|       7       |              |
|       8       |              |
|       9       |              |
|      10       |              |

### Executing using a Priority Queue (Min Heap)

| Execution no. | Elapsed time |
| :-----------: | :----------: |
|       1       |      24      |
|       2       |      27      |
|       3       |      28      |
|       4       |      27      |
|       5       |      28      |
|       6       |      27      |
|       7       |              |
|       8       |              |
|       9       |              |
|      10       |              |

### Results

After 10 executions each, 

| Data Structure |        Elapsed Time ($\mu$)         |
| :------------: | :---------------------------------: |
|     Vector     | 193 microseconds (0.000193 seconds) |
| Priority Queue | 24 microseconds  (0.000024 seconds) |

