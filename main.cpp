#include <iostream> 
#include <stdlib.h>  
#include <string> 
#include <cstring>

int main(int argc, char** argv){ 

    // checks for invalid input
    if(argc != 2){ 
        std::cout << "Invalid input:" << std::endl; 
        return 1;
    }

    // creates shell command 
    std::string command = "find ~/ -type d -name ";   
    command.append(argv[1]);   

    // converts shell command into a c string 
    char* command_c = new char[command.length()+1]; 
    std::strcpy(command_c, command.c_str()); 

    // pipes the output of the command onto a string
    std::string output; 
    FILE* pipe = popen(command_c,"r");   
    char buffer[1024]; 
    while(fgets(buffer, sizeof(buffer), pipe) != NULL){ 
        output += buffer;
    } 

    // deletes unused allocated variables
    pclose(pipe);
    delete command_c;

    // Either open a vscode session in the directory and print the output, or print an error message if the directory doesn't exist 
    if(output.length() == 0){ 
        std::cout << "Path not found" << std::endl; 
        return 1;
    } 
    else{ 
        std::cout << output << std::endl; 

        std::string run_command = "code ";  
        std::string prep_command = "cd ";   

        run_command += output;  
        prep_command += output; 

        char* run_command_c = new char[run_command.length()+1];   
        std::strcpy(run_command_c,run_command.c_str());  

        system(run_command_c); 
        delete run_command_c;
    } 

    // terminate program 
    return 0;
}