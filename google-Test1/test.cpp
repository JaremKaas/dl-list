#include "pch.h"
#include <iostream>
#include "slist.h"

using std::cout;
using std::endl;
using std::string;

struct testList_int : public testing::Test {
	List<int,int>* l;

	void SetUp() { l = new List<int,int>(); }
	void TearDown() { delete l; }

};
TEST_F(testList_int, initialLength) {
	ASSERT_EQ(l->refLength() , 0);
}
TEST_F(testList_int, afterAdding_1) {
	l->insert(1, 1);
	ASSERT_EQ(l->refLength(), 1);
	ASSERT_TRUE(l->doesNodeExist(1));
	l->clear();
	ASSERT_EQ(l->refLength(), 0);
	ASSERT_FALSE(l->doesNodeExist(1));
}
TEST_F(testList_int, afterAdding_2) {
	l->insert(1, 3);
	l->insert(2, 2);
	l->insert(4, 4);
	l->insert(5, 3);
	l->insert(7, 2);
	l->insert(100, 4);
	ASSERT_EQ(l->refLength(), 6);
	ASSERT_TRUE(l->doesNodeExist(100)&& l->doesNodeExist(1)
		&& l->doesNodeExist(7)&&l->doesNodeExist(5)
		&& l->doesNodeExist(4)&& l->doesNodeExist(2));
	l->clear();
	ASSERT_EQ(l->refLength(), 0);
	ASSERT_FALSE(l->doesNodeExist(100) && l->doesNodeExist(1)
		&& l->doesNodeExist(7) && l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
}
TEST_F(testList_int, noDuplicates) {
	l->insert(1, 3);
	l->insert(2, 2);
	l->insert(4, 4);
	l->insert(5, 3);
	l->insert(7, 2);
	l->insert(100, 4);
	ASSERT_EQ(l->refLength(), 6);
	ASSERT_TRUE(l->doesNodeExist(100) && l->doesNodeExist(1)
		&& l->doesNodeExist(7) && l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
	l->insert(1, 3);
	l->insert(2, 2);
	l->insert(4, 4);
	l->insert(5, 3);
	l->insert(7, 2);
	l->insert(100, 4);
	ASSERT_EQ(l->refLength(), 6);
	ASSERT_TRUE(l->doesNodeExist(100) && l->doesNodeExist(1)
		&& l->doesNodeExist(7) && l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
}
TEST_F(testList_int, removeHead) {
	l->insert(1, 3);
	l->insert(2, 2);
	l->insert(4, 4);
	l->insert(5, 3);
	l->insert(7, 2);
	l->insert(100, 4);
	ASSERT_EQ(l->refLength(), 6);
	ASSERT_TRUE(l->doesNodeExist(100) && l->doesNodeExist(1)
		&& l->doesNodeExist(7) && l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
	l->erase(1);
	ASSERT_EQ(l->refLength(), 5);
	ASSERT_TRUE(l->doesNodeExist(100)&& l->doesNodeExist(7) 
		&& l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
	ASSERT_FALSE(l->doesNodeExist(1));
}
TEST_F(testList_int, removeTail) {
	l->insert(1, 3);
	l->insert(2, 2);
	l->insert(4, 4);
	l->insert(5, 3);
	l->insert(7, 2);
	l->insert(100, 4);
	ASSERT_EQ(l->refLength(), 6);
	ASSERT_TRUE(l->doesNodeExist(100) && l->doesNodeExist(1)
		&& l->doesNodeExist(7) && l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
	l->erase(100);
	ASSERT_EQ(l->refLength(), 5);
	ASSERT_TRUE(l->doesNodeExist(1) && l->doesNodeExist(7)
		&& l->doesNodeExist(5)
		&& l->doesNodeExist(4) && l->doesNodeExist(2));
	ASSERT_FALSE(l->doesNodeExist(100));
}

struct testList_string : public testing::Test {
	List<int,string>* l2;

	void SetUp() { l2 = new List<int, string>(); }
	void TearDown() { delete l2; }
};
TEST_F(testList_string, initial) {
	ASSERT_EQ(l2->refLength(), 0);
}
TEST_F(testList_string, afterAdding_1) {
	l2->insert(1, "text one");
	ASSERT_EQ(l2->refLength(), 1);
	ASSERT_TRUE(l2->doesNodeExist(1));
	ASSERT_EQ(l2->getInfo(1), "text one");
	l2->clear();
	ASSERT_EQ(l2->refLength(), 0);
	ASSERT_FALSE(l2->doesNodeExist(1));
}
TEST_F(testList_string, afterAdding_2) {
	l2->insert(1, "text one");
	l2->insert(2, "text two");
	l2->insert(4, "text four");
	l2->insert(5, "text five");
	l2->insert(7, "text seven");
	l2->insert(100, "text hundred");
	ASSERT_EQ(l2->refLength(), 6);
	ASSERT_TRUE(l2->doesNodeExist(100) && l2->doesNodeExist(1)
		&& l2->doesNodeExist(7) && l2->doesNodeExist(5)
		&& l2->doesNodeExist(4) && l2->doesNodeExist(2));
	l2->clear();
	ASSERT_EQ(l2->refLength(), 0);
	ASSERT_FALSE(l2->doesNodeExist(100) && l2->doesNodeExist(1)
		&& l2->doesNodeExist(7) && l2->doesNodeExist(5)
		&& l2->doesNodeExist(4) && l2->doesNodeExist(2));
}