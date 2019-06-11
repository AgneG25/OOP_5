#include "functions.h"

void removeCharsFromString( string &str) {

    char chars[] = "()-,./?~`!@#$^&*()_+][}{|:;–' ' ";
    for (int i = 0; i < strlen(chars); ++i ) {
        str.erase( remove(str.begin(), str.end(), chars[i]), str.end() );
    }
}
void checkLetter (string &word) {
    if(isupper(word[0]))
        word[0] = tolower(word[0]);
}

void printFrequency() {
    map<string, int> findWords;
    multimap<string, int> lines;
    string str;
    std::ifstream ifs(text);
    if (ifs.fail()) throw "Source file not found!";
    string Word;
    std::set<std::string> url;
    int line = 0;
    std::ofstream rf("rez.txt");

    while(getline(ifs, str)){
        line++;
        std::stringstream ss(str);
        while (ss >> Word){
            if (std::regex_match (Word, std::regex("^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$") ))
                url.insert(Word);
            else {
                removeCharsFromString(Word);
                checkLetter(Word);
                findWords[Word]++;
                lines.insert(std::pair<string, int>(Word, line));
            }
        }
    }

    map<string, int>::iterator it;
    multimap<string, int>::iterator it1;
    
    int max = 0;
    for(it = findWords.begin(); it != findWords.end(); it++) {
        int m = 0;
        if (it->second > 1) {
            for (it1 = lines.begin(); it1 != lines.end(); it1++){
                if (it->first == it1->first){
                    m = m + 1;
                    if(m > max) m = max;
                }
            }
        }
    }

    for (int i = 2; i < 100; i++){
        for(it = findWords.begin(); it != findWords.end(); it++) {
         if (it->second == i) {
            rf << std::setw(13) << it->first << " tekste pasikartoja " << std::setw(10) << it->second  << " kartus ";
                for (it1 = lines.begin(); it1 != lines.end(); it1++)
                if (it->first == it1->first) {
                    rf << it1->second << " ";
            }
            rf << " eilutese." << std::endl;
        }
    }
    }
    

    rf << "ULR adresai, rasti tekste: " << std::endl;
    for(std::set<std::string>::iterator it = url.begin(); it != url.end(); ++it)
        rf << *(it) << std::endl;


}
