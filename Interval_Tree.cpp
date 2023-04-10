using namespace std;
#include <iostream>
using namespace std;
//in terval low an high
struct interval
{
    int low, high;
};
//node
struct Node{
    interval *i;
    int max;
    bool overlap;   //if we overlaps that node =true
    Node *left;
    Node *right;
};

class IntervalTree {

    Node *root;
 //constructor
public: IntervalTree(Node *r){
        this->root=r;
    }
// create new node
    Node *new_node(interval i) {
        Node *n = new Node;
        n->i = new interval(i);
        n->max = i.high;
        n->overlap=false;
        n->left = NULL;
        n->right = NULL;
        return n;
    };
//add new node in the interval tree
    Node *Add_node(Node *r, interval i) {
        //if root is empty add this in the root
        if (r == NULL)
            return root= new_node(i);
        int l = r->i->low;
        //else if low in the new node < low in the root add the node to the left
        if (i.low < l) {
            if (r->left == NULL)
                r->left = new_node(i);
            //if !empty use recursion function
            else
             root=Add_node(r->left, i);
        }
            //else if low in the new node >= low in the root add the node to the right
        else {
            if (r->right == NULL)
                r->right = new_node(i);
                //if !empty use recursion function
            else
                root=Add_node(r->right, i);

        }
      //update the max num in the node
        if (r->max < i.high)
            r->max = i.high;

        return root;

    }
       //overlap function in the left hand side
    Node *overlap(Node *r, interval i) {
        //if in empty return null
        if (r == NULL) return NULL;

      //return the node that overlaps with
        if ((r->i->low <= i.high) && (i.low <= r->i->high) && r->overlap==false)
        { r->overlap=true;
            return r;  }
//return left node if max>low interval
        if (r->left != NULL && r->left->max >= i.low)
            return overlap(r->left, i);
//return right node if max>low interval
        return overlap(r->right, i);
    }
    //overlap function in the right hand side
    Node *overlap_right(Node *r, interval i) {
        if (r == NULL) return NULL;

        //return the node that overlaps with
        if ((r->i->low <= i.high) && (i.low <= r->i->high) && r->overlap==false)
        { r->overlap=true;
            return r;  }

        //return right node if max>low interval
        if (r->right != NULL && r->right->max >= i.low)
            return overlap(r->right, i);

        //return left node if max>low interval
        return overlap(r->left, i);
    }
    //insert new interval
    void insert(interval i){
        Add_node(root,i);
    }
    //insert again to update max number
    void *insert_again(Node *n){
        if(n==NULL)
            return 0;

        int l= n->i->low;
        int h=n->i->high;
        insert ({l,h});
        //return all tree nodes to insert again and update
        if(n->left!=NULL)
            insert_again(n->left);
        if(n->right!=NULL)
            insert_again(n->right);
    }
    //find the successor
    Node* inorder_successor(Node* temp)
    {
        //loop to find the successor in the ost left right node
        while (temp && temp->left != NULL)
            temp = temp->left;
       //return it
        return temp;
    }
    //delete node after overlaps with it
     Node* delete_node(Node* root, Node *n)
    {
        if (root == NULL)
            return root;
      //find the node we want to delete in the left hand side or in the right and return it
        if ( (n->i->low) < (root->i->low))
            root->left =delete_node(root->left, n);

        else if ((n->i->low) > (root->i->low))
            root->right =delete_node(root->right, n);

         //else when we find the node
        else {
            //if no children delete it
            if ((root->left == NULL && root->right == NULL))
                return NULL;

            //if has one children left or right return the child and delete the node
            else if (root->left == NULL) {
                 Node* temp = root->right;
                root=NULL;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                root=NULL;
                return temp;
            }
            //if has one children two children get inorder successor
            Node* temp =inorder_successor(root->right);

            //swap the inorder successor and the node
            root->i->low = temp->i->low;
            root->i->high = temp->i->high;

            // then delete it
            root->right=delete_node(root->right, n);
        }
        //return the tree
        return root;
    }
   //check if the node which we want to delete if overlaps with any node or not
    void deleteInterval( interval i){
        Node * n =overlap(root, i);
        //if not overlap
     if(n==NULL)
    {cout<< "No Interval overlapping to Delete!!\n";}

//else call the function delete and send the node in it
    if(n!=NULL)
    {  delete_node(root,n);}
//insert again to update the max
        Node *temp=this->root;
        root=NULL;
        insert_again(temp);
    }
//search to find overlaps node
    void SearchInterval(interval i){
        Node* temp = root;
        //in the left and right node
        Node *l=overlap(temp,i);
        Node *r=overlap_right(temp,i);
        if (l == NULL&&r==NULL)
            cout << "No Overlapping Interval\n";
        else{

        while(l!=NULL){
            cout << "Overlaps with l[" << l->i->low << " , " << l->i->high << "]\n";
             l=NULL;
            l=overlap(temp,i);
        }

            while(r!=NULL){
                cout << "Overlaps with r[" << r->i->low << " , " << r->i->high << "]\n";
                r=NULL;
                r=overlap_right(temp,i);
            }
        }
        //insert again to update bool overlap
        root=NULL;
        insert_again(temp);
    }
    //print tree inorder left->root->right
    void inorder(Node *root)
    {
        if (root == NULL) return;

        inorder(root->left);

        cout << "[" << root->i->low << ", " << root->i->high << "]"
             << " max = " << root->max << endl;
        inorder(root->right);
    }
    //print call in order
    void print(){
        inorder(root);
    }
};
int main()
{
    Node *root = NULL;
    IntervalTree t(root);
    t.insert({15,20});                //15
    t.insert({10,30});          //10        //30
    t.insert({5,20});       //5    //12
    t.insert({30,40});   //4
    t.insert({4,20});
    t.insert({3,7});
    t.insert({35,45});
    t.insert({25,45});
    ///////////////////////////////////
    interval x = {29, 11};
    cout<<"\n1-search {29, 11}\n\n";
    t.SearchInterval(x);
    x = {5, 19};
    cout<<"\n2-search {5, 19}\n\n";
    t.SearchInterval(x);
    x = {19, 16};
    cout<<"\n3-search {19, 16}\n\n";
    t.SearchInterval(x);
    x = {39, 31};
    cout<<"\n4-search {39, 31}\n\n";
    t.SearchInterval(x);
    x = {50, 4};
    cout<<"\n5-search {50, 4}\n\n";
    t.SearchInterval(x);
    x = {5, 20};
    cout<<"\n6-search {5,20}\n\n";
    t.SearchInterval(x);
    x = {5, 30};
    cout<<"\n7-search {5,30}\n\n";
    t.SearchInterval(x);
    x = {1, 100};
    cout<<"\n8-search {1,100}\n\n";
    t.SearchInterval(x);
    x = {1, 100};
    cout<<"\n9-search {1,100}\n\n";
    t.SearchInterval(x);
    x = {15, 20};
    cout<<"\n10-search {15,20}\n\n";
    t.SearchInterval(x);
    x = {7, 10};
    cout<<"\n11-search {7,10}\n\n";
    t.SearchInterval(x);
//    cout<<"\nafter delete {19, 16}\n\n";
//    t.deleteInterval(x);
//    t.SearchInterval(x);
    interval y = {44, 36};
    cout<<"\n12-search {44,36}\n\n";
    t.SearchInterval(y);
    t.deleteInterval(y);
    cout<<"\ntree after delete {44, 36}\n\n";
    t.print();
     y = {40, 36};
    cout<<"\n13-search {40,36}\n\n";
    t.SearchInterval(y);
    y = {3, 2};
    cout<<"\n14-search {3,2}\n\n";
    t.SearchInterval(y);
    y = {19, 15};
    cout<<"\n15-search {19,15}\n\n";
    t.SearchInterval(y);
    y = {7, 2};
    cout<<"\n16-search {7,2}\n\n";
    t.SearchInterval(y);
    t.print();


    return 0;
}