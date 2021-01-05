#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NMAX 20 //n
#define VEX 1025 //the number of vertices 2^n

int g[VEX][VEX],gt[VEX][NMAX+1],gg[VEX][NMAX+1],b[VEX],v[VEX],vd[VEX],dd[VEX],vj[VEX],f[NMAX],d[VEX][VEX];
int gg0[VEX][NMAX+1],vd0[VEX],eb[VEX],ee[VEX],eb0[VEX],ee0[VEX];
int erroe[VEX];
int ff[VEX];
int gg0[VEX][NMAX+1],vd0[VEX];
int gg1[VEX][NMAX+1],vd1[VEX];
int n,q0,q,n0,k0,fn,go,no;
int efn,vfn;
FILE *pfile;
char ma[10];

void TestCl(int v0,int vn)  // find the path 
{
int i,j,k,ii,cl,l,cl0,cl1,v1,n1,j1;


    if(go==1){ cl0=4; cl1=2; n1=n-2*fn; } //hypercube Qn
	if(go==3){ cl0=d[v0][vn]+4; cl1=1; n1=n-vfn-1; } // crossed cubes CQn
	if(go==4){ cl0=d[v0][vn]+5; cl1=1; n1=n-vfn-1; } // locally twisted cubes LTQn
	if(go==5){ cl0=d[v0][vn]+5; cl1=1; n1=n-vfn-1; } // 0-mobius cubes 0MQn
	if(go==6){ cl0=5; cl1=1; n1=n-fn-1; }  // 1-mobius cubes 1MQn
	if(go==7){ cl0=n-fn-1;cl1=1; n1=n-fn-1;} // augmented cubes AQn
	if(go==8){ cl0=3;cl1=1; n1=n-fn-1;} //twisted cubes TQn

	       	 
	for(cl=cl0;cl<=n1;cl+=cl1)
	{		
	    for(i=1;i<=n;i++)b[i]=0; // b[i] denote the if the vertex i has been used
		k=v0; v[1]=k; b[k]=1; l=1; b[vn]=1;
l0:		l++; j=0;
l1:		j++; 
		v1=v[l-1];
		if(j>vd[v1])goto l2;
		k=gg[v1][j]; //gg[v1][j] is the j-th adjacent vertex of v1
		if(b[k])goto l1; // If b[k]=1, then the vertex k has been used and need to find the next non-used vertex.
	//  if(n<0) 
	//	{
	//		v[l]=k;
	//		for(ii=1;ii<=l;ii++)
	//		{
	//			for(i=1;i<=k0;i++)printf("%2d ",gt[v[ii]][i]); printf("  ");
	//		}
	//		printf("\n");
	//		getchar();
	//	}  

		if(l<cl)
		{
			b[k]=1;	v[l]=k; vj[l]=j; goto l0;
		}
		
l4:		for(i=1;i<=vd[k];i++) if(gg[k][i]==vn) break;
		if(i<=vd[k])// find the path
		{
			v[l]=k;
			if(fn)//
			{
				printf("begin:%d fault:",v0);
				for(i=1;i<=vfn;i++)// faulty vertices
					printf("%2d ",f[i]); 
				for(i=1;i<=efn;i++) printf("%2d-%2d ",eb0[ff[i]],ee0[ff[i]]); //faulty edges
				printf("length:%2d  end:%d\n",cl,vn);
				for(i=1;i<=cl;i++)
				{
					printf("%2d ",v[i]); printf("  "); 
			//		for(j=1;j<=k0;j++)printf("%2d ",gt[v[i]][j]); printf("  ");
				}
				printf("%2d ",vn);
				printf("\n");
			//	getchar();						
                                fprintf(pfile,"Faults:");
				for(i=1;i<=vfn;i++)// faulty vertices
				{
					for(j=1;j<=k0;j++) fprintf(pfile,"%d ",gt[f[i]][j]); fprintf(pfile,"  ");
				}
				for(i=1;i<=efn;i++)
				{
					for(j=1;j<=k0;j++) fprintf(pfile,"%d ",gt[eb0[ff[i]]][j]); fprintf(pfile,"- ");
					for(j=1;j<=k0;j++) fprintf(pfile,"%d ",gt[ee0[ff[i]]][j]); fprintf(pfile,"  ");
				}
				fprintf(pfile,"Start:%d  End:%d",v0,vn); fprintf(pfile,"  ");
				fprintf(pfile,"Length:%2d ",cl);	
				fprintf(pfile,"%2d   ",cl);
				fprintf(pfile,"\n Path:");
				for(i=1;i<=cl;i++)// the vertices in path
				{
					fprintf(pfile,"%2d ",v[i]); printf("  ");
				//	for(j=1;j<=k0;j++)fprintf(pfile,"%2d ",gt[v[i]][j]); fprintf(pfile,"  ");
				}
				fprintf(pfile,"%2d ",vn);
				fprintf(pfile,"\n");
			}
			continue;
		}
		goto l1;
l2:		l--;
		if(l>1)
		{
			k=v[l]; b[k]=0; j=vj[l]; goto l1; 
		}

l5:		for(i=1;i<=fn;i++)//Path not found
		{
			for(j1=1;j1<=k0;j1++)printf("%d ",gt[f[i]][j1]); fprintf(pfile,"  "); 
		}
		printf("Not found：  Start:%d  End:%d",v0,vn);
		printf("cl=%2d\n",cl);
		fprintf(pfile,"  Start:%d  End:%d",v0,vn);
		fprintf(pfile,"cl=%2d\n",cl);
		getchar();
	}
}

