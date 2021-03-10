#include <iostream>
#include <stack>
#include<queue>
using namespace std;

struct TreeNode {
	int key;
	TreeNode *left, *right;
	TreeNode(int, TreeNode*, TreeNode*);
	TreeNode() {
		left = right = nullptr;
	}
};

// main functios fwd
void formTable(int *&, bool *&, int &, int &);
void insertKey(int *&, bool *&, int &, int &);
void findKey(int *&, bool *&, int &, int &);
void deleteKey(int *&, bool *&, int &, int &);
void print(int *&, bool *&, int &, int &);
void formTree(int *&, bool *&, int&, int&, TreeNode *&);
void printTree( TreeNode*);
void findTree(TreeNode*);
void deleteTree(TreeNode *&);
void insertTree(TreeNode *root);
void findCritical(TreeNode *);
int treeHeight(TreeNode *);



int main() {
	int option, *table, size, c;
	bool *vector=nullptr, created = false;
	TreeNode *root=nullptr;

	cout << "\n Izaberite jednu od opcija: \n [1] Formiranje tabele \n [2] Umetanje kljuca \n [3] Pretraga kljuca \n [4] Brisanje kljuca \n [5] Ispis \n [6] Formiranje stabla \n [7] Ispis \n [8] Pretraga kljuca u stablu \n [9] Brisanje stabla \n [10] Umetanje kljuca u stablo \n [11] Odredjivanje kriticnog cvora \n [0] Kraj \n ";
	cin >> option;
	while (option != 0) {
		switch (option)
		{
		case 1:
			if (!created) {
				formTable(table, vector, size, c);
				created = true;
			}
			else {
				cout << "\n Tabela je vec formirana." << endl;
			}
			break;
		case 2:
			if (created) {
				insertKey(table, vector, size, c);
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 3:
			if (created) {
				findKey(table, vector, size, c);
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 4:
			if (created) {
				deleteKey(table, vector, size, c);
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 5:
			print(table, vector, size, c);
			break;
		case 6:
			if (created) {
				if (root == nullptr) {
					formTree(table, vector, size, c, root);
				}
				else {
					cout << "\n Stablo je vec formirano" << endl;
				}
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 7:
			if (created) {
				if (root != nullptr) {
					printTree(root);
				}
				else {
					cout << "\n Stablo nije formirano" << endl;
				}
			}
			else {
				cout << "\n Tabela nije formirana" << endl;
			}
			break;
		case 8:
			if (created) {
				if (root != nullptr) {
					findTree(root);
				}
				else {
					cout << "\n Stablo nije formirano" << endl;
				}
			}
			else {
				cout << "\n Tabela nije formirana" << endl;
			}
			break;
		case 9:
			if (created) {
				if (root != nullptr) {
					deleteTree(root);
				}
				else {
					cout << "\n Stablo nije formirano" << endl;
				}
			}
			else {
				cout << "\n Tabela nije formirana" << endl;
			}
			break;
		case 10:
			if (created) {
				if (root != nullptr) {
					insertTree(root);
				}
				else {
					cout << "\n Stablo nije formirano" << endl;
				}
			}
			else {
				cout << "\n Tabela nije formirana" << endl;
			}
			break;
		case 11:
			if (created) {
				if (root != nullptr) {
					findCritical(root);
				}
				else {
					cout << "\n Stablo nije formirano" << endl;
				}
			}
			else {
				cout << "\n Tabela nije formirana" << endl;
			}
			break;
		default:cout << "\n Izabrana opcija ne postoji!";
			break;
		}	cout << "\n Izaberite jednu od opcija: \n [1] Formiranje tabele \n [2] Umetanje kljuca \n [3] Pretraga kljuca \n [4] Brisanje kljuca \n [5] Ispis \n [6] Formiranje stabla \n [7] Ispis \n [8] Pretraga kljuca u stablu \n [9] Brisanje stabla \n [10] Umetanje kljuca u stablo \n [11] Odredjivanje kriticnog cvora \n [0] Kraj \n ";
		cin >> option;
	}
	return 0;
}

/*
 * Utility functions.
 */

int binarySearch(int *&table, bool *&vector, int &size, int &c, int &key) {
	int low = 0, mid, high = size * c - 1;

	while (low <= high) { // moguca greska
		mid = (low + high) / 2;
		if (key == table[mid]) {
			//while (key == table[mid] && vector[mid] == false) mid--;
			return mid;
		}
		else if (key < table[mid]) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return mid;
}

void expandTable(int *&table, bool *&vector, int &size, int &c) {
	size = size * 2;
	int *temp = new int[size*c];
	bool *pom = new bool[size*c];

	for (int i = 0; i < size*c / 2; i++) {
		temp[2 * i] = table[i];
		pom[2 * i] = vector[i];
		temp[2 * i + 1] = table[i];
		pom[2 * i + 1] = false;
	}

	delete[] table;
	delete[] vector;
	table = temp;
	vector = pom;
}

/*
 * Main menu functions.
 */

void formTable(int *&table, bool *&vector, int &size, int &c) {


	cout << "\n Unesite velicinu tabele" << endl;
	cin >> size;
	cout << "\n Unesite faktor uvecanja" << endl;
	cin >> c;

	table = new int[size*c];
	vector = new bool[size*c];

	for (int i = 0; i < size*c; i++) {
		if (i % c == 0) {
			cout << "\n Unesite " << i << ". broj: ";
			cin >> table[i];
			vector[i] = true;
		}
		else {
			table[i] = table[i - 1];
			vector[i] = false;
		}
	}
}

void insertKey(int *&table, bool *&vector, int &size, int &c) {
	int key;
	bool full = true;
	cout << "\n Unesite vrednost novog kljuca" << endl;
	cin >> key;
	int index = binarySearch(table, vector, size, c, key);

	for (int i = 0; i < size*c; i++) {
		if (vector[i] == false) {
			full = false;
			break;
		}
	}
	if (index < 0) { // prvi element u nizu
		index = 0;
	}

	if (index >= size * c) { // poslednji element u nizu
		index = size * c - 1;
	}

	if (table[index] == key) {
		while (index > 0 && table[index - 1] == key) index--; // trazimo najlevlji primerak broja
		vector[index] = true;
		return;
	}

	if (table[index] != key && vector[index] == false) {
		table[index] = key;
		vector[index] = true;
		for (int i = index + 1; i < size*c && vector[i] == false; i++) {
			table[i] = key;
		}
		return;
	}

	if (table[index] != key && vector[index] == true) {

		if (full) {
			expandTable(table, vector, size, c);
			index = index * 2;
		}
		if (key > table[index]) {

			bool flag = false;
			for (int i = index + 1; i < size*c; i++) {
				if (vector[i] == false) {
					for (int j = i; j > index + 1; j--) {
						table[j] = table[j - 1];
						vector[j] = vector[j - 1];
					}
					index++;
					flag = true;
					break;
				}
			}
			if (!flag) {
				for (int i = index - 1; i >= 0; i--) {
					if (vector[i] == false) {
						for (int j = i; j < index; j++) {
							table[j] = table[j + 1];
							vector[j] = vector[j + 1];
						}
						break;
					}

				}
			}

		}
		else if (key < table[index]) {

			bool flag = false;
			for (int i = index - 1; i >= 0; i--) {
				if (vector[i] == false) {
					for (int j = i; j < index - 1; j++) {
						table[j] = table[j + 1];
						vector[j] = vector[j + 1];
					}
					index--;
					flag = true;
					break;
				}

			}

			if (!flag) {
				for (int i = index + 1; i < size*c; i++) {
					if (vector[i] == false) {
						for (int j = i; j > index; j--) {
							table[j] = table[j - 1];
							vector[j] = vector[j - 1];
						}
						break;
					}
				}
			}

		}
		table[index] = key;
		vector[index] = true;
		// kopije desno
		for (int i = index + 1; i < size*c && vector[i] == false; i++) {
			table[i] = key;
		}


	}
}

void findKey(int *&table, bool *&vector, int &size, int &c) {
	int key;

	cout << "\n Unesite vrednost  kljuca" << endl;
	cin >> key;
	int index = binarySearch(table, vector, size, c, key);
	while (table[index] == key && vector[index] == false && index > 0)index--;
	if (table[index] == key) {
		cout << "Kljuc je pronadjen na lokaciji " << index << ".";
	}
	else {
		cout << "Kljuc nije pronadjen";
	}
}

void deleteKey(int *&table, bool *&vector, int &size, int &c) {
	int key;

	cout << "\n Unesite vrednost  kljuca" << endl;
	cin >> key;
	int index = binarySearch(table, vector, size, c, key);
	while (table[index] == key && vector[index] == false && index > 0)index--;
	if (table[index] == key) { // samo slucaj kada postoji validna kopija na pocetku podniza
		vector[index] = false;
	}
}

void print(int *&table, bool *&vector, int &size, int &c) {
	for (int i = 0; i < size*c; i++) {
		cout << table[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < size*c; i++) {
		cout << vector[i] << "\t";
	}	
	cout << endl;
}

TreeNode::TreeNode(int k, TreeNode* l, TreeNode* r) {
	key = k;
	left = l;
	right = r;
}

struct StackElem {
	TreeNode *node;
	int low,high;
	StackElem(TreeNode* n, int l, int h) {
		node = n;
		low = l;
		high = h;
	}
};

TreeNode *bstSearch(TreeNode *root, int key) {
	TreeNode *temp = root;
	while (temp != nullptr && temp->key != key) {
		if (key < temp->key) {
			temp = temp->left;
		}
		else if(key>temp->key) {
			temp = temp->right;
		}
	}
	return temp;
}

void formTree(int *&table, bool *&vector, int &size, int &c, TreeNode *&root) {
	int low, mid, high;
	TreeNode *next;
	stack<StackElem*> stack;
	low = 0;
	high = size * c;
	mid = (high + low) / 2;
	int temp = mid;
	while (vector[temp] == false && temp>0) {
		temp--;
	}
	root = new TreeNode(table[temp], nullptr, nullptr);
	next = root;
	stack.push(new StackElem(next, temp + 1, high));
	high = temp - 1;
	while (low < high) {
		mid = (high + low) / 2;
		temp = mid;
		while (vector[temp] == false && temp > 0) {
			temp--;
		}
		if (bstSearch(root, table[temp]) == nullptr) {
			next->left = new TreeNode();
			next = next->left;
			next->key = table[temp];
			stack.push(new StackElem(next, temp + 1, high));
			
		}
		high = temp - 1;		
	}
	next->left = nullptr;
	while (!stack.empty()) {
		StackElem* pop = stack.top(); stack.pop();
		low = pop->low;
		high = pop->high;
		next = pop->node;
		delete pop;
		if (low <= high && low<size*c) { //low<=high
			mid = (high + low) / 2;
			temp = mid;
			while (vector[temp] == false && temp > 0) {
				temp--;
			}
			if (bstSearch(root, table[temp]) == nullptr) {
				next->right = new TreeNode(); // mora postojati neka zastita
				next = next->right;
				next->key = table[temp];
				stack.push(new StackElem(next,temp + 1, high));
			}
			high = temp - 1;
			while (low < high) {
				mid = (high + low) / 2;
				temp = mid;
				while (vector[temp] == false && temp > 0) {
					temp--;
				}
				if (bstSearch(root, table[temp]) == nullptr) {
					next->left = new TreeNode();
					next = next->left;
					next->key = table[temp];
					stack.push(new StackElem(next, temp + 1, high));
				}
				high = temp - 1;
			}
			next->left = nullptr;
		}
		else {
			next->right = nullptr;
		}
		
	}

}

void printTree(TreeNode *root) {
	queue<TreeNode*> q;
	int i, line_len = 62;
	int height;
	int first_skip = line_len, in_between_skip;
	height = treeHeight(root);
	if (!q.empty())   return;
	q.push(root);
	for (i = 0; i <= height; i++) {
		int j = 1 << i, k, l;
		in_between_skip = first_skip;
		first_skip = (first_skip - 2) / 2;
		for (k = 0; k < first_skip; k++) putchar(' ');
		for (k = 0; k < j; k++) {
			TreeNode *btn = (TreeNode*)q.front();
			q.pop();
			if (btn) {
				q.push(btn->left);
				q.push(btn->right);
			}
			else {
				q.push(0);
				q.push(0);
			}
			if (btn)  cout<< btn->key;
			else       cout<<"  ";
			for (l = 0; l < in_between_skip; l++) putchar(' ');
		}
		putchar('\n');
		putchar('\n');
	
}

}






void findTree(TreeNode *root) {
	int key;
	TreeNode *temp;
	cout << "\n Unesite kljuc za pretragu: ";
	cin >> key;
	temp = bstSearch(root, key);
	if ( temp == nullptr) {
		cout << "\n Kljuc nije pronadjen" << endl;

	}
	else {
		cout << "\n Kljuc je pronadjen";
	}
}

void insertTree(TreeNode *root) {
	TreeNode *temp, *pom;
	int key;
	temp = root;
	pom = nullptr;
	cout << "\n Unesite novi kljuc: ";
	cin >> key;
	while (temp != nullptr) {
		pom = temp;
		if (key == temp->key) {
			cout << "\n Kljuc vec postoji";
			return;
		}
		else if (key < temp->key) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (key < pom->key) {
		pom->left = new TreeNode(key,nullptr,nullptr);
	}
	else {
		pom->right = new TreeNode(key, nullptr, nullptr);
	}
}







void deleteTree(TreeNode *&root) {
	stack<TreeNode*>stack;
	stack.push(root);
	while (!stack.empty()) {
		TreeNode *temp = stack.top();
		stack.pop();
		if (temp->left) {
			stack.push(temp->left);
		}
		if (temp->right) {
			stack.push(temp->right);
		}
		delete(temp);
	}
	 root=nullptr;
}
int treeHeight(TreeNode*root)
{
	
	if (root == nullptr) {
		return 0;
	}
	queue<TreeNode *> q;
	q.push(root);
	int height = 0;

	while (true)
	{
		int nodeCount = q.size();
		if (nodeCount == 0) {
			return height;
		}
		height++;
		while (nodeCount > 0)
		{
			TreeNode *node = q.front();
			q.pop();
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
			nodeCount--;
		}
	}
}

void findCritical(TreeNode *root) {
	int balans, height1=0, height2=0;
	stack<TreeNode*>stack;
	stack.push(root);
	while (!stack.empty()) {
		TreeNode *temp = stack.top();
		stack.pop();
		height1 = treeHeight(temp->left);
		height2 = treeHeight(temp->right);
		balans = abs(height1 - height2);
		if (balans >= 2) {
			cout << "Kriticni cvor je " << temp->key << endl;
		}
		if (temp->left) {
			stack.push(temp->left);
		}
		if (temp->right) {
			stack.push(temp->right);
		}

	}

}

