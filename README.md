[//]: # (vim README.md && pandoc README.md > a.html)
# Huffman-based Text Encoder and Decoder 
Home of a simple Huffman-based encoder and decoder.

## Why?
This project was requested by a Professor in my BCompSc university course.

## Technologies used:
- C++20
- Makefile
- Microsoft Visual Studio and VSCode

## The project
Given a text file encoded in ASCII, run the encoder. 
The encoder will create a new file, <code>filename_ENC</code> (no extension), with a one-line header containing the character decoding table and the encoded text.
The decoder reads this file and uses the decoding table to decode the contents of the encoded file, saving it in <code>filename.txt</code>.

I used a [Priority Queue](https://en.cppreference.com/w/cpp/container/priority_queue) for the final version, but I also made a version that uses a [Vector](https://en.cppreference.com/w/cpp/container/vector).
This was done to emphasize the difference in execution time between the two data structures.

Using a priority queue, I hope to see something close to ![O(nlog(n))](http://www.sciweavers.org/upload/Tex2Img_1569330333/eqn.png "Priority Queue Complexity") in complexity.
Using a vector, I'm aiming at a ![O(n^2)](http://www.sciweavers.org/upload/Tex2Img_1569330375/eqn.png "Vector Complexity") complexity.

Execution times:

| Characters | Expected Time | Elapsed Time |
| :---:      | :------:      | :-----:      |
|  50        | 30s           | 29.9s        |

These values are purely placeholders for now.
