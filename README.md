## ICS-53-Virtual-Memory-Simulator
A simple c program the replicates the Virtual memory System

# Where is Offset Stored
1. Simple Equation
  * Address Number = Page Number * 4 + Offset

# Data Structures
1. <Structure> pageEntry
    Represents a row in the PageTable Object and contains all relevant information
    * <Int> Valid : Represents whether this entry is stored in main memory at the moment
      * <1> Contained in Main Memory <2> Stored in Disk
    * <Int> Dirty : Represents if the page has been changed since it has been loaded into Main Memory.
    *  Mainly used to determine if we need to copy the page into Disk when removing the page.
      * <1> The page is different from Disk.  <2> The page has been unchanged
    * <Int> pageNum : The location of page on Main Memory if Valid = <1> or Disk if Valid = <0>
      * <0-7> valid page numbers for both Main Memory and Disk <8-15> only valid for Disk pages
2. <Structure> address
    Represents a row in both the Main Memory and Disk Object and contains all relevant information.
    * <Int> address : the address of the current row **Possible unneeded**
      *<0-15> Valid Addresses for main Memory <0-31> Valid Addresses
    * <int> data : the data stored at the address.
      * <-1> When the address is empty, it is initialized to -1
3. <Array> PageTable
    * 8 pageEntry Objects
4. <Array> MainMemory
    * 16 address Objects
5. <Array> Disk
    * 32 address Objects

# Expected Functions
1. void read(int virtualAddress)
  * print out contents of Memory Address
   * **CAN CAUSE PAGE FAULT**
2.  void write( int virtualAddress, int num)
  * look into virtual address and insert Num
   * **CAN CAUSE PAGE FAULT**
3.  void showMain(int physicalPageNumber)
  * prints out the 4 address and data associated with the main memory page
4.  void showDisk(int diskPageNumber)
  * prints out the 4 addresses and data associated with the disk page
5.  void showPageTable()
  * print out the 8 pageEntry Objects
6.  void quit()
  * exits the programs
