/*
 This file is used to test the libVC.so output of the linux makefile.
 This file is not designed to be used on Windows.
 Author: Thomas Lemiere
*/

#include <iostream>

#include "RDBHandler.hh"
#include "vclient.h"


int main()
{
	int IDs[] = {1,2,3};
	int wheelIDs[] = {4,5,6};
	
	std::cout << "Test for libVC.so" << std::endl;
	std::cout << "void InitReceiveRDB(int pkID, const int noElements, int IDs[], int WheelIDs[]);;" << std::endl;
	InitReceiveRDB(0, 3, IDs, wheelIDs);
	std::cout << "no error handling ... did it crash?" << std::endl;
	std::cout << "void clear();" << std::endl;
	clear();	
	std::cout << "no error handling ... did it crash?" << std::endl;
	
	return 0;
}
	