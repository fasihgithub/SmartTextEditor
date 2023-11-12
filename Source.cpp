//#include<iostream>
//#include"Date_Time.h"

#include"Input.h"
//#include"Huffman.h"
//#include"TrieTree.h"
//#include"Vector.h"


//global variable

	struct node1
	{
		char data;
		string brr;
		node1* next;
		node1* previous;
	};
	
	struct NODE {
		char data;
		NODE* LEFT;
		NODE* RIGHT;
		int frequency;
	};

	struct node :public NODE {
		char  data;
		node* next;
		int frequency;
		NODE* obj;
	};

	string name_of_file;
	node* front;
	node* rear;
	node1* head;//for linklist
	node1* tail;

	node* swap(node * ptr1, node * ptr2)
	{
		node* tmp = ptr2->next;
		ptr2->next = ptr1;
		ptr1->next = tmp;
		return ptr2;
	}

	bool isempty()
	{
		if (head == nullptr)
		{
			return 1;
		}
		else return 0;
	}

	void insert_end(char data, string b1)
	{
		node1* ptr = new node1();
		bool flag;
		flag = isempty();
		if (flag == 1)//checking if head is null then it put head to ptr
		{
			head = ptr;
			tail = ptr;
			ptr->data = data;
			ptr->brr = b1;
			ptr->next = nullptr;
			ptr->previous = nullptr;
		}
		else {
			ptr->brr = b1;
			ptr->data = data;
			node1* copy;
			copy = head;
			while (copy->next != nullptr)//loop runs until it find last node
			{
				copy = copy->next;
			}
			copy->next = ptr;
			ptr->previous = copy;
			tail = ptr;
			ptr->next = nullptr;
		}
	}

	string findingcode(char a)
	{
		node1* ptr = head;
		while (ptr != nullptr)
		{
			if (ptr->data == a)
			{
				return (ptr->brr);
			}
			ptr = ptr->next;
		}

	}

	void makingpriotyqueue()
	{
		int count = 0;
		node** head = &front;
		node* start = front;
		while (start != NULL) { //grab count
			count++;
			start = start->next;
		}
		struct node** h;
		int i, j, swapped;

		for (i = 0; i <= count; i++)
		{

			h = head;
			swapped = 0;

			for (j = 0; j < count - i - 1; j++)
			{

				node* p1 = *h;
				node* p2 = p1->next;

				if (p1->frequency > p2->frequency)
				{

					/* update the link after swapping */
					*h = swap(p1, p2);
					swapped = 1;
				}

				h = &(*h)->next;
			}

			/* break if the loop ended without any swap */
			if (swapped == 0)
				break;
		}
	}

	void enqueue(char a, int freq, bool symbol, NODE * kl)///making proity queueu 
	{
		if (front == nullptr && rear == nullptr)
		{
			node* newnode = new node();
			front = newnode;
			rear = newnode;
			newnode->data = a;
			newnode->frequency = freq;
			newnode->obj = kl;
			newnode->obj->data = a;
			newnode->obj->frequency = freq;

		}
		else
		{
			bool flag = 0;
			if (symbol == 0)
			{

				node* check = front;
				while (check != NULL)
				{
					if (check->data == a)
					{
						check->frequency++;////last rear masla may be
						check->obj->frequency++;
						flag = 1;
						break;
					}
					check = check->next;
				}
			}
			if (flag == 0)
			{
				node* check = front;
				while (check->next != NULL)
				{
					check = check->next;
				}
				node* newnode = new node();
				check->next = newnode;
				newnode->data = a;
				newnode->frequency = freq;
				newnode->obj = kl;
				newnode->obj->data = a;
				newnode->obj->frequency = freq;
				rear = newnode;
			}
		}
	}

	void dequeue()
	{
		if (front == nullptr && rear == nullptr)
		{
			cout << "queue is empty";
		}
		else if (front == rear)
		{
			front = nullptr;
			rear = nullptr;
		}
		else {
			node* temp = front;
			front = front->next;
			delete temp;
		}
	}

	void displayqueue()
	{
		node* temp = front;
		cout << "updated queue is:";
		while (temp != nullptr) {
			cout << temp->data << " " << temp->frequency << endl;
			temp = temp->next;
		}
		cout << endl;
	}

	int isSizeOne()
	{
		int counter = 0;
		node* check = front;
		while (check != NULL)
		{
			counter++;
			check = check->next;
		}
		return counter;

	}

	NODE* extractmin()
	{
		node* check = front;
		NODE* temp = new NODE();
		temp = check->obj;
		temp->data = check->data;
		temp->frequency = check->frequency;
		dequeue();
		return temp;
	}

	NODE* huffmantree() //here
	{
		NODE* LL;
		NODE* RR;
		NODE* TOP;
		while (isSizeOne() != 1)
		{
			LL = extractmin();
			RR = extractmin();
			TOP = new NODE();
			TOP->data = '$';
			TOP->frequency = LL->frequency + RR->frequency;
			TOP->LEFT = LL;
			TOP->RIGHT = RR;
			enqueue('$', TOP->frequency, 1, TOP);//also want to wnqueue node actuall
			makingpriotyqueue();

		}
		return(extractmin());

	}

	int check(int a)
	{
		if (a == 0)
		{
			return 48;
		}
		else if (a == 1)
		{
			return 49;
		}
	}

	string printArr(int brr[], int n)
	{
		string h1;
		int i;
		for (i = 0; i < n; ++i)
		{
			//cout << brr[i];
			h1 += check(brr[i]);
		}
		//	cout << "\n";
		return h1;
	}

	int isLeaf(NODE * rooot)
	{

		return !(rooot->LEFT) && !(rooot->RIGHT);
	}

	void printshfcodes(NODE * fun, int ARR[], int n)
	{
		if (fun->LEFT)
		{

			ARR[n] = 0;
			printshfcodes(fun->LEFT, ARR, n + 1);
		}

		// Assign 1 to right edge and recur
		if (fun->RIGHT) {

			ARR[n] = 1;
			printshfcodes(fun->RIGHT, ARR, n + 1);
		}
		if (isLeaf(fun)) {
			string b10;
			//cout << fun->data << ": ";
			b10 = printArr(ARR, n);
			insert_end(fun->data, b10);
			///enqueue
		}

	}

	void encoding()
	{
		int* ARR = new int[100000000];
		bool flag = 0;
		char c1;
		ifstream f1;

		f1.open(name_of_file + ".txt");/////change filename here
		if (!f1) {
			cout << "file not found:";
			exit(0);
		}
		while (!f1.eof())
		{
			NODE* PTR2 = new NODE();
			f1 >> c1;
			if (f1.eof())
			{
				flag = 1;
				break;
			}
			enqueue(c1, 1, 0, PTR2);
		}
		makingpriotyqueue();
		//displayqueue();
		NODE* HFTREE;
		HFTREE = huffmantree();
		printshfcodes(HFTREE, ARR, 0);
	}

	void tablewrite()
	{
		char a;
		string q;
		ofstream f4;
		f4.open(name_of_file + ".table.txt");
		node1* ptr = head;
		while (ptr != NULL)
		{
			a = ptr->data;
			q = ptr->brr;
			f4 << a;
			f4 << q;
			f4 << endl;
			ptr = ptr->next;
		}
		f4.close();
	}

	void makingcompressedfile()
	{
		string d1;
		bool flag;
		char c1;
		ifstream f1;
		ofstream f3;
		f1.open(name_of_file + ".txt");
		f3.open(name_of_file + ".compress.txt");
		while (!f1.eof())
		{
			f1 >> c1;
			if (f1.eof())
			{
				flag = 1;
				break;
			}
			d1 = findingcode(c1);
			f3 << d1;
		}
		f1.close();
		f3.close();
		tablewrite();
	}

	char checking_ifpresentinlist(string w)
	{
		bool flag = 0;
		char q;
		node1* check = head;
		while (check != nullptr)
		{
			if (check->brr == w)
			{
				flag = 1;
				q = check->data;
				break;

			}
			check = check->next;
		}
		if (flag == 0)
		{
			return 48;
		}
		else return q;
	}

	void convetingcompress_to_real()
	{
		char fun;
		char z;
		string q;
		ifstream f2;
		ofstream f3(name_of_file + "_2.txt");
		f2.open(name_of_file + ".compress.txt");
		if (!f2)
		{
			cout << "not opened";
		}
		while (!f2.eof())
		{
			f2 >> z;
			if (f2.eof())
				break;
			q += z;
			fun = checking_ifpresentinlist(q);
			if (fun != 48)
			{
				f3 << fun;
				q.clear();
			}
		}
	}

	void decoding1()
	{
		char a;
		string b;

		int input;
		/*cout << "enter the file on which your compressed data is stored:";
		cin >> input;*///check how do it?
		ifstream f1;
		f1.open(name_of_file + ".table.txt");
		if (!f1)							//if file does not open
		{
			cout << "File could not be opened\n";
			exit(0);
		}
		else {
			while (!f1.eof())
			{
				f1 >> a;
				f1 >> b;
				if (f1.eof())
				{
					break;
				}
				insert_end(a, b);

			}
		}
		//display10();
		convetingcompress_to_real();

	}



