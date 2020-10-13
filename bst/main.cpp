#include<fstream>
#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

ifstream fin("date.in");
ifstream fi("deluxe.in");
ofstream fout("date.out");
int tata[10],n,ko=0;

struct nod2
{
    int info;
    nod2 *urm;
    void creare(int x);
    void inserare(nod2* Q,int d);

}*p,*u, lista[101];

void afisare()
{
    nod2 *q;
    q=p;
    while(q!=NULL)
    {
        fout<<q->info<<" ";
        q=q->urm;
    }
    fout<<endl;
}
//ex4
void creare(int x)
{

    nod2 *q;
        q=new nod2;
        q->info=x;
        q->urm=NULL;
        if(p==NULL)
            p=u=q;
        else
        {
            u->urm=q;
            u=q;
        }
}
void inserare(nod2 *Q, int d)
{
    nod2 *c,*q;
    c=new nod2;
    c->info=d;
    if(Q==p)
    {
        c->urm=p;
        p=c;
    }
    else
    {
        q=p;
        while(q->urm!=Q)
            q=q->urm;
        c->urm=Q;
        q->urm=c;
    }

}

int a[101][101];
void dfs(int k, int pred)
{
    tata[k]=pred;
    for(int i=1;i<=n;i++)
        if(a[k][i] && !tata[i])
        dfs(i,k);
}
//ex2 common parent


int parent(int i1, int i2)
{
    if(i1==NULL || i2==NULL)
        return -1;
    if(tata[i1]==NULL || tata[i2]==NULL)
        return -1;
    if(tata[i1]==tata[i2])
        return tata[i1];
    else
        return 0;
}

//ex3
char* check(int i , int j)
{
    if(i==tata[tata[j]])
        return "is";
    else
        return "is not";
}

/*  Tree node structure */
struct Node
{
   int key;
    struct Node *left, *right;



};

// Returns depth of leftmost leaf.
int findADepth(Node *node)
{
   int d = 0;
   while (node != NULL)
   {
      d++;
      node = node->left;
   }
   return d;
}

/* This function tests if a binary tree is perfect
   or not. It basically checks for two things :
   1) All leaves are at same level
   2) All internal nodes have two children */
bool isPerfectRec(struct Node* root, int d, int level = 0)
{
    // An empty tree is perfect
    if (root == NULL)
        return true;

    // If leaf node, then its depth must be same as
    // depth of all other leaves.
    if (root->left == NULL && root->right == NULL)
        return (d == level+1);

    // If internal node and one child is empty
    if (root->left == NULL || root->right == NULL)
        return false;

    // Left and right subtrees must be perfect.
    return isPerfectRec(root->left, d, level+1) &&
           isPerfectRec(root->right, d, level+1);
}

// Wrapper over isPerfectRec()
bool isPerfect(Node *root)
{
   int d = findADepth(root);
   return isPerfectRec(root, d);
}

/* Helper function that allocates a new node with the
   given key and NULL left and right pointer. */
struct Node *newNode(int k)
{
    struct Node *node = new Node;
    node->key = k;
    node->right = node->left = NULL;
    return node;
}


Node* flipBinaryTree(Node* root)
{

    if (root == NULL)
        return root;
    if (root->left == NULL && root->right == NULL)
        return root;

    Node* flippedRoot = flipBinaryTree(root->left);


    root->left->left = root->right;
    root->left->right = root;
    root->left = root->right = NULL;

    return flippedRoot;
}


void printLevelOrder(Node *root)
{

    if (root == NULL)  return;


    queue<Node *> q;


    q.push(root);

    while (1)
    {

        int nodeCount = q.size();
        if (nodeCount == 0)
            break;


        while (nodeCount > 0)
        {
            Node *node = q.front();
            cout <<(char)(node->key+96-32) << " ";
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
        cout << endl;
    }
}

int main()
{

    /*

        1:A
        2:B
        3:C
        4:D
        5:E
        6:F
        7:G
        */
//ex5
 struct Node* root = NULL;
    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);

    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    if (isPerfect(root))
        printf("Yes\n");
    else
        printf("No\n");

    cout<<endl;
    cout << "Level order traversal of given tree\n";
    printLevelOrder(root);

    root = flipBinaryTree(root);

    cout << "\nLevel order traversal of the flipped"
            " tree\n";
    printLevelOrder(root);


    int x;
    int k;
    int y1,y;
    fi>>n>>k;
    while(fi>>y1>>y && (y1!=0 && y!=0))
    {

        a[y1][y]=a[y][y1]=1;
    }

    dfs(k,1);
    tata[k]=0;
    for(int i=1;i<=n;i++)
        fout<<(char)(tata[i]+96 -32)<<" ";

        int o,p;
        cout<<"read two descendents: ";
        cin>>o>>p;
        cout<<endl;
    fout<<endl;
    fout<<"common ancestor of "<<(char)(o+96 -32)<<" & "<<(char)(p+96 -32)<<" is: "<<(char)(parent(o,p)+96 -32);
    fout<<endl;
    cout<<endl<<"new var for grandparent: ";
    int var1,var2;
    cin>>var1>>var2;
    fout<<"var1 "<<(char)(var1+96-32)<<" "<<check(var1,var2)<<" the gradparent of var2 " <<(char)(var2+96-32)<<endl;
    int kappa[10];
    for(int i=1;i<=10;i++)
        kappa[i]=0;
//nu mi dau seama cum fac sa nu crape
        for(int j=1;j<10;j++)
        {
           int cop=tata[j];
           for(int i=j+1;i<=10;i++)
           {
               if(tata[i]==cop && kappa[cop]==0)
               {
                   creare(cop);
                   kappa[cop]++;
               }
               else
                if(tata[i]==cop&&kappa[cop]!=0)
                {
                    nod2 *d;
                    d->info=cop;
                    inserare(d,cop);
                }
           }
        }
    afisare();


    return 0;
}
