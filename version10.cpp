#include<cstdio>
#include<cstdlib>

bool map[1000][1000];
bool clean[1000][1000];
int rx,ry;//x y
char c[1002];
int BFS[1000][1000];
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int DFS[1000][1000];
bool ob,de; //out of batery , dead end
int xx,yy,xxx,yyy,last,total=0;



typedef struct node {
    int x,y;//from   up=1;dn=2;lf=3;rt=4;
    struct node *next;
    
} node_t;


node_t *head = NULL;
node_t *rear = NULL;
node_t *head2 = NULL;
node_t *rear2 = NULL;

node_t *top = NULL;
node_t *top2 = NULL;
node_t ex,eex;

void push(int x,int y){
	node_t *new_node = (node*)malloc(sizeof(node_t));
    if (!new_node) return;
	
	new_node->next=top;
	top=new_node;
	new_node->x = x;
    new_node->y = y;
    

}

void pop(){
	if(top==NULL)return;	
	else{
		node_t *current=top;
		top=top->next;
		free(current);
		
	
	}
}

void push2(int x,int y){
	node_t *new_node = (node*)malloc(sizeof(node_t));
    if (!new_node) return;
	
	new_node->next=top2;
	top2=new_node;
	new_node->x = x;
    new_node->y = y;
    

}

void pop2(){
	if(top2==NULL)return;	
	else{
		node_t *current=top2;
		top2=top2->next;
		free(current);
		
	
	}
}





void enqueue(int x,int y) {
    node_t *new_node = (node*)malloc(sizeof(node_t));
    if (!new_node) return;
	
	if(head==NULL){
		head=new_node;
		rear=new_node;
	}
    new_node->x = x;
    new_node->y = y;
    rear->next=new_node;
    rear=new_node;
    new_node->next=NULL;
        
}

void dequeue(){
	if(head==NULL)return;
	else{
		node_t *current=head;
		head=head->next;
		free(current);
		if(head==NULL)rear=NULL;
		return;
	
	}
		
}

void enqueue2(int x,int y) {
    node_t *new_node = (node*)malloc(sizeof(node_t));
    if (!new_node) return;
	
	if(head2==NULL){
		head2=new_node;
		rear2=new_node;
	}
    new_node->x = x;
    new_node->y = y;
    rear2->next=new_node;
    rear2=new_node;
    new_node->next=NULL;
        
}

void dequeue2(){
	if(head2==NULL)return;
	else{
		node_t *current=head;
		head2=head2->next;
		free(current);
		if(head2==NULL)rear2=NULL;
		return;
	
	}
		
}