int main()
{
	fstream my_file, your_file;
	/*cout << "Hello world\n";
	cout << date_time.GenerateTime() << endl;*/
	Date_Time date_time;
	Input input;
	TrieTree tree;
	//ask username and the file name that we may want use for writing
	input.AskDetails();

	input.InsertDictionary(tree);
	string option;
	
		cout << "1. Open notepad\n";
		cout << "2. Search for file\n";
		cout << "3. Check History\n";
		cout << "4. Clear Screen\n";
		cout << "5. Do HuffMan Compression\n";
		cout << "6. Change your username\n";
		cin >> option;
		cout << "Your entered option is: ";
		switch (option[0])
		{
		case 'n':
			break;

		case 'N':
			break;
		case '1':
			cout << "Launching notepad!\n";
			
			input.LaunchNotepad(tree,my_file,your_file);
			break;
		case '2':
			cout << "Search function called\n";
			input.SearchFile(my_file,your_file);
			break;
		case '3':
			cout << "Beloved History:\n";
			input.SearchHistory(my_file,your_file);
			break;
		case '4':
			system("cls");
			break;
		case '5':
			name_of_file = input.file_name;
			    encoding();
			    makingcompressedfile();
			   decoding1();
			break;
		case '6':
			cout << "Enter the username\n";
			cin >> input.user_name;
			break;
		case '7':
			cout << "Not constructed yet!\n";
			break;
		default:
			cout << "Please enter a valid option";
			break;
		}
	
	return -0;
}