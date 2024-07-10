// Do NOT add any other includes
#include "dict.h"

Dict::Dict() : v(1000000), u(1000000)
{
}

Dict::~Dict()
{
    v.clear();
    u.clear();
}

int Dict::hash_value(string s)
{
    int base = 91;
    int q = 999983;
    int hash = 0;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash * base + (s[i] + 19) * (s[i] + 31)) % q; // rolling hash
    }
    return hash;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    sentence += ".";
    string s = "";
    char p;
    for (int i = 0; i < sentence.size(); i++)
    {
        if (sentence[i] >= 65 && sentence[i] <= 90)
        {
            p = sentence[i] + 32;
            s += p;
        }
        else if (sentence[i] == 46 || sentence[i] == 44 || sentence[i] == 45 || sentence[i] == 58 || sentence[i] == 33 || sentence[i] == 34 || sentence[i] == 39 || sentence[i] == 40 || sentence[i] == 41 || sentence[i] == 63 || sentence[i] == 91 || sentence[i] == 93 || sentence[i] == 59 || sentence[i] == 64 || sentence[i] == 32)
        {
            bool a = false;
            for (int i = 0; i < v[hash_value(s)].size(); i++)
            {
                if (u[hash_value(s)][i] == s)
                {
                    v[hash_value(s)][i]++;;
                    a = true;
                }
            }
            if (a == false)
            {
                u[hash_value(s)].push_back(s);
                v[hash_value(s)].push_back(1);
            }
            s="";
        }
        else
        {
            s += sentence[i];
        }
    }
    s = "";
    return;
}

int Dict::get_word_count(string word)
{
    string s = "";
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
        {
            s += (word[i] + 32);
        }
        else
        {
            s += word[i];
        }
    }
    for (int i = 0; i < v[hash_value(s)].size(); i++)
    {
        if (u[hash_value(s)][i] == s)
        {
            return v[hash_value(s)][i];
        }
    }
    return 0;
}

void Dict::dump_dictionary(string filename)
{
    ofstream file(filename);
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            if (u[i][j] != "")
            {
                file << u[i][j] << ", " << v[i][j] << endl;
            }
        }
    }
    file.close();
    return;
}

// int main()
// {
//     Dict krishna;
//     krishna.insert_sentence(10, 10, 10, 10, "('1', 0, 0, 1, 0) VOL.1: 1884 30 NOVEMBER, 1896 1('1', 0, 1, 2, 32) 1. A CONFESSION 1('1', 0, 2, 3, 50) [1884] I wrote it on a slip of paper and handed it to him myself.");
//     // krishna.helper_function();
//     krishna.dump_dictionary("krishna");
//     return 0;
// }