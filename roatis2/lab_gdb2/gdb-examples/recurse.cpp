#include <iostream>
#include <cstdlib>



/*
*	This function should print a right triangle of stars
*
*/

void recurse(int index, int length) {
//
    if(index == 0)
        return;
    for(int i=0; i<index; i++)
	{
	for(int q=0; q<=i; q++)
	    {
	    std::cout<<'*';
	    }
        std::cout<<std::endl;
        }
}



int main (int argc, char * argv[]) {
//Please enter the size of the triangle you want to see!
if (argc<2)
{
	std::cout<<"./recurse number"<<std::endl;
	return 0;
}

int input = std::atoi(argv[1]);

recurse(input,1);


}
