// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine() : HashTable(100000)
{
    // Implement your function here
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
}

Node *SearchEngine::push(Node *node, int b_code, int pg, int para, int s_no, int off)
{
    Node *newnode = new Node(b_code, pg, para, s_no, off);

    if (node == nullptr)
    {
        return newnode;
    }

    newnode->left = node;
    newnode->right = node->right;
    if (node->right != NULL)
    {
        node->right->left = newnode;
    }
    node->right = newnode;
    return node;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    for (int i = 0; i < sentence.length(); i++)
    {
        sentence[i] = tolower(sentence[i]);
    }
    // calculating hash for a particular string
    int hash = calc_hashval(sentence, sentence.length());
    // storing in index with hashvalue
    int idx = hash % q;
    // updating parameters accordingly
    Details d{book_code, page, paragraph, sentence_no};
    HashTable[idx].sentenceInfo.push_back(d);
    HashTable[idx].sentences.push_back(sentence); // closed hashing
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    for (int i = 0; i < pattern.length(); i++)
    {
        pattern[i] = tolower(pattern[i]);
    }
    // making a linked list
    Node *output = nullptr;
    // initialy no matches found
    n_matches = 0;
    // calculating hasval of pattern
    int hashval_pattern = calc_hashval(pattern, pattern.length());
    // traversing hashtable
    for (int i = 0; i < q; i++)
    {
        if (HashTable[i].sentences.empty())
        {
            continue; // Skip empty vectors.
        } // sentence found
        for (int j = 0; j < HashTable[i].sentences.size(); j++)
        {
            string sentence = HashTable[i].sentences[j];
            Details d = HashTable[i].sentenceInfo[j];

            int s_length = sentence.length();
            if (s_length >= pattern.length())
            { // for match is sentence and pattern . the size of the sentence must be grater or equal to pateern.length
                // calculate hashval for every substring of same length of pattern
                for (int j = 0; j <= s_length - pattern.length(); j++)
                {
                    int hash = calc_hashval(sentence.substr(j, pattern.length()), pattern.length());
                    if (hash == hashval_pattern)
                    { // comparing hashval of substr and pattern
                        bool match = true;
                        int off = j; // offset of probable matching string(definition of offset given in the assignment)
                        for (int k = 0; k < pattern.length(); k++)
                        { // if hashval matches we are check if characters are equal or not
                            if (sentence[j + k] != pattern[k])
                            {
                                match = false; // updating boolian flag
                                off = -1;
                                break;
                            }
                        }
                        if (match)
                        {
                            // it's a match!
                            n_matches++; // updating matching number
                            // pushing the string into linked list
                            output = push(output, d.book_code, d.page, d.para, d.sentence_no, off);
                        }
                    }
                }
            }
            continue; // if sentence length is less than pattern length
        }
    }
    if (n_matches == 0) // no matches found
    {
        delete output;
        return nullptr;
    }
    return output;
}

// int main()
// {
//     SearchEngine krishna;
//     cout << "Krishna Gopal Agarwal" << endl;
//     return 0;
// }