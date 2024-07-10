#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;
vector<string> separators2 = {" ", ".", ",", "-", ":", "!", "\"", "'", "(", ")", "?", "—", "[", "]", "“", "”", "‘", "’", "˙", ";", "@"};

bool is_separator(char c)
{
    for (string sep : separators2)
    {
        if (sep[0] == c)
            return true;
    }
    return false;
}

PriorityQueue::PriorityQueue()
{
    size = 0;
}

PriorityQueue::~PriorityQueue()
{
}

void PriorityQueue::push(Para_Info para_info)
{
    heap.push_back(para_info);
    size++;
    int i = size - 1;
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap[parent].score > heap[i].score)
        {
            Para_Info temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;
            i = parent;
        }
        else
        {
            break;
        }
    }
}

Para_Info PriorityQueue::pop()
{
    assert(size > 0);
    Para_Info ans = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heap.pop_back();
    int i = 0;
    while (i < size)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < size && heap[left].score < heap[smallest].score)
        {
            smallest = left;
        }
        if (right < size && heap[right].score < heap[smallest].score)
        {
            smallest = right;
        }
        if (smallest != i)
        {
            Para_Info temp = heap[smallest];
            heap[smallest] = heap[i];
            heap[i] = temp;
            i = smallest;
        }
        else
        {
            break;
        }
    }
    return ans;
}

Para_Info PriorityQueue::top()
{
    return heap[0];
}

int PriorityQueue::get_size()
{
    return size;
}

bool PriorityQueue::empty()
{
    return size == 0;
}

string toLower(string s)
{
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    return s;
}

long double split_sentence(string s, HashMap &scores)
{
    int si = 0;
    long double ans = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        char c = s[i];

        if (is_separator(c))
        {
            int len = i - si;
            string word = s.substr(si, len);
            if (word != "")
            {
                word = toLower(word);
                ans += scores.getScore(word);
            }

            si = i + 1;
        }
    }

    int len = s.size() - si;
    string word = s.substr(si, len);

    if (word != "")
    {
        word = toLower(word);
        ans += scores.getScore(word);
    }

    return ans;
}

vector<string> split_sentence(string s)
{
    vector<string> ans;

    int si = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        char c = s[i];

        if (is_separator(c))
        {
            int len = i - si;
            string word = s.substr(si, len);
            if (word != "")
            {
                word = toLower(word);
                ans.push_back(word);
            }

            si = i + 1;
        }
    }

    int len = s.size() - si;
    string word = s.substr(si, len);

    if (word != "")
    {
        word = toLower(word);
        ans.push_back(word);
    }

    return ans;
}

QNA_tool::QNA_tool() : csv_dict("unigram_freq.csv")
{
    // Implement your function here
}

QNA_tool::~QNA_tool()
{
    // Implement your function here
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    dict.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    return;
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    vector<string> words = split_sentence(question);
    vector<long double> scores;
    long double score;
    HashMap score_dict;

    for (string word : words)
    {
        score = (dict.get_word_count(word) + 1) / (long double)(csv_dict.get(word) + 1);
        scores.push_back(score);
        score_dict.insertScore(word, score);
    }

    PriorityQueue pq;

    Node *root = get_top_k_para_util(scores, pq, score_dict, k);
    return root;
}

