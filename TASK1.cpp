#include <bits/stdc++.h>
using namespace std;

class FamilyNode
{
public:
  vector<FamilyNode *> children;
  string name;
  int age;
  float income;
  string occupation;

  // Constructor to initialize the node
  FamilyNode(string name, int age, float income, string occupation)
      : name(name), age(age), income(income), occupation(occupation) {}

  // Function to get total income of a family
  float getTotalIncome()
  {
    float totalIncome = income;
    for (FamilyNode *child : children)
    {
      totalIncome += child->getTotalIncome();
    }
    return totalIncome;
  }

  // Function to get total age of a family
  int getTotalAge()
  {
    int totalAge = age;
    for (FamilyNode *child : children)
    {
      totalAge += child->getTotalAge();
    }
    return totalAge;
  }
};

// Function to build the Family Tree
FamilyNode *buildTree()
{
  string name, occupation;
  int age;
  float income;

  cout << "Enter name: ";
  cin >> name;
  cout << "Enter age: ";
  cin >> age;
  cout << "Enter income: ";
  cin >> income;
  cout << "Enter occupation: ";
  cin >> occupation;

  int numOfChildren;
  cout << "Enter number of children: ";
  cin >> numOfChildren;

  FamilyNode *node = new FamilyNode(name, age, income, occupation);

  for (int i = 0; i < numOfChildren; i++)
  {
    node->children.push_back(buildTree());
  }

  return node;
}

// Function to check if a node with given parameters exists or not
bool checkIfNodeExists(FamilyNode *node, string name, int age, float income, string occupation)
{
  if (node->name == name && node->age == age && node->income == income && node->occupation == occupation)
  {
    return true;
  }

  for (FamilyNode *child : node->children)
  {
    if (checkIfNodeExists(child, name, age, income, occupation))
    {
      return true;
    }
  }

  return false;
}

void removeNode(FamilyNode *node, FamilyNode *parent, string name, int age, float income, string occupation)
{
  if (node->name == name && node->age == age && node->income == income && node->occupation == occupation)
  {
    if (parent != nullptr)
    {
      // Replace the current node with the child having the highest income
      FamilyNode *highestIncomeChild = nullptr;
      float maxIncome = 0;

      for (FamilyNode *child : node->children)
      {
        if (child->income > maxIncome)
        {
          maxIncome = child->income;
          highestIncomeChild = child;
        }
      }

      if (highestIncomeChild != nullptr)
      {
        parent->children.push_back(highestIncomeChild);
        parent->children.erase(remove(parent->children.begin(), parent->children.end(), node), parent->children.end());
        delete node;
        return;  // Return after removing the node
      }
    }
    else
    {
      // If the root node is removed, replace it with the child having the highest income
      FamilyNode *highestIncomeChild = nullptr;
      float maxIncome = 0;

      for (FamilyNode *child : node->children)
      {
        if (child->income > maxIncome)
        {
          maxIncome = child->income;
          highestIncomeChild = child;
        }
      }

      if (highestIncomeChild != nullptr)
      {
        *node = *highestIncomeChild;
        delete highestIncomeChild;
        return;  // Return after removing the node
      }
    }
  }

  // Continue the process for other nodes
  for (FamilyNode *child : node->children)
  {
    removeNode(child, node, name, age, income, occupation);
  }
}


// Function to find the family with the highest income-to-age ratio
FamilyNode *getHighestIncomeAgeRatioFamily(vector<FamilyNode *> &familyTrees)
{
  FamilyNode *maxRatioFamily = nullptr;
  float maxRatio = 0.0;

  for (FamilyNode *family : familyTrees)
  {
    float currFamilyTotalIncome = family->getTotalIncome();
    int currFamilyTotalAge = family->getTotalAge();
    float currFamilyRatio = currFamilyTotalIncome / currFamilyTotalAge;

    if (currFamilyRatio > maxRatio)
    {
      maxRatio = currFamilyRatio;
      maxRatioFamily = family;
    }
  }

  return maxRatioFamily;
}

// Function to print families in decreasing order of total family income
void printFamiliesInDecrOrder(vector<FamilyNode *> &familyTrees)
{
  vector<pair<string, float>> familyIncomePairs;

  for (FamilyNode *family : familyTrees)
  {
    float totalIncome = family->getTotalIncome();
    familyIncomePairs.push_back(make_pair(family->name, totalIncome));
  }

  // Sort the vector of pairs by total income in decreasing order
  sort(familyIncomePairs.begin(), familyIncomePairs.end(), [](const pair<string, float> &a, const pair<string, float> &b)
       {
         return a.second > b.second;
       });

  // Print the families in decreasing order of total income
  for (const auto &pair : familyIncomePairs)
  {
    cout << pair.first << " : " << pair.second << endl;
  }
}

int main()
{
  int numOfFamilies;
  cout << "Enter the number of families: ";
  cin >> numOfFamilies;

  vector<FamilyNode *> familyTrees;

  for (int i = 0; i < numOfFamilies; i++)
  {
    familyTrees.push_back(buildTree());
  }

  while (1)
  {
    int choice;
    cout << "1. Remove node" << endl;
    cout << "2. Find Highest Income-To-Age-Ratio Family" << endl;
    cout << "3. Print Family(Ancestor) Names in Decreasing Income Order" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
  
    switch (choice)
    {
    case 1:
    {
      int num;
      cout << "Enter Family member whose node is to be removed (0-" << numOfFamilies - 1 << "): ";
      cin >> num;
      cout << "Enter name, age, income, and occupation of member to be removed: ";
      string name, occupation;
      int age;
      float income;
      cin >> name >> age >> income >> occupation;

      if (!checkIfNodeExists(familyTrees[num], name, age, income, occupation))
        cout << "No such family member exists" << endl;
      else
        removeNode(familyTrees[num], nullptr, name, age, income, occupation);
      break;
    }
    case 2:
    {
      FamilyNode *node = getHighestIncomeAgeRatioFamily(familyTrees);
      cout << "Name of ancestor of family with highest total income is " << node->name << endl;
      break;
    }
    case 3:
    {
      printFamiliesInDecrOrder(familyTrees);
      break;
    }
    case 4:
    {
      // Free memory before exiting
      for (FamilyNode *family : familyTrees)
      {
        delete family;
      }
      return 0;
    }
    default:
    {
      cout << "Incorrect choice!!!" << endl;
      break;
    }
    }
  }
  return 0;
}