void Test(int vvfn) //vvfn: the faulty vertices, fn-vvfn: the faulty edges
{
//int i,j,k,l,i1,ii,j1,j2,m, eb0,ee0;
int i,j,k,l,i1,ii,j1,j2,x,y,m;
int jj,ll,jj1,jj2,mm1,lls,ww,mm2,eb3,ee3;

	l=0; f[0]=0;   vfn=vvfn; efn=fn-vfn;//vfn: the faulty vertices，efn: the faulty edges

l0: l++; j=f[l-1];//f[] store the faulty elements 

l1: j++; if(j>n)goto l2;

	f[l]=j;

	if(l<vfn)goto l0;

	for(i=1;i<=n;i++) //restore 
	{
		vd[i]=vd0[i]; for(j1=1;j1<=vd[i];j1++)gg[i][j1]=gg0[i][j1];
	}
	for(i=1;i<=vfn;i++)
	{
		k=f[i];

		for(i1=1;i1<=vd[k];i1++)// delete vertices
		{
			ii=gg[k][i1];
			for(j1=1;j1<=vd[ii];j1++)
			{
				if(gg[ii][j1]==k)
				{
					for(j2=j1;j2<vd[ii];j2++)gg[ii][j2]=gg[ii][j2+1]; vd[ii]--;
					break;
				}
			}
		}
		vd[k]=0;
	}

	for(i=1;i<=n;i++)//Backup
	{
		vd1[i]=vd[i]; for(j1=1;j1<=vd[i];j1++)gg1[i][j1]=gg[i][j1];
	}
	
	if(n<0)// the graph after delete vertices
	{
		for(i=1;i<=n;i++)
		{
			printf("  i=%2d ",i);
			for(j1=1;j1<=vd[i];j1++)printf("%2d ",gg[i][j1]);
			printf("\n");
		}
//		getchar();
	}

	ll=0; ff[0]=0;
ll0: ll++; jj=ff[ll-1];//ll:the number of faulty edges
	
ll1: jj++; 
	 for(i=1;i<=vfn;i++)
	 {
		 if(eb0[jj]==f[i]||ee0[jj]==f[i])
			 goto ll1;
	 }
	
	 if(jj>q0)goto ll2;// j>q0 unsatisfied condition n0=2
	
	ff[ll]=jj;
	
	if(ll<efn)goto ll0;// find the required number of faulty edge

	for(i=1;i<=n;i++)//initialization
	{
		vd[i]=vd1[i]; 
		for(j1=1;j1<=vd[i];j1++)
			gg[i][j1]=gg1[i][j1];
	}
	
	for(i=1;i<=efn;i++)// modify
	{
		k=ff[i]; x=eb0[k]; y=ee0[k];
		
		for(jj1=1;jj1<=vd[x];jj1++) //find y is which adjacent vertex of x
			if(gg[x][jj1]==y)
				break;
		for(jj2=jj1;jj2<vd[x];jj2++)//delete edge
			gg[x][jj2]=gg[x][jj2+1];
		vd[x]--;	
		
		for(jj1=1;jj1<=vd[y];jj1++) // delete the faulty edge in y
			if(gg[y][jj1]==x)
				break;
		for(jj2=jj1;jj2<vd[y];jj2++)
			gg[y][jj2]=gg[y][jj2+1]; 
		vd[y]--;
	}

//	for(i=1;i<=fn;i++)printf("%2d ",f[i]); printf("\n"); //getchar();
	if(n<0)
	{
		for(i=1;i<=n;i++)
		{
			printf("  i=%2d ",i);
			for(j1=1;j1<=vd[i];j1++)printf("%2d ",gg[i][j1]);
			printf("\n");
		}
		getchar();
	}

	q=0;
	for(i=1;i<=n;i++)//Compressed storage
	{
		for(j=1;j<=vd[i];j++)
		{
			k=gg[i][j]; if(k<=i)continue;// Only save adjacent nodes larger than this node
			q++; eb[q]=i; ee[q]=j;
		}
	}

	for(i=1;i<=n;i++)
	 {	
		for(j=1;j<=n;j++)
			if(i==j)
				d[i][j]=0;
			else
			{
				for(i1=1;i1<=vd[i];i1++)
					if(j==gg[i][i1])
					{	d[i][j]=1; break;}

				if(d[i][j]!=1)			 
					d[i][j]=VEX;
			}
	 }	
	 for(m=1;m<=n;m++)
     for(i=1;i<=n;i++)
     for(j=1;j<=n;j++)
	 {	if(d[i][m]+d[m][j]<d[i][j])
			d[i][j]=d[i][m]+d[m][j];
	 }

	eb3=0; ee3=0;
	for(k=1;k<=n;k++) //weak vertex pair
	{
		if(vd[k]!=2)continue;
		eb3=gg[k][1]; ee3=gg[k][2]; 
		printf("eb3=%d ee3=%d\n",eb3,ee3); break;
	}
   for(i=1;i<=n;i++)
	{
//		i=1;
		if(vd[i]==0)
			continue;
		for(j=i+1;j<=n;j++)
		{	
			
			if(vd[j]==0)
				continue;
			if((i==eb3)&&(j==ee3))continue; //weak vertex pair
			if((i==ee3)&&(j==eb3))continue;	    
			TestCl(i,j);
		}
	}

  	ll++;
ll2:ll--; 
	if((ll>1)&&(efn>0)||(ll==1)&&(go>1)&&(ff[1]<=q0-efn+1)&&(efn>0))//(l>1)||(l==1)&&(go>1)&&(f[1]<=q0-fn+1)??????????????????????????
	{ jj=ff[ll]; goto ll1; }

    l++;
l2: l--; 
	if((l>1)&&(vfn>0)||(l==1)&&(go>1)&&(f[1]<=n-vfn+1)&&(vfn>0))
	{ j=f[l]; goto l1; }
}




