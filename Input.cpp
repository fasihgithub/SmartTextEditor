#include"Input.h"

//Taking obj.GetRoot() node of the Trie Tree and fstream object to write and read data into the user file
void Input::LaunchNotepad(TrieTree& obj,fstream& my_file,fstream& my_file2)
{
   // my_file.flush();
    my_file.open(file_name+".txt", std::ios::app);
    char* ch_array;
    if (!my_file.is_open())
        std::cout << "File is not open\n";
    else
        std::cout << "File is opened/created. Now you can type into the file\n";
    //created a variable of string and str
    std::string string, str;
    //creating a size variable and initializing it with 0
    int _size = 0;
    //creating a character variable initiliazing it with NULL value
    char ch = NULL;
    bool condition = true;
    Date_Time date_time;
    while (condition)
    {
        //As soon as a key from keyboard is pressed then this if will be executed
        if (_kbhit())//taking input form the keyboard
        {
            switch (_getch())//taking the pressed key ascii from getch() as it is stored in getch() when ever kbhit function is used for taking the input keystroke
            {
            case 'a':
                std::cout << 'a';
                string += 'a';
                my_file << 'a';
                break;

            case 'b':
                std::cout << 'b';
                string += 'b';
                my_file << 'b';
                break;

            case 'c':
                std::cout << 'c';
                string += 'c';
                my_file << 'c';
                break;

            case 'd':
                std::cout << 'd';
                string += 'd';
                my_file << 'd';
                break;

            case ('e'):
                std::cout << 'e';
                string += 'e';
                my_file << 'e';
                break;

            case  'f':
                std::cout << 'f';
                string += 'f';
                my_file << 'f';
                break;

            case ('g'):
                std::cout << 'g';
                string += 'g';
                my_file << 'g';

                break;
            case  'h':
                std::cout << 'h';
                string += 'h';
                my_file << 'h';
                break;

            case ('i'):
                std::cout << 'i';
                string += 'i';
                my_file << 'i';

                break;
            case  'j':
                std::cout << 'j';
                string += 'j';
                my_file << 'j';
                break;

            case ('k'):
                std::cout << 'k';
                string += 'k';
                my_file << 'k';
                break;

            case  'l':
                std::cout << 'l';
                string += 'l';
                my_file << 'l';
                break;

            case ('m'):
                std::cout << 'm';
                string += 'm';
                my_file << 'm';
                break;

            case  'n':
                std::cout << 'n';
                string += 'n';
                my_file << 'n';
                break;

            case ('o'):
                std::cout << 'o';
                string += 'o';
                my_file << 'o';
                break;

            case  'p':
                std::cout << 'p';
                string += 'p';
                my_file << 'p';
                break;

            case ('q'):
                std::cout << 'q';
                string += 'q';
                my_file << 'q';
                break;

            case  'r':
                std::cout << 'r';
                string += 'r';
                my_file << 'r';
                break;

            case ('s'):
                std::cout << 's';
                string += 's';
                my_file << 's';
                break;

            case  't':
                std::cout << 't';
                string += 't';
                my_file << 't';
                break;

            case ('u'):
                std::cout << 'u';
                string += 'u';
                my_file << 'u';
                break;

            case  'v':
                std::cout << 'v';
                string += 'v';
                my_file << 'v';
                break;

            case ('w'):
                std::cout << 'w';
                string += 'w';
                my_file << 'w';
                break;

            case  'x':
                std::cout << 'x';
                string += 'x';
                my_file << 'x';
                break;

            case ('y'):
                std::cout << 'y';
                string += 'y';
                my_file << 'y';
                break;

            case  'z':
                std::cout << 'z';
                string += 'z';
                my_file << 'z';
                break;

            case 27://when ESC key is pressed
                condition = false;
                break;

            case 13://new line ascii
                std::cout << "\n";
                string = "";//empty the string
                my_file << '\n';
                break;

            case 32://space ascii
                std::cout << " ";
                string = "";//empty the string
                my_file << ' ';
                break;

            case '.':
                std::cout << ".";
                my_file << '.';
                break;

            case ',':
                std::cout << ",";
                my_file << ',';
                break;

            case '!':
                std::cout << "!";
                my_file << '!';
                break;

            case '/':
                std::cout << "/";
                my_file << '/';
                break;

            case 224:
                for (int a = string.length(); a < str.size(); a++)
                {
                    std::cout << str[a];
                    my_file << str[a];
                }
                //replacing the string with the new one
                string = str;
                break;
            }
            str = (obj.auto_complete(obj.GetRoot(), string));
        }
    }
    //Now adding an new line in it then closing the file
    my_file.close();
    cout << "The file is saved with name: " << file_name << "\n";
    my_file2.open("History.txt", std::ios::app);
    //creating in object of time and date class to generate time
    my_file2 << "User: " << user_name << " opened/edited file: " << file_name << " " << date_time.GenerateTime() << "\n";
    my_file2.close();
}

