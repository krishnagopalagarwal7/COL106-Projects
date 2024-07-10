// Do NOT add any other includes
#include "dict.h"

// separators -> . , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @
vector<string> separators = {" ", ".", ",", "-", ":", "!", "\"", "'", "(", ")", "?", "—", "[", "]", "“", "”", "‘", "’", "˙", ";", "@"};

bool isSeparator(char c)
{
    for (string sep : separators)
    {
        if (sep[0] == c)
            return true;
    }
    return false;
}

// MetaData
MetaData::MetaData()
{
    book_code = 0;
    page = 0;
    paragraph = 0;
    sentence_no = 0;
}

MetaData::MetaData(int b, int p, int par, int s)
{
    book_code = b;
    page = p;
    paragraph = par;
    sentence_no = s;
}

// DictNode
DictNode::DictNode()
{
    word = "";
    count = 0;
}

DictNode::DictNode(string w, long long c, MetaData m)
{
    word = w;
    count = c;
    metaData.push_back(m);
    noOfDocs = 1;
    prevDoc = m.book_code;
}

DictNode::DictNode(string w, long double s)
{
    word = w;
    score = s;
}

DictNode::~DictNode()
{
}

// HashMap
HashMap::HashMap()
{
    noOfBuckets = 10;
    noOfElements = 0;
    max_alpha = 0.7;
    multiplier = 4;
    table.resize(noOfBuckets);
}

HashMap::HashMap(int size)
{
    noOfBuckets = size;
    noOfElements = 0;
    max_alpha = 0.7;
    multiplier = 4;
    table.resize(noOfBuckets);
}

HashMap::~HashMap()
{
    for (int i = 0; i < noOfBuckets; i++)
    {
        table[i].clear();
    }
    table.clear();
}

int HashMap::hash(std::string id)
{
    long long p = 137;
    long long mod = 1e9 + 7;
    long long pow = 1;

    long long hash = 0;

    for (int i = 0; i < (int)id.length(); i++)
    {
        hash = (hash + (int(id[i]) * pow) % mod) % mod;
        pow = (pow * p) % mod;
    }

    return hash % noOfBuckets;
}

void HashMap::insert(string word, MetaData m)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            table[index][i].count++;
            table[index][i].metaData.push_back(m);
            if (table[index][i].prevDoc != m.book_code)
            {
                table[index][i].noOfDocs++;
                table[index][i].prevDoc = m.book_code;
            }
            return;
        }
    }
    table[index].push_back(DictNode(word, 1, m));
    noOfElements++;
    double alpha = (double)noOfElements / noOfBuckets;
    if (alpha > max_alpha)
        increaseSize();
}

void HashMap::insertOne(string word, long long count)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            table[index][i].count += count;
            return;
        }
    }
    table[index].push_back(DictNode(word, count, MetaData()));
    noOfElements++;
    double alpha = (double)noOfElements / noOfBuckets;
    if (alpha > max_alpha)
        increaseSize();
}

bool HashMap::remove(string word)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            table[index].erase(table[index].begin() + i);
            noOfElements--;
            double alpha = (double)noOfElements / noOfBuckets;
            if (alpha < 1 - max_alpha)
                decreaseSize();
            return true;
        }
    }
    return false;
}

long long HashMap::get(string word)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            return table[index][i].count;
        }
    }
    return 0;
}

void HashMap::insertScore(string word, long double score)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            table[index][i].score += score;
            return;
        }
    }
    table[index].push_back(DictNode(word, score));
    noOfElements++;
    double alpha = (double)noOfElements / noOfBuckets;
    if (alpha > max_alpha)
        increaseSize();
}

long double HashMap::getScore(string word)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            return table[index][i].score;
        }
    }
    return 0;
}

void HashMap::increaseSize()
{
    noOfBuckets *= multiplier;
    vector<vector<DictNode>> newTable;
    newTable.resize(noOfBuckets);
    for (int i = 0; i < (int)table.size(); i++)
    {
        for (int j = 0; j < (int)table[i].size(); j++)
        {
            int index = hash(table[i][j].word);
            newTable[index].push_back(table[i][j]);
        }
    }
    table.clear();
    table = newTable;
}

