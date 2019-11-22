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
	int n,m,b;
	while(scanf("%d%d%d",&n,&m,&b)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%s",c);
			for(int j=0;j<m;++j){
				if(c[j]=='R'||c[j]=='r'){rx=i;ry=j;clean[i][j]=map[i][j]=1;/*puts("rr");*/DFS[i][j]=BFS[i][j]=-2;}
				else if(c[j]=='1'){clean[i][j]=map[i][j]=1; /*puts("gg");*/DFS[i][j]=BFS[i][j]=-1;}
				else {clean[i][j]=map[i][j]=0;/*puts("zz");*/DFS[i][j]=BFS[i][j]=0;}
				//printf("%c ",c[j]);
			}
		}	
		
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
			//	printf("%d %d\n",nx,ny);
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
						printf("%d %d\n",nx,ny);
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
				//	printf("%d %d\n",nx,ny);
				}
		
			
			}
		
		} //BFS END
		
		
		
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				printf("%d\t",BFS[i][j]);
			printf("\n");
		}
		
		
	//	printf("%d,%d\n",rx,ry);
		
		int step=b;
		push(rx,ry);
		now=*top;
		pop();
		
		DFS[now.x][now.y]=-5;
		
//		printf("%d,%d\n",now.x,now.y);
		
		
		for(int i=0;i<4;++i){
			nx=now.x+dx[i];ny=now.y+dy[i];
			if(nx<0||nx>=n||ny<0||ny>=m)continue;
				if(DFS[nx][ny]==0){
				push(nx,ny);
			
				//printf("DFS %d %d\n",nx,ny);
				}
			}
		
//		printf("%d,%d\n",top->x,top->y);
//		printf("%d\n",DFS[5][5]);
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
					if(now.x==3&&now.y==13)printf("-13/9- %d %d %d\n",nx,ny,step);
					if(step-1>BFS[nx][ny]&&BFS[nx][ny]!=-1)ob=0;
				}
				if(ob){	//printf("ob %d %d %d\n",now.x,now.y,step);push(now.x,now.y);now.x=ex.x;now.y=ex.y; printf("ob %d %d %d\n",now.x,now.y,step);
					push(now.x,now.y);
				
					
					printf("ex %d %d %d\n",ex.x,ex.y,step);
					printf("eex %d %d %d\n",eex.x,eex.y,step+1);
						int jj=0;
						for(int i=0;i<4;++i){
							nx=ex.x+dx[i];ny=ex.y+dy[i];
							if(step>BFS[nx][ny]&&BFS[nx][ny]!=-1){now.x=ex.x;now.y=ex.y;jj=1;step=BFS[nx][ny]+1;}
						}
						if(jj==0){
							push(ex.x,ex.y);
							DFS[ex.x][ex.y]=0;
							step++;
							for(int i=0;i<4;++i){
								nx=eex.x+dx[i];ny=eex.y+dy[i];
								if(step>BFS[nx][ny]&&BFS[nx][ny]!=-1){now.x=eex.x;now.y=eex.y;step=BFS[nx][ny]+1;jj=2;}
							}
						}
					
					printf("jj %d\n",jj);
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
				printf("%d %d %d\n",now.x,now.y,step);
			}
			if(de){break;}
		}	
		
	printf("ob %d de %d\n",ob,de);	
	
		
			
	//	if(top!=NULL)printf("%d %d %d\n",top->x,top->y,step);
	if(ob){
/*		printf("11");
	//	now=*top;	
		int mx,my;
		for(int i=0;i<4;++i){
			printf("22");
			nx=now.x+dx[i];ny=now.y+dy[i];
			if(BFS[nx][ny]==step)
				for(int j=0;j<4;++j){
					printf("33");
					mx=nx+dx[j];my=ny+dy[j];
					printf("%d %d %d %d\n",nx,ny,mx,my);	
					if(DFS[mx][my]==step+1)
						break;
				}
				//break;
		
		}
		
		if(BFS[nx][ny]==step){ now.x=nx;now.y=ny; }
		*/
		while(step!=1){
		//	printf("%d %d %d\n",now.x,now.y,step);
			for(int i=0;i<4;++i){
				nx=now.x+dx[i];ny=now.y+dy[i];
				if(BFS[nx][ny]==step-1){ 
					step--;
					now.x=nx;now.y=ny;
					DFS[nx][ny]=step;
					printf("%d %d %d\n",now.x,now.y,step);
					break;
				} 
			}
		
		}
		push(rx,ry);
		step=b;	//1 times
	}
	else if(de){
		while(top!=NULL){
			now=*top;
			
			if(DFS[now.x][now.y]==0){step=b-BFS[now.x][now.y];break;} 
			pop();	
	
	
	
		}
	}
	
	
		printf("\n");
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				printf("%d\t",DFS[i][j]);
			printf("\n");
		}
		
	
}
		
		
		
	
		printf("%d %d\n",rx,ry);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				if(i==rx&&j==ry)printf("R ");
				else printf("%d ",map[i][j]);
			printf("\n");
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				printf("%d\t",BFS[i][j]);
			printf("\n");
		}
		
		printf("\n");
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;++j)
				printf("%d\t",DFS[i][j]);
			printf("\n");
		}
		
	
		
	}
	return 0;
}