#include<bits/stdc++.h>

#define fillZero(S, r, t)     for(int i=0;i<r;i++)  for(int j=i;j<t;j++){   S[i][j] = 0;    S[j][i] = 0;    }
#define shuffleIndex(ele, zA, nzA)      for (unsigned int i = 0; i < zA; ++i)   ele.push_back(0);   for (unsigned int i = 0; i < nzA; ++i)  ele.push_back(1); random_shuffle(ele.begin(), ele.end());
#define fillMatrix(ele,row,column,value,m,n)  it = ele.begin(); for(int i=0;i<m;i++){  for(int j=0;j<n;j++){ if(*it)   row.push_back(i); column.push_back(j); value.push_back(rand()%1000); it++;}}
#define printMatrix(row,column,value,ptr,m,n)    for( int i = 0; i < m; i++){   for( int j = 0; j < n; j++) {  if(row[ptr]==i && column[ptr]==j){  cout<<value[ptr]<<" ";ptr++;}else  cout<<"0 ";    }  cout<<'\n'; }

using namespace std;
using namespace std::chrono;



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	freopen("input.txt", "r", stdin);
	auto start = high_resolution_clock::now();

  int m,n,p,ptr;
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
  vector<int> rowA,columnA,valueA;
  vector<int> rowB,columnB,valueB;
  vector<int> ele;
  auto it = ele.begin();
 
  shuffleIndex(ele,zA,nzA)
  fillMatrix(ele,rowA,columnA,valueA,m,n)
  cout<<"A:\n";
  ptr=0;
  printMatrix(rowA,columnA,valueA,ptr,m,n)

  ele.clear();
  shuffleIndex(ele,zB,nzB)
  fillMatrix(ele,rowB,columnB,valueB,n,p)
  cout<<"\nB:\n";
  ptr=0;
  printMatrix(rowB,columnB,valueB,ptr,n,p)

//Multiplication
  vector<int> rowC,columnC,valueC;
  map<pair<int,int>,int> mp;
  map<pair<int,int>,int> :: iterator itr;
  for (int i = 0; i < columnA.size(); i++) {
      for (int j = 0; j < rowB.size(); j++) {
          if(columnA[i] == rowB[j]){
              mp[{rowA[i],columnB[j]}] += valueA[i] * valueB[j];
          }
      }
  }
  itr = mp.begin();
  cout<<"\nC:\n";
  for( int i = 0; i < m; i++){   
      for( int j = 0; j < n; j++) {  
          if(itr->first.first==i && itr->first.second==j){ 
               cout<<itr->second<<" ";itr++;}
          else  cout<<"0 ";    
          }  
      cout<<'\n';
  }
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;
	return 0;
}