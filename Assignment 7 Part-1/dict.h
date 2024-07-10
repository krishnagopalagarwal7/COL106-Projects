// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct MetaData
{
    int book_code;
    int page;
    int paragraph;
    int sentence_no;

    MetaData();

    MetaData(int b, int p, int par, int s);
};

// Node for HashMap
class DictNode
{
public:
    string word;
    long long count;
    vector<MetaData> metaData;
    int noOfDocs;
    int prevDoc;
    long double score;

    DictNode();

    DictNode(string w, long long c, MetaData m);

    DictNode(string w, long double s);

    ~DictNode();
};

class HashMap
{
private:
    int noOfBuckets;
    int noOfElements;
    int multiplier;
    double max_alpha;

public:
    vector<vector<DictNode>> table;

    HashMap();

    HashMap(int size);

    ~HashMap();

    int hash(string word);

    void insert(string word, MetaData m);

    void insertOne(string word, long long count);

    void insertScore(string word, long double score);

    long long get(string word);

    long double getScore(string word);

    int getDocCount(string s);

    bool remove(string word);

    void increaseSize();

    void decreaseSize();
};

struct Para_Info
{
    int book_code;
    int page;
    int paragraph;
    int min_sentence_no;
    int max_sentence_no;
    long double score;

    Para_Info();
    Para_Info(int b, int p, int par, int min_s, int max_s, long double sc);

    bool operator<(const Para_Info &p) const
    {
        return score > p.score;
    }
};

class CSV_Dict
{
private:
    HashMap map;
    vector<string> getNextLineAndSplitIntoTokens(string line);

public:
    CSV_Dict();
    CSV_Dict(string filename);
    ~CSV_Dict();

    long long get(string word);
    void init(string filename);
};

class Dict
{
private:
    // You can add attributes/helper functions here
    HashMap map;

public:
    long long int total_words;
    vector<long long int> noOfWordsInDoc;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    Dict(int size);

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    int get_doc_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};