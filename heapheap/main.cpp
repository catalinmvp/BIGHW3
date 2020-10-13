#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");
template<typename T> class Heap {
    public:
        T *H;
        int currentDim, maxDim;

        Heap(int maxDim) {
            this->maxDim = maxDim;
            H = new T[this->maxDim];
            currentDim = -1;
        }

        void insertElement(T x) {
            if (currentDim == maxDim-1) {
                cout<< "Error!"<<endl;
                return;
            }
            currentDim++;
            H[currentDim] = x;
            filterUp(currentDim);
       }

	T peek() {
            if (currentDim == -1) {
                cout<< "Error!"<<endl;
                T x;
                return x;
            }

            return H[0];
        }


T deleteElement() {
            if (currentDim == -1) {
                cout<< "Error!"<<endl;
                T x;
                return x;
            }

            T minValue = H[0];
            H[0] = H[currentDim];
            currentDim--;
     if (currentDim > 0)
                filterDown();

            return minValue;
        }

        void filterUp(int l) {
            int parent;
            T vaux;

            parent = (l-1) / 2;
           while (l > 0 && H[parent] > H[l]) {
                vaux = H[parent];
                H[parent] = H[l];
                H[l] = vaux;

                l = parent;
                parent = (l-1) / 2;
            }
        }

 void filterDown() {
           int l = 0;
            T vaux;

            while (1) {
                if (2 * l + 1 > currentDim) {
                    if (2 * (l+1) > currentDim)
                        break;
                     else if (H[2 *(l+1)] < H[l]) {
                        vaux = H[2 * (l+1)];
                        H[2 * (l+1)] = H[l];
                        H[l] = vaux;
                        l = 2 * (l+1);
                    }
                    else
                        break;
                }
                else {

                    if (H[2 * (l+1) ] <= H[2 * l + 1] && H[2 * (l+1) ] < H[l]) {
                        vaux = H[2 * (l+1)];
                        H[2 * (l+1)] = H[l];
						H[l] = vaux;
                        l = 2 * (l+1);
                    }
                    else
                    if (H[2 * l + 1] <= H[2 * (l+1)] && H[2 * l + 1] < H[l]) {
                        vaux = H[2 * l + 1];
                        H[2 * l + 1] = H[l];
                        H[l] = vaux;
                        l = 2 * l + 1;
                    }
                    else
                        break;
                }
            }
        }

int parent(int poz)
{
    return (poz-1)/2;
}
int leftSub(int poz)
{
    return 2*(poz+1);
}
int rightSub(int poz)
{
    return 2*poz+1;
}

int getmax(int indx)
{
   int mazh=0;
   if(mazh<=H[leftSub(indx)])
        {
            mazh=H[leftSub(indx)];
            return mazh;
        }
        else getmax(parent(indx));
}
};
Heap<int> heap(100);
bool check(int v[10], int dim)
{
    //9 elem, 3 niv= nr aparitii max
    int cont1=0,cont2=0;
    fout<<endl;
    for(int i=dim-1;i>=0;i--)
    {
        fout<<v[i]<<" ";
        if(heap.leftSub(i)==v[i]    &&  heap.rightSub(i)==v[i])
        {
            return false;
            break;
        }

        if(heap.leftSub(i)!=v[i]    &&  heap.rightSub(i)!=v[i])
        {
            cout<<"cioc : "<<v[heap.leftSub(i)]<<" "<<v[heap.rightSub(i)];
            return false;
            break;
        }

        if(heap.leftSub(i)==NULL    &&  heap.rightSub(i)==NULL)
        {
            cont1++;
        }

        if((heap.leftSub(i)!=NULL   &&   heap.rightSub(i)!=NULL)  &&  heap.parent(i)!=NULL)
            cont2++;

    }
    if(cont1==4 && cont2==2)
        return true;

        cout<<endl;

}


int secondwinner(int v[10],int dim)
{
    for(int i=0;i<dim;i++)
    {

        if(heap.leftSub(i)==NULL    &&  heap.rightSub(i)==NULL)
        {
            if(v[heap.rightSub(heap.parent(i))]==v[dim])
                return v[i];
        }
    }
}

void dislp(int v[10],int dim)
{
    int maxi=v[dim-1];
    int kappa[10];
    for(int j=0;j<=9;j++)
        kappa[j]=0;
    kappa[maxi]++;
    int c=1;
    fout<<endl;
    for(int i=dim-1;i>=0;i--)
    {

        if(v[i]!=maxi)
        {
             kappa[v[i]]++;

        }
    }
    for(int i=dim-1;i>=0;i--)
    {

        if(v[i]!=maxi)
        {

           if(kappa[v[i]]>0)
            fout<<endl<<"the loser of round "<<kappa[v[i]]<<" is "<<v[i];
            else
                if(kappa[v[i]]>1)
                    fout<<endl<<"the loser of round "<<kappa[v[i]]<<" is "<<v[i];
            maxi=v[i];
        }
    }
}
int main()
{
    int vec[10];
    int n,dim=0;

    while(fin>>n&&n!=0)
    {
        heap.insertElement(n);
        dim++;
    }


    int i=0;
    int coop=dim;
    while(dim--)
    {
        fout<<heap.peek()<<" ";
        vec[i++]=heap.peek();
        heap.deleteElement();

    }

    for(int i=0;i<coop;i++)
        cout<<vec[i]<<" ";
    fout<<endl;
    fout<<check(vec,coop);
     fout<<endl;
    fout<<"second winner is: "<<secondwinner(vec,coop);
    dislp(vec,coop);
    cout<<endl;
    int p=vec[coop-1];
    int conto=0;
    for(int i=0;i<coop;i++)
    {
        if(vec[i]==p)
            conto++;
    }

    Heap<int> heap1(100);

    for(int i=0;i<coop-3;i++)
    {
        heap1.insertElement(vec[i]);
    }

    fout<<endl<<"loser tree: "<<endl;
    int psf=coop-3;
    int mini=999,maxi=0;
    while(psf--)
    {
        if(mini>=heap1.peek())
            mini=heap1.peek();
        if(maxi<=heap1.peek())
            maxi=heap1.peek();
        fout<<heap1.deleteElement()<<" ";
    }

    fout<<endl<<"winner is "<<maxi<<" and the loser "<<mini;

}
