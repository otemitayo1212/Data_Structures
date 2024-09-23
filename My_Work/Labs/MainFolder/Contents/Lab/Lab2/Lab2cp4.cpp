#include <iostream>
#include <fstream>
#include  <vector>
int main(){
    std:: string filename = "input.txt";
    std:: string outputfilename = "output.txt";
    std::ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		std::cerr << "Failed to open the user data file." << std::endl;
		exit(1);
	}

    std::ofstream outputFile(outputfilename);

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the output file." << std::endl;
        exit(1);
    }
    std::string name, gender, number, profession, school;
	int age , phone_num;
	double latitude, longitude;
    std::string line;
    while(inputFile >> name
		>> age
		>> gender
		>> number
		>> profession
		>> school
		>> latitude
		>> longitude
    ){
        outputFile << name + ','+ number<< std::endl;


    }
    

}
