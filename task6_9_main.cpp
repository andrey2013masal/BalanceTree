
#include "task6_9_tree.h"


int main(){
        char *c=NULL;
	c=new char[50];
	strcpy(c,"asdf");
	tree a;
	strcpy(c,"Awewewwewew");
	a.put_Node(c);
	strcpy(c,"Asss");
	a.put_Node(c);
	strcpy(c,"Cji");
	a.put_Node(c);
        strcpy(c,"Dioio");
	a.put_Node(c);
	strcpy(c,"Fklk");
	a.put_Node(c);
	strcpy(c,"AAuiuiuiu");
	a.put_Node(c);
        strcpy(c,"Bkkl;kkp[[][][");
        cout<<"a-tree"<<endl;
	a.print();  
	tree b(a);
        cout<<"b-tree"<<endl;
	b.print();
	cout<<"udalili B is a"<<endl;
	a.delette("B");
	a.print();
	cout<<"nahodim D i C iz b"<<endl;
	b.findvalue("Deeeeeeeeeeeeeer");
	b.findvalue("Cyyyyyy");
	b.findvalue("Asss");
	cout<<endl;
	cout<<"iterator prihoditsa po vsemu derevu"<<endl;
	auto iter(b.begin());
	for(int i=0; i<b.kolichestvo()-1; i++){
		cout<<*iter<<" ";
		++iter;}
	cout<<endl;
	iter=b.end();
        cout<<*(iter)<<endl;
	iter=b.begin();
	cout<<*(++iter)<<"  "<<*(++iter)<<endl;
	iter.find("Asss");
	cout<<*iter<<endl;
	cout<<*(++iter)<<endl;

	cout<<endl;
	cout<<"kol-vo elem v a: "<<a.kolichestvo()<<endl<<"kol-vo elem v b: "<<b.kolichestvo()<<endl;
	delete[] c;
	return 0;
}                            

