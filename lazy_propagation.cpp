#include<bits/stdc++.h>
using namespace std;
#define ll long long

class ST{
   vector<ll> seg, lazy;

public:
   ST(ll n){
      seg.resize(4*n);
      lazy.resize(4*n);
   }

public:
   void build(ll ind,ll low,ll high,ll arr[]){
      if(low==high){
         seg[ind]=arr[low];
         return;
      }

      ll mid=(low+high)>>1;
      build(2*ind+1,low,mid,arr);
      build(2*ind+2,mid+1,high,arr);
      seg[ind]=seg[2*ind+1]+seg[2*ind+2];
   }
public:
   void update(ll ind,ll low,ll high,ll l ,ll r,ll val){

      // update the previous remaining updates
      // and propagates downwards

      if(lazy[ind]){
         seg[ind]+=(high-low+1)*lazy[ind];

         // propagate the lazy update downwards
         // for the remaining nodes to get upadated

         if(low!=high){  // not a leaf node
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];

         }

         lazy[ind]=0;
      }

      // no overlap we dont do anything and return
      // low high l r        l r low high

      if(high<l || r<low){
         return;
      }

      // complete overlap
      // l low high r

      if(l<=low && r>=high){
         seg[ind]+=(high-low+1)*val;

         if(low!=high){
            lazy[2*ind+1]+=val;
            lazy[2*ind+2]+=val;
         }

         return;
      }

      ll mid=(low+high)>>1;
      update(2*ind+1,low,mid,l,r,val);
      update(2*ind+2,mid+1,high,l,r,val);

      seg[ind]=seg[2*ind+1]+seg[2*ind+2];

   }

public:
   ll query(ll ind,ll low,ll high,ll l ,ll r){

      // update if any updates are remaining
      // as the node will stay fresh and upadted

      if(lazy[ind]){
         seg[ind]+=(high-low+1)*lazy[ind];

         // propagate the lazy update downwards
         // for the remaining nodes to get upadated

         if(low!=high){  // not a leaf node
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];

         }

         lazy[ind]=0;
      }

      if(high<l || low>r){
         return 0;
      }

      if(low>=l && high<=r)
      return seg[ind];

      ll mid=(low+high)>>1;

      ll left=query(2*ind+1,low,mid,l,r);
      ll right=query(2*ind+2,mid+1,high,l,r);

      return left+right;
   }


};

int main(){

   ll n;
   cin>>n;

   ll vec[n];
   for(ll i=0;i<n;i++)
   cin>>vec[i];

   ST st(n);
   st.build(0,0,n-1,vec);

   ll q;
   cin>>q;

   while(q--){
      ll type;
      cin>>type;

      if(type==1){
         ll l,r;
         cin>>l>>r;
         cout<<st.query(0,0,n-1,l,r)<<endl;
      }
      else{
         ll l,r,val;
         cin>>l>>r>>val;

         st.update(0,0,n-1,l,r,val);
      }

   }
  
   return 0;
}
