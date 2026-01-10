# VZIP

**VZIP** (Vatsal’s ZIP) is a file compression tool written in C that implements **static Huffman coding** from scratch.
It analyzes byte frequencies, builds a Huffman tree, and compresses data using custom bit-level I/O.

All core components:- heap, tree, bit packing, and file format—are implemented manually without external libraries.

---

## Build

### Requirements

* C compiler (`gcc` or compatible)
* `make`
* POSIX-compatible system

### Compile

```bash
make
```

### Clean

```bash
make clean
```

---

## Usage

### Compress

```bash
./vzip -c file.txt
```

Creates `file.txt.vzip`

### Decompress

```bash
./vzip -d file.txt.vzip
```

### Help

```bash
./vzip -h
```

---

## File Format (`.vzip`)

The compressed file consists of a fixed header followed by a bitstream payload.

| Offset |       Size | Description                        |
| -----: | ---------: | ---------------------------------- |
|   0x00 |    4 bytes | Magic string `"VZIP"`              |
|   0x04 |    8 bytes | Original file size (`uint64_t`)    |
|   0x0C | 2048 bytes | Frequency table (256 × `uint64_t`) |
|  0x80C |   variable | Huffman-encoded bitstream          |

The frequency table is used during decompression to reconstruct the exact Huffman tree.


Each `.vzip` file starts with a **fixed header** followed by compressed data.

---

## Compression Logic

1. Scan the input file to build a frequency table.
2. Construct a Huffman tree using a min-heap.
3. Generate prefix codes from the tree.
4. Encode input data into a bitstream.
5. Write bits using a custom BitWriter.
6. Decompression reads bits and traverses the rebuilt tree to recover symbols.

---

## Notes

* The header size is ~2 KB due to the fixed frequency table.
* Small files may increase in size instead of shrinking.
* The implementation uses static (non-adaptive) Huffman coding.
