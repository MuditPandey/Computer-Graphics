#include "tree.h"
#include "primitives.h"
#include <math.h>
#include <gl/glew.h>
#include <GL/GL.h>
#include<cstdlib>
#include <GL/glut.h>
#include <iostream>
#include<time.h>
#include<vector>
#define rr 10
#define MINSEP 50
#define YSCALE 30

using namespace std;
primitives p;
/*! Returns the maximum of the two numbers passed
*/
int max(int a, int b)
{
	return a > b ? a : b;
}
/*! Returns a random number from l to u inclusive
Precondition: the seed should be assigned by srand(time(NULL)) for random values on every run
*/
int Random_num(int l, int u)
{
	return rand() % (u - l + 1) + l;
}
/*! This function calculates all offsets for the tidier algo
*/
void setup_tdr(node* root, int level, extreme &rightmost, extreme &leftmost) {
	node* left;
	node* right;
	extreme LR, LL, RR, RL;
	int CURsep, ROOTsep, LOffsum, ROffsum;
	if (root == NULL) {
		leftmost.level = -1;
		rightmost.level = -1;
	}
	else {
		root->y = level;
		left = root->llink;
		right = root->rlink;
		setup_tdr(left, level +1, LR, LL);       //Position left subtree recursively 
		setup_tdr(right, level +1, RR, RL);	  //Postion right subtree recursively
		if (left == NULL && right == NULL) {
			rightmost.adr = root;
			leftmost.adr = root;
			rightmost.level = level;
			leftmost.level = level;
			rightmost.offset = 0;
			leftmost.offset = 0;
			root->offset = 0;
		}
		else {

			//Set up for subtree pushing. Place roots of subtrees minimum distance apart
			CURsep = MINSEP;
			ROOTsep = MINSEP;
			LOffsum = 0;
			ROffsum = 0;
			/*Now consider each level  in turn until one subtree is exhausted
			pushing the subtrees apart when neccessary.*/
			while (left != NULL && right != NULL) {
				if (CURsep < MINSEP) {
					ROOTsep = ROOTsep + (MINSEP - CURsep);
					CURsep = MINSEP;
				}
				//Advance left 
				if (left->rlink != NULL) {
					LOffsum = LOffsum + left->offset;
					CURsep = CURsep - left->offset;
					left = left->rlink;
				}
				else {
					LOffsum = LOffsum - left->offset;
					CURsep = CURsep + left->offset;
					left = left->llink;
				}
				//Advance right
				if (right->llink != NULL) {
					ROffsum = ROffsum - right->offset;
					CURsep = CURsep - right->offset;
					right = right->llink;
				}
				else {
					ROffsum = ROffsum + right->offset;
					CURsep = CURsep + right->offset;
					right = right->rlink;
				}
			}
			/*Set the offset in node root and include it in accumulated offsets in right and left*/
			root->offset = (ROOTsep + 1) / 2;
			LOffsum = LOffsum - root->offset;
			ROffsum = ROffsum + root->offset;
			/*Update extreme descendents information*/
			if (RL.level > LL.level || root->llink == NULL) {
				leftmost = RL;
				leftmost.offset = leftmost.offset + root->offset;
			}
			else {
				leftmost = LL;
				leftmost.offset = leftmost.offset - root->offset;
			}
			if (LR.level > RR.level || root->rlink == NULL) {
				rightmost = LR;
				rightmost.offset = rightmost.offset - root->offset;
			}
			else {
				rightmost = RR;
				rightmost.offset = rightmost.offset + root->offset;
			}
			/*If subtrees of root were of uneven heights,check to see if threadng is necessary
			At most one thread needs to be inserted*/
			if (left != NULL && left != root->llink) {
				(RR.adr)->thread = true;
				(RR.adr)->offset = abs((RR.offset + root->offset) - LOffsum);
				if ((LOffsum - root->offset) <= RR.offset) {
					(RR.adr)->llink = left;
				}
				else {
					(RR.adr)->rlink = left;
				}
			}
			else if (right != NULL && right != root->rlink) {
				(LL.adr)->thread = true;
				(LL.adr)->offset = abs((LL.offset - root->offset) - ROffsum);
				if ((ROffsum + root->offset) >= LL.offset) {
					(LL.adr)->rlink = right;
				}
				else {
					(LL.adr)->llink = right;
				}
			}
		}
	}
}
/*!This procedures forms the pre-order traversal of the tree
converting the relative coordinates to absolute coordinates*/
void petrify(node* root, int col) {
	/*This procedures forms the pre-order traversal of the tree
	converting the relative coordinates to absolute coordinates*/
	if (root != NULL) {
		root->x = col;
		if (root->thread==true) {
			root->thread = false;
			root->llink = NULL;
			root->rlink = NULL;
		}
		petrify(root->llink, col - root->offset);
		petrify(root->rlink, col + root->offset);
	}
}
/*! This is a private function which will make an array,
such that the BST implemented from the array, is a balanced tree
*/
void tree::ArrBST(vector <int> &a, int start, int finish, int beg = 0) //needs to be private
{
	if (start > finish) return;
	int mid = (start + finish) / 2;
	a[beg] = mid;
	//cout << "beg" << endl;
	//for (int i = start; i < finish; ++i) cout << a[i] << " ";
	//cout << endl;
	ArrBST(a, start, mid - 1, beg+1);
	ArrBST(a, mid + 1, finish, mid - start + beg+1);
	//cout << "end\n";
	//for (int i = start; i < finish; ++i) cout << a[i] << " ";
	//cout << endl;
}
/*! tree constructor which will take the number of nodes n
and a boolean value which tells if the tree to be generated is balanced or not
*/
tree::tree(int n, bool balanced)
{
	node *N = new node;
	root = N;
	root->llink = NULL;
	root->rlink = NULL;
	root->thread = false;
	vector <int> arr(10000000);
	if (balanced == true)
		ArrBST(arr, 0, n - 1);
	else
	{
		srand(time(NULL));
		for (int i = 0; i < n; ++i)
			arr[i] = Random_num(0, n);
	}
	//for (int i = 0; i < n; ++i) cout << arr[i] << " ";
	this->initializer(arr, n);
}
/*! Prints the tree in inorder
*/
void tree::printTree(node *N)
{
	if (N == NULL)
		return;
	printTree(N->llink);
	cout << N->val << " ";
	printTree(N->rlink);
}
/*! tree constructor which takes an input array of n nodes and converts it into a BST
*/
tree::tree(vector <int> &input, int n)
{
	node *N = new node;
	root = N;
	root->llink = NULL;
	root->rlink = NULL;
	this->initializer(input, n);
}
/*! This is an private function which generates a BST from a given input array
It is used by constructor calls
*/
void tree::initializer(vector <int> &input, int n) //needs to be private
{
	root->val = input[0];
	root->father = NULL;
	root->level = 0;
	for (int i = 1; i < n; ++i)
	{
		node *N = new node;
		N->llink = NULL;
		N->rlink = NULL;
		N->val = input[i];
		node *curr = this->root, *parent;
		while (curr != NULL)
		{
			parent = curr;
			if (N->val >= curr->val)
				curr = (curr->rlink);
			else
				curr = (curr->llink);
		}
		if (N->val >= parent->val)
		{
			parent->rlink = N;		
		}
		else
		{
			parent->llink = N;
		}
		N->father = parent;
		N->level = parent->level + 1;
	}
}
/*! This function returns the height of the tree
*/
int tree::calcHeight(node *N = NULL)
{
	if (N == NULL) N = root;
	if (N->llink == NULL && N->rlink == NULL) return 0; //change return 0 to return 1 if height of single node tree is treated as 1
	if (N->llink == NULL) return 1 + calcHeight(N->rlink);
	if (N->rlink == NULL) return 1 + calcHeight(N->llink);
	return 1 + max(calcHeight(N->llink), calcHeight(N->rlink));
}
/*! This function takes in the values of x and y of the parent node and draws the node
as well as the line connecting it with the parent node
The function does this recursively for each child of the node
No parameters need to be passed when calling it
*/
void tree::drawTree(int cx = 0, int cy = 0, node *N = NULL)
{
	if (N == NULL) N = root;
	int dx = N->x;
	int dy = (N->y)*YSCALE-200;
	if (cx == 0 && cy == 0)
	{
		cx = dx;
		cy = dy;
	}
	if (N->llink != NULL) //draw the root -> llink subtree
		drawTree(dx, dy, N->llink);
	if (N->rlink != NULL) //draw the root -> rlink subtree
		drawTree(dx, dy, N->rlink);
	if(N->llink ==NULL && N->rlink==NULL)//if node is a leaf draw a diamond
	{
		//cout << "drawing leaf\n";
		p.use_as_line(dx - rr, dy, dx, dy + rr);
		p.draw_line();
		p.use_as_line(dx, dy + rr, dx + rr, dy);
		p.draw_line();
		p.use_as_line(dx + rr, dy, dx,dy- rr);
		p.draw_line();
		p.use_as_line(dx, dy - rr, dx - rr, dy);
		p.draw_line();
	}
	else //if node is not a leaf then draw circle
	{
		p.use_as_circle(dx, dy, rr);
		//cout << "drawing circle\n";
		p.draw_circle();
	}
	p.use_as_line(dx, dy, cx, cy); 
	//cout << "drawing line to parent\n";
	p.draw_line();    //drawing a line from the center of current node to the center of parent node
}
/*! This function sets up the initial conditions and calls the functions to implement tidier algorithm
	and draws the tree
*/
void tree::Tidier(void)
{
	clock_t start=clock();
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	extreme rightmost, leftmost;
	setup_tdr(root,0,rightmost, leftmost);
	//printTree(root);
	petrify(root, 680);
	clock_t end = clock();
	double duration = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Tidier duration:" << duration << endl;
	//printTree(root);
	cout << "DRAWING..\n";
	drawTree();
	clock_t afterdraw = clock();
	duration = (afterdraw - end) / (double)CLOCKS_PER_SEC;
	cout << "Tidier Tree drawing Time:" << duration << endl;
	cout << "DRAWING DONE\n";

}
/*! This function sets up the initial conditions and calls the functions to implement tidy algorithm
	and draws the tree
*/
void tree::Tidy(void)
{
	clock_t start=clock();
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	//Var
	//Input variables
	int i, j, n, h, place, modifier_sum, max_height;
	node *current;
	bool is_leaf;
	int fl = 0;
	int first_visit = 0, left_visit = 1, right_visit = 2;
	//Input
	//printTree(this->root);
	int modifier[1000];
	int next_pos[1000];
	max_height = calcHeight();

	for (i = 0; i <= max_height; i++)
	{
		modifier[i] = 0;
		next_pos[i] = MINSEP;
	}
	current = root;
	current->status = first_visit;
	modifier_sum = 0;
	while (current != NULL)
	{
		//cout << current->status << endl;
		switch (current->status)
		{
		case 0: //first visit
				//modifier_sum = modifier_sum + t[current].modifier;
			current->status = left_visit;
			if (current->llink != NULL)
			{
				current = current->llink;
				current->status = first_visit;
			}
			//printf("current %d status %d",current,current -> status);
			break;
		case 1: //left visit
			current->status = right_visit;
			if (current->rlink != NULL)
			{
				current = current->rlink;
				current->status = first_visit;
			}
			//printf("current %d status %d",current,current -> status);
			break;
		case 2: //right visit
			h = current -> level; 
			//cout << "h = " << h << endl;
			is_leaf = (current->llink == NULL) && (current->rlink == NULL);
			if (is_leaf)
			{
				place = next_pos[h];
			}
			else if (current->llink == NULL)
			{
				place = current->rlink->x - MINSEP;
			}
			else if (current->rlink == NULL)
			{
				place = current->llink->x + MINSEP;
			}
			else
			{
				place = ((current->llink->x) + (current->rlink->x)) / 2;
			}
			modifier[h] = max(modifier[h], next_pos[h] - place);
			if (is_leaf)
			{
				current->x = place;
			}
			else
			{
				current->x = place + modifier[h];
			}
			next_pos[h] = current->x + 2*MINSEP;
			current->modifier = modifier[h];
			current = current->father;
			break;
		}
	}//while ends
	current = root;
	current->status = first_visit;
	modifier_sum = 0;
	fl = 0;
	while (current != NULL)
	{
		switch (current->status)
		{
		case 0: //first visit
			current->x += modifier_sum;
			modifier_sum += current->modifier;
			current->y = (2 * (current -> level) + 1);
			current->status = left_visit;
			if (current->llink)
			{
				//printf("line 128");
				current = current->llink;
				current->status = first_visit;
			}
			//       printf("current %d status %d",current,current -> status);
			break;
		case 1:
			current->status = right_visit;
			if (current->rlink)
			{
				current = current->rlink;
				current->status = first_visit;
			}
			//     printf("current %d status %d",current,current -> status);
			break;
		case 2:
			modifier_sum = modifier_sum - current->modifier;
			current = current->father;
			break;
		}
	}//while ends
	clock_t end = clock();
	double duration = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Tidy Duration:" << duration << endl;
	cout << "DRAWING..\n";
	drawTree();
	clock_t afterdraw = clock();
	duration = (afterdraw - end) / double(CLOCKS_PER_SEC);
	cout << "Draw Tidy Tree Duration:" << duration << endl;
	cout << "DRAWING DONE\n";
}