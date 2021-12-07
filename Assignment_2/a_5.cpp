#include<iostream>
#include<vector>
#include<mpi.h>
#include<cstdlib>
#define N 20
using namespace std;

int main(int argc, char **argv)
{
    vector<int64_t> v,v1,v2;
    int rank,size,c,n,a;
    int64_t b,sum=0;
    cin>>n;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    n=N/size;
    
    srand(time(NULL)+rank);
    for(int i=(rank*n);i<(rank+1)*n;i++){
        c=rand()%10+1;
        v.push_back(c);
    }
    for(int i=(rank*n);i<(rank+1)*n;i++){
        c=rand()%10+1;
        v1.push_back(c);   
    }
    if(rank==(size-1)){
        if(N%size!=0){
            a=N%size;
            for(int i=N-1;i>=N-a;i--){
                c=rand()%10+1;
                v.push_back(c);
            }
            for(int i=N-1;i>=N-a;i--){
                c=rand()%10+1;
                v1.push_back(c);
            }
        }
    }
    // for(int i=0;i<v.size();i++)
    // {
    //     cout<<v[i]<<" ";
    // }
    // cout<<"\n";
    // for(int i=0;i<v1.size();i++)
    // {
    //     cout<<v1[i]<<" ";
    // }
    // cout<<"\n";
    for(int i=0;i<v.size();i++){
        c=v[i]*v1[i];
        sum=sum+c;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    // cout<<"rank is "<<rank<<" sum is "<<sum<<"\n";
    if(rank==0){
        for(int i=1;i<size;i++){
            MPI_Recv(&a,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            v2.push_back(a);
        }
    }
    else{
        MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if(rank==0){
        for(int i=0;i<size-1;i++){
            sum=sum+v2[i];
        }
    cout<<"Sum = "<<sum<<"\n";
    }
    MPI_Finalize();
    return 0;
}