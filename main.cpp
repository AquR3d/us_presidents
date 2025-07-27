/* Courtesy of Daniel Nguyen!!!!
 * Development time: 05/12/24 - 05/13/24
 * Publish Date: 05/13/24
 * This is my own US Presidents vocab game I made in like
 * one night and one morning.
 * 
 * Have fun with it! plz don't repost this code as yours
 * and give credit to me if you publish it!
 */

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct pres {
    string num;
    string name;
    string years;
};

vector<string> correctResponses {"Correct!", "W bro!", "you're him. or her we dont judge based off sex.", "SHEESH", "NOICE!!",
                                 "you're goated!", "maybe u should become the next president no cap!", "holy shmoly that's right!"
                                 "take a back pat cause u deserve it!", "you're cooking", "ur such a sigma for that", "YESSIR OR MA'AM!",
                                 "YOU GOT GAME!", "GG!", "ur gamin", "i bet u get all the hoes bc of how smart u r!", "That is right!", "you're so BARACK!"};
vector<string> wrongResponses {"Wrong.", "what the sigma?", "Incorrect.", "Dude.", "we're not cooking...", "it's so joever..."
                               "ain't no way u said that.", "erm, what da sigma.", "chat.", "Bro.", "Dudette.", "no.", "No.", "NO!",
                               "how r u gonna be the next US pres w/ this knowledge.", "so we're trolling.", "so we're inting."
                               "yk how ppl say gg like good game at the end of a game? this is bg, for bad game.", "bro is not barack..."};
vector<pres> PRESIDENTS; // vector of order of US presidents
const int PRES_SIZE = 46;

void printPresident(pres current) {
    cout << current.num << ":\t" << current.name << "\r\t\t\t\t\t[" << current.years << "]\n";
}

void printPresidents() {
    cout << "-=List of US Presidents=-\nnth\t\tName\t\t\tYears\n";
    for (int i = 0; i < PRES_SIZE; i++) {
        printPresident(PRESIDENTS[i]);
    }
}

string getOrdinalEnding(int num) {
    // changes ordinal number ending based off the number...
    // please don't try to understand this random code part it's just for fun xd
    // bc/ im nitpicky
    string ordEnd = "th";
    if (num < 4 || num > 20) {
            switch (num % 10) {
                case 1: ordEnd = "st"; break;
                case 2: ordEnd = "nd"; break;
                case 3: ordEnd = "rd"; break;
            }
    }
    return ordEnd;
}

vector<pres> getNextPresidents(int discludeIdx, int choices) {
    pres correct = PRESIDENTS[discludeIdx];
    vector<pres> next;
    vector<pres> scrambled = PRESIDENTS;
    int mcq = rand()%choices; // pick a rnadom mcq choice for the correct answer
    
    // erase disclude idx
    scrambled.erase(scrambled.begin() + discludeIdx);
    
    for (int c = 0; c < choices; c++) {
        if (c != mcq) {
            int rPres = rand()%(scrambled.size());
            next.push_back(scrambled.at(rPres));
            scrambled.erase(scrambled.begin()+rPres);
        }
        else next.push_back(correct);
    }
        
    return next;
}

void printResponse(bool correct) {
    // response based on user response validity
    string response; 
    if (correct) response = correctResponses.at(rand()%correctResponses.size()); // if guessed correct number....
    else response = wrongResponses.at(rand()%wrongResponses.size()); // if guessed the wrong number...
    
    cout << response << " ";
}

