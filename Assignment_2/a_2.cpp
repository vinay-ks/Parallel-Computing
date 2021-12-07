#include<iostream>
#include<vector>
#include<mpi.h>
#include<cstdlib>
using namespace std;

int main(int argc, char **argv)
{
    int v[10],v1[10];
    int *p,*q;
    int rank,size;
    int n,a,b,c;
    p=v;
    q=v1;

    n=10;
    // cin>>n;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    srand(time(NULL)+rank);
    for(int i=0;i<n;i++){
        a=rand();
        v[i]=a;
    }
    cout<<"Rank "<<rank<<" value before exchange is-> ";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<"\n";

    if(rank<size)
    {
        b=rank;
        b=(rank+1)%size;
        MPI_Send(&v,n,MPI_INT,b,0,MPI_COMM_WORLD);
        c=(rank+size-1)%size;
        MPI_Recv(&v1,n,MPI_INT,c,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int i=0;i<n;i++){
            v[i]=v1[i];
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    
    cout<<"Rank "<<rank<<" value after exchange is-> ";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<"\n";
    MPI_Finalize();
    return 0;
}