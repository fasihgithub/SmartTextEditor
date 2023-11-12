#include"TrieTree.h"

TrieNode* TrieTree::GetNewNode()
{
	TrieNode* temp = new TrieNode;
	temp->is_word = false;
	for (int i = 0; i < 26; i++)
	{
		temp->child[i] = NULL;
	}
	return temp;
}

TrieTree::TrieTree()
{
	//initializing the root node
	root = GetNewNode();
}

void TrieTree::Insert(std::string key)
{
	//storing the root in temp
	TrieNode* temp = root;
	//insert all the characters of the string by starting from 0 index to key length()-1 index
	for (int i = 0; i < key.length(); i++)
	{
		//taking mode with 97 so a smaller number than 97 will be stored in it
		int index = (key[i]) - int('a');
		//discarding speacial characters and only accepting alpabets
		if (index < 0 || index>25)
		{
			break;
		}
		//if null then get an address at that index to ensure the existence/insertion of that character
		if (temp->child[index] == NULL)
		{
			temp->child[index] = GetNewNode();
			//in case the heap is not able to assign memory
			if (temp->child[index] == NULL)
				return;
		}
		//iterate irrespective of the fact that the charcter is already in the tree or not
		temp = temp->child[index];//going in to the new node which is present at the index of child
	}
	//marking that the current word is in the tree
	//the last character of the word in the tree will have is_word true which indicates its the last character of the word

	temp->is_word = true;//if we need to find the word with the help of this will be able to find the word and we do not have to further iterate in the tree
}

bool TrieTree::Search(std::string key)
{
	//comparing the passed root in the parameter
	if (root == NULL)
		return false;
	TrieNode* temp = root;
	for (int i = 0; i < key.length(); i++)
	{
		//taking mod with 26 as there are total 26 aplhabers/characters in English
		int index = (key[i]) -'a';
		//if the trie tree lacks any character of the word in it then simple return not present i.e. false
		if (temp->child[index] == NULL) return false;
		temp = temp->child[index];
	}
	return temp->is_word;
}

//Delete function helper
TrieNode* TrieTree::Helper(TrieNode* root, std::string key, int index)
{
	//if tree is empty
	if (root == NULL)
		return NULL;
	bool is_empty = true;
	for (int i = 0; i < 26; i++)
	{
		if (root->child[i] != NULL)
		{
			is_empty = false;
			break;
		}
	}

	//This will be the case when have completed the iteration completly through the word
	if (index == key.length())
	{
		//Now we need to check whether this word is prefix of some other word(s)
		//In the first case, we will make is is_word false

		//otherwise if the word is compelte and ther is no further character linked to
		//then we will simply delete that character
		if (is_empty == false)
		{
			//scenario 1
			//it will look then word is not present in the tree
			root->is_word = false;
		}
		else
		{
			//scenario 2
			//delete that key and the root will be the sub root will be signifying the first letter of the word
			delete(root);
			root = NULL;
		}
		return root;
	}
	int pos = int(key[index]) - 'a';
	root->child[pos] = Helper(root->child[pos], key, index + 1);

	is_empty = true;
	for (int i = 0; i < 26; i++)
	{
		if (root->child[i] != NULL)
		{
			is_empty = false;
			break;
		}
	}
	/* here we have two case
	1) if all child nodes of root is empty and this root is not marked as
	 of word then delete this node

	2) if all child nodes are not empty "OR" this root is marked as end of
	 word then do nothing
	*/
	if (is_empty && root->is_word == false)
	{
		delete(root);
		root = NULL;
	}
	return root;
}

TrieNode* TrieTree::DeleteKey(std::string key)
{
	//if trie is empty
	if (root == NULL)
	{
		return root;
	}
	//if key is empty
	if (key == "")
		return root;
	//recursive call to delete the key
	root = Helper(root, key, 0);
	return root;
}

