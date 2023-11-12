#pragma once
#include <iostream>
#include"Vector.h"
#include<queue>
#include<ctime>
#include<cctype>
#include"Date_Time.h"
#include<string>
#include<fstream>
//Global variables
////my_file to write into file and my_file2 is to search for a file and print its data on screen
//disabling un_usual warning
#pragma warning(disable : 4996)

using namespace std;

class TrieNode
{
public:
	//signifies the completion of the word
	bool is_word;
	TrieNode* child[26];
};

class TrieTree {
	TrieNode* root;


public:

	//Default constructor
	TrieNode* GetNewNode();
	TrieTree();
	TrieNode* GetRoot();


	//insert key in the tree
	void Insert(std::string key);

	//additional function to search a particular key
	bool Search(std::string key);

	/*
	helper function takes 3 parameters
	1) root of subtrie of Trie Tree (or subtree)
	2) processing key (key which is going to be deleted). key is string
	3) index -> which character is processing or how much depth

	It returns the root of the subtrie
	*/
	//associated with the delete function
	TrieNode* Helper(TrieNode* root, std::string key, int index);

	TrieNode* DeleteKey(std::string key);
	//find all words related to a prefix or which a key prefix
	//function associated with the auto_complete function. Helper function of auto_complete
	void find_all_words(TrieNode* root, std::string key, Vector<std::string>& all_words);
	std::string auto_complete(TrieNode* root, std::string key);

};