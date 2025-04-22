#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "myArray_class.h"
using namespace std;

enum NucleicAcid {DNA = 0, RNA = 1} ;

class BaseError : public std::exception
{
private:
    std::string message;
public:
    explicit BaseError(const std::string &msg) : message(msg) {}
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class MolecularArray
{
private:
    myArray<char> sequence;
    NucleicAcid type;
    char complementaryBase(const char &inputBase, NucleicAcid to);
    bool isCorrectNucleotide(char &inputBase, NucleicAcid of) const;
    string transform(NucleicAcid to);
    string aminoAcid(const char &base1, const char &base2, const char &base3);
public:
    MolecularArray(const string &input, NucleicAcid type, bool isFile = false);
    string transcribe();
    string reverseTranscribe();
    string complementSequence(NucleicAcid type);
    bool isProteinCoding();
    myArray<string> translate();
    size_t startCodonIndex(size_t from = 0);
    size_t stopCodonIndex(size_t from = 0);
    string splice(const vector<pair<size_t, size_t>> &intronRegions);
    myArray<pair<size_t, size_t>> findORFs();
    void induceDeletion(size_t position, size_t how);
    double gcContent() const;
    bool isPalindrome() const;
    myArray<pair<size_t, size_t>> predictHairpins();
    void induceSubstitution(size_t position, string &newBases);
    void induceInsertion(size_t position, string &newBases);
    void writeToFile(const string &filePath) const;
};

char MolecularArray::complementaryBase(const char &inputBase, NucleicAcid to)
{
    switch (inputBase)
    {
        case 'A':
            if(to == DNA)
                return 'T';
            return 'U';
        case 'T':
            return 'A';
        case 'G':
            return 'C';
        case 'C':
            return 'G';
        case 'U':
            return 'A';
        default:
            throw BaseError("Input char is not a base.\n");
    }
}

MolecularArray::MolecularArray(const string &input, NucleicAcid type, bool isFile) : type(type)
{
    string inputSequence;
    if (isFile)
    {
        std::ifstream file(input);
        if (!file.is_open())
            throw BaseError("Failed to open file: " + input);
        std::getline(file, inputSequence);
        file.close();
    } else
        inputSequence = input;

    for (char base : inputSequence)
    {
        if (!isCorrectNucleotide(base, type))
        {
            sequence.clear(true);
            throw BaseError("Input sequence is not valid for the specified type.");
        }
        sequence.append(base);
    }
}

string MolecularArray::transcribe()
{
    string outSeq = transform(RNA);
    return outSeq;
}

string MolecularArray::reverseTranscribe()
{
    string outSeq = transform(DNA);
    return outSeq;
}

string MolecularArray::complementSequence(NucleicAcid toType)
{
    ostringstream output;
    for(size_t j = sequence.length(); j >= 1; --j)
        output << complementaryBase(sequence.at(j - 1), toType);
    return output.str();
}


bool MolecularArray::isCorrectNucleotide(char &inputBase, NucleicAcid of) const
{
    switch (inputBase)
    {
        case 'A':
        case 'G':
        case 'C':
            return true;
        case 'T':
            if(of == DNA)
                return true;
            return false;
        case 'U':
            if(of == RNA)
                return true;
            return false;
        default:
            return false;
    }
}


string MolecularArray::transform(NucleicAcid to)
{
    ostringstream output;
    if(to == DNA && type == RNA)
    {
        for (size_t n = 0; n < sequence.length(); n += 1)
        {
            if(sequence.at(n) == 'U')
                output << 'T';
            else
                output << sequence.at(n);
        }
        return output.str();
    }
    else if(to == RNA && type == DNA)
    {
        for (size_t n = 0; n < sequence.length(); n += 1)
        {
            if(sequence.at(n) == 'T')
                output << 'U';
            else
                output << sequence.at(n);
        }
        return output.str();
    }
    return sequence.str("").substr(1, sequence.length() - 2);
}


bool MolecularArray::isProteinCoding()
{
    try {
        auto begin = startCodonIndex();
        auto end = stopCodonIndex();
        return true;
    } catch (BaseError &e) {
        return false;
    }
}

string MolecularArray::aminoAcid(const char &base1, const char &base2, const char &base3)
{
    std::string codon = {base1, base2, base3};
    static const std::unordered_map<std::string, std::string> geneticCode = {
            {"UUU", "Phe"}, {"UUC", "Phe"}, {"UUA", "Leu"}, {"UUG", "Leu"},
            {"CUU", "Leu"}, {"CUC", "Leu"}, {"CUA", "Leu"}, {"CUG", "Leu"},
            {"AUU", "Ile"}, {"AUC", "Ile"}, {"AUA", "Ile"}, {"AUG", "Met"},
            {"GUU", "Val"}, {"GUC", "Val"}, {"GUA", "Val"}, {"GUG", "Val"},

            {"UCU", "Ser"}, {"UCC", "Ser"}, {"UCA", "Ser"}, {"UCG", "Ser"},
            {"CCU", "Pro"}, {"CCC", "Pro"}, {"CCA", "Pro"}, {"CCG", "Pro"},
            {"ACU", "Thr"}, {"ACC", "Thr"}, {"ACA", "Thr"}, {"ACG", "Thr"},
            {"GCU", "Ala"}, {"GCC", "Ala"}, {"GCA", "Ala"}, {"GCG", "Ala"},

            {"UAU", "Tyr"}, {"UAC", "Tyr"}, {"UAA", "Stop"}, {"UAG", "Stop"},
            {"CAU", "His"}, {"CAC", "His"}, {"CAA", "Gln"}, {"CAG", "Gln"},
            {"AAU", "Asn"}, {"AAC", "Asn"}, {"AAA", "Lys"}, {"AAG", "Lys"},
            {"GAU", "Asp"}, {"GAC", "Asp"}, {"GAA", "Glu"}, {"GAG", "Glu"},

            {"UGU", "Cys"}, {"UGC", "Cys"}, {"UGA", "Stop"}, {"UGG", "Trp"},
            {"CGU", "Arg"}, {"CGC", "Arg"}, {"CGA", "Arg"}, {"CGG", "Arg"},
            {"AGU", "Ser"}, {"AGC", "Ser"}, {"AGA", "Arg"}, {"AGG", "Arg"},
            {"GGU", "Gly"}, {"GGC", "Gly"}, {"GGA", "Gly"}, {"GGG", "Gly"}
    };
    auto it = geneticCode.find(codon);
    if (it != geneticCode.end())
        return it->second;
    return "Invalid";
}

size_t MolecularArray::stopCodonIndex(size_t from)
{
    myArray<char> stopCodons[] = {
            myArray<char>(type == DNA ? "TAG" : "UAG", 3),
            myArray<char>(type == DNA ? "TAA" : "UAA", 3),
            myArray<char>(type == DNA ? "TGA" : "UGA", 3)
    };

    for(auto &c: stopCodons)
    {
        try {
            return sequence.subarrayIndex(c, from);
        } catch (const out_of_range &e) {
            continue;
        }
    }
    throw BaseError("No stop codon found.");
}

size_t MolecularArray::startCodonIndex(size_t from)
{
    try {
        myArray<char> code(type == DNA ? "ATG" : "AUG", 3);
        return sequence.subarrayIndex(code, from);
    } catch (out_of_range &e) {
        throw BaseError("No start codon found.");
    }
}

myArray<string> MolecularArray::translate()
{
    auto ORFs = findORFs();
    myArray<string> output;
    ostringstream read;
    for(size_t j = 0; j < ORFs.length(); ++j)
    {
        size_t beg = ORFs.at(j).first;
        size_t end = ORFs.at(j).second;
        for (size_t i = beg; i <= end - 3; i += 3)
        {
            if (!output.str().empty())
                read << '-';
            read << aminoAcid(sequence.at(i), sequence.at(i + 1), sequence.at(i + 2));
        }
        output.append(read.str());
        read.clear();
    }
    return output;
}

string MolecularArray::splice(const vector<pair<size_t, size_t>> &intronRegions)
{
    if(type == DNA) throw BaseError("DNA cannot be spliced.");
    vector<pair<size_t, size_t>> sortedIntrons = intronRegions;
    std::sort(sortedIntrons.begin(), sortedIntrons.end());
    size_t previousEnd = 0;
    for (const auto &region : sortedIntrons)
    {
        if (region.first >= region.second || region.first < previousEnd)
            throw BaseError("Invalid or overlapping intron regions.");
        if (region.second > sequence.length())
            throw BaseError("Intron region exceeds sequence length.");
        previousEnd = region.second;
    }
    ostringstream splicedSequence;
    size_t currentIndex = 0;
    for (const auto &region : sortedIntrons)
    {
        splicedSequence << sequence.str("").substr(currentIndex, region.first);
        currentIndex = region.second;
    }
    splicedSequence << sequence.str("").substr(currentIndex);
    return splicedSequence.str();
}


myArray<pair<size_t, size_t>> MolecularArray::findORFs()
{
    myArray<pair<size_t, size_t>> orfs;
    size_t currentPos = 0;
    while (currentPos < sequence.length())
    {
        try
        {
            auto start = startCodonIndex(currentPos);
            auto stop = stopCodonIndex(start);
            while (stop % 3 != start % 3)
                stop = stopCodonIndex(stop+1);
            orfs.append(pair<size_t, size_t>(start, stop));
            currentPos = stop + 3;
        }
        catch (const BaseError &e)
        {
            break;
        }
    }
    return orfs;
}

double MolecularArray::gcContent() const
{
    return static_cast<double>(
      sequence.countIf([](char input){return input == 'C' || input == 'G'; })) / sequence.length();
}

bool MolecularArray::isPalindrome() const
{
    return sequence == sequence[0, sequence.length() - 1, -1];
}

myArray<pair<size_t, size_t>> MolecularArray::predictHairpins()
{
    myArray<pair<size_t, size_t>> hairpins;
    constexpr size_t minStemLength = 3;
    constexpr size_t minLoopSize = 3;

    for (size_t i = 0; i < sequence.length(); ++i)
    {
        for (size_t j = i + minStemLength + minLoopSize; j < sequence.length(); ++j)
        {
            size_t stemLength = 0;
            while (i + stemLength < j &&
              complementaryBase(sequence.at(i + stemLength), type) == sequence.at(j - stemLength))
            {
                stemLength += 1;
                if (stemLength >= minStemLength && j - (i + stemLength) >= minLoopSize)
                {
                    hairpins.append(pair<size_t, size_t>(i, j));
                    break;
                }
            }
        }
    }
    return hairpins;
}

void MolecularArray::induceSubstitution(size_t position, string &newBases)
{
    for(const auto &base: newBases)
    {
        try {
            sequence[position++] = base;
        } catch (const std::out_of_range &e)
        {
            throw BaseError("Invalid nucleotide position.\n");
        }
    }
}

void MolecularArray::induceInsertion(size_t position, string &newBases)
{
    if(position > sequence.length() - 1) throw BaseError("Invalid nucleotide position.\n");
    for(const auto &base: newBases)
        sequence.insert(base, position);
}

void MolecularArray::induceDeletion(size_t position, size_t how)
{
    if(position > sequence.length() - 1) throw BaseError("Invalid nucleotide position.\n");
    while(how-- >= 1)
    {
        try {
            sequence.pop(position);
        } catch (const std::out_of_range &e)
        {
            break;
        }
    }
}


void MolecularArray::writeToFile(const string &filePath) const
{
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open())
    {
        throw std::ios_base::failure("Failed to open file: " + filePath);
    }
    outputFile << sequence.str("");
    outputFile.close();
}