void Input::SearchFile(fstream& my_file,fstream& my_file2)
{
    std::string line;
    Date_Time date_time;
    std::cout << "\n Enter the file name whose content you would like to see!\n";
    std::cin >> line;

    //my_file.flush();
    my_file.open(line + ".txt", std::fstream::in);//file in input mode to get data form the file
    char ch;
    if (my_file.is_open())
    {
        //print character by charcter from file till the end of the file
        while (my_file.eof() == 0)//if the end of file is not reached then again iterate
        {
            my_file.get(ch);
            std::cout << ch;
        }
    }
    else std::cout << "Can't open the file\n";// in case, unable to open the file
    //In case the ofstream object do not work. So its the quick fix for it
    //my_file2.flush();
    //Noting the time and date of file opening in the History file
    my_file2 << "User: " << user_name << " searched file: " << file_name << " " << date_time.GenerateTime() << "\n";

}

void Input::SearchHistory(fstream& my_file,fstream& my_file2)
{
    std::string line;
    Date_Time date_time;
    //my_file.flush();
    my_file.open("History.txt", std::fstream::in);//file in input mode to get data form the file
    char ch;
    if (my_file.is_open())
    {
        //print character by charcter from file till the end of the file
        while (my_file.eof() == 0)//if the end of file is not reached then again iterate
        {
            
            my_file.get(ch);
            std::cout << ch;
        }
    }
    else std::cout << "Can't open the file\n";// in case, unable to open the file
    //In case the ofstream object do not work. So its the quick fix for it
   // my_file2.flush();
    //Noting the time and date of file opening in the History file
    my_file2.open("History.txt", ios::app);
    my_file2 << "User: " << user_name << " checked History " << date_time.GenerateTime() << "\n";

}


void Input::AskDetails()
{
    std::cout << "Enter your name?\n";
    std::getline(std::cin, user_name);
    std::cout << "Enter the name of the file\n";
    std::cin >> file_name;
    //clearing everyting especially the white space from the cin operator
    std::cin.ignore();
    //adding txt extension to the file name
    
}


void Input::InsertDictionary(TrieTree obj)
{
    std::ifstream dictionary_file("dictionary.txt");
    int index = 0;
    if (dictionary_file.is_open())
    {
        //getting each every character(except the newline ascii) from the file saving it into string variable line
        while (getline(dictionary_file, line))//it will saving each line in the string variable until the last line from the file is not taken/met
        {
            //Inserting the file word string in the tree
            obj.Insert(line);
        }
    }
    else// in case the program is not able to open the file
        std::cout << "Unable to open the file\n";

}


//
//void Input::HuffManCompression() {
//    
//    cout << file_name << endl;
//    huffman.setFileName(file_name);
//    huffman.encoding();
//    huffman.makingcompressedfile();
//    huffman.decoding1();
//}
