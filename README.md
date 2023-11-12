# SmartTextEditor
 
Project Purpose:
The primary objective was to develop a user-friendly text editor in C++ that not only simplifies text editing but also allows for easy adaptation and modification by programmers. The platform's adaptability ensures that changes can be effortlessly coded and implemented, catering to diverse user needs.

Project Features:
The Smart Text Editor offers a unique user flow, suggesting word completions as users type, compressing text for efficient storage, and enabling secure encoding for confidentiality. The ability to save and load text files seamlessly enhances user convenience, fostering a dynamic and interactive editing experience.

Functionalities:

Typing Text:

Implemented a console-based module for forward typing with vector strings, iterators, and loops.
Word Completion Suggestions:

Developed a system using trie trees or B-trees to provide users with expected word completions from a provided dictionary.
Compression of Text:

Employed Huffman encoding for text compression, storing both the compressed text and the compression tree for recovery.
Saving and Loading Text:

Enabled users to save compressed text and compression tree to a local machine, with an option to reload files for continued editing.
Uncompressing of Text:

Implemented Huffman compression tree loading to decompress the text encoding and recover the original text.
Continue Editing:

Ensured users could seamlessly continue editing, saving, and reloading files multiple times.
