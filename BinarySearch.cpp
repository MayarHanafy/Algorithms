#include <bits/stdc++.h>
using namespace std;

long long l,mid,h;  //l is low. mid is binary search mid. h is high.
long long n;  //number of loops.

bool ok(long long mid){
  for(int i=0;i<n;++i){
    if(/* anything */ 1) return 0;
  }
  return 1;
}

int MaxBS(){
  l=0,h=2e9+100;  //assume high with very large number and low with very small one
   while (l < h)  //loop till they points on same number
   {
    mid=l+(h-l+1)/2;  //get mid of every test
    if (!ok(mid)) //11111100000 monochromatic function
     h = mid-1;
    else
     l = mid;
   }
  return l;
}


int MinBS(){
  l=0,h=2e9+100;  //assume high with very large number and low with very small one
   while (l < h)  //loop till they points on same number
   {
    mid=l+(h-l)/2;  //get mid of every test
    if (!ok(mid)) //00000111111 monochromatic function
     l = mid+1;
    else
     h = mid;
   }
  return h;
}

int main(){
  puts("HELLO BinarySearch");
  return 0;
}
