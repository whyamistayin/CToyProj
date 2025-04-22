#include "gtest/gtest.h"
#include "Node_Class.h"

using namespace ::testing;

TEST(NodeTest, Assignment)
{
    Node<int> a(1);
    Node<int> b(10);
    Node<int> c(77);

    ASSERT_EQ(a.get_data(), 1);
    ASSERT_EQ(b.get_data(), 10);
    ASSERT_EQ(c.get_data(), 77);
}

TEST(NodeTest, ConstructorWithPrev)
{
    Node<int> prevNode(5);
    Node<int> node(10, *prevNode);
    EXPECT_EQ(node.get_data(), 10);
    EXPECT_EQ(node.get_previous()->get_data(), 5);
}

TEST(NodeTest, ConstructorWithPrevAndNext)
{
    Node<int> prevNode(5);
    Node<int> nextNode(15);
    Node<int> node(10, *prevNode, *nextNode);
    EXPECT_EQ(node.get_data(), 10);
    EXPECT_EQ(node.get_previous()->get_data(), 5);
    EXPECT_EQ(node.get_next()->get_data(), 15);
}

TEST(NodeTest, GetData)
{
    Node<int> node(42);
    EXPECT_EQ(node.get_data(), 42);
}

TEST(NodeTest, SetNext)
{
    Node<int> node(10);
    Node<int> nextNode(20);
    node.set_next(*nextNode);
    EXPECT_EQ(node.get_next()->get_data(), 20);
}

TEST(NodeTest, SetPrevious)
{
    Node<int> node(10);
    Node<int> prevNode(5);
    node.set_previous(*prevNode);
    EXPECT_EQ(node.get_previous()->get_data(), 5);
}

TEST(NodeTest, OperatorGreaterThan)
{
    Node<int> node1(10);
    Node<int> node2(5);
    EXPECT_TRUE(node1 > node2);
}

TEST(NodeTest, OperatorLessThan)
{
    Node<int> node1(5);
    Node<int> node2(10);
    EXPECT_TRUE(node1 < node2);
}

TEST(NodeTest, OperatorEquals)
{
    Node<int> node1(10);
    Node<int> node2(10);
    EXPECT_TRUE(node1 == node2);
}

TEST(NodeTest, OperatorNotEquals)
{
    Node<int> node1(10);
    Node<int> node2(5);
    EXPECT_TRUE(node1 != node2);
}

TEST(NodeTest, OperatorGreaterThanOrEqual)
{
    Node<int> node1(10);
    Node<int> node2(10);
    Node<int> node3(5);
    EXPECT_TRUE(node1 >= node2);
    EXPECT_TRUE(node1 >= node3);
}

TEST(NodeTest, OperatorLessThanOrEqual)
{
    Node<int> node1(5);
    Node<int> node2(5);
    Node<int> node3(10);
    EXPECT_TRUE(node1 <= node2);
    EXPECT_TRUE(node1 <= node3);
}

TEST(NodeTest, CopyAssignment)
{
    Node<int> node1(10);
    Node<int> node2 = node1;
    EXPECT_EQ(node2.get_data(), 10);
}


TEST(NodeTest, OperatorPlusEqualsNode)
{
    Node<int> node1(10);
    Node<int> node2(5);
    node1 += node2;
    EXPECT_EQ(node1.get_data(), 15);
}

TEST(NodeTest, OperatorPlusEqualsValue)
{
    Node<int> node1(10);
    node1 += 5;
    EXPECT_EQ(node1.get_data(), 15);
}

TEST(NodeTest, Destructor)
{
    auto node = new Node<int>(42);
    delete node;
    SUCCEED();
}

TEST(NodeTest, DefaultConstructor)
{
    Node<int> node(0);
    EXPECT_EQ(node.get_data(), 0);
}

TEST(NodeTest, OperatorLessThanWithValue)
{
    Node<int> node(10);
    EXPECT_TRUE(node < 20);
}

TEST(NodeTest, OperatorEqualsWithValue)
{
    Node<int> node(10);
    EXPECT_TRUE(node == 10);
}