void vocabGame(bool isMcq, bool ordered, int mcqChoices = 1) {
    
    // print instructions
    cout << "\n-=Game Instructions=-\n";
    cout << "Type [-1] to EXIT.\n\n-FRQ Instructions-\n";
    cout << "Type the corresponding ordinal number to the given president,\n";
    cout << "or type the corresponding president to the ordinal number.\n\n";
    cout << "-MCQ Instructions-\n";
    cout << "Type the corresponding letter response for your guess IN CAPITAL!\nGL memorizing!\n\n";
    cout << "-=Game begins!=-\n\n";
    
    // initialize variables
    string input, ordEnd = "th", correct;
    int presNum = 0, option = 0, x = 0, n = 0;
    vector<pres> choices;
    
    // game cycle
    while((ordered && presNum < PRES_SIZE) || !ordered) {
        
        // randomized game settings
        if (!ordered) {
            option = rand()%2; // 2 different options... if 0, represents given nth ?, if 1, represents given name ?
            presNum = rand()%PRES_SIZE; // gives a random president number between 0-45 representing the PRESIDENTS indices
        }
        
        // get question president
        pres qPres = PRESIDENTS.at(presNum);
        
        // mcq game settings
        if (isMcq) {
            choices = getNextPresidents(presNum, mcqChoices); // get 4 random other president choices
            for (int p = 0; p < choices.size(); p++) {
                if (choices[p].num == qPres.num) {
                    correct = 'A' + p;
                    break;
                }
            }
            //cout << correct << endl;
        }
        
        // get question president related info
        presNum = stoi(qPres.num); // 1. increment if ordered 2. just assigning for ltr use
        ordEnd = getOrdinalEnding(presNum); 
        
        // given nth ?
        if (option == 0) {
            cout << "Who is the " << qPres.num << ordEnd << " US President? ";
            
            if (isMcq) {
                // print options
                cout << endl;
                for (int p = 0; p < choices.size(); p++)
                    cout << char('A' + p) << ". " << choices[p].name << endl;
                cout << "Letter response: ";
            }
            
            getline(cin, input); // console input
            
            if (isMcq) {
                if (input != "-1") {
                    printResponse(input == correct);
                    if (input == correct) x++; // increment # of successes
                }
            }
        }
        
        // given name ?
        if (option == 1) {
            cout << "What's the ordinal president number of US President " << qPres.name << "? ";
            
            if (isMcq) {
                // print options
                cout << endl;
                for (int p = 0; p < choices.size(); p++)
                    cout << char('A' + p) << ". " << choices[p].num << endl;
                cout << "Letter response: ";
            } else { correct = qPres.num; }
            
            getline(cin, input); // console input
            
            if (input != "-1") {
                printResponse(input == correct);
                if (input == correct) x++; // increment # of successes
            }
        }
        
        // quit
        if (input == "-1") {
            cout << "\nYou scored " << x << "/" << n << " = " << double(x) / double(n) * 100 << "%" << endl;
            cout << "Successfully exited the game!\n\n";
            return;
        }
        
        // print answer
        cout << qPres.name << " is the " << qPres.num << ordEnd << " US President!";
        
        cout << endl << endl;
        
        if (isMcq) n++; // increment # mcq answered
    } // reached end of game cycle
    
    // print results
    cout << "You scored " << x << "/" << n << " = " << double(x) / double(n) * 100 << "%" << endl;
    cout << "-=Game ended.=-\n\n";
    
}

int main() {
    
    srand(time(NULL)); // randomization...
    
    // start of .txt file importing
    ifstream in;
    in.open("presidents.txt");
    string buffer;
    int n = 0;
    
    if(in.fail()) return 1;
    
    while (true) {
        // track pres number with line iterations
        n++;
        // get a line in .txt file
        getline(in, buffer);
        
        if (in.fail()) break; // if error from no more lines...
        // convert line to string stream
        istringstream stream(buffer);
        
        // breakup string stream to put into a term struct... while condition returns true when a line is obtained
        pres next;
        while(getline(stream, buffer, ',')) { // get 1st section of line from .txt file
            next.num = to_string(n); // assign corresponding president num to line number from n
            next.name = buffer; // assign first line section as the name
            getline(stream, buffer, '\n'); // get 2nd section of line from .txt file
            next.years = buffer.substr(1, buffer.length()-1); // assign  2nd line section as years served
        }
        PRESIDENTS.push_back(next); // add edited term struct into vector
    }
    // end of file importing

    // prompt cycle
    while(true) {
        cout << "-=Daniel's US Presidents Vocab Program!=-\n";
        cout << "Type [-1] to QUIT the program.\n";
        cout << "1. Show President list\n";
        cout << "2. Play Randomized Vocab Game (Free-Response)\n";
        cout << "3. Play Ordered Vocab Game (Free-Response)\n";
        cout << "4. Play Randomized Vocab Game (MCQ)\n";
        cout << "5. Play Ordered Vocab Game (MCQ)\n";
        cout << "Type a NUMBER here: ";
        
        getline(cin, buffer); // get console input aka user input
        
        if (buffer == "-1") break; // BREAK out of prompt cycle
        if (buffer == "1") printPresidents();
        if (buffer == "2") vocabGame(false, false);
        if (buffer == "3") vocabGame(false, true);
        if (buffer == "4") vocabGame(true, false, 5);
        if (buffer == "5") vocabGame(true, true, 5);
    }
    
    return 0;
}