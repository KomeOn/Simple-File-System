#include<iostream>
#include<fstream>
#include<string>
#include<list>

using namespace std;

// Max number of blocks
#define LIMIT 1000

// File pointer for writing
ofstream ofptr;

// File pointer for reading
ifstream ifptr;

// Indexes of blocks that are occupied
bool disk_space[LIMIT] = { 0 };

// Number of blocks allocated
int parts_allocated = 0;

// Relation handling between file name
// and blocks
list < pair<string, list<int>>> dir;

int finddir(string);
int dfdir(string);
int pfdir(string);
int lsdir(string);
int rfdir(string, string);
// Function for command "mf"
// make file
int mfdir(string fn, string fc) {

    if (finddir(fn) == 1){
        cout<<"File already exists"<<endl;
        return 1;
    }
	// For maintaining the blocks
	list <int> listNodes;
	int i, counter = 0;
	string temp = "";

	// Checking whether the file contents
	// are of length divisible by 4
	int rem = (fc.length() % 4);
	// If not, then padding with
	// dummy character
	if (rem != 0) {
		fc += string(4 - rem, '\0');
	}
	// For maintaing the string slice of
	// length 4
	counter = 0;

	// For loop for slicing the string into
	// parts of 4 and writing it into 
	// block files
	for (i = 0; i < fc.length(); i++) {
		temp += fc[i];
		counter += 1;
		// If counter is of size 4
		// then write it into a block file
		// of number upto which blocks are
		// occupied
		if (counter == 4) {
			// Creating file of name block number
			ofptr.open((to_string(parts_allocated) + ".txt").c_str());
			// Maintaining which block is associated with the
			// given file name
			listNodes.push_back(parts_allocated);
			// The next block to write
			parts_allocated += 1;
			// Resetting the slice size to 0
			counter = 0;
			ofptr << temp;
			// Resetting the slice value to ""
			temp = "";
			ofptr.close();
		}
	}

	// Maintaing the number of blocks relation with the
	// file name
	dir.push_back(make_pair(fn, listNodes));

	cout << "\t\t" << fn << " named file generated\n";
	return 0;
}

// Function for command "df"
// delete file
int dfdir(string fn) {
	auto file_entry = dir.begin();
	while (file_entry != dir.end())
	{
		if (file_entry->first == fn)
		{
			auto blocks = file_entry->second.begin();
			while (blocks != file_entry->second.end())//find file block
			{
				auto block_loc = (to_string(*blocks) + ".txt");
				remove(block_loc.c_str()); //deleting file
				disk_space[*blocks++] = 0;

			}
			dir.remove(*file_entry);//remove file directory
			return 0;
		}
		file_entry++;
	}
	cout << "File not found" << endl;
	return 1;
}

// Function pre existing 
// file
int finddir(string fn) {
	auto file_entry = dir.begin();
	while (file_entry != dir.end())
	{
		if (file_entry->first == fn)
		{
			return 1;
		}
		file_entry++;
	}
	return 0;
}

// Function for command "rf"
// rename file
int rfdir(string fn1, string fn2) {
	auto file_entry = dir.begin();
	if (finddir(fn2) == 1)
	{
		cout << "Can't rename to existing file name" << endl;
		return 0;
	}

	while (file_entry != dir.end())
	{
		if (file_entry->first == fn1)
		{
			file_entry->first = fn2;

			return 1;
		}
		file_entry++;
	}
	cout << "File not found" << endl;
	return 1;
}

// Function for command "pf"
// printing file
int pfdir(string fn) {
	auto file_entry = dir.begin();
	while (file_entry != dir.end())
	{
		if (file_entry->first == fn)
		{
			auto blocks = file_entry->second.begin();
			string fc = "";
			while (blocks != file_entry->second.end())
			{
				auto block_loc = (to_string(*blocks) + ".txt");
				ifptr.open(block_loc);
				string line;
				getline(ifptr, line);
				fc += line;
				ifptr.close();
				blocks++;
			}

			cout << file_entry->first << ": " << fc << endl;
			return 0;
		}
		file_entry++;
	}
	cout << "File not found" << endl;
	return 1;
}

// Function for command "ls"
// List of directories
int lsdir() {
	auto file_entry = dir.begin();
	while (file_entry != dir.end())
	{
		auto blocks = file_entry->second.begin();
		string fb = "";
		while (blocks != file_entry->second.end())
		{
			fb += to_string(*blocks) + ",";
			blocks++;
		}
		fb.pop_back();
		cout << file_entry->first << ": " << fb << endl;

		file_entry++;
	}
	return 0;
}

int main() {

	// User given command
	string command = "";
	// Command type
	string fcmd = "";
	// File name
	string fname = "";
	// Contents of the file
	string fcontents = "";

	string temp = "";
	int i, j = 0;
	char ch = 'Y';
	// While loop for user driven
	// loop
	while (ch == 'Y') {
		temp = "";
		fcmd = "";
		// File name
		fname = "";
		// Contents of the file
		fcontents = "";
		cout << ">>: ";
		getline(cin, command);
		for (i = 3; i < command.length(); i++) {
			if (command[i] == ' ') {
				fname = temp;
				j = i;
				temp = "";
				break;
			}
			temp += command[i];
		}
		if (temp != "")
		{
			fname = temp;
		}

		for (i = j + 1; i < command.length(); i++) {
			if (command[i] == '"')
            {
                continue;
            }
            
            temp += command[i];

		}
		fcontents = temp;

		fcmd = fcmd + command[0] + command[1];

		// If command is mf,
		// then make file
		if (fcmd == "mf") {
			fcmd = "";
			mfdir(fname, fcontents);
		}
		// If command is rf,
		// then rename file
		else if (fcmd == "rf") {
			fcmd = "";
			rfdir(fname, fcontents);
		}
		// If command is df,
		// then delete file
		else if (fcmd == "df") {
			fcmd = "";
			dfdir(fname);
		}
		// If command is pf,
		// then print file
		else if (fcmd == "pf") {
			fcmd = "";
			pfdir(fname);
		}
		// If command is ls,
		// then list all directories
		else if (fcmd == "ls") {
			fcmd = "";
			lsdir();
		}
		// If command is es,
		// then exiting the system
		else if (fcmd == "es") {
			fcmd = "";
			exit(0);
		}
		// If no command is valid
		else {
			fcmd = "";
			cout << "Invalid command: " << fcmd << endl;
			cout << "Existing commands: \n";
			cout << "1. mf: Make file.\nSyntax:> mf <filename> <file contents>\n";
			cout << "2. rf: Rename file.\nSyntax:> rf <old filename> <new filename>\n";
			cout << "3. df: Delete file.\nSyntax:> df <filename>\n";
			cout << "4. pf: Print file.\nSyntax:> pf <filename>\n";
			cout << "5. ls: List all files.\nSyntax:> ls\n";
			cout << "6. es: Escape program.\nSyntax: es\n";
		}
	}

	return 1;
}