void QNA_tool::query(string question, string filename)
{
    // Implement your function here

    // Extract the main words from the question and get the score for each word
    string pre_query_1 = "Extract the noun word(s) from the given question (output only the noun words in space separated(not comma) format):\n";
    pre_query_1 += question;
    query_llm(filename, nullptr, 0, "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", pre_query_1);

    vector<string> words;

    // Read the words from reply.txt which contains space separated words
    fstream file("reply.txt");
    string word;

    while (file >> word)
    {
        word = toLower(word);
        if (word[word.size() - 1] == ',')
            word = word.substr(0, word.size() - 1);
        words.push_back(word);
    }

    file.close();

    vector<long double> scores;
    long double score;
    HashMap score_dict;
    int k = 5;

    for (string word : words)
    {
        // score = 1 / (long double)(dict.get_word_count(word) + 1);
        long long book_count = dict.get_word_count(word);
        score = 1 / (long double)(book_count + 1);

        // if (book_count > 100000)
        //     score = 0.01;
        // else if (book_count > 1000 && book_count <= 100000)
        //     score = 0.1;
        // else if (book_count > 98 && book_count <= 1000)
        //     score = 1;
        // else
        //     score = 10;

        scores.push_back(score);
        score_dict.insertScore(word, score);
    }

    PriorityQueue pq;

    Node *root = get_top_k_para_util(scores, pq, score_dict, k);
    query_llm(filename, root, k, "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", question);

    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph)
{
    std::string filename = "corpus/mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ','))
        {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos)
            {
                token = token.substr(start, end - start + 1);
            }

            // Check if the element is a number or a string
            if (token[0] == '\'')
            {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            }
            else
            {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if (
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph))
        {
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

Node *QNA_tool::get_top_k_para_util(vector<long double> &scores, PriorityQueue &pq, HashMap &score_dict, int k)
{
    for (int i = 1; i <= 98; i++)
    {
        string filename = "corpus/mahatma-gandhi-collected-works-volume-" + to_string(i) + ".txt";
        std::ifstream inputFile(filename);

        std::string tuple;
        std::string sentence;

        long long para_no = 0;
        long long min_s_no = 1;
        long long max_s_no = 0;
        int book_code = i;
        int page = 0;

        long double score = 0;

        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open the input file." << std::endl;
            exit(1);
        }

        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
        {
            // Get a line in the sentence
            tuple += ')';

            vector<int> metadata;
            std::istringstream iss(tuple);

            // Temporary variables for parsing
            std::string token;

            // Ignore the first character (the opening parenthesis)
            iss.ignore(1);

            // Parse and convert the elements to integers
            while (std::getline(iss, token, ','))
            {
                // Trim leading and trailing white spaces
                size_t start = token.find_first_not_of(" ");
                size_t end = token.find_last_not_of(" ");
                if (start != std::string::npos && end != std::string::npos)
                {
                    token = token.substr(start, end - start + 1);
                }

                // Check if the element is a number or a string
                if (token[0] == '\'')
                {
                    // Remove the single quotes and convert to integer
                    int num = std::stoi(token.substr(1, token.length() - 2));
                    metadata.push_back(num);
                }
                else
                {
                    // Convert the element to integer
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }

            // Get the sentence
            sentence = toLower(sentence);
            score += split_sentence(sentence, score_dict);

            if (metadata[2] != para_no)
            {
                long double currentScore = split_sentence(sentence, score_dict);
                score -= currentScore;
                if (pq.get_size() < k)
                {
                    pq.push(Para_Info(book_code, page, para_no, min_s_no, max_s_no, score));
                }
                else
                {
                    if (pq.top().score < score)
                    {
                        pq.pop();
                        pq.push(Para_Info(book_code, page, para_no, min_s_no, max_s_no, score));
                    }
                }
                min_s_no = metadata[3];
                score = currentScore;
            }

            para_no = metadata[2];
            max_s_no = metadata[3];
            book_code = metadata[0];
            page = metadata[1];
        }

        if (pq.get_size() < k)
        {
            pq.push(Para_Info(book_code, page, para_no, min_s_no, max_s_no, score));
        }
        else
        {
            if (pq.top().score < score)
            {
                pq.pop();
                pq.push(Para_Info(book_code, page, para_no, min_s_no, max_s_no, score));
            }
        }
    }

    Node *root = nullptr;
    while (!pq.empty())
    {
        Para_Info p = pq.top();
        pq.pop();

        if (root == nullptr)
        {
            root = new Node(p.book_code, p.page, p.paragraph, -1, -1);
        }
        else
        {
            Node *temp = new Node(p.book_code, p.page, p.paragraph, -1, -1);
            temp->right = root;
            root->left = temp;
            root = temp;
        }
    }

    return root;
}

void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY, string question)
{

    // first write the k paragraphs into different files

    Node *traverse = root;
    int num_paragraph = 0;

    while (traverse != nullptr)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    if (num_paragraph != 0)
        outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, answer the following question:\n";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}