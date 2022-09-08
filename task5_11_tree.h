#include <iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include "task5_11_string.h"


using namespace std;

class tree{
	private:
		struct Node
		{
		  Str value;

		  int	height;
		  struct Node *less; // указатель на следующий меньший элемент
		  struct Node *equalmore; // указатель на следующий больший элемент
		  struct Node *parent; // указатель на предыдущий элемент
		};

		Node* start;
		int number; //  количество ключей в дереве
		Node* elfound;

	public:	
		/* дальше идет описание функций:
			tree()
			int GetHeight(element* root)	
		        void SetHeight(element* root)
		        int GetDifference(element* root){
		        void Turn_Right( element *(&put_start) ) {
	                void Turn_Left( element *(&put_start) ) {
	                element* Balance(element* root){
		        int internal_put( element *(&put_start), const char * &put_value){
		        void update_parents( element *put_start) {
		        void put_element(const char *put_value){
		        void internal_print ( const element *p, int n, int level, int prob) {
		        void print()
        		 ~tree() {
                        void internal_clear( element *(&put_start) ) {
	                tree(const maptree &Cop) { // конструктор копирования
		        internal_copy( element *(&root), element *Cop ) {
	                int kolichestvo(void){

		*/

                class iterator
		{
		private:
			Node *n;
			tree *a; 
		public:
			iterator(tree *a,Node *n) { this->a = a; this->n = n;  }
			iterator(const iterator &src) { a = src.a; n = src.n; }
			const Str &operator*() { return n->value; }
			iterator &operator++() { n = a->internal_findNext(n); return *this;}
			iterator &operator--() { n = a->internal_findPrev(n); return *this;}
			bool operator==(const iterator other) { return n == other.n; }
			bool operator!=(const iterator other) { return n != other.n; }
			friend class tree;
		};

		iterator begin() { return iterator(this, SearchMin(start)); }
		iterator end() { return iterator(this, SearchMax(start)); }
//		iterator nul() { return iterator(nullptr, this); }


                tree(){
			start = NULL;
			elfound = NULL;
			number=0;
		}

	
		

		int GetHeight(Node* root){
			return root?root->height:0;
		}


	       	void SetHeight(Node* root){
			if (!root)
			return;
			SetHeight(root->equalmore);
			SetHeight(root->less);
			int hl = GetHeight(root->equalmore);
			int hr = GetHeight(root->less);
			root->height = (hl>hr?hl:hr)+1;
		}

		int GetDifference(Node* root){
			return GetHeight(root->equalmore)-GetHeight(root->less);
		}

	        void Turn_Right( Node *(&put_start) ) {
	
			element *LeftSubTree, *LeftSubTreeRightSubtree;
	
			LeftSubTree= put_start->less;
			LeftSubTreeRightSubtree=LeftSubTree->equalmore;
	
			LeftSubTree->equalmore= put_start;
			put_start->less= LeftSubTreeRightSubtree;
			put_start=LeftSubTree;

		}

	
		void Turn_Left( Node *(&put_start) ) {
	
			element *RightSubTree, *RightSubTreeLeftSubtree;
		
			RightSubTree= put_start->equalmore;
			RightSubTreeLeftSubtree=RightSubTree->less;
			
			RightSubTree->less= put_start;
			put_start->equalmore= RightSubTreeLeftSubtree;
			put_start=RightSubTree;
		
		}

		
        	Node* Balance(Node* root){
			SetHeight(root);
			if( GetDifference(root)>1)
			{
			if( GetDifference(root->equalmore) < 0 )
				Turn_Right(root->equalmore);
			Turn_Left(root);
			return root;
			}
			if( GetDifference(root)<-1 )
			{
			if( GetDifference(root->less) > 0  )
				Turn_Left(root->less);
			Turn_Right(root);
			return root;
			}
			return root;
		}