//void TrieTree::find_all_words(TrieNode* root, std::string key, Vector<string>& all_words)
//{
//	if (root == NULL)
//		return;
//	TrieNode* temp = root;
//
//	//check if the prefix is prensent in the tree or not
//	for (int i = 0; i < key.size(); i++)
//	{
//		int index = (key[i]) - ('a');
//		//if the child at index of current root is NULL
//		//if any character of the prefix is not in the tree then simply exit or return
//		if (temp->child[index] == NULL)
//			return;
//		temp = temp->child[index];
//	}
//	//we are on this line which means the prefix is present in tree
//	queue<TrieNode*> q;
//	queue<std::string> q2;
//	q.push(temp);//pushing the the address of node next to key prefix i.e. giving it the next character but not exactly
//	q2.push(key);
//	std::string this_word;
//	while (!q.empty())
//	{
//		temp = q.front();
//		this_word = q2.front();
//		//if this is word, then add it to the all_words(Vector) */
//		for (int i = 0; i < 26; i++)
//		{
//			//otherwise push the words in the queue in lexicographical manner
//			if (temp->child[i] != NULL)
//			{
//				q.push(temp->child[i]);
//				q2.push(this_word + char(i + int('a')));
//			}
//		}
//	}
//}

//std::string TrieTree::auto_complete(TrieNode* root, std::string key)
//{
//	std::fstream auto_file;
//	auto_file.open("suggestions.txt", std::ios::out);//opening file to write on it
//
//	if (!auto_file.is_open())
//		std::cout << "Can't open the file\n";
//	/*This function takes 2 parameters
//	* 1) root node of trie
//	* 2) key for which suggestion need to find.
//	*
//	* This function prints all words for which key is available
//	*/
//
//	/* if key is empty, no need to print*/
//	if (key.size() == 0) return key;
//	//if key is not empty, then we will show all the words
//	Vector<string> all_words;
//	find_all_words(root, key, all_words);
//	//print all words
//	bool condition = false;
//	int i = 1;
//
//	// in case we encounter the same word in the suggestion then we need to have an additional varaible that will not print more than 10 suggestions in any case
//	int end_point = 10;
//	if (all_words.size() == 1)//if there exist only one suggest
//	{
//		if (all_words[0].size() == key.size())//The suggested word is that word then we need skip it while printing
//			condition = true;
//		else
//		{
//			i = 0;
//			end_point = 9;
//		}
//	}
//
//	if (all_words.size() == 0 || condition)//excluding the word itself from suggestion
//	{
//		auto_file << "There are no suggestions.\n";
//		return key;
//	}
//	//excluding the word itself form suggestion
//	if (all_words[0].size() == key.size())//in case same word is going to be suggested then we have to eradicate it while printing
//	{
//		auto_file << "There are " << all_words.size() - 1;
//		end_point = 10;
//
//	}
//	else
//	{
//		auto_file << "There are " << all_words.size();
//		i = 0;
//		end_point = 9;
//
//	}
//	auto_file << " suggestions for this/these letters: " << key << "\n";
//	for (; i < all_words.size() && i <= end_point; i++)
//	{
//		auto_file << all_words[i] << "\n";
//	}
//	if (all_words.size() >= 1)
//	{
//		if (all_words[0].size() > key.size())
//			return all_words[0];
//
//		return all_words[1];
//	}
//	else
//		return key;
//}

//void TrieTree::find_all_words(TrieNode* root, string key, Vector<string>& all_words)
//{
//    if (root == NULL) return;
//	TrieNode* temp = root;
//
//    for (int i = 0; i < (int)key.size(); i++)
//    {
//        int ind = int(key[i]) - 'a';
//        /* if child node at ind of current root is NULL this prefix do not exist in trie  */
//        if (temp->child[ind] == NULL) return;
//
//        temp = temp->child[ind];
//    }
//
//    /* if this prefix exist in trie then do BFS from current node to find all words  */
//    queue<TrieNode* > q;
//    queue<string> q2;
//    q.push(temp);
//    q2.push(key);
//    string this_word;
//    while (!q.empty())
//    {
//        temp = q.front();
//        this_word = q2.front();
//        /* if this is word ,then add it to the all_words(Vector) */
//        if (temp->is_word) all_words.push_back(this_word);
//        q.pop();
//        q2.pop();
//        for (int i = 0; i < 26; i++)
//        {
//            if (temp->child[i] != NULL)
//            {
//                q.push((temp->child[i]));
//                q2.push(this_word + char(i + int('a')));
//            }
//        }
//    }
//
//}

