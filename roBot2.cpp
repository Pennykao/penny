#include<cstdio>
#include<cstdlib>

bool map[1000][1000];
bool clean[1000][1000];
int rx,ry;//x y
char c[1002];
int BFS[1000][1000];
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int DFS[1000][1000];



typedef struct node {
    int x,y;//from   up=1;dn=2;lf=3;rt=4;
    struct node *next;
    
} node_t;


node_t *head = NULL;
node_t *rear = NULL;

node_t *top = NULL;

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
	
		
		while(top!=NULL){  //DFS MAZE
			node_t now=*top;
			pop();
			
			bool ob=1;
				for(int i=0;i<4;++i){
					nx=now.x+dx[i];ny=now.y+dy[i];
					if(step>BFS[nx][ny]&&BFS[nx][ny]!=-1)ob=0;
				}
				if(ob){break;}
			
				
			for(int i=0;i<4;++i){
				nx=now.x+dx[i];ny=now.y+dy[i];
				if(DFS[nx][ny]==0){
						
					push(nx,ny);
					//	printf("DFS %d %d\n",nx,ny);
				}
		
			
			}
			if(DFS[now.x][now.y]==0){
				/*bool ob=1;
				for(int i=0;i<4;++i){
					nx=now.x+dx[i];ny=now.y+dy[i];
					if(step>BFS[nx][ny]&&BFS[nx][ny]!=-1)ob=0;
				}
				if(ob){break;}*/
				
				DFS[now.x][now.y]=--step;
				printf("%d %d %d\n",now.x,now.y,step);
			}
				
		
			
		
		
		}	
	
		
			
	//	if(top!=NULL)printf("%d %d %d\n",top->x,top->y,step);
		
		now=*top;	
		
		for(int i=0;i<4;++i){
			nx=now.x+dx[i];ny=now.y+dy[i];
			if(BFS[nx][ny]==step)
				break;
			
		}
		if(BFS[nx][ny]==step){ now.x=nx;now.y=ny; }
		
		while(step!=1){
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
		
		}	//1 times
		
	
		
		
	
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