int main(){
	
	FILE *fin, *fout,*finall;
	 fin=fopen("floor.data","rt");
	 fout=fopen("middle.txt","w+t");
	 
	 
	 
	int n,m,b;
	while(fscanf(fin,"%d%d%d",&n,&m,&b)!=EOF){
		for(int i=0;i<n;i++){
			fscanf(fin,"%s",c);
			for(int j=0;j<m;++j){
				if(c[j]=='R'||c[j]=='r'){rx=i;ry=j;clean[i][j]=map[i][j]=1;/*puts("rr");*/DFS[i][j]=BFS[i][j]=-2;}
				else if(c[j]=='1'){clean[i][j]=map[i][j]=1; /*puts("gg");*/DFS[i][j]=BFS[i][j]=-1;}
				else {clean[i][j]=map[i][j]=0;/*puts("zz");*/DFS[i][j]=BFS[i][j]=0;last++;}
				//printf("%c ",c[j]);
			}
		}	
	//	fprintf(fout,"%d %d\n",rx,ry);
		xx=rx;yy=ry;
//		printf("%d\n",last);
		enqueue(rx,ry); //BFS R
		
		node_t now=*head;
		dequeue();
		int nx,ny;
		for(int i=0;i<4;++i){
			nx=now.x+dx[i];ny=now.y+dy[i];
			if(nx<0||nx>=n||ny<0||ny>=m)continue;
			if(BFS[nx][ny]==0){
				BFS[nx][ny]=1;			
				enqueue(nx,ny);
			//	fprintf(fout,"%d %d\n",nx,ny);
			}
		
			
		}
			
			
/*			for(int k=0;k<20;++k){
				node_t now=*head;
				dequeue();
				int nx,ny;
				for(int i=0;i<4;++i){
					nx=now.x+dx[i];ny=now.y+dy[i];
					if(BFS[nx][ny]==0){
						BFS[nx][ny]=BFS[now.x][now.y]+1;			
						enqueue(nx,ny);
						fprintf(fout,"%d %d\n",nx,ny);
					}
		
			
				}
			
			
			
			}
*/		
		
		while(head!=NULL){  //BFS MAZE
			node_t now=*head;
			dequeue();
			int nx,ny;
			for(int i=0;i<4;++i){
				nx=now.x+dx[i];ny=now.y+dy[i];
				if(BFS[nx][ny]==0){
					BFS[nx][ny]=BFS[now.x][now.y]+1;			
					enqueue(nx,ny);
				//	fprintf(fout,"%d %d\n",nx,ny);
				}
		
			
			}
		
		} //BFS END
		
		
		
		
	/*	for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				fprintf(fout,"%d\t",BFS[i][j]);
			fprintf(fout,"\n");
		}
	*/	
		
	//	fprintf(fout,"%d,%d\n",rx,ry);
		
		int step=b;
		push(rx,ry);
		now=*top;
		pop();
		
		DFS[now.x][now.y]=-5;
		
//		fprintf(fout,"%d,%d\n",now.x,now.y);
		
		
		for(int i=0;i<4;++i){
			nx=now.x+dx[i];ny=now.y+dy[i];
			if(nx<0||nx>=n||ny<0||ny>=m)continue;
				if(DFS[nx][ny]==0){
				push(nx,ny);
			
				//fprintf(fout,"DFS %d %d\n",nx,ny);
				}
			}
		
//		fprintf(fout,"%d,%d\n",top->x,top->y);
//		fprintf(fout,"%d\n",DFS[5][5]);
	while(top!=NULL){
//for(int hh=0;hh<2;++hh){		
		while(top!=NULL){  //DFS MAZE
			eex=ex;
			ex=now;
			now=*top;
			pop();
			 ob=1;
				for(int i=0;i<4;++i){
					
					nx=now.x+dx[i];ny=now.y+dy[i];
//					if(now.x==3&&now.y==13)fprintf(fout,"-13/9- %d %d %d\n",nx,ny,step);
					if(step-1>BFS[nx][ny]&&BFS[nx][ny]!=-1)ob=0;
				}
				if(ob){	//fprintf(fout,"ob %d %d %d\n",now.x,now.y,step);push(now.x,now.y);now.x=ex.x;now.y=ex.y; fprintf(fout,"ob %d %d %d\n",now.x,now.y,step);
					push(now.x,now.y);
				
					
/*					fprintf(fout,"ex %d %d %d\n",ex.x,ex.y,step);
					fprintf(fout,"eex %d %d %d\n",eex.x,eex.y,step+1);*/
						int jj=0;
						for(int i=0;i<4;++i){
							nx=ex.x+dx[i];ny=ex.y+dy[i];
							if(step>BFS[nx][ny]&&BFS[nx][ny]!=-1){now.x=ex.x;now.y=ex.y;jj=1;step=BFS[nx][ny]+1;}
						}
						if(jj==0){
							push(ex.x,ex.y);
							DFS[ex.x][ex.y]=0;
							last++;
							//printf("%d %d \n",ex.x,ex.y);
							step++;
							for(int i=0;i<4;++i){
								nx=eex.x+dx[i];ny=eex.y+dy[i];
								if(step>BFS[nx][ny]&&BFS[nx][ny]!=-1){now.x=eex.x;now.y=eex.y;step=BFS[nx][ny]+1;jj=2;}
							}
						}
					
//					fprintf(fout,"jj %d\n",jj);
					break;
				}
			
					
				de=1;
			for(int i=0;i<4;++i){
				nx=now.x+dx[i];ny=now.y+dy[i];
				if(nx<0||nx>=n||ny<0||ny>=m)continue;
				if(DFS[nx][ny]==0){
					de=0;
					push(nx,ny);
				
				}
			}
				
				
			if(DFS[now.x][now.y]==0){
			
				DFS[now.x][now.y]=--step;
				last--;
				xxx=now.x;yyy=now.y;
				if(xx!=xxx||yy!=yyy){
				fprintf(fout,"%d %d\n",xx,yy);total++;
				xx=xxx;yy=yyy;
				
				}
//				fprintf(fout,"last= %d\n",last);
			}
			if(de){break;}
		}	
		
//	fprintf(fout,"ob %d de %d\n",ob,de);	
	
		
			
	//	if(top!=NULL)fprintf(fout,"%d %d %d\n",top->x,top->y,step);
	if(ob){
/*		fprintf(fout,"11");
	//	now=*top;	
		int mx,my;
		for(int i=0;i<4;++i){
			fprintf(fout,"22");
			nx=now.x+dx[i];ny=now.y+dy[i];
			if(BFS[nx][ny]==step)
				for(int j=0;j<4;++j){
					fprintf(fout,"33");
					mx=nx+dx[j];my=ny+dy[j];
					fprintf(fout,"%d %d %d %d\n",nx,ny,mx,my);	
					if(DFS[mx][my]==step+1)
						break;
				}
				//break;
		
		}
		
		if(BFS[nx][ny]==step){ now.x=nx;now.y=ny; }
		*/
		while(step!=1){
		//	fprintf(fout,"%d %d %d\n",now.x,now.y,step);
			for(int i=0;i<4;++i){
				nx=now.x+dx[i];ny=now.y+dy[i];
				if(BFS[nx][ny]==step-1){ 
					step--;
					for(int j=0;j<4;++j){
						int nxx=nx+dx[j];int nyy=ny+dy[j];
						if(DFS[nxx][nyy]==0)
							push(nxx,nyy);
						
					} 
					now.x=nx;now.y=ny;
					if(DFS[now.x][now.y]==0)last--;
					DFS[nx][ny]=step;
					
					xxx=now.x;yyy=now.y;
					if(xx!=xxx||yy!=yyy){
						fprintf(fout,"%d %d\n",xx,yy);total++;
						xx=xxx;yy=yyy;
				
					}
					break;
				} 
			}
		
		}
		//fprintf(fout,"%d %d\n",rx,ry);total++;
		
		xxx=rx;yyy=ry;
		if(xx!=xxx||yy!=yyy){
			fprintf(fout,"%d %d\n",xx,yy);total++;
			xx=xxx;yy=yyy;
			
		}
		
		push(rx,ry);
		step=b;	//1 times
/*		fprintf(fout,"%d\n",last);
		
		fprintf(fout,"\n");
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				fprintf(fout,"%d\t",DFS[i][j]);
			fprintf(fout,"\n");
		}
*/		
		if(last==0)break;
	}
	else if(de){
		int qq=BFS[now.x][now.y];
		node_t ee=now;
		
	if(ee.x!=rx&&ee.y!=ry)
		while(qq!=1){
		//	fprintf(fout,"%d %d %d\n",now.x,now.y,step);
			for(int i=0;i<4;++i){
				nx=ee.x+dx[i];ny=ee.y+dy[i];
				if(BFS[nx][ny]==qq-1){ 
					qq--;
					ee.x=nx;ee.y=ny;
					if(DFS[ee.x][ee.y]==0)last--;
					DFS[nx][ny]=qq;
					for(int j=0;j<4;++j){
						int nxx=nx+dx[j];int nyy=ny+dy[j];
						if(DFS[nxx][nyy]==0)
							push(nxx,nyy);
						
					} 
					
					
					
					xxx=ee.x;yyy=ee.y;
					if(xx!=xxx||yy!=yyy){
						fprintf(fout,"%d %d\n",xx,yy);total++;
						xx=xxx;yy=yyy;
				
					}
					break;
				} 
			}
		
		}
		
		
		
		while(top!=NULL){
			now=*top;
			
			if(DFS[now.x][now.y]==0){step=b-BFS[now.x][now.y];break;} 
			pop();	
		
	
		}
		
		xxx=rx;yyy=ry;
		if(xx!=xxx||yy!=yyy){
			fprintf(fout,"%d %d\n",xx,yy);total++;
			xx=xxx;yy=yyy;
				
		}
//		fprintf(fout,"%d\n",last);
		
/*		fprintf(fout,"\n");
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				fprintf(fout,"%d\t",DFS[i][j]);
			fprintf(fout,"\n");
		}
		
*/		if(last==0)break;
		node_t aa=now;
		int bb=BFS[aa.x][aa.y];
		while(bb!=1){
		//	fprintf(fout,"%d %d %d\n",now.x,now.y,step);
			for(int i=0;i<4;++i){
				nx=aa.x+dx[i];ny=aa.y+dy[i];
				if(BFS[nx][ny]==bb-1){ 
					bb--;
					aa.x=nx;aa.y=ny;
					
					for(int j=0;j<4;++j){
						int nxx=nx+dx[j];int nyy=ny+dy[j];
						if(DFS[nxx][nyy]==0)
							push(nxx,nyy);
						
					} 
					
				//		if(DFS[aa.x][aa.y]==0){last--;DFS[aa.x][aa.y]=100;	fprintf(fout,"alast= %d\n",last);}
					//DFS[nx][ny]=step;
					push2(aa.x,aa.y);
					//fprintf(fout,"%d %d %d\n",now.x,now.y,step);
					break;
				} 
			}
		}
		while(top2!=NULL){
			aa=*top2;
			if(DFS[aa.x][aa.y]==0){last--;DFS[aa.x][aa.y]=100;	/*fprintf(fout,"blast= %d\n",last);*/}
		
			
			xxx=aa.x;yyy=aa.y;
			if(xx!=xxx||yy!=yyy){
				fprintf(fout,"%d %d\n",xx,yy);total++;
				xx=xxx;yy=yyy;
				
			}
			
			pop2();
		
		}
		
		
		
		xxx=now.x;yyy=now.y;
					if(xx!=xxx||yy!=yyy){
						fprintf(fout,"%d %d\n",xx,yy);total++;
						xx=xxx;yy=yyy;
				
					}
		
	}
	
	
	/*	printf("\n");
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				printf("%d\t",DFS[i][j]);
			printf("\n");
		}
	*/	
	
}
		
		
		
	
/*		fprintf(fout,"%d %d\n",rx,ry);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				if(i==rx&&j==ry)fprintf(fout,"R ");
				else fprintf(fout,"%d ",map[i][j]);
			fprintf(fout,"\n");
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				fprintf(fout,"%d\t",BFS[i][j]);
			fprintf(fout,"\n");
		}
		
		fprintf(fout,"\n");
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				fprintf(fout,"%d\t",DFS[i][j]);
			fprintf(fout,"\n");
		}
		
*/	
		
		xxx=rx;yyy=ry;
		if(xx!=xxx||yy!=yyy){
			fprintf(fout,"%d %d\n",xx,yy);total++;
			xx=xxx;yy=yyy;
				
		}
		fprintf(fout,"%d %d",rx,ry);total++;
		//fprintf(fout,"  %d",total);
	}
		fclose(fin);

	 fclose(fout);
	 
	fout=fopen("middle.txt","rt");
	finall=fopen("final.path","w+t");
	fprintf(finall,"%d",total);
	
	while(fscanf(fout,"%d %d",&xxx,&yyy)!=EOF){
    fprintf(finall,"\n%d %d",xxx,yyy);
	}
	fclose(fout);
	fclose(finall);
	 
	 
	 
	 
	 
	return 0;
}