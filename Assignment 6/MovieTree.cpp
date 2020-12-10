#include <iostream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

MovieTree::MovieTree(){
    
	root=NULL;
} 
TreeNode *get(TreeNode *&a){
	if(a->leftChild==NULL){
		return a;
	}
	return get(a->leftChild);
}

void byeLL(TreeNode*node){
    if (node==NULL){
        return;
    }
    LLMovieNode* a= node->head;
    while (a!=NULL){
        LLMovieNode* temp= a->next;
        delete(a);
        a=temp;
    }
    byeLL(node->leftChild);
    byeLL(node->rightChild);
}


void bye(TreeNode* node){
    if (node==NULL){
        return;
    }
    bye(node->leftChild);
    bye(node->rightChild);
    delete node;
}


TreeNode* deleteNode (TreeNode*& node,char titleChar)
{
    if(node == NULL){
        return NULL;
    }
    else if(titleChar < node->titleChar){
        node->leftChild = deleteNode(node->leftChild, titleChar);
    }
    else if(titleChar > node->titleChar){
        node->rightChild = deleteNode(node->rightChild, titleChar);
    }
    else{
        if(node->leftChild == NULL && node->rightChild == NULL){
            delete node;
            node=NULL;
            return node;
        }
        else if(node->leftChild == NULL){
            TreeNode* temp=node;
            node=node->rightChild;
            delete temp;
        }
        else if(node->rightChild == NULL){
            TreeNode* temp=node;
            node=node->leftChild;
            delete temp;
        }
        else{
            TreeNode*temp=get(node->rightChild);
            node->titleChar=temp->titleChar;
            node->rightChild = deleteNode(node->rightChild,node->titleChar);
        }
    }    
    return node;
}

void print(TreeNode* n){
	if (n == NULL){
		return;
	}
	else{
		print(n->leftChild);
		cout << "Movies starting with letter: " << n->titleChar << endl;
		LLMovieNode* temp=n->head;
		while (temp!=NULL){
			cout << " >> " << temp->title << " " << temp->rating << endl;
			temp=temp->next;
		}
		print(n->rightChild);
	}
}



void MovieTree::printMovieInventory(){
	if (root==NULL){
		return;
	}	
	else {
		print(root);
	}
}

//This helper function finds to see if the title char node in the tree already exists.
TreeNode* findFirstLetterNode(TreeNode* n,char titleLetter){
	if(n==NULL){
		return NULL;
	}
	else if (n->titleChar==titleLetter){
		return n;
	}
	else {
		TreeNode *left = findFirstLetterNode(n->leftChild,titleLetter);
		TreeNode *right = findFirstLetterNode(n->rightChild,titleLetter);
		if (left!=NULL||right!=NULL){
			if (right==NULL){
				return left;
			}
			else if (left==NULL){
				return right;
			}
			else{
				return NULL;
			}
		}
	}
}

void addTreeNode(char titleChar, TreeNode*&n){
	if (n==NULL){
		n=new TreeNode();
		n->titleChar=titleChar;
		n->head=NULL;
		n->leftChild=NULL;
		n->rightChild=NULL;
		return;
	}
	if (titleChar>n->titleChar){
		addTreeNode (titleChar,n->rightChild);
	}
	else if (titleChar<n->titleChar){
		addTreeNode(titleChar,n->leftChild);
	}
}

void addLL(LLMovieNode *&head,int ranking, string title, int year, float rating){
	if (head==NULL){
		head=new LLMovieNode(ranking,title,year, rating);
	}
	else{
		if(title<head->title){
			LLMovieNode* current = head;
			head = new LLMovieNode(ranking,title,year,rating);
			head->next=current;
		}
		else {
			LLMovieNode* current=head;
			LLMovieNode* previous=head;
			while(current!=NULL){
				if (title<current->title){
					LLMovieNode* temp= new LLMovieNode(ranking,title, year,rating);
					temp->next=current;
					previous->next=temp;
					break;
				}
				else if (current->next == NULL){
					current->next= new LLMovieNode(ranking,title,year,rating);
					current=current->next;
					current->next==NULL;
					break;

				}
				else{
					previous=current;
					current=current->next;
				}
			}
		}
	}
}


void MovieTree::addMovie(int ranking, string title, int year, float rating){
	if (root==NULL){
		addTreeNode(title[0], root);
		addLL(root->head,ranking,title,year,rating);

		return;
	}
	else if (findFirstLetterNode(root,title[0])==NULL){
		addTreeNode(title[0],root);
		TreeNode* NodeAt=findFirstLetterNode(root,title[0]);
		addLL(NodeAt->head,ranking,title,year,rating);
		return;
	}
	else{
		TreeNode* nodeAt=findFirstLetterNode(root,title[0]);
		addLL(nodeAt->head,ranking,title,year,rating);
		return;
	}
}


void byeMovie (string movieTitle,LLMovieNode *&head){
	bool exists=false;
	if (head==NULL){
		return;
	}
	else if(head->title==movieTitle){
		LLMovieNode *t = head;
		LLMovieNode *a=head->next;
		delete t;
		head=a;
		exists=true;
	}
	else{
		LLMovieNode *temp=head;
		LLMovieNode *whale=NULL;
		while (temp!=NULL){
			if (temp->title==movieTitle){
				whale->next=temp->next;
				delete temp;
				exists=true;
				break;
			}
			else{
				whale=temp;
				temp=temp->next;
			}	
		}
		if (exists==false){
			cout << "Movie: " << movieTitle << " not found, cannot delete." << endl;
			return;
		}
	}
}

void MovieTree::deleteMovie(string title){
	TreeNode* whalesbutt = findFirstLetterNode(root,title[0]);
	if (whalesbutt==NULL){
		cout << "Movie: " << title << " not found, cannot delete." << endl;
		return;	
	}
	else{	
		byeMovie(title,whalesbutt->head);
		if (whalesbutt->head==NULL){
			root = deleteNode(root,title[0]);
		}
	}
}

MovieTree::~MovieTree(){
    byeLL(root);
    bye(root);
    //TreeNode*b=findFirstLetterNode(root,'G');
    //deleteNode(b,'G');
    //TreeNode*a=findFirstLetterNode(root,'T');
    //deleteNode(a,'T');
    
}