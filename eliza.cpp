
#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

vector<string> match(string input, regex pattern) {
    vector<string> matches;
    smatch match;
    while (regex_search(input, match, pattern)) {
        matches.push_back(match[0]);
        input = match.suffix().str();
    }
    return matches;
}

string eliza(string input) {
    regex pattern_name("\\bmy name is (\\w+)\\b");
    regex pattern_hello("(hi|hello|hey)\\b");
    regex pattern_question("\\?");
    regex pattern_response("(yes|no)\\b");
    regex pattern_weather("(what's|what is) the weather( like)?\\b");

    vector<string> name_matches = match(input, pattern_name);
    if (!name_matches.empty()) {
        return "Hello, " + name_matches[0].substr(11) + ". How are you feeling today?";
    }
    if (regex_search(input, pattern_hello)) {
        return "Hi there! How can I help you today?";
    }
    if (regex_search(input, pattern_question)) {
        return "Interesting question.";
    }
    vector<string> response_matches = match(input, pattern_response);
    if (!response_matches.empty()) {
        return "Why do you say '" + response_matches[0] + "'?";
    }
    if (regex_search(input, pattern_weather)) {
        return "I don't know lol.";
    }

    return "I didn't get that. Can you rephrase that please?";
}

int main() {
    string input;
    cout << "Hi, I'm Eliza. What's your name?" << endl;
    getline(cin, input);
    cout << eliza(input) << endl;

    while (true) {
        getline(cin, input);
        if (input == "exit") {
            cout << "Goodbye!" << endl;
            break;
        }
        cout << eliza(input) << endl;
    }

    return 0;
}