	        int internal_put( Node *(&put_start), const char * &put_value){
			struct Node* nn;
			int res;
	                Str value_(put_value);
			res = value_>put_start->value;
			if (  res < 0 ) { // less
				if ( !(put_start->less) ) {
					nn = new Node [1];
                                     	nn -> value = value_;
			
					nn -> less = NULL;
					nn -> equalmore = NULL;
					nn -> height = 1;
					nn -> parent = put_start;
					put_start->less = nn;
					SetHeight(put_start);
			
					return 1;
					}
				else {
					internal_put( put_start->less, put_value );
					if ( GetDifference(put_start) < -1 ) {
						if ( GetHeight(put_start->less->less) < GetHeight(put_start->less->equalmore) ) 
							Turn_Left(put_start->less);
						Turn_Right(put_start);
					}
					SetHeight(put_start);
					return 1;
					}
				} 
			else 
				if ( res > 0 ) { // equalmore
					if ( !(put_start->equalmore) ) {
						nn = new Node [1];
   	
						nn -> value = value_;

						nn -> less = NULL;
						nn -> equalmore = NULL;
						nn -> height = 1;
						nn -> parent = put_start;
						put_start->equalmore = nn;
						SetHeight(put_start);
						return 1;
					}	
				else {
					internal_put( put_start->equalmore, put_value );
					if ( GetDifference(put_start) > 1 ) {
						if ( GetHeight(put_start->equalmore->equalmore) < GetHeight(put_start->equalmore->less) ) 
							Turn_Right(put_start->equalmore);
						Turn_Left(put_start);
					}
					SetHeight(put_start);
					return 1;
				}
				}
		else { // equal	
		//cout << "equal: "<<put_key<<endl;
		return -1;
		}
		}

 		void update_parents( Node *put_start) {
			if (put_start) {
				if (put_start->less) {
					put_start->less->parent = put_start;
					update_parents(put_start->less);
				}
				if (put_start->equalmore) {
					put_start->equalmore->parent = put_start;
					update_parents(put_start->equalmore);
				}
			}
		}

		
                void put_element(const char *put_value){
			int res=-1;
			if (!start) {
				Str str_(put_value);
				struct Node* nn;
				nn = new Node [1];
		
				nn -> value = str_;
				nn -> less = NULL;
				nn -> equalmore = NULL;
				nn -> parent = NULL;
				nn -> height = 1;
				start = nn;
				} 
			else {
				res = internal_put( start, put_value);
			}
			if (res>0) {
		//		number++;
				update_parents(start);
			}
			number++;
			start->parent = NULL;
		}


		void internal_print ( const Node *p, int n, int level, int prob) {
			if (p) {
				if (level == n) {
					for (int i=1; i<= prob; i++) cout << " ";
					cout<< p->value <<"("<< GetDifference((element *)p)<<")";
				}
			else {
				internal_print (p->less,n, level+1,prob);
				internal_print (p->equalmore,n, level+1,prob);
			}
			} 
		 	else {
				for (int j=level; j<=n;j++){
					for (int i=1; i<= prob; i++) cout << " ";
				}
				cout << "   ";
			}
		}

                void print(){
			cout << "  -------------------- "<<endl;
			int h= GetHeight(start);
			int prob=3;
			if (start) {
				for (int i=0; i<=h; i++) {
					internal_print ( start,i,0,prob*(h-i) );
					cout<<endl;
				}
				}
	
			}

		 ~tree() {
	//		cout << "destroy"<<endl;
			if (start) {
				internal_clear(start);
			}
		}

                void internal_clear( Node *(&put_start) ) {
	
			if ( (put_start->less) ) {
				internal_clear(put_start->less);
			}
			
			if ( (put_start->equalmore) ) {
				internal_clear(put_start->equalmore);
			}
	
			put_start->parent = NULL;
			delete [] put_start;
			put_start=NULL; 
		}	


