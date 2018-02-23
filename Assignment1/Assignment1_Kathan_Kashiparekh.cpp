#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// Kathan Kashiparekh: 2014B3A7792G

//Struct for entries in the symbol table.
struct entry{
	string identifier;
	string kind;
	string type;
};

//Struct for SymbolTableNode
struct node{
	node *parent; //Hold a pointer to the parent of current scope.
	vector <entry> entries;  //List of all entries in the current scope symbol table.
	vector <node*> children; //List of all the children nodes of current scope.

	// bool addEntry(node *current,string identifier,string type,string kind);  //Add an entry to the entries vector for current symbol table node. 
	// //Return false if same entry exists already. Else return true.
	// void addChildren(node * current,node * child); //Add a new child scope to current symbol table node.
};

class tree{
	struct node * current;
	struct node * rt;
public:
	tree()
	{
		current=NULL;
	}

	// Inserts a new entry into the current scope. If a similar named entry exists,give an error! 
	void insert(string name,string type,string kind)
	{
		entry new_entry;
		new_entry.identifier=name;
		new_entry.kind=kind;
		new_entry.type=type;

		vector <entry> e=current->entries;
		vector <entry> :: iterator iter;
		entry temp;
		bool flag=true;
		for(iter=e.begin() ;iter!=e.end(); ++iter)
		{
			temp=*iter;
			// Allows function overloading! 
			if(kind=="fun"){
				if(temp.identifier==name&&temp.type==type){
					cout<<"Function with same name and return type+paramters exist! ERROR!"<<endl;
					flag=false;
					break;
				}
			}
			else{
				if(temp.identifier==name){
				cout<<"Variable "<<name<<" already declared in current scope! Can't redeclare it! ERROR!"<<endl;
				flag=false;
				break;
				}
			}
		}
		if(flag){
			current->entries.push_back(new_entry);
		}
	}

	// Returns the most recent definition of name by searching the tree from leaf to root. If no match is found it throws an error.
	
	// Modify lookup so that it matches the parameter list as well,in case of a function call! 
	void lookup(string name,string kind,string type)
	{
		vector <entry> e;
		vector <entry> :: iterator iter;
		entry temp;
		bool found=false;

		// If match not found in current scope,go till the root node to check for a match. If still not found,throw error! 
		node * p=current;
		do{
			e=p->entries;
			for(iter=e.begin(); iter!=e.end(); ++iter)
			{
				temp=*iter;
				if(temp.identifier==name&&temp.kind==kind&&temp.type==type){
					found=true;
					break;
				}
			}
			if(found){
				break;
			}
			p=p->parent;
		}while(p!=NULL);

		if(!found){
			cout<<"No declaration of Name:"<<name<<" Type:"<<type<<" Kind:"<<kind<<" found! ERROR!"<<endl;
		}
	}


	// Function to create a new level of scoping with parent as the current node. It will be a child of this current node.
	// Consider looking for functions in the current scope too! So,iterate through the children list as well.
	// Just do insert first to see if error thrown or not. If error there then can't make a new scope for it (issue only for functions)
	// Will work for manually calling functions.If you use regex to parse input,you have to incorporate this in the code.
	void enter_scope()
	{
		if(current==NULL){
			struct node * t=new node;
			t->parent=NULL;
			current=t;
			rt=t;
		}
		else{
			struct node * t=new node;
			t->parent=current;
			current->children.push_back(t);
			current=t;
		}
	}

	// Function to leave current scope and go to its parent. Donot have to delete the current node.
	void exit_scope()
	{
		if(current->parent==NULL){
			cout<<"At the global node! Cant go beyond!"<<endl;
		}
		else{
			current=current->parent;
		}
	}

	// Prints all entries in current scope
	void print()
	{
		vector <entry> e=current->entries;
		vector <entry> :: iterator iter;
		entry temp;
		for(iter=e.begin(); iter!=e.end(); ++iter)
		{
			temp=*iter;
			cout<<"<"<<temp.identifier<<"|"<<temp.type<<"|"<<temp.kind<<">"<<endl;
		}
		cout<<endl;
	}

