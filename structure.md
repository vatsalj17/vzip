## 📁 Project Structure (clean, scalable, very C-core)

```txt
huffzip/
├── include/
│   ├── huffman.h        // tree, node, code generation
│   ├── heap.h           // min-heap (priority queue)
│   ├── bitio.h          // bit-level read/write
│   ├── fileformat.h     // header layout & constants
│   ├── compress.h
│   └── decompress.h
├── src/
│   ├── main.c
│   ├── huffman.c
│   ├── heap.c
│   ├── bitio.c
│   ├── compress.c
│   ├── decompress.c
│   └── fileformat.c
├── Makefile
├── README.md
└── .gitignore
```

---

## 🧭 Roadmap

### 🧩 Phase 0 – Ground rules

**Decide upfront:**

* `unsigned char` for symbols (0–255)
* All file I/O in **binary mode**
* Fixed-width types (`uint32_t`, `uint64_t`)
* One compression format version (add later)

Create `fileformat.h`:

```c
#define MAGIC "VZP"
```

---

### 🧩 Phase 1 – Min Heap (foundation stone)

📂 `heap.h / heap.c`

You need:

```c
typedef struct {
    Node **data;
    int size;
    int capacity;
} MinHeap;
```

Functions:

* `heap_create`
* `heap_push`
* `heap_pop`
* `heapify_up`
* `heapify_down`

⚠️ Things to keep in mind:

* Stable ordering not required
* Compare **frequency only**
* Heap stores **pointers**, not structs

✅ Test this independently before touching Huffman.

---

### 🧩 Phase 2 – Huffman Tree

📂 `huffman.h / huffman.c`

Structures:

```c
typedef struct Node {
    unsigned char symbol;
    uint64_t freq;
    struct Node *left, *right;
} Node;
```

Functions:

* `build_frequency_table(FILE*)`
* `build_huffman_tree(freq[])`
* `free_tree(Node*)`

⚠️ Gotchas:

* Single-symbol file → special case (tree with one node, code = `0`)
* Never assume both children exist

---

### 🧩 Phase 3 – Code Table Generation

📂 `huffman.c`

Data structure:

```c
typedef struct {
    uint32_t bits;
    uint8_t  length;
} HuffCode;

HuffCode table[256];
```

Why this over strings?

* Faster
* Memory efficient
* Easier bit-writing

⚠️ Rules:

* Max code length ≤ 32 (safe for Huffman)
* Reset table before each compression

---

### 🧩 Phase 4 – Bit-level I/O (the danger zone)

📂 `bitio.h / bitio.c`

You need **two structs**:

```c
typedef struct {
    FILE *fp;
    uint8_t buffer;
    uint8_t bit_count;
} BitWriter;

typedef struct {
    FILE *fp;
    uint8_t buffer;
    uint8_t bit_count;
} BitReader;
```

Functions:

* `bw_init`
* `bw_write_bits`
* `bw_flush`
* `br_read_bit`

⚠️ Absolute rules:

* Always flush writer
* Reader must reload buffer when empty
* Never mix `fread` and bit reads on same file

---

### 🧩 Phase 5 – File Format (don’t wing this)

📂 `fileformat.h / fileformat.c`

Header layout (example):

```txt
4 bytes  → magic "VZP\0"
1 byte   → version
8 bytes  → original file size
256 × 8  → frequency table
```

```c
typedef struct {
    char magic[4];          // "VZP\0"
    uint8_t version;        // 1
    uint8_t compression_type; // 0 = Static Huffman, 1 = Canonical
    uint64_t original_size; // Original byte count
    uint32_t checksum;      // CRC32 of original data (Fail Loudly!)
} HuffHeader;
```

Why frequency table?

* Rebuild tree deterministically
* Avoid storing tree structure

⚠️ Endianness:

* Choose little-endian
* Document it
* Stick to it

---

### 🧩 Phase 6 – Compression Logic

📂 `compress.c`

Steps:

1. Read input → frequency table
2. Build Huffman tree
3. Build code table
4. Write header
5. Rewind input file
6. Encode data → bitstream

⚠️ Mistakes to avoid:

* Forgetting to rewind file
* Writing bits before header
* Not counting original size correctly

---

### 🧩 Phase 7 – Decompression Logic

📂 `decompress.c`

Steps:

1. Read header
2. Validate magic + version
3. Rebuild tree
4. Read bits
5. Decode until `original_size` bytes written

⚠️ Critical:

* Stop decoding by **byte count**, not EOF
* Corrupted file should fail gracefully

---

## 🧪 Testing Strategy (non-negotiable)

Test files:

* Empty file
* Single byte repeated
* ASCII text
* Random binary
* ELF executable

---

## 🧠 Design Principles to Keep in Mind

### 1️⃣ Determinism matters

Same input → same output
(important for debugging)

### 2️⃣ Separate concerns

* Tree ≠ encoding
* Bit I/O ≠ file format
* CLI ≠ logic

### 3️⃣ Fail loudly

If header is wrong:

```c
fprintf(stderr, "Invalid file format\n");
exit(1);
```

Silent corruption is worse than crashing.
