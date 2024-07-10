/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

// Write your code below this line

void generate_targ_commands_util(ExprTreeNode *root, vector<string> &code, Parser &targ)
{
  if (root == nullptr)
    return;

  generate_targ_commands_util(root->right, code, targ);
  generate_targ_commands_util(root->left, code, targ);

  if (root->type == "VAR")
  {
    int address = targ.symtable->search(root->id);
    code.push_back("PUSH mem[" + to_string(address) + "]");
  }
  else if (root->type == "VAL")
  {
    code.push_back("PUSH " + to_string(root->num));
  }
  else
  {
    code.push_back(root->type);
  }
}

EPPCompiler::EPPCompiler()
{
}

int get_address(vector<int> &v)
{
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i] == 0)
      return i;
  }

  return -1;
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
  output_file = out_file;
  memory_size = mem_limit;

  mem_loc = vector<int>(memory_size, 0);
}

void EPPCompiler::compile(vector<vector<string>> code)
{
  fstream file(output_file, ios::out | ios::trunc);
  file.close();

  for (vector<string> expression : code)
  {
    for (string s : expression)

      targ.parse(expression);
    vector<string> commands = generate_targ_commands();
    write_to_file(commands);
  }
}

vector<string> EPPCompiler::generate_targ_commands()
{
  ExprTreeNode *node = targ.expr_trees.back();
  vector<string> ans;

  if (node->left->type != "DEL")
    generate_targ_commands_util(node->right, ans, targ);

  if (node->left->type == "VAR")
  {
    int address = targ.symtable->search(node->left->id);

    if (address == -1)
    {
      address = get_address(mem_loc);
      mem_loc[address] = 1;
      targ.symtable->assign_address(node->left->id, address);
    }

    ans.push_back("mem[" + to_string(address) + "] = POP");
  }
  else if (node->left->type == "DEL")
  {
    int address = targ.symtable->search(node->right->id);
    mem_loc[address] = 0;
    targ.symtable->remove(node->right->id);
    ans.push_back("DEL = mem[" + to_string(address) + "]");
  }
  else
  {
    ans.push_back("RET = POP");
  }

  return ans;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
  fstream file(output_file, ios::out | ios::app);
  for (string command : commands)
    file << command << endl;
  file.close();
}

EPPCompiler::~EPPCompiler()
{
}