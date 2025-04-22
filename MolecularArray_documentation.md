# MolecularArray Class Documentation

The `MolecularArray` class provides methods for manipulating and analyzing DNA and RNA sequences, including transcription, translation, splicing, and structural property detection.

---

## **Class Definition**

The class includes the following methods:

### Constructor

#### **MolecularArray(const string &input, NucleicAcid type, bool isFile = false)**
Initializes the `MolecularArray` object with a nucleotide sequence.

- **Parameters**:
    - `input` (string): The sequence or file path containing the sequence.
    - `type` (NucleicAcid): Specifies whether the sequence is `DNA` or `RNA`.
    - `isFile` (bool): Indicates if `input` is a file path.
- **Throws**:
    - `BaseError` if the file cannot be opened or the sequence is invalid.

---

### Sequence Operations

#### **string transcribe()**
Converts a DNA sequence to RNA.

- **Returns**: A string representing the RNA sequence.

#### **string reverseTranscribe()**
Converts an RNA sequence to DNA.

- **Returns**: A string representing the DNA sequence.

#### **string complementSequence(NucleicAcid toType)**
Generates the complement of the sequence.

- **Parameters**:
    - `toType` (NucleicAcid): Specifies whether to complement to `DNA` or `RNA`.
- **Returns**: A string representing the complemented sequence.

#### **bool isProteinCoding()**
Checks if the sequence contains a valid open reading frame (ORF).

- **Returns**: `true` if the sequence is protein-coding, otherwise `false`.

#### **myArray<string> translate()**
Translates the sequence into amino acids.

- **Returns**: An array of strings, each representing an amino acid sequence for an ORF.

---

### Codon Indexing

#### **size_t startCodonIndex(size_t from = 0)**
Finds the index of the first start codon (`AUG` in RNA or `ATG` in DNA).

- **Parameters**:
    - `from` (size_t): The starting index for the search.
- **Returns**: The index of the start codon.
- **Throws**:
    - `BaseError` if no start codon is found.

#### **size_t stopCodonIndex(size_t from = 0)**
Finds the index of the first stop codon (`UAG`, `UAA`, `UGA` in RNA or `TAG`, `TAA`, `TGA` in DNA).

- **Parameters**:
    - `from` (size_t): The starting index for the search.
- **Returns**: The index of the stop codon.
- **Throws**:
    - `BaseError` if no stop codon is found.

---

### Splicing and ORF Analysis

#### **string splice(const vector<pair<size_t, size_t>> &intronRegions)**
Removes intron regions from an RNA sequence.

- **Parameters**:
    - `intronRegions` (vector<pair<size_t, size_t>>): Start and end indices of introns to be removed.
- **Returns**: The spliced RNA sequence as a string.
- **Throws**:
    - `BaseError` for invalid intron regions or if the sequence is DNA.

#### **myArray<pair<size_t, size_t>> findORFs()**
Identifies open reading frames (ORFs) in the sequence.

- **Returns**: An array of pairs, where each pair contains the start and stop indices of an ORF.

---

### Sequence Modification

#### **void induceSubstitution(size_t position, string &newBases)**
Substitutes bases in the sequence.

- **Parameters**:
    - `position` (size_t): The index to start substitution.
    - `newBases` (string): The new bases to insert.
- **Throws**:
    - `BaseError` if the position is invalid.

#### **void induceInsertion(size_t position, string &newBases)**
Inserts new bases into the sequence.

- **Parameters**:
    - `position` (size_t): The index to start insertion.
    - `newBases` (string): The bases to insert.
- **Throws**:
    - `BaseError` if the position is invalid.

#### **void induceDeletion(size_t position, size_t how)**
Deletes bases from the sequence.

- **Parameters**:
    - `position` (size_t): The starting index for deletion.
    - `how` (size_t): The number of bases to delete.
- **Throws**:
    - `BaseError` if the position is invalid.

---

### Sequence Analysis

#### **double gcContent() const**
Calculates the GC content of the sequence.

- **Returns**: A double representing the GC content as a fraction of the total sequence length.

#### **bool isPalindrome() const**
Checks if the sequence is a palindrome.

- **Returns**: `true` if the sequence is palindromic, otherwise `false`.

#### **myArray<pair<size_t, size_t>> predictHairpins()**
Predicts hairpin structures in the sequence.

- **Returns**: An array of pairs, where each pair contains the start and end indices of a hairpin.

---

### File Operations

#### **void writeToFile(const string &filePath) const**
Writes the sequence to a file.

- **Parameters**:
    - `filePath` (string): The path of the file to write to.
- **Throws**:
    - `std::ios_base::failure` if the file cannot be opened.