//string TrieTree::auto_complete(TrieNode* root, string key)
//{
//	fstream auto_file;
//	auto_file.open("my.txt", ios::out);//opening file to write on it
//
//	if (!auto_file.is_open())
//		std::cout << "Can't open the file\n";
//	/* this function takes two parametes
//	   1.) root node of trie
//	   2.) key for which suggestion need to find.
//
//	   this function prints all the words for which key is prefix.
//	*/
//
//	/* if key is empty , no need to print */
//	if (key.size() == 0) return key;
//
//	/* if key is not empty , then we will print all words in trie for which key is PREFIX. */
//
//	Vector<string> all_words;
//
//	find_all_words(root, key, all_words);
//
//	/* print all words */
//
//	bool condition = false;
//	int i = 1;
//
//	if (all_words.size() == 1)//if there exist only one suggest
//	{
//		if ((all_words[0]).size() == key.size())//The suggested word is that word then we need to remove it
//			condition = true;
//		else i = 0;
//	}
//
//	if (all_words.size() == 0 || condition)//excluding the word itself from suggestion
//	{
//		auto_file << "There are no suggestions." << '\n';
//		return key;
//	}
//	//excluding the word itself from suggestion
//	if (all_words[0].size() == key.size())//in case the same word is going to suggested then we have to eradicate it
//		auto_file << "There are " << all_words.size() - 1;
//	else
//	{
//		auto_file << "There are " << all_words.size();
//		i = 0;
//	}
//	auto_file << " suggestions for this prefix but showing 10=>suggestions  " << key << '\n';
//	for (; i < all_words.size() && i <= 10; i++) {
//		auto_file << all_words[i] << '\n';
//	}
//	if (all_words.size() >= 1)
//	{
//		if (all_words[0].size() > key.size())
//			return all_words[0];
//
//		return all_words[1];
//	}
//	else
//		return key;
//}

void TrieTree::find_all_words(TrieNode* root, string key, Vector<string>& all_words)
{
	if (!root)//if root is NULL
	{
		return;
	}
	TrieNode* temp = root;
	//check if the word (prefix) is present in the trie tree or not
	for(int i = 0; i < key.size(); i++)
	{
		int index = key[i] - 97;
		//if the child at index of current root is NULL
		//if any character of the prefix is not in the tree then simply exit or return
		if (temp->child[index] == NULL)
		{
			return;
		}
		temp = temp->child[index];
	}
	//if this prefix exist in trie then do BFS form current node to find all words 
	queue<TrieNode*>q;
	queue<string>q2;
	q.push(temp);
	q2.push(key);
	string this_word;
	while (!q.empty())
	{
		temp = q.front();
		this_word = q2.front();
		//if this is_word then add it to the all_words(Vector)
		if (temp->is_word) all_words.push_back(this_word);
		q.pop();
		q2.pop();
		for (int i = 0; i < 26; i++)
		{
			if (temp->child[i] != NULL)
			{
				q.push(temp->child[i]);//inserting the child node address present at index of the child TrieNode array
				q2.push(this_word + char(i + 'a'));//
			}
		}
	}
}

string TrieTree::auto_complete(TrieNode* root, string key)
{
	fstream auto_file;
	auto_file.open("my.txt", ios::out);//opening file to write on it

	if (!auto_file.is_open())
		std::cout << "Can't open the file\n";
	/* this function takes two parametes
	   1.) root node of trie
	   2.) key for which suggestion need to find.

	   this function prints all the words for which key is prefix.
	*/

	/* if key is empty , no need to print */
	if (key.size() == 0) return key;

	/* if key is not empty , then we will print all words in trie for which key is PREFIX. */

	Vector<string> all_words;

	find_all_words(root, key, all_words);

	/* print all words */

	bool condition = false;
	int i = 1;
	if (all_words.size() == 1)//if there exist only one suggest
	{
		if ((all_words[0]).size() == key.size())//The suggested word is that word then we need to remove it
			condition = true;
		else i = 0;
	}

	if (all_words.size() == 0 || condition)//excluding the word itself from suggestion
	{
		auto_file << "There are no suggestions." << '\n';
		return key;
	}
	//excluding the word itself from suggestion
	if (all_words[0].size() == key.size())//in case the same word is going to suggested then we have to eradicate it
		auto_file << "There are " << all_words.size() - 1;
	else
	{
		auto_file << "There are " << all_words.size();
		i = 0;
	}
	auto_file << " suggestions for this prefix but showing 10=>suggestions  " << key << '\n';
	for (; i < all_words.size() && i <= 10; i++) {
		auto_file << all_words[i] << '\n';
	}
	if (all_words.size() >= 1)
	{
		if (all_words[0].size() > key.size())
			return all_words[0];

		return all_words[1];
	}
	else
		return key;
}

TrieNode* TrieTree::GetRoot()
{
	return root;
}
