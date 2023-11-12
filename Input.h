#pragma once
#include<fstream>
#include"TrieTree.h"
#include<string>
#include<conio.h>
#include"Huffman.h"

struct Input
{
	string file_name;
	string user_name;
	string line;
	//HuffMan huffman;
	void LaunchNotepad(TrieTree& obj, fstream& my_file, fstream& my_file2);
	void SearchFile(fstream& my_file, fstream& my_file2);
	void SearchHistory(fstream& my_file, fstream& my_file2);
	void AskDetails();
	void InsertDictionary(TrieTree obj);
	//void HuffManCompression();
};
