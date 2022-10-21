/*Since we are solving this using Dynamic Programming, we know that Dynamic Programming approach contains sub-problems.

Here after reaching ith node finding remaining minimum distance to that ith node is a sub-problem.

If we solve recursive equation we will get total (n-1) 2(n-2)  sub-problems, which is O (n2n).

Each sub-problem will take  O (n) time (finding path to remaining (n-1) nodes).

Therefore total time complexity is O (n2n) * O (n) = O (n22n)

Space complexity is also number of sub-problems which is O (n2n)*/

#include<iostream>

using namespace std;

int ary[10][10],completed[10],n,cost=0;

void takeInput()
{
    int i,j;

    cout<<"Enter the number of villages: ";
    cin>>n;

    cout<<"\nEnter the Cost Matrix\n";

    for(i=0;i < n;i++)
    {
        cout<<"\nEnter Elements of Row: "<<i+1<<"\n";

        for( j=0;j < n;j++)
            cin>>ary[i][j];

        completed[i]=0;
    }
}

int least(int c)
{
    int i,nc=999;
    int min=999,kmin;

    for(i=0;i < n;i++)
    {
        if((ary[c][i]!=0)&&(completed[i]==0))
            if(ary[c][i]+ary[i][c] < min)
            {
                min=ary[i][c]+ary[c][i];;
                kmin=ary[c][i];
                nc=i;
            }
    }

    if(min!=999)
        cost+=kmin;

    return nc;
}

void mincost(int city)
{
    int i,ncity;

    completed[city]=1;

    cout<<city<<"--->";
    ncity=least(city);

    if(ncity==999)
    {
        ncity=0;
        cout<<ncity+1;
        cost+=ary[city][ncity];

        return;
    }

    mincost(ncity);
}

int main()
{
    takeInput();

    cout<<endl<<"2. Ruta a seguir por el personal que reparte correspondencia, considerando inicio y fin en al misma colonia."<<endl;
    cout<<"\n\nEl camino pasando por todas las colonias y de regreso es:\n";
    mincost(0); //passing 0 because starting vertex

    cout<<"\n\nEl costo minímo es: "<<cost<<endl;

    return 0;
}