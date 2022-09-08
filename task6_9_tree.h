#include <iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include "task6_9_string.h"


using namespace std;

class tree{
	private:
		struct Node
		{
		  Str value;

		  int	height;
		  struct Node *left; 
		  struct Node *right;
		  struct Node *parent;

		};
	public:	

		Node* root;
		int count; 
		Node* Cur;


                class iterator
		{
		private:
			Node *n;
			tree *a; 
		public:
			iterator(tree *a,Node *n) { this->a = a; this->n = n;  }
			iterator(const iterator &src) { a = src.a; n = src.n; }
			const Str &operator*() { return n->value; }
			iterator &operator++() { if(a->_find__Next(n)!=NULL) n=a->_find__Next(n); return *this;}
			iterator find(const char *str){if( a->_find__(a->root,str)!=NULL) n =a->_find__(a->root,str); return *this;}
			iterator &operator--() {if( a->_find__Prev(n)!=NULL)  n =a->_find__Prev(n); return *this;}
			bool operator==(const iterator other) { return n == other.n; }
			void operator=(const iterator other){ n=other.n; a=other.a;}
			bool operator!=(const iterator other) { return n != other.n; }
			friend class tree;
		};

		iterator begin() { return iterator(this, SearchMin(root)); }          
		iterator end() { return iterator(this, SearchMax(root)); }

	        tree(){
			root = NULL;
			Cur = NULL;
			count=0;
		}
		

		int GetHeight(Node* root){
			return root?root->height:0;
		}


	       	void SetHeight(Node* root){
			if (!root)
			return;
			SetHeight(root->right);
			SetHeight(root->left);
			int le = GetHeight(root->right);
			int ri = GetHeight(root->left);
			root->height = (le>ri?le:ri)+1;
		}

		int GetDifference(Node* root){
			return GetHeight(root->right)-GetHeight(root->left);
		}

	        void Turn_Right( Node *(&put_root) ) {
	
			Node *Ltree, *LRtree;
	
			Ltree= put_root->left;
			LRtree=Ltree->right;
	
			Ltree->right= put_root;
			put_root->left= LRtree;
			put_root=Ltree;

		}

	
		void Turn_Left( Node *(&put_root) ) {
	
			Node *Rtree, *RLtree;
		
			Rtree= put_root->right;
			RLtree=Rtree->left;
			
			Rtree->left= put_root;
			put_root->right= RLtree;
			put_root=Rtree;
		
		}

		
        	Node* Balance(Node* root){
			SetHeight(root);
			if( GetDifference(root)>1)
			{
			if( GetDifference(root->right) < 0 )
				Turn_Right(root->right);
			Turn_Left(root);
			return root;
			}
			if( GetDifference(root)<-1 )
			{
			if( GetDifference(root->left) > 0  )
				Turn_Left(root->left);
			Turn_Right(root);
			return root;
			}
			return root;
		}

	        int _put__( Node *(&put_root), const char * &put_value){
			struct Node* laf;
	                Str value_(put_value);
			if ( value_<put_root->value ) { 
				if ( !(put_root->left) ) {
					laf = new Node [1];
                                     	laf -> value = value_;			
					laf -> left = NULL;
					laf -> right = NULL;
					laf -> height = 1;
					laf -> parent = put_root;
					put_root->left = laf;
					SetHeight(put_root);
			
					return 1;
					}
				else {
					_put__( put_root->left, put_value );
					if ( GetDifference(put_root) < -1 ) {
						if ( GetHeight(put_root->left->left) < GetHeight(put_root->left->right) ) 
							Turn_Left(put_root->left);
						Turn_Right(put_root);
					}
					SetHeight(put_root);
					return 1;
					}
				} 
			else 
				if (( value_>put_root->value )){
					if ( !(put_root->right) ) {
						laf = new Node [1];   	
						laf -> value = value_;
						laf -> left = NULL;
						laf -> right = NULL;
						laf -> height = 1;
						laf -> parent = put_root;
						put_root->right = laf;
						SetHeight(put_root);
						return 1;
					}	
				else {
					_put__( put_root->right, put_value );
					if ( GetDifference(put_root) > 1 ) {
						if ( GetHeight(put_root->right->right) < GetHeight(put_root->right->left) ) 
							Turn_Right(put_root->right);
						Turn_Left(put_root);
					}
					SetHeight(put_root);
					return 1;
				}
				}
		else {return -1;}
		}

 		void update_parents( Node *put_root) {
			if (put_root) {
				if (put_root->left) {
					put_root->left->parent = put_root;
					update_parents(put_root->left);
				}
				if (put_root->right) {
					put_root->right->parent = put_root;
					update_parents(put_root->right);
				}
			}
		}

		
                void put_Node(const char *put_value){
			int res=-1;
			if (!root) {
				Str str_(put_value);
				struct Node* laf;
				laf = new Node [1];
		
				laf -> value = str_;
				laf -> left = NULL;
				laf -> right = NULL;
				laf -> parent = NULL;
				laf -> height = 1;
				root = laf;
				} 
			else {
				res = _put__( root, put_value);
			}
			if (res>0) {
				update_parents(root);
			}
			count++;
			root->parent = NULL;
		}


		void _print__ ( const Node *p, int n, int level, int space) {
			if (p) {
				if (level == n) {
					for (int i=1; i<= space; i++) cout << " ";
					cout<< p->value <<"("<< GetDifference((Node *)p)<<")";
		
				}
				else {
				_print__ (p->left, n, level+1, space);
				_print__ (p->right, n, level+1, space);
				}
			}
		
			else {
				for (int j=level; j<=n;j++){
					for (int i=1; i<=space; i++) cout << " ";
				}	
				cout << "                   ";
			}

 
		}

