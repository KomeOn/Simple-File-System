# Simple-File-System

Designed a simple File System having defined constraints using C++.  
Implemented multiple functions such as create a file, list all files, delete the file, read and write the file.

# Input

* Input is taken through Console.

  * Input includes the following commands: 
  - "Make file": mf filename filecontents
  - "Delete file": df filename
  - "Rename file": rf filename1 filename2
  - "Print file": pf filename 
  - "List file": ls


        Note: 
            *  No space contained words can be used for file name .i.e, 
                  ex: mf file name "Hello worlds"   ====> Not supported
                  ex: mf filename "Hello worlds"    ====> Supported
                  
# Commands

* mf file-name filecontents
	* first check for the uniqueness of the filename
	* create a unique inode for file
	* insert filename and corresponding inode into the meta data.
	* insert the inode and filename into the sets for checking the uniqueness further.
	* calculate the number of disk files required and create disk block files with inodeno_blockno

* df file-name
	* check if the file with given name is present in the file system
	* get the inode of the file to be deleted
	* remove the file entry from the meta data
	* retrieve the number of disk files created for the file to be deleted
	* remove the disk block entry from the file
	* delete all the disk files.
	* remove the file from the list of files
	* remove the inode from the inode list.

* rf file-name1 file-name2
	* check whether the new filename is unique
	* check if the file with given name is present in the file system
	* rename the filename in the metadata
	* remove the file from the list of files
	* insert the new filename into the list of files

* pf file-name 
	* check if the file with given name is present in the file system
	* get the inode of the file to be displayed
	* retrieve the number of disk files created for the file to be displayed
	* display all the disk file contents


* ls
	* list all the files from the meta_data

# Screenshots

### "mf" command
![Screenshot from 2022-09-17 12-14-17](https://user-images.githubusercontent.com/29372200/190845137-15ea792a-e380-4d09-b878-54b4290c1530.png)

### "df" command
![imgonline-com-ua-twotoone-Iv43QjJ68F](https://user-images.githubusercontent.com/29372200/190845446-97c787f0-dc5f-40d9-bcec-756a1cde92f8.png)

### "rf" command
![imgonline-com-ua-twotoone-fvY5eRFXugcg](https://user-images.githubusercontent.com/29372200/190845542-c48c2168-3af7-42b8-b1c5-e98b6bed41ea.png)

### "pf" command
![imgonline-com-ua-twotoone-AEEEVz9EqzLR7ky](https://user-images.githubusercontent.com/29372200/190845587-1b8a87c8-eb5b-426b-bc1e-e91bad100477.png)

### "ls" command
![imgonline-com-ua-twotoone-JL5HXwv2iprb0Ab](https://user-images.githubusercontent.com/29372200/190845644-95815ae7-c3f0-42bd-9101-5a16d2eb9651.png)

### "Files"
![Screenshot from 2022-09-17 12-16-48](https://user-images.githubusercontent.com/29372200/190845695-8c719185-3625-4d95-b581-fc839d5fe20b.png)
