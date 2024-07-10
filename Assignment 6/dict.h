// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    vector <vector<int>> v;
    vector <vector<string>> u;
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);
    // void helper_function();

    /* -----------------------------------------*/
    int hash_value(string s);
    // void helper_function();
};