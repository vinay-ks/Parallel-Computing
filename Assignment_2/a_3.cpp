#include<iostream>
#include<vector>
#include<mpi.h>
#include<cstdlib>
#define N 10
using namespace std;

int main(int argc, char **argv)
{
    vector<int> v,v1;
    int rank,size;
    int n,a,sum=0,b,c;
    cin>>n; 

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    a=N/size;

    for(int i=rank*a;i<(rank+1)*a;i++){
        v.push_back(i);
    }
    if(rank==(size-1))
    {
        if(N%size!=0){
            a=N%size;
            for(int i=N-1;i>=N-a;i--){
                sum=sum+v[i];
            }
        }
    }
    for(int i=0;i<v.size();i++){
        sum=sum+v[i];;
    }

    if(rank==0)
    {
        for(int i=1;i<size;i++)
        {
            MPI_Recv(&b,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            v1.push_back(b);
        }
    }
    else{
        MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    
    if(rank==0)
    {
        for(int i=0;i<size-1;i++)
        {
            sum=sum+v1[i];
        }
    cout<<"Sum = "<<sum<<"\n";
    }

    MPI_Finalize();
    return 0;
}