                tree(const tree &Cop) { // конструктор копирования
			start = NULL;
			elfound = NULL;
			number=0;
			if (Cop.start) {
				struct element* nn;
				nn = new element [1];
		
				nn -> value = Cop.start->value;
		
		
				nn -> parent = NULL;
				nn -> height = Cop.start-> height;
				internal_copy( nn -> less, Cop.start -> less);
				internal_copy( nn -> equalmore, Cop.start -> equalmore);
				start = nn;
				update_parents(start);
				number=Cop.number;
			}
		}

                void internal_copy( element *(&root), element *Cop ) {
			if (Cop) {
				struct element* nn;
				nn = new element [1];
		
				nn -> value = Cop->value;
		
		
				nn -> parent = NULL;
				nn -> height = Cop -> height;
				root = nn;
				internal_copy( root -> less, Cop -> less);
				internal_copy( root -> equalmore, Cop -> equalmore);
			} 
			else {
				root = NULL;
			}
		}

                int kolichestvo(void){
		 	return number;
		}


                int internal_delette(element *(&del_start), const char* delete_key) {
			int res;
			if(del_start==NULL){return -1;  }
	                Str delete_value(delete_key);
			if(del_start->value<delete_value) {
				res = internal_delette(del_start->equalmore,delete_key);
				if (res == 1)
				del_start = Balance(del_start);
				return res;
			}
			if((del_start->value>delete_value)) {
				res = internal_delette(del_start->less,delete_key);
				if (res == 1)
				del_start = Balance(del_start);
				return res;
			}
				element * less;
				element * equalmore;
				less = del_start->less;
				equalmore = del_start->equalmore;
		
				delete [] del_start;
				del_start = NULL;
		
				if ( !equalmore ) {
					del_start = less;
					return 1;
				}
				element * elmin;
				elmin = SearchMin( equalmore );
			
				elmin->equalmore = RemoveMin(equalmore);
				elmin->less = less;
				del_start = Balance(elmin);
				return 1;     
		}

                int delette(const char* delete_key){
			if (!start){ 
				return -1;}
			int res = internal_delette( start,delete_key);
			if ( res == 1 ) {
				number--;
				if (start)
					start = Balance(start);
			}
			if (start) {
				update_parents(start);
				start->parent = NULL;
			}
			return res;
		}

                element* RemoveMin(element* root){
			if ( !(root->less) )
				return root->equalmore;
			root->less = RemoveMin(root->less);
			return Balance(root);
		}

                element* SearchMin(element* root){
			if (root) 
				return root->less?SearchMin(root->less):root;
			else return NULL;
		}

                element* SearchMax(element *root){
			if (root) 
				return root->equalmore?SearchMax(root->equalmore):root;
			else return NULL;
		}

                int findvalue(const char* find_str) {
			elfound = internal_find(start,find_str);
			if (!elfound)
				return -1;
		       return 1;
		}

                element* internal_find(element* root, const char* find_str) {
	
			if(root==NULL)
				return NULL;
			Str find_value(find_str);
			cout<<root->value;
	
			if(root->value==find_value){
				cout<<endl;
				return root; }

			if(root->value<find_value){
				cout<< "-> ";
				return internal_find(root->equalmore,find_str);}
			else {
				cout<< "-> ";
				return internal_find(root->less,find_str);  }
	
		}


                element* internal_findNext(element* root) {
			if (!root)
				return NULL;
			else {
				if ( (root->equalmore) ) {
					return SearchMin( root->equalmore );
				}
				element *cur = root;
				while(cur->parent && cur!=cur->parent->less){
				//cout<<"cur: "<< cur->key <<endl;
					cur=cur->parent;
				}
		
				return  cur->parent;
			}
		
		}

                element* internal_findPrev(element* root) {
			if (!root)
				return NULL;
			else {
				if ( (root->less) ) {
					return SearchMax( root->less );
				}
				element *cur = root;
				while(cur->parent && cur!=cur->parent->equalmore){
				//cout<<"cur: "<< cur->key <<endl;
				cur=cur->parent;
				}
		
			return  cur->parent;
			}
	
		}



};	















	