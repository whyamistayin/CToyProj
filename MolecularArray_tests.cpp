#include <gtest/gtest.h>
#include "MolecularArray.h"

std::string createTempFile(const std::string &content)
{
    std::string tempFileName = "temp_test_file.txt";
    std::ofstream outFile(tempFileName);
    outFile << content;
    outFile.close();
    return tempFileName;
}

void removeTempFile(const std::string &fileName)
{
    std::remove(fileName.c_str());
}

TEST(MolecularArrayFileTests, ReadValidDNAFile)
{
    std::string fileName = createTempFile("ATGCGTACG");
    MolecularArray molArray(fileName, DNA, true);
    EXPECT_EQ(molArray.complementSequence(DNA), "CGTACGCAT");
    removeTempFile(fileName);
}

TEST(MolecularArrayFileTests, ReadInvalidDNAFile)
{
    std::string fileName = createTempFile("ATXCGTACG");
    EXPECT_THROW(MolecularArray molArray(fileName, DNA, true), BaseError);
    removeTempFile(fileName);
}

TEST(MolecularArrayFileTests, WriteSequenceToFile)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    std::string fileName = "output_test_file.txt";
    molArray.writeToFile(fileName);
    std::ifstream inFile(fileName);
    std::string content;
    std::getline(inFile, content);
    inFile.close();
    EXPECT_EQ(content, "ATGCGTACG");
    removeTempFile(fileName);
}

TEST(MolecularArrayComplementTests, ComplementDNASequence)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    EXPECT_EQ(molArray.complementSequence(DNA), "CGTACGCAT");
}

TEST(MolecularArrayComplementTests, ComplementRNASequence)
{
    MolecularArray molArray("AUGCGUACG", RNA);
    EXPECT_EQ(molArray.complementSequence(RNA), "CGUACGCAU");
}

TEST(MolecularArrayTranscriptionTests, TranscribeDNA)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    EXPECT_EQ(molArray.transcribe(), "AUGCGUACG");
}

TEST(MolecularArrayTranscriptionTests, ReverseTranscribeRNA)
{
    MolecularArray molArray("AUGCGUACG", RNA);
    EXPECT_EQ(molArray.reverseTranscribe(), "ATGCGTACG");
}


TEST(MolecularArrayGCTests, MixedGCContent)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    EXPECT_NEAR(molArray.gcContent(), 0.555, 0.001);
}

TEST(MolecularArrayGCTests, HighGCContent)
{
    MolecularArray molArray("GGGGCCCC", DNA);
    EXPECT_NEAR(molArray.gcContent(), 1.0, 0.001);
}

TEST(MolecularArrayGCTests, NoGCContent)
{
    MolecularArray molArray("ATATATAT", DNA);
    EXPECT_NEAR(molArray.gcContent(), 0.0, 0.001);
}

TEST(MolecularArrayPalindromeTests, PalindromeSequence)
{
    MolecularArray molArray("AGCTTCGA", DNA);
    EXPECT_TRUE(molArray.isPalindrome());
}

TEST(MolecularArrayPalindromeTests, NonPalindromeSequence)
{
    MolecularArray molArray("AGCTTGCA", DNA);
    EXPECT_FALSE(molArray.isPalindrome());
}

TEST(MolecularArrayORFTests, FindSingleORF)
{
    MolecularArray molArray("ATGCGTACGTAG", DNA);
    auto orfs = molArray.findORFs();
    ASSERT_EQ(orfs.length(), 1);
    EXPECT_EQ(orfs.at(0).first, 0);
    EXPECT_EQ(orfs.at(0).second, 9);
}

TEST(MolecularArrayORFTests, NoStartCodon)
{
    MolecularArray molArray("CGTACGTAG", DNA);
    auto orfs = molArray.findORFs();
    EXPECT_EQ(orfs.length(), 0);
}

TEST(MolecularArrayORFTests, MultipleORFs)
{
    MolecularArray molArray("ATGCGTACGTAGATGCCCTGA", DNA);
    auto orfs = molArray.findORFs();
    ASSERT_EQ(orfs.length(), 2);
    EXPECT_EQ(orfs.front().first, 0);
    EXPECT_EQ(orfs.front().second, 9);
    EXPECT_EQ(orfs.at(1).first, 12);
    EXPECT_EQ(orfs.at(1).second, 18);
}

TEST(MolecularArraySplicingTests, RemoveSingleIntron)
{
    MolecularArray molArray("AUGCGUUACG", RNA);
    std::vector<std::pair<size_t, size_t>> introns = {{3, 5}};
    EXPECT_EQ(molArray.splice(introns), "AUGUUACG");
}

TEST(MolecularArraySplicingTests, OverlappingIntrons)
{
    MolecularArray molArray("AUGCGUUACG", RNA);
    std::vector<std::pair<size_t, size_t>> introns = {{3, 5}, {4, 6}};
    EXPECT_THROW(molArray.splice(introns), BaseError);
}

// Test Suite for Hairpin Prediction
TEST(MolecularArrayHairpinTests, DetectHairpin)
{
    MolecularArray molArray("GCCGAAAAAGCGG", DNA);
    auto hairpins = molArray.predictHairpins();
    ASSERT_EQ(hairpins.length(), 1);
    EXPECT_EQ(hairpins.at(0).first, 1);
    EXPECT_EQ(hairpins.at(0).second, 12);
}

TEST(MolecularArrayHairpinTests, NoHairpin)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    auto hairpins = molArray.predictHairpins();
    EXPECT_EQ(hairpins.length(), 0);
}

TEST(MolecularArrayEditTests, InduceInsertion)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    std::string insert = "TTT";
    molArray.induceInsertion(3, insert);
    EXPECT_EQ(molArray.complementSequence(DNA), "CGTACGAAACAT");
}

TEST(MolecularArrayEditTests, InduceDeletion)
{
    MolecularArray molArray("ATGCGTACG", DNA);
    molArray.induceDeletion(3, 2);
    EXPECT_EQ(molArray.complementSequence(DNA), "CGTACAT");
}
