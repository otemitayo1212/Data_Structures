#include <iostream>
#include <vector>
#include <string>
#include <fstream>


void addTrack(std::ifstream& file, std::string& title, std::string library_name, std::string& outputName){  
    std::vector<std::string> playlist;
     // Try to convert playlist to a vector
     std::string line1;
    while(std::getline(file,line1)){
        playlist.push_back(line1);
    }

    // Find the text in library 
    std:: string library_info = library_name; // opening the library
    std::ifstream inputFile(library_info);
    if (!inputFile.is_open()) {
    std::cerr << "Error opening file: " << library_info << std::endl;
    return; // or handle the error appropriately
    }
    std::string line;
     while(std::getline(inputFile,line)){
       int start = line.find("\"");
       int end =  line.find_last_not_of(" "); 
       std::string result = line.substr(start, end+1); 
       
       int end2 = result.find("\"", start+1); 
       std::string check_title = result.substr(start+1 , end2-1 );
       check_title = " "+check_title;
       if (check_title == title){
        // add the string to the vector and get out 
        playlist.push_back(result);
       }
     }
      // open an output file to write the result in
     std::string outputFileName = outputName;

	 // but we can't just use that string to open a file, we have to create an std::ofstream object.
     std::ofstream outputFile(outputFileName); 
     if (outputFile.is_open()){
        for (std:: string txt: playlist){
            outputFile << txt << "\n";
        }
        outputFile.close();
     }



}

// Function to remove a music track from a playlist
void removeTrack(std::ifstream& file, const std::string& title, std::string& outputName) {
    std::vector<std::string> playlist;
     // Try to convert playlist to a vector
     std::string line1;
    while(std::getline(file,line1)){
        playlist.push_back(line1);
    }
    for (int i = 0 ; i < playlist.size(); i++){
        int start =  playlist[i].find("\"") + 1;
        int end =  playlist[i].find("\"", start);
        std::string target =  playlist[i].substr(start,end-1);
        target = " "+target;
        if (target == title){
            playlist.erase(playlist.begin()+i); // playlist.begin() goes to the first element in a vector + i moves the pointer by that amount of time 
        }

    }  
    // close the playlist file and open an output file to write the result in
     std::string outputFileName = outputName;

	 // but we can't just use that string to open a file, we have to create an std::ofstream object.
     std::ofstream outputFile(outputFileName); 
     if (outputFile.is_open()){
        for (std:: string txt: playlist){
            outputFile << txt << "\n";
        }
        outputFile.close();
     }


}
// Function to move a music track to a new position in the playlist
void moveTrack(std::ifstream& file, const std::string& title, int newPosition , std::string& outputName ) {
     std::vector<std::string> playlist;
     // Try to convert playlist to a vector
     std::string line1;
    while(std::getline(file,line1)){
        playlist.push_back(line1);
    }  
    for (int i = 0 ; i < playlist.size(); i++){
        int start =  playlist[i].find("\"") + 1;
        int end =  playlist[i].find("\"", start);
        std::string target =  playlist[i].substr(start,end-1);
        target = " "+target;
        int pos = newPosition - 1 ;
        if (target == title){
            std::string in = playlist[i];
             playlist.erase(playlist.begin()+i); // playlist.begin() goes to the first element in a vector + i moves the pointer by that amount of time
             playlist.insert(playlist.begin() + pos , in ); // not working for some reason
             }
             
    }


    
    // close the playlist file and open an output file to write the result in
     std::string outputFileName = outputName;

	 // but we can't just use that string to open a file, we have to create an std::ofstream object.
     std::ofstream outputFile(outputFileName); 
     if (outputFile.is_open()){
        for (std:: string txt: playlist){
            outputFile << txt << "\n";
        }
        outputFile.close();



     }
}


int main(int argc, char* argv[]){
    std:: string infile = std:: string (argv[1]); // opening the playlist
    std::ifstream inputFile(infile); // opening the playlist 
        if (argc < 6) {
            std::cerr << "Usage ./nyplaylists.exe playlist.txt library.txt output.txt action title"<< std::endl;
            return 1 ; // or handle the error appropriately
             }


        if (std::string(argv[4]) == "add") {
        // Code for 'add'
        std::string outputFileName = std::string(argv[3]);
        std::string Title = "";
        for(int i = 5; i < argc; i++){
            // append to the text make sure to convert to string;

            Title += " " + std::string(argv[i]);
        }
        size_t quotePos;
        if ((quotePos = Title.find('"')) != std::string::npos) {
            Title.erase(quotePos, 1); // Remove the double quote character at the found position
        }

        // Remove closing quote
        if ((quotePos = Title.rfind('"')) != std::string::npos) {
            Title.erase(quotePos, 1); // Remove the double quote character at the found position
        }
        addTrack(inputFile, Title, std::string(argv[2]), outputFileName);
    } 
    else if (std::string(argv[4]) == "remove") {
        // Code for 'remove'
        std::string Title = "";
        std::string outputFileName = std::string(argv[3]);
        for(int i = 5; i < argc; i++){
            // append to the text make sure to convert to string;
            Title += " "+ std::string(argv[i]);
        }
        size_t quotePos;
        if ((quotePos = Title.find('"')) != std::string::npos) {
            Title.erase(quotePos, 1); // Remove the double quote character at the found position
        }

        // Remove closing quote
        if ((quotePos = Title.rfind('"')) != std::string::npos) {
            Title.erase(quotePos, 1); // Remove the double quote character at the found position
        }
        removeTrack(inputFile, Title, outputFileName);
    } 
    else if (std::string(argv[4]) == "move") {
        // Code for 'move'
        std::string Title = "";
        std::string outputFileName = std::string(argv[3]);
        for(int i = 5; i < argc - 1; i++){
            // append to the text make sure to convert to string;
            Title += " "+ std::string(argv[i]);
        }
        size_t quotePos;
        if ((quotePos = Title.find('"')) != std::string::npos) {
            Title.erase(quotePos, 1); // Remove the double quote character at the found position
        }

        // Remove closing quote
        if ((quotePos = Title.rfind('"')) != std::string::npos) {
            Title.erase(quotePos, 1); // Remove the double quote character at the found position
        }
        // find a way to get the position 
        int position = std::stoi(argv[argc-1]); // test if this is correct
        moveTrack(inputFile, Title , position ,outputFileName);

    } 
    

}
    
   


// 