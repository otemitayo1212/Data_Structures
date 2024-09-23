#include <iostream>	// include iostream so we can do std::cin, std::cout, and std::cerr
#include <fstream>	// include fstream so we can do file input and output.

int main(int argc, char* argv[]){
	if(argc!=3){
		std::cout << "Usage: ./a.out input.txt output.txt" << std::endl;
		exit(1);
	}

	// store the first argument in inputFileName, as a C++ string
	std::string inputFileName = std::string(argv[1]);

	// but we can't just use that string to open a file, we have to create an std::ifstream object.
    std::ifstream inputFile(inputFileName);

	// this is how we actually open the input file.
        if (!inputFile.is_open()) {
		// if the file can't be opened, we print an error message.
                std::cerr << "Failed to open the input file." << std::endl;
                exit(1);
        }

	// store the second argument in outputFileName, as a C++ string
	std::string outputFileName = std::string(argv[2]);

	// but we can't just use that string to open a file, we have to create an std::ofstream object.
    std::ofstream outputFile(outputFileName);

	// this is how we actually open the output file.
        if (!outputFile.is_open()) {
		// if the file can't be opened, we print an error message.
                std::cerr << "Failed to open the output file." << std::endl;
                exit(1);
        }

	std::string line;

	// read the input file one line each time, and store the content of that one line into this string variable line.
	// The getline function returns the input stream (inputFile in this case), 
	// and the loop condition while(getline(inputFile, line)) checks whether the stream is in a good state.
	// If getline successfully reads a line from inputFile, 
	// it returns the stream (inputFile) which evaluates to true in a boolean context.
	// If getline encounters the end-of-file (EOF) while reading, it sets the end-of-file flag on the stream, 
	// and the next attempt to read from the stream will fail. 
	// in this case, getline returns the stream in a boolean context, which evaluates to false.

    while (getline(inputFile, line)) {
        // Find the position of "username" in the current line
        size_t start = line.find("\"username\": ");
        
        if (start != std::string::npos) {
            // Move the start position to the beginning of the actual username
            start = line.find("\"", start + 12) + 1;

            // Find the end position of the username
            size_t end = line.find("\"", start);

            // Extract the username from the line
            std::string username = line.substr(start, end - start);

            // Print the extracted username to the console
            std::cout << username << std::endl;

            // Write the username to the output file
            outputFile << username << std::endl;
        }
    }

    std::cout << "Usernames written to output.txt successfully." << std::endl;

    return 0;
}
