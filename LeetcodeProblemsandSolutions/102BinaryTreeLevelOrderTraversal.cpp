#include <iostream>
#include <vector>
#include <queue>
//#include <pair>
using namespace std;

//Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
    private:
            vector<vector<int>> vctResult;  // Final vector of all levels data
            vector<int> vctTemp;            // To store the current level data
          
    public:
			vector<vector<int>> LevelOrderTraversal(TreeNode* root) 
			{
				int iHeight = GetHeightOfTree(root);
				int i = 0;
				
				for(i = 1; i <= iHeight; ++i)
				{
				   GetGivenLevel(root, i);
				   vctResult.push_back(vctTemp);
				   //PrintLevel(vctTemp);
				   vctTemp.clear();
				}
				return vctResult;
			}
				
            void GetGivenLevel(TreeNode* ptr, int iLevel)
			{
				if(ptr == NULL)
				{
				    return;
				}
				if(iLevel == 1)
				{
				   vctTemp.push_back(ptr->val);
				}
				else if(iLevel > 1)
				{
				    GetGivenLevel(ptr->left, iLevel - 1);
				    GetGivenLevel(ptr->right, iLevel - 1); 
				}
			}
					
			int GetHeightOfTree(TreeNode *root)
			{
				int iLeftHeight, iRightHeight;

				/* Base Case */
				if(root == NULL)
				    return 0;

				iLeftHeight = GetHeightOfTree(root->left);
				iRightHeight = GetHeightOfTree(root->right);

				if(iLeftHeight > iRightHeight)
				    return 1 + iLeftHeight;
				else
				    return 1 + iRightHeight;		
			}
			
			/*	For debugging
				void PrintLevel(vector<int> vctInp)
				{
					for(auto inp : vctInp)
					{
						cout<<inp<<" ";
					}
				}
			*/

			//Second Solution
			vector<vector<int>> levelOrder_MJ(TreeNode* root)
			{
				vector<vector<int>> vctRet;
				if (root == NULL)
				{
					return vctRet;
				}

				queue<pair<TreeNode *, int>> q;
				q.push(make_pair(root, 1));

				vector<int> vctCurrLevel;
				int iCurrLevel = 1;
				while (!q.empty())
				{
					pair<TreeNode *, int> node = q.front();
					q.pop();
					if (node.first->left != NULL)
					{
						q.push(make_pair(node.first->left, node.second + 1));
					}

					if (node.first->right != NULL)
					{
						q.push(make_pair(node.first->right, node.second + 1));
					}

					if (iCurrLevel == node.second)
					{
						vctCurrLevel.push_back(node.first->val);
					}
					else
					{
						vctRet.push_back(vctCurrLevel);
						vctCurrLevel.clear();
						vctCurrLevel.push_back(node.first->val);
						iCurrLevel++;
					}
				}

				vctRet.push_back(vctCurrLevel);
				return vctRet;
			}
};

struct TreeNode* newNode(int data)
{
	struct TreeNode* node = new struct TreeNode;
	node->val = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int main()
{
	TreeNode *root = newNode(3);

	root->right = newNode(20);
	root->left = newNode(9);
	root->left->left = root->left->right = NULL;
	root->right->left = newNode(15);
	root->right->right = newNode(7);
	
	Solution objSolution;
	vector<vector<int>> vctRet = objSolution.levelOrder_MJ(root);
	
	// Input: root = [3,9,20,null,null,15,7]
	// Output: [ [3], [9, 20], [15, 7] ]
	cout<<"Output: [ ";
	for(auto vct : vctRet)
	{
		cout<<"[";
		for(auto i : vct)
		{
			cout<<i<<", ";
		}
		cout<<"\b\b], ";
	}
	cout<<"\b\b ]"<<endl;
	
	return 0;
}
