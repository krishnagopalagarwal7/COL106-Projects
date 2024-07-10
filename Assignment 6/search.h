// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

struct Details {
    int book_code;
    int page;
    int para;
    int sentence_no;

    Details() {
        book_code = -1;
        page = -1;
        para = -1;
        sentence_no = -1;
    }

    Details(int b, int pg, int pa, int s_no){
        book_code = b;
        page = pg;
        para = pa;
        sentence_no = s_no;
    }
};

struct HTsentence
{ // implimenting hashtable to store related data to a sentence
    vector<Details> sentenceInfo;
    vector<string> sentences; // inserting setences(strings) in a vector

    HTsentence() {
    }
};

class SearchEngine
{
private:
    // building hasfunc
    // hashtable attritubutes and hashfunc params
    int q=99997;
    const int base = 137;
    vector<HTsentence> HashTable;
    // vector<vector<pair<Details, string>>> HashTable;


    // hashfunction
    int calc_hashval(const string &str, int len)
    {
        // calculating hashval using rabin-carp algo
        int hash = 0;
        for (int i = 0; i < len; i++)
        {
            hash = (hash * base + str[i]) % q; // rolling hash
        }
        return hash;
    }

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/

    Node* push(Node* node, int b_code, int pg, int para, int s_no, int off);
};