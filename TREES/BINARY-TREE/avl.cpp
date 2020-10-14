#include <iostream>

using namespace std;
class Node{
public:

    int data;
    Node *lchild;
    Node *rchild;
};

class AVLTree{
public:
    Node *root,*loc,*ploc;
    bool isEmpty(){
    	
        return root==NULL;
    }

    int Max(int x,int y){
        if(x>y){
            return x;
        }
        else{
            return y;
        }
    }
    int height(Node *temp){
        if(temp==NULL){
            return 0;
        }
        else{
            return 1+Max(height(temp->lchild),height(temp->rchild));
        }
    }

    int LeftHeight(Node *temp){
        temp=temp->lchild;
        return height(temp);
    }
    int RightHeight(Node *temp){
        temp=temp->rchild;
        return height(temp);
    }
    
    int depth(Node *temp,int Dep){
        if(temp==NULL){
            return Dep;
        }
        else{
            int rd=depth(temp->rchild,Dep+1);
            int ld=depth(temp->lchild,Dep+1);
            return Max(rd,ld);
        }
    }
    void PrintPreOrder(Node *temp){
        if(temp!=NULL){
            cout<<temp->data<<",";
            PrintPreOrder(temp->lchild);
            PrintPreOrder(temp->rchild);
        }
    }
    Node *rightRotate(Node *y){
        Node *x = y->lchild;
        Node *T2 = x->rchild;

    // Perform rotation
        x->rchild = y;
        y->lchild = T2;
        return x;
    }
    Node *leftRotate(Node *x){
        Node *y = x->rchild;
        Node *T2 = y->lchild;

        // Perform rotation
        y->lchild = x;
        x->rchild= T2;
        return y;
    }

    int difference(Node *temp){
        return  LeftHeight(temp)-RightHeight(temp);
    }
    
    void BalanceTheTree(Node *prev,Node *temp){
    	
        if(temp==NULL){
            return;
        }

        BalanceTheTree(temp,temp->lchild);
        BalanceTheTree(temp,temp->rchild);
        int left=LeftHeight(temp);
        int right=RightHeight(temp);
        int balance=left-right;
        //cout<<balance<<endl;
        if(balance<-1 && left<right){
            //cout<<"Inside Rotation 1"<<endl;
            if(difference(temp->rchild)>0){
                Node *x=rightRotate(temp->rchild);
                temp->rchild=x;
                Node *y=leftRotate(temp);
                if(prev==NULL){
                    root=y;
                }
                else{
                    prev->lchild=y;
                }
            }
            else{
                Node *y=leftRotate(temp);
                if(prev==NULL){
                    root=y;
                }
                else{
                    prev->rchild=y;
                }
            }
        }
        if(balance>1 && left>right){
            //cout<<"Inside Rotation 2"<<endl;
            if(difference(temp->lchild)<0){
                temp->lchild=leftRotate(temp->lchild);
                Node *x=rightRotate(temp);
                //PrintPreOrder(root);
                if(prev==NULL){
                    root=x;
                }
                else{
                    prev->lchild=x;
                }
            }
            else{
                Node *x =rightRotate(temp);
                if(prev==NULL){
                    root=x;
                }
                else{
                    prev->lchild=x;
                }
            }
        }

    }

    void Insert(int value){
        Node *NN=new Node();
        NN->data=value;
        if(isEmpty()){
            root=NN;
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
                ploc->lchild=NN;
            }
            else{
                ploc->rchild=NN;
            }
        }
        BalanceTheTree(NULL,root);
    }

    void Delete(Node *loc,Node *ploc,int value){
        if(!isEmpty()){
            loc=root;
            ploc=NULL;
            //searches a value
            while(loc!=NULL && loc->data!=value){
                if(value<loc->data){
                    ploc=loc;
                    loc=loc->lchild;
                }
                else{
                    ploc=loc;
                    loc=loc->rchild;
                }
            }
            //if value not found
            if(loc==NULL){
                cout<<"Value Not Found"<<endl;
                return;
            }
            //if value found
            else if(loc->data==value){
                    //if value is at leaf node
                if(loc->lchild==NULL && loc->rchild==NULL){
                    if(loc!=root){
                        if(ploc->lchild==loc){
                            ploc->lchild=NULL;
                            delete loc;
                        }
                        else{
                            ploc->rchild=NULL;
                            delete loc;

                        }
                    }
                    else{

                        root=NULL;
                        delete loc;

                    }

                }
                //if node contains only left subtree
                else if(loc->lchild!=NULL && loc->rchild==NULL){
                    if(loc!=root){
                        if(ploc->lchild==loc){
                            ploc->lchild=loc->lchild;
                            delete loc;
                        }
                        else{
                            ploc->rchild=loc->lchild;
                            delete loc;
                        }
                    }
                    else{
                        root=loc->lchild;
                        delete loc;
                    }

                }
                //if node contain only right subtree
                else if(loc->rchild!=NULL && loc->lchild==NULL){
                    if(loc!=root){
                        if(ploc->lchild==loc){
                            ploc->lchild=loc->rchild;
                            delete loc;
                        }
                        else{
                            ploc->rchild=loc->rchild;
                            delete loc;
                        }
                    }
                    else{
                        root=loc->rchild;
                        delete loc;
                    }

                }
                    //if node has both left and right child
                else if(loc->lchild!=NULL && loc->rchild!=NULL){
                    Node *loc2=loc->rchild;
                    while(loc2->lchild!=NULL){
                        loc2=loc2->lchild;
                    }
                    int Copy=loc2->data;
                    Delete(root,NULL,Copy);
                    if(loc==root){
                        root->data=Copy;
                        loc=root;
                    }
                    else{
                        loc->data=Copy;
                    }
                }
            }
            BalanceTheTree(NULL,root);
        }
    }
};


int main()
{
    AVLTree *A;
    A=new AVLTree();
    A->Insert(9);
    A->Insert(5);
    A->Insert(10);
    A->Insert(0);
    A->Insert(6);
    A->Insert(11);

    A->Insert(-1);
    A->Insert(1);
    A->Insert(2);
    cout<<endl;
    A->PrintPreOrder(A->root);
/*    A->Delete(A->root,NULL,-1);
    cout<<endl;
    A->PrintPreOrder(A->root);*/

    return 0;
}