void Get_Test_Graph() // draw the graph
{
int i,j,k,l,j1,j2,d;
//Q4    go=1;   n0=1;k0=4;
//CQ4   go=3;   n0=1;k0=4;
//LTQ4  go=4;   n0=1;k0=4;
//0MQ4  go=5;   n0=1;k0=4;
//1MQ4  go=6;  n0=1;0=4;
//TQn   go=8;

	q0=0;
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)g[i][j]=0;

	for(i=1;i<=n;i++)v[i]=0;
	l=0; k=0;
l0:	l++; j=0; if(go<10)j=-1;
l1: j++; if(j>n0)goto l2;
	if(v[j]&&(go>=10))goto l1;
	f[l]=j; v[j]=1;
	if(l<k0)goto l0;
	k++; for(j=1;j<=k0;j++)gt[k][j]=f[j];
	l++;
l2: l--; if(l>=1){ j=f[l]; v[j]=0; goto l1; }
	if(q<0)
	{  
		printf("n0=%d k0=%d\n",n0,k0);
		for(i=1;i<=k;i++)
		{ 
			printf("  i=%2d ",i);
			for(j=1;j<=k0;j++)printf("%2d ",gt[i][j]);
			printf("\n");
		}
//		getchar();
	}
	if((go<=2)||(go==8))
	{
		vd[1]=0;
		for(i=1;i<=k;i++)
		{
			d=0;
			for(j=1;j<=k;j++)
			{
				if(j==i)continue;
				if((go==2)&&(i+j==n+1)){ gg[i][++d]=j; q0++; }
				else
				{
					for(j1=1;j1<=k0;j1++)
					{
						for(j2=1;j2<=k0;j2++)if((j2!=j1)&&(gt[i][j2]!=gt[j][j2]))break;
						if(j2>k0)break;
					}
					if(j1<=k0){	gg[i][++d]=j; q0++; }
				}
			}
			vd[i]=d;
		}
		if(go==8)
		{
			for(i=1;i<=n;i++)
			{
				for(j1=1;j1<=vd[i];j1++)
				{
					j=gg[i][j1]; 
					for(j2=1;j2<=k0;j2++)if(gt[i][j2]!=gt[j][j2])break;
					if(j2%2==k0%2)continue;
					if(j2==1)continue;
					l=0; for(k=j2+1;k<=k0;k++)l+=gt[i][k];
					if(l%2)continue;
					for(l=1;l<=n;l++)
					{
						for(k=1;k<=k0;k++)if((k!=j2-1)&&(k!=j2)&&(gt[i][k]!=gt[l][k])||((k==j2-1)||(k==j2))&&(gt[i][k]==gt[l][k]))break;
						if(k<=k0)continue;
						gg[i][j1]=l; 
	//					printf("i=%d j=%d l=%d\n",i-1,j-1,l-1);
						break;
					}
				}
			}
		}
	}
	else if(go==3)
	{
		for(i=1;i<=k;i++)
		{
			d=0;
			for(j=1;j<=k;j++)
			{
				if(i==j)continue;
				for(j1=1;j1<=k0;j1++)
				{
					if(gt[i][j1]==gt[j][j1])continue;
					if(((k0+1-j1)%2==0)&&(gt[i][j1+1]!=gt[j][j1+1]))continue;
					for(j2=1;j2<j1;j2++)if(gt[i][j2]!=gt[j][j2])break;
					if(j2<j1)continue;
					for(j2=k0;j2>j1+1;j2-=2)
					{
						if((gt[i][j2]!=gt[j][j2])||(gt[i][j2-1]!=(1-gt[j][j2])*gt[j][j2-1]+(1-gt[j][j2-1])*gt[j][j2]))break;
					}
					if(j2<=j1+1){ gg[i][++d]=j; q0++; }
				}
				
			}
			vd[i]=d;
		}
	}
	else if(go==4)
	{
		for(i=1;i<=n;i++)vd[i]=0;
		for(i=1;i<=k;i++)
		{
			for(j=1;j<=k;j++)
			{
				if((i-1)/4==(j-1)/4)
				{
					if((i%4<=1)&&(j%4>=2)||(i%4>=2)&&(j%4<=1))gg[i][++vd[i]]=j; q0++; 
				}
				else
				{
					for(j1=1;j1<=k0-2;j1++)
					{
						if(gt[i][j1]==1)
						{
							if(gt[j][j1]!=0)continue;
							if((gt[j][j1+1]+gt[j][k0])%2!=gt[i][j1+1])continue;
							for(j2=1;j2<=k0;j2++)if(((j2<j1)||(j2>j1+1))&&(gt[i][j2]!=gt[j][j2]))break;
							if(j2<=k0)continue;
							gg[i][++vd[i]]=j; q0++; 
						}
						else if(gt[j][j1]==1)
						{
							if(gt[i][j1]!=0)continue;
							if((gt[i][j1+1]+gt[i][k0])%2!=gt[j][j1+1])continue;
							for(j2=1;j2<=k0;j2++)if(((j2<j1)||(j2>j1+1))&&(gt[j][j2]!=gt[i][j2]))break;
							if(j2<=k0)continue;
							gg[i][++vd[i]]=j; q0++; 
						}
					}
				}				
			}
		}
	}
	else if((go==5)||(go==6))
	{
		for(i=1;i<=n;i++)vd[i]=0;
		for(i=1;i<=k;i++)
		{
			for(j=1;j<=k;j++)
			{
				for(j1=1;j1<=k0;j1++)
				{
					if(gt[i][j1]==gt[j][j1])continue;
					if(j1==1)
					{
						for(j2=j1+1;j2<=k0;j2++)
						{
							if((go%2==1)&&(gt[i][j2]!=gt[j][j2]))break;
							if((go%2==0)&&(gt[i][j2]==gt[j][j2]))break;
						}
						if(j2<=k0)continue;

					}
					else
					{
						for(j2=1;j2<j1;j2++)
						{
							if(gt[i][j2]!=gt[j][j2])break;
						}
						if(j2<j1)continue;
						for(j2=j1+1;j2<=k0;j2++)
						{
							if((gt[i][j1-1]==0)&&(gt[i][j2]!=gt[j][j2]))break;
							if((gt[i][j1-1]==1)&&(gt[i][j2]==gt[j][j2]))break;
						}
						if(j2<=k0)continue;
					}
					gg[i][++vd[i]]=j; q0++; 
				}				
			}
		}
	}
	else if(go==7)
	{
		for(i=1;i<=n;i++)vd[i]=0;
		for(i=1;i<=k;i++)
		{
			for(j=1;j<=k;j++)
			{
				for(j1=1;j1<=k0;j1++)
				{
					if(gt[i][j1]==gt[j][j1])continue;
					if(j1==1)
					{
						for(j2=j1+1;j2<=k0;j2++)
						{
							if(gt[i][j2]!=gt[j][j2])break;
						}
						if(j2<=k0)
						{
							for(j2=j1+1;j2<=k0;j2++)
							{
								if(gt[i][j2]==gt[j][j2])break;
							}
						}
						if(j2<=k0)continue;

					}
					else
					{
						for(j2=1;j2<j1;j2++)
						{
							if(gt[i][j2]!=gt[j][j2])break;
						}
						if(j2<j1)continue;
						for(j2=j1+1;j2<=k0;j2++)
						{
							if(gt[i][j2]!=gt[j][j2])break;
						}
						if(j2<=k0)
						{
							for(j2=j1+1;j2<=k0;j2++)
							{
								if(gt[i][j2]==gt[j][j2])break;
							}
						}
						if(j2<=k0)continue;
					}
					gg[i][++vd[i]]=j; q0++; 
				}				
			}
		}
	}

	for(i=1;i<=n;i++)
	{
		vd0[i]=vd[i]; for(j=1;j<=vd[i];j++)gg0[i][j]=gg[i][j];
	}

	q0=0;// the total number of edges
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=vd[i];j++)
		{
			k=gg[i][j]; if(k<=i)continue;
			q0++; eb0[q0]=i; ee0[q0]=k;//eb: the start vertex of edge q0，ee: the end vertex of edge q0;
		}
	}
