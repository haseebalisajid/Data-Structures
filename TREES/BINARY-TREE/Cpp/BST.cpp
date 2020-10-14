#include<iostream>
using namespace std;

class TNode{
	public:
		int data;
		TNode *rchild;
		TNode *lchild;
};

class BST{
	public:
	TNode *loc,*ploc;
	TNode *root;
	int count=0;
	
	bool isEmpty(){
		return root==NULL;
	}
	
	void insert(int value){
		TNode *nn = new TNode();
		nn->data=value;
		if(isEmpty()){
			root=nn;
		}
		else{
			loc=root;
			ploc=NULL;
			while(loc!=NULL){
				if(value<=loc->data){
					ploc=loc;
					loc=loc->lchild;
				}
				else{
					ploc=loc;
					loc=loc->rchild;
				}
			}
			if(value<=ploc->data){
				ploc->lchild=nn;
			}
			else{
				ploc->rchild=nn;
			}
		}
	//	Preorder(root);
	//	cout<<endl;
	}
	void del(int value){
		loc=root;
		ploc=NULL;
		if(!isEmpty()){
			while(loc!=NULL && loc->data!=value){
				if(value<=loc->data){
					ploc=loc;
					loc=loc->lchild;
				}
				else{
					ploc=loc;
					loc=loc->rchild;
				}
			}
			
			if(loc==NULL){
				cout<<"Kisi aur din try karna AJ yahan kuch ni hai "<<endl;
			}
			//LEaf Node
			if(loc->lchild==NULL && loc->rchild==NULL){
				if(ploc->lchild==loc){
					ploc->lchild=NULL;
					delete loc;
				}
				else if(ploc->rchild==loc){
					ploc->rchild=NULL;
					delete loc;
				}
			}
			//If right node NULL
			if(loc->lchild!=NULL && loc->rchild==NULL){
				if(ploc->lchild==loc){
					ploc->lchild=loc->lchild;
					delete loc;
				}
				else{
					ploc->rchild=loc->lchild;
					delete loc;
				}
			}
			//if Left node NULL 
			if(loc->rchild!=NULL && loc->lchild==NULL){
				if(ploc->rchild==loc){
					ploc->rchild=loc->rchild;
					delete loc;
				}
				else{
					ploc->lchild=loc->rchild;
					delete loc;
				}
			}
			
		}
		else{
			cout<<"Pagla gaye ho kya"<<endl;
		}
	}
	void Preorder(TNode *temp){
		if(temp!=NULL){
			cout<<temp->data<<" ";
			Preorder(temp->lchild);
			Preorder(temp->rchild);
		}	
	}
	void Inorder(TNode *temp){
		if(temp!=NULL){
			Inorder(temp->lchild);
			cout<<temp->data<<" ";
			Inorder(temp->rchild);
		}
	}
	void PostOrder(TNode *temp){
		if(temp!=NULL){
			PostOrder(temp->lchild);
			PostOrder(temp->rchild);
			cout<<temp->data<<" ";
		}
	}
	void LeafPrint(TNode *temp){
		if(temp!=NULL){
			if(temp->lchild==NULL && temp->rchild==NULL){
				cout<<temp->data<<" ";
			}
			LeafPrint(temp->lchild);
			LeafPrint(temp->rchild);
		}
	}
	void LeftPrint(TNode *temp){
		if(temp!=NULL){
			if(temp->lchild!=NULL){
				cout<<temp->data<<" ";
			}
			LeftPrint(temp->lchild);
			LeftPrint(temp->rchild);
		}
	}
	void RightPrint(TNode *temp){
		if(temp!=NULL){
			if(temp->rchild!=NULL){
				cout<<temp->data<<" ";
			}
			RightPrint(temp->lchild);
			RightPrint(temp->rchild);
		}
	}
	
	int Minvalue(TNode *current){
		while(current->lchild!=NULL){
			current=current->lchild;
		}
		return current->data;
	}
	
	int MaxValue(TNode *current){
		while(current->rchild!=NULL){
			current=current->rchild;
		}
		return current->data;
	}
	
	int CountLeafNode(TNode *root){
		if(root==NULL){
			return 0;
		}
		else if(root->lchild==NULL && root->rchild==NULL){
			return 1;	
		}
		else{
			return CountLeafNode(root->lchild)+ CountLeafNode(root->rchild);
		}
	}
	
	int CountNodeWithOneChild(TNode *temp){
		if(temp==NULL){
			return 0;
		}
		else if(temp->lchild!=NULL && temp->rchild==NULL){
			return 1+CountNodeWithOneChild(temp->lchild);
		}
		else if(temp->rchild!=NULL && temp->lchild==NULL){
			return 1+CountNodeWithOneChild(temp->rchild);
		}
		else{
			return CountNodeWithOneChild(temp->lchild)+CountNodeWithOneChild(temp->rchild);
		}
	}
	
	int CountAllNodes(TNode *root){
		int count=0;
		if(root!=NULL){
			count++;
			count=count+CountAllNodes(root->lchild);
			count=count+CountAllNodes(root->rchild);
		}
		return count;
	}
	int SumOfNodes(TNode *root){
		if(root==NULL){
			return 0;
		}
		else{
			return root->data + SumOfNodes(root->lchild) + SumOfNodes(root->rchild);
		}
	}
	int max(int a,int b){
		if(a==b){
			return a;
		}
		else if(a>b){
			return a;
		}
		else{
			return b;
		}
	}
	int min(int a,int b){
		if(a==b){
			return a;
		}
		else if(a<b){
			return a;
		}
		else{
			return b;
		}
	}
	int height(TNode *temp){
		if(temp==NULL){
			return 0;
		}
		else{
			return 1+max(height(temp->lchild),height(temp->rchild));
		}
	}
	int depth(TNode *temp){
		if(temp==NULL){
			return 0;
		}
		if(temp->lchild==NULL && temp->rchild==NULL){
			return 1;
		}
		if(temp->lchild==NULL){
			return depth(temp->rchild)+1;
		}
		if(temp->rchild==NULL){
			return depth(temp->lchild)+1;
		}
		return max(depth(temp->lchild),depth(temp->rchild));
	}
	
};
int main(){
	BST *abc=new BST();
	int arr[5]={15,10,18,16,8};
	for(int i=0;i<5;i++){
		abc->insert(arr[i]);
	}
	abc->Preorder(abc->root);
	abc->del(18);
	cout<<endl;
	abc->Preorder(abc->root);
	cout<<endl;
	//cout<<abc->LF(abc->root);
	
}
