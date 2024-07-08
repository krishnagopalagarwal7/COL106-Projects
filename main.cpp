#include <iostream>
#include <vector>
using namespace std;
class SET
{
private:
    vector<vector<int>> v;
    vector<int> one;

public:
    void inserting(int x, int y)
    {
        if (x + 1 <= v.size())
        {
            if (v[x].size() == 0)
            {
                v[x].push_back(y);
                cout << 1 << endl;
            }
            else
            {
                for (int i = 0; i < v[x].size(); i++)
                {
                    if (v[x][v[x].size() - 1] < y)
                    {
                        v[x].push_back(y);
                        cout << v[x].size() << endl;
                        break;
                    }
                    if (v[x][i] == y)
                    {
                        cout << v[x].size() << endl;
                        break;
                    }
                    else if (v[x][i] > y)
                    {
                        v[x].insert(v[x].begin() + i, y);
                        cout << v[x].size() << endl;
                        break;
                    }
                }
            }
        }
        else
        {
            v.push_back(vector<int>{});
            v[x].push_back(y);
            cout << 1 << endl;
        }
    }
    void belongs_to(int x, int y)
    {
        int c = 1;
        if (x + 1 > v.size())
        {
            cout << -1 << endl;
        }
        else
        {
            for (int i = 0; i < v[x].size(); i++)
            {
                if (v[x][i] == y)
                {
                    cout << 1 << endl;
                    c = 0;
                    break;
                }
            }
            if (c == 1)
            {
                cout << 0 << endl;
            }
        }
    }
    bool search(int x, int y)
    {
        for (int i = 0; i < v[x].size(); i++)
        {
            if (v[x][i] == y)
            {
                return true;
                break;
            }
        }
        return false;
    }
    void deleting(int x, int y)
    {
        if (x + 1 > v.size())
        {
            cout << -1 << endl;
        }
        else
        {
            for (int i = 0; i < v[x].size(); i++)
            {
                if (v[x][i] == y)
                {
                    v[x].erase(v[x].begin() + i);
                    break;
                }
            }
            cout << v[x].size() << endl; // I have to check that whether this line should be here or not.
        }
    }
    void print(int x)
    {
        if (x + 1 > v.size())
        {
            cout << endl;
        }
        else
        {
            for (int i = 0; i < v[x].size(); i++)
            {
                cout << v[x][i];
                if (i != v[x].size() - 1)
                {
                    cout << ",";
                }
            }
            cout << endl;
        }
    }
    void size(int x)
    {
        if (x + 1 > v.size())
        {
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else
        {
            cout << v[x].size() << endl;
        }
    }
    void unions(int x, int y)
    {
        if (x + 1 > v.size() && y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else if (x + 1 > v.size())
        {
            v.push_back(vector<int>{});
            for (int i = 0; i < v[y].size(); i++)
            {
                v[x].push_back(v[y][i]);
            }
            cout << v[x].size() << endl;
        }
        else if (y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            cout << v[x].size() << endl;
        }
        else
        {
            int i = 0, j = 0;
            while (i < v[x].size() && j < v[y].size())
            {
                if (v[x][i] == v[y][j])
                {
                    one.push_back(v[x][i]);
                    i++;
                    j++;
                }
                else if (v[x][i] < v[y][j])
                {
                    one.push_back(v[x][i]);
                    i++;
                }
                else
                {
                    one.push_back(v[y][j]);
                    j++;
                }
            }
            for (int p=i; p<v[x].size(); p++)
            {
                one.push_back(v[x][p]);
            }
            for (int q=j; q<v[y].size(); q++)
            {
                one.push_back(v[y][q]);
            }
            v[x].clear();
            for (int i = 0; i < one.size(); i++)
            {
                v[x].push_back(one[i]);
            }
            one.clear();
            cout << v[x].size() << endl;
        }
    }
    void intersection(int x, int y)
    {
        if (x + 1 > v.size() && y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else if (y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            v[x].clear();
            cout << 0 << endl;
        }
        else if (x + 1 > v.size())
        {
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else
        {
            int i = 0, j = 0;
            while (i < v[x].size() && j < v[y].size())
            {
                
                if (v[x][i] < v[y][j])
                {
                    i++;
                }
                else if (v[x][i] == v[y][j])
                {
                    one.push_back(v[x][i]);
                    i++;
                    j++;
                }
                else
                {
                    j++;
                }
            }
            v[x].clear();
            for (int i = 0; i < one.size(); i++)
            {
                v[x].push_back(one[i]);
            }
            one.clear();
            cout << v[x].size() << endl;
        }
    }
    void difference(int x, int y)
    {
        if (x + 1 > v.size() && y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else if (x + 1 > v.size())
        {
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else if (y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            cout << v[x].size() << endl;
        }
        else
        {
            int i = 0, j = 0;

            while (i < v[x].size() && j < v[y].size())
            {
                if (v[x][i] == v[y][j])
                {
                    i++;
                    j++;
                }
                else if (v[x][i] < v[y][j])
                {
                    one.push_back(v[x][i]);
                    i++;
                }
                else
                {
                    j++;
                }
            }
            for (int p=i; p<v[x].size(); p++)
            {
                one.push_back(v[x][p]);
            }
            v[x].clear();
            for (int i = 0; i < one.size(); i++)
            {
                v[x].push_back(one[i]);
            }
            one.clear();
            cout << v[x].size() << endl;
        }
    }
    void symmetric_difference(int x, int y)
    {
        if (x + 1 > v.size() && y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            v.push_back(vector<int>{});
            cout << 0 << endl;
        }
        else if (x + 1 > v.size())
        {
            v.push_back(vector<int>{});
            for (int i = 0; i < v[y].size(); i++)
            {
                v[x].push_back(v[y][i]);
            }
            cout << v[y].size() << endl;
        }
        else if (y + 1 > v.size())
        {
            v.push_back(vector<int>{});
            cout << v[x].size() << endl;
        }
        else
        {
            int i = 0, j = 0;
            while (i < v[x].size() && j < v[y].size())
            {
                if (v[x][i] == v[y][j])
                {
                    i++;
                    j++;
                }
                else if (v[x][i] < v[y][j])
                {
                    one.push_back(v[x][i]);
                    i++;
                }
                else
                {
                    one.push_back(v[y][j]);
                    j++;
                }
            }
            for (int p=i; p<v[x].size(); p++)
            {
                one.push_back(v[x][p]);
            }
            for (int q=j; q<v[y].size(); q++)
            {
                one.push_back(v[y][q]);
            }
            v[x].clear();
            for (int i = 0; i < one.size(); i++)
            {
                v[x].push_back(one[i]);
            }
            one.clear();
            cout << v[x].size() << endl;
        }
    }
};
int main()
{
    SET krishna;
    int a, b, c;
    while (cin >> a)
    {
        switch (a)
        {
        case 1:
            cin >> b >> c;
            krishna.inserting(b, c);
            break;
        case 2:
            cin >> b >> c;
            krishna.deleting(b, c);
            break;
        case 3:
            cin >> b >> c;
            krishna.belongs_to(b, c);
            break;
        case 4:
            cin >> b >> c;
            krishna.unions(b, c);
            break;
        case 5:
            cin >> b >> c;
            krishna.intersection(b, c);
            break;
        case 6:
            cin >> b;
            krishna.size(b);
            break;
        case 7:
            cin >> b >> c;
            krishna.difference(b, c);
            break;
        case 8:
            cin >> b >> c;
            krishna.symmetric_difference(b, c);
            break;
        case 9:
            cin >> b;
            krishna.print(b);
            break;
        }
    }
    return 0;
}