//   if(q<0) // output the graph
	{ 
		printf("n=%d q0=%d\n",n,q0); 
		for(i=1;i<=n;i++)
		{
			printf("  i=%2d ",i); 
			for(j=1;j<=k0;j++)printf("%2d ",gt[i][j]); printf("  ");
			for(j=1;j<=vd[i];j++)printf("%2d ",gg[i][j]);
			printf("\n");
		}
		for(i=1;i<=n;i++)
		{
			fprintf(pfile,"  i=%2d ",i);
			for(j=1;j<=k0;j++)fprintf(pfile,"%2d ",gt[i][j]); fprintf(pfile,"  ");
			for(j=1;j<=vd[i];j++)fprintf(pfile,"%2d ",gg[i][j]);
			fprintf(pfile,"\n");
		}
		//getchar();
	}
}



void main()
{
	int i,j;
	no=0;                          //no=2    
//Qn
//	go=1;
//	n=8; n0=1; k0=3; fn=k0-2;      //fn<=1    fn=2   c4??                      fn<=1    fn=2   c4??
//	n=16; n0=1; k0=4; fn=k0-1;     //fn<=3    fn=4   c6??                      fn<=3    fn=4   c6??
//	n=32; n0=1; k0=5; fn=2*k0;     //fn<=10   fn=11  c10??                     fn<=10   fn=11  c10??

//CQn
//	go=3;
//	n=8; n0=1; k0=3; fn=k0-2;      //fn<=1    fn=2   c6??                      fn<=1    fn=2   c6??  
//	n=16; n0=1; k0=4; fn=k0-2;     //fn<=2    fn=3   c13??                     fn<=2    fn=3   c13??
//	n=32; n0=1; k0=5; fn=k0-2;     //fn<=4    fn=5   c27??                     fn<=3    fn=4   c28??///////////////////////////// 
//	n=64; n0=1; k0=6; fn=0;
//	n=512; n0=1; k0=9; fn=k0-2;
//LTQn
//	go=4;
//	n=8; n0=1; k0=3; fn=k0-2;      //fn<=1    fn=2   c6??                      fn<=1    fn=2   c6?? 
//	n=16; n0=1; k0=4; fn=k0-2;     //fn<=2    fn=3   c13??                     fn<=2    fn=3   c13?? 
//	n=32; n0=1; k0=5; fn=k0-2;     //fn<=4    fn=5   c27??                     fn<=3    fn=4   c28??///////////////////////////// 
//0MQn
//	go=5;
//	n=8; n0=1; k0=3; fn=k0-2;      //fn<=1    fn=2   c5??                      fn<=1    fn=2   c5??  
//	n=16; n0=1; k0=4; fn=k0-2;     //fn<=2    fn=3   c13??                     fn<=2    fn=3   c13?? 
//	n=32; n0=1; k0=5; fn=k0-2;       //fn<=5    fn=6   c26??                     fn<=3    fn=4   c28??/////////////////////////////   
//1MQn
//	go=6;
//	n=8; n0=1; k0=3; fn=k0-2;      //fn<=1    fn=2   c5??                      fn<=1    fn=2   c5?? 
//	n=16; n0=1; k0=4; fn=k0-2;     //fn<=2    fn=3   c13??                     fn<=2    fn=3   c13??
//	n=32; n0=1; k0=5; fn=k0-2;       //fn<=5    fn=6   c26??                     fn<=3    fn=4   c28??/////////////////////////////     
//AQn
	go=7;
//	n=8; n0=1; k0=3;  fn=2*k0-4;     //fn<=2    fn=3   c4??                       fn<=2    fn=3   c4??  
//	n=16; n0=1; k0=4; fn=2*k0-3;     //fn<=6    fn=7   c8??                       fn<=5    fn=6   c10??/////////////////////////////
 	n=32; n0=1; k0=5; fn=2*k0-3;      //fn<=12   fn=13  c18??/////                 fn<=7    fn=8   c24??/////////////////////////////
//      n=64; n0=1; k0=6; fn=2*k0-3;	
//TQn
//	go=8;
//	n=8; n0=1; k0=3;  fn=2*k0-3;     //fn<=2    fn=3   c4??                       fn<=2    fn=3   c4??  
//	n=16; n0=1; k0=4; fn=k0-2;     //fn<=6    fn=7   c8??                       fn<=5    fn=6   c10??/////////////////////////////
//	n=32; n0=1; k0=5; fn=k0-2;  //fn<=12   fn=13  c18??/////                 fn<=7    fn=8   c24??/////////////////////////////
//  n=64; n0=1; k0=6; fn=k0-2;
//  n=128; n0=1; k0=7; fn=k0-2;


    sprintf(ma,"go=%d  n0=%d  k0=%d  fn=%d.txt",go,n0,k0,fn);
	pfile=fopen(ma,"w");
	for(i=0;i<VEX;i++)
		for(j=0;j<VEX;j++)
			d[i][j]=-1;
	
	Get_Test_Graph(); 
	Test(1);
	return;
}
