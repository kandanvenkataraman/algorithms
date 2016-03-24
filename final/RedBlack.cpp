// topcoder SRM 155 Div 1 level 3
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

enum eColor {black, red};

struct Node {
	int val;
	eColor color;
	Node *parent;
	Node *left;
	Node *right;
	
	Node(int v, eColor c, Node *p) : val(v), color(c), parent(p), left(NULL), right(NULL) {}
};

class RedBlack {

Node *insert(Node **root, int val, Node *parent)
{
	if (*root == NULL) {
		*root = new Node(val, red, parent);
		return *root;
	}
	
	Node *head = *root;
	
	if (head->val > val) 
		return insert(&head->left, val, head);
		
	return insert(&head->right, val, head);
}

public:
	int numTwists(vector <int> keys) {
	
		Node *root = NULL;
		int numTwists = 0;
		
		for (int i = 0; i < keys.size(); i++) {
			Node *n = insert(&root, keys[i], NULL);
			while (n->parent != NULL && n->parent->parent != NULL) {
				if (n->color == black || n->parent->color == black) {
					n = n->parent;
					continue;
				}
				Node *p = n->parent;
				Node *gp = p->parent;
				Node *ggp = gp->parent;
				if (gp->left == p) {
					if (p->left == n) {
						n->color = black;
						p->color = red;
						gp->color = black;
						gp->left = p->right;
						if (p->right != NULL)
							p->right->parent = gp;
						p->right = gp;
						gp->parent = p;
						if (ggp != NULL) {
							if (ggp->left == gp)
								ggp->left = p;
							else
								ggp->right = p;
						}
						p->parent = ggp;
					}
					else {
						n->color = red;
						p->color = black;
						gp->color = black;
						gp->left = n->right;
						if (n->right != NULL)
							n->right->parent = gp;
						p->right = n->left;
						if (n->left != NULL)
							n->left->parent = p;
						p->parent = n;
						n->left = p;
						gp->parent = n;
						n->right = gp;
						if (ggp != NULL) {
							if (ggp->left == gp)
								ggp->left = n;
							else
								ggp->right = n;
						}
						n->parent = ggp;					
					}
				}
				else {
					if (p->right == n) {
						n->color = black;
						p->color = red;
						gp->color = black;
						gp->right = p->left;
						if (p->left != NULL)
							p->left->parent = gp;
						p->left = gp;
						gp->parent = p;
						if (ggp != NULL) {
							if (ggp->left == gp)
								ggp->left = p;
							else
								ggp->right = p;
						}
						p->parent = ggp;	
					}
					else {
						n->color = red;
						p->color = black;
						gp->color = black;
						gp->right = n->left;
						if (n->left != NULL)
							n->left->parent = gp;
						p->left = n->right;
						if (n->right != NULL)
							n->right->parent = p;					
						n->left = gp;
						gp->parent = n;
						n->right = p;
						p->parent = n;
						if (ggp != NULL) {
							if (ggp->left == gp)
								ggp->left = n;
							else
								ggp->right = n;
						}
						n->parent = ggp;
					}
				}
				numTwists++;
			}
			if (n->parent == NULL) {
				root = n;
			}
			else {
				root = n->parent;
			}
			root->color = black;
		}
		
		return numTwists;
		
	}
};
