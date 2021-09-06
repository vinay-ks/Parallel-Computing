#include<bits/stdc++.h>

#define fillZero(S, r, t)     for(int i=0;i<r;i++)  for(int j=i;j<t;j++){   S[i][j] = 0;    S[j][i] = 0;    }
#define shuffleIndex(ele, zA, nzA)      for (unsigned int i = 0; i < zA; ++i)   ele.push_back(0);   for (unsigned int i = 0; i < nzA; ++i)  ele.push_back(1); random_shuffle(ele.begin(), ele.end());
#define fillMatrix(ele,A,m,n)  it = ele.begin(); for(int i=0;i<m;i++){  for(int j=0;j<n;j++){ if(*it) A[i][j] = rand()%1000; it++;}}
#define printMatrix(A,m,n)    for( int i = 0; i < m; i++){   for( int j = 0; j < n; j++)  cout<<A[i][j]<<'\t';  cout<<'\n'; }


using namespace std;
using namespace std::chrono;



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	freopen("input.txt", "r", stdin);
	auto start = high_resolution_clock::now();

  int m,n,p;
  double spA,spB;
	cin>>m>>n>>p>>spA>>spB;
 
  srand(time(0));
 
 // Calculating the number of zero and non zero elements in the Arrays A and B
  int tA = m*n;
  int nzA = ceil(spA*tA);
  int zA = tA - nzA;
  int tB = n*p;
  int nzB = ceil(spB*tB);
  int zB = tB - nzB;

//Generating the elements to fill up the matrix
  int  A[m][n],B[n][p];
 
  fillZero(A,m,n)
  fillZero(B,n,p)
 

  vector<int> ele;
  auto it = ele.begin();
 
  shuffleIndex(ele,zA,nzA)
  fillMatrix(ele,A,m,n)
  cout<<"A:\n";
  printMatrix(A,m,n)

  ele.clear();
  shuffleIndex(ele,zB,nzB)
  fillMatrix(ele,B,n,p)
  cout<<"\nB:\n";
  printMatrix(B,n,p)

//Multiplication
  int C[m][p];
  for (int i = 0; i < m; i++) {
      for (int j = 0; j < p; j++) {
          C[i][j] = 0;
          for (int k = 0; k < n; k++)
              C[i][j] += A[i][k] * B[k][j];
      }
  }
  cout<<"\nC:\n";
  printMatrix(C,m,p)

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;
	return 0;
}