void HashMap::decreaseSize()
{
    noOfBuckets /= (multiplier / 2);
    vector<vector<DictNode>> newTable;
    newTable.resize(noOfBuckets);
    for (int i = 0; i < (int)table.size(); i++)
    {
        for (int j = 0; j < (int)table[i].size(); j++)
        {
            int index = hash(table[i][j].word);
            newTable[index].push_back(table[i][j]);
        }
    }
    table.clear();
    table = newTable;
}

int HashMap::getDocCount(string word)
{
    int index = hash(word);
    for (int i = 0; i < (int)table[index].size(); i++)
    {
        if (table[index][i].word == word)
        {
            return table[index][i].noOfDocs;
        }
    }
    return 0;
}

// Helper Functions
string toLowerCase(string word)
{
    string ans = "";

    for (char c : word)
    {
        if (c >= 'A' && c <= 'Z')
        {
            ans += c - 'A' + 'a';
        }
        else
        {
            ans += c;
        }
    }

    return ans;
}

vector<string> splitSentence(string sentence)
{
    int si = 0;
    vector<string> ans;

    for (int i = 0; i < (int)sentence.size(); i++)
    {
        char c = sentence[i];

        if (isSeparator(c))
        {
            int len = i - si;
            string word = sentence.substr(si, len);
            if (word != "")
            {
                word = toLowerCase(word);
                ans.push_back(word);
            }

            si = i + 1;
        }
    }

    int len = sentence.size() - si;
    string word = sentence.substr(si, len);

    if (word != "")
    {
        word = toLowerCase(word);
        ans.push_back(word);
    }

    return ans;
}

bool isNumber(string s)
{
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}

// Para_Info
Para_Info::Para_Info()
{
}

Para_Info::Para_Info(int b_code, int pg, int para, int min_s_no, int max_s_no, long double sc)
{
    book_code = b_code;
    page = pg;
    paragraph = para;
    min_sentence_no = min_s_no;
    max_sentence_no = max_s_no;
    score = sc;
}

// CSV_Dict
CSV_Dict::CSV_Dict()
{
}

CSV_Dict::CSV_Dict(string filename)
{
    init(filename);
}

CSV_Dict::~CSV_Dict()
{
}

long long CSV_Dict::get(string word)
{
    return map.get(word);
}

vector<string> CSV_Dict::getNextLineAndSplitIntoTokens(string line)
{
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = line.find(',')) != string::npos)
    {
        token = line.substr(0, pos);
        result.push_back(token);
        line.erase(0, pos + 1);
    }
    result.push_back(line); // Add the last token after the last comma
    return result;
}

void CSV_Dict::init(string filename)
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        vector<string> tokens = getNextLineAndSplitIntoTokens(line);
        if (tokens.size() == 2)
        {
            string word = tokens[0];
            if (isNumber(tokens[1]))
            {
                long long count = stoll(tokens[1]);
                map.insertOne(word, count);
            }
        }
    }

    file.close();
}

// Dictionary
Dict::Dict()
{
    total_words = 0;
    noOfWordsInDoc.resize(98);
}

Dict::Dict(int size)
{
    total_words = 0;
    noOfWordsInDoc.resize(98);
    map = HashMap(size);
}

Dict::~Dict()
{
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    MetaData m(book_code, page, paragraph, sentence_no);
    vector<string> words = splitSentence(sentence);

    for (string word : words)
    {
        total_words++;
        noOfWordsInDoc[book_code - 1]++;
        map.insert(word, m);
    }

    return;
}

int Dict::get_word_count(string word)
{
    return map.get(word);
}

int Dict::get_doc_count(string s)
{
    return map.getDocCount(s);
}

void Dict::dump_dictionary(string filename)
{
    ofstream file(filename, ios::out | ios::trunc);

    for (int i = 0; i < (int)map.table.size(); i++)
    {
        for (int j = 0; j < (int)map.table[i].size(); j++)
        {
            file << map.table[i][j].word << ", " << map.table[i][j].count << endl;
        }
    }

    file.close();
    return;
}