                void print(){
			cout << "_________________________________ "<<endl;
			int h= GetHeight(root);
			int space=5;
			if (root) {
				for (int i=0; i<=h; i++) {
					_print__ ( root,i,0,(h-i)*space );
					cout<<endl;
				}
				}
	
		}

		 ~tree() {
			if (root) {
				_clear__(root);
			}
		}

                void _clear__( Node *(&put_root) ) {
	
			if ( (put_root->left) ) {
				_clear__(put_root->left);
			}
			
			if ( (put_root->right) ) {
				_clear__(put_root->right);
			}
	
			put_root->parent = NULL;
			delete [] put_root;
			put_root=NULL; 
		}	


                tree(const tree &Cop) {
			root = NULL;
			Cur = NULL;
			count=0;
			if (Cop.root) {
				struct Node* laf;
				laf = new Node [1];
		
				laf -> value = Cop.root->value;
		
		
				laf -> parent = NULL;
				laf -> height = Cop.root-> height;
				_copy__( laf -> left, Cop.root -> left);
				_copy__( laf -> right, Cop.root -> right);
				root = laf;
				update_parents(root);
				count=Cop.count;
			}
		}

                void _copy__( Node *(&root), Node *Cop ) {
			if (Cop) {
				struct Node* laf;
				laf = new Node [1];
		
				laf -> value = Cop->value;
		
		
				laf -> parent = NULL;
				laf -> height = Cop -> height;
				root = laf;
				_copy__( root -> left, Cop -> left);
				_copy__( root -> right, Cop -> right);
			} 
			else {
				root = NULL;
			}
		}

                int kolichestvo(void){
		 	return count;
		}


                int _delete__(Node *(&del_root), const char* delete_key) {
			int res;
			if(del_root==NULL){return -1;  }
	                Str delete_value(delete_key);
			if(del_root->value<delete_value) {
				res = _delete__(del_root->right,delete_key);
				if (res == 1)
				del_root = Balance(del_root);
				return res;
			}
			if((del_root->value>delete_value)) {
				res = _delete__(del_root->left,delete_key);
				if (res == 1)
				del_root = Balance(del_root);
				return res;
			}
				Node * left;
				Node * right;
				left = del_root->left;
				right = del_root->right;
		
				delete [] del_root;
				del_root = NULL;
		
				if ( !right ) {
					del_root = left;
					return 1;
				}
				Node * elmin;
				elmin = SearchMin( right );
			
				elmin->right = RemoveMin(right);
				elmin->left = left;
				del_root = Balance(elmin);
				return 1;     
		}

                int delette(const char* delete_key){
			if (!root){ 
				return -1;}
			int res = _delete__( root,delete_key);
			if ( res == 1 ) {
				count--;
				if (root)
					root = Balance(root);
			}
			if (root) {
				update_parents(root);
				root->parent = NULL;
			}
			return res;
		}

                Node* RemoveMin(Node* root){
			if ( !(root->left) )
				return root->right;
			root->left = RemoveMin(root->left);
			return Balance(root);
		}

                Node* SearchMin(Node* root){
			if (root) 
				return root->left?SearchMin(root->left):root;
			else return NULL;
		}

                Node* SearchMax(Node *root){
			if (root) 
				return root->right?SearchMax(root->right):root;
			else return NULL;
		}

                int findvalue(const char* find_str) {
			Cur = _find__(root,find_str);
			if (!Cur)
				return -1;
		       return 1;
		}

                Node* _find__(Node* root, const char* find_str) {
	
			if(root==NULL) { cout<<"net takogo"<<endl;
				return NULL;  }
			Str find_value(find_str);
			cout<<root->value;
	
			if(root->value==find_value){
				cout<<endl;
				return root; }

			if(root->value<find_value){
				cout<< "-> ";
				return _find__(root->right,find_str);}
			else {
				cout<< "-> ";
				return _find__(root->left,find_str);  }
	
		}


                Node* _find__Next(Node* root) {
			if (!root)
				return NULL;
			else {
				if ( (root->right) ) {
					return SearchMin( root->right );
				}
				Node *cur = root;
				while(cur->parent && cur!=cur->parent->left){
					cur=cur->parent;
				}
		
				return  cur->parent;
			}
		
		}

                Node* _find__Prev(Node* root) {
			if (!root)
				return NULL;
			else {
				if ( (root->left) ) {
					return SearchMax( root->left );
				}
				Node *cur = root;
				while(cur->parent && cur!=cur->parent->right){
				cur=cur->parent;
				}
		
			return  cur->parent;
			}
	
		}

                tree &operator=(const tree &Cpy) { // опаертор присваивания копированием

			if (&Cpy == this)
				return *this;

			if (root) {
				_clear__(root);
			}
	
			root = NULL;
			Cur = NULL;
			count=0;
			if (Cpy.root) {
				struct Node* elem;
				elem = new Node [1];
		                count = Cpy.count;
				elem -> value = Cpy.root->value;
				elem -> parent = NULL;
				elem -> height = Cpy.root-> height;
				_copy__( elem -> left, Cpy.root -> left);
				_copy__( elem-> right, Cpy.root -> right);
					root = elem;
				update_parents(root);
			}
			return *this;
		}

};	















	