	// Get root! 
	node * getRoot()
	{
		return rt;
	}

	//Print entire symbol table tree! Prints all children first then its root node. Start in an in-orderly fashion from leftmost node!
	void print_tree(node * root)
	{
		// cout<<"in fun"<<endl;
		vector <entry> :: iterator iter1;
		entry e;
		node *temp;
		int i,j;
		if(!(root->children.empty())){
			// cout<<"in if:"<<endl;
			// cout<<"Size:"<<root->children.size()<<endl;
			// temp=root->children[1];
			// cout<<"Size2:"<<temp->entries.size();
			for(i=0;i<(root->children.size());i++){
				// cout<<"in for:"<<endl;
				temp=root->children[i];
				print_tree(temp);
				for(iter1=temp->entries.begin(); iter1!=temp->entries.end(); ++iter1){
					e=*iter1;
					cout<<"<"<<e.identifier<<"|"<<e.type<<"|"<<e.kind<<">"<<endl;
				}
				cout<<endl;
			}
		}
		if(root==rt){
			int i;
			entry e;
			for(i=0;i<root->entries.size();i++)
			{
				e=root->entries[i];
				cout<<"<"<<e.identifier<<"|"<<e.type<<"|"<<e.kind<<">"<<endl;
			}
		}		
	}
};

//ToDo: Read from a table and go till the end. If some error found,exit from there! 
int main()
{
	tree t;
	// Example 1: Inserting tuples in one ago and not sequentially as and when they are seen! 
	// t.enter_scope();
	// t.insert("x","int","var");
	// t.insert("f","int->void","fun");
	// t.insert("g","int->int","fun");
	// t.print();
	// t.enter_scope();
	// t.insert("x","float","var");
	// t.insert("y","float","var");
	// t.print();
	// t.enter_scope();
	// t.insert("i","int","var");
	// t.insert("j","int","var");
	// t.lookup("x");
	// t.lookup("k"); //To check if lookup goes all the way to the parent node! 
	// t.print();
	// t.exit_scope();
	// t.enter_scope();
	// t.insert("x","int","var");
	// t.insert("l","","lab");
	// t.lookup("x");
	// t.print();
	// t.exit_scope();
	// t.exit_scope();	
	// t.enter_scope();
	// t.insert("t","bool","var");
	// t.lookup("x");
	// t.print();
	// t.exit_scope();
	// t.print();

	// Example 2: Adding tuples as and when they are seen! Output is printed such that before exiting the scope,all tuples in
	// that scope are printed.
	// t.enter_scope();
	// t.insert("f","int,int->void","fun");
	// t.enter_scope();
	// t.insert("a","int","par");
	// t.insert("b","int","par");
	// t.insert("x","double","var");
	// t.insert("i","int","var");
	// t.enter_scope();
	// t.lookup("i","var","int");
	// t.insert("y","int","var");
	// // t.print();
	// t.exit_scope();
	// // t.print();
	// t.exit_scope();
	// t.insert("g","void->void","fun");
	// t.enter_scope();
	// t.insert("x","int","var");
	// t.lookup("f","fun","void->void"); 
	// // t.print(); 
	// t.exit_scope();
	// // t.print();
	// node * r=t.getRoot();
	// t.print_tree(r);

	// Example 3: Same input as Example 1 but done in a way similar to Example 2!
	t.enter_scope();
	t.insert("x","int","var");
	t.insert("f","int->void","fun");
	t.enter_scope();
	t.insert("m","int","par");
	t.insert("x","float","var");
	t.insert("y","float","var");
	t.enter_scope();
	t.insert("i","int","var");
	t.insert("j","int","var");
	t.lookup("x","var","float");
	t.exit_scope();
	t.enter_scope();
	t.insert("x","int","var");
	t.insert("l","","lab");
	t.lookup("x","var","int");
	t.exit_scope();
	t.exit_scope();
	t.insert("g","int->int","fun");
	t.enter_scope();
	t.insert("n","int","par");
	t.insert("t","bool","var");
	t.lookup("x","var","int");

	// Print entire symbol table tree
	node * r=t.getRoot();
	t.print_tree(r);
	return 0;
}