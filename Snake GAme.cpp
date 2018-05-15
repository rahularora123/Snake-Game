#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<fstream>
#include<iostream>
#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
using namespace std;

struct snake
{
	int x;
	int y;
	char var;
	snake *next;
}*head=NULL;

struct Food
{
	int x;
	int y;
	char var;
}*food;

int input(char *s,int n,int p)
{
	cout<<n<<endl;
	char c='0';
	while(n>0)
	{
		int d=n%10;
		s[p++]=d+48;
		n=n/10;
	}
	return p;
}

void pri(struct snake *head,Food *food,int score)
{
	char *mat[41];
	for(int i=0;i<41;i++)
	{
		mat[i]=(char *)calloc(41,sizeof(char));
	}
	snake *t=head;

	for(int i=0;i<41;i++)
	{
		for(int j=0;j<41;j++)
		{
			if(i==0||j==0||i==40||j==40)
			{
				mat[i][j]='*';
			}
		}
	}
	mat[food->x][food->y]=food->var;
	while(t!=NULL)
	{
		mat[t->x][t->y]=t->var;
		t=t->next;
	}

	for(int i=0;i<41;i++)
	{
		for(int j=0;j<41;j++)
		{
			printf("%c ",mat[i][j]);
		}
		printf("\n");
	}
	printf("Score=: %d\n",score);
	for(int d=0;d<41;d++)
	{
		delete [] mat[d];
	}





}

struct snake* create(struct snake *head)
{
	head=new snake();
	head->var='A';
	head->x=1+rand()%39;
	head->y=1+rand()%39;
	snake *n1=new snake();
	snake *n2=new snake();
	n1->x=head->x;
	n2->x=head->x;
	n1->y=head->y+1;
	if(n1->y>39)
	n1->y=1;
	n2->y=n1->y+1;

	if(n2->y>39)
	n2->y=1;

	n1->var='#';
	n2->var='#';
	head->next=n1;
	n1->next=n2;
	n2->next=NULL;
	return head;

}

struct Food * generateFood(snake *head,Food *food)
{
	food->var='X';
	int flag=1;
	do
	{
		flag=1;
		food->x=1+rand()%39;
		food->y=1+rand()%39;
		snake *t=head;
		while(t!=NULL)
		{
			if(t->x==food->x && t->y==food->y)
			{
				flag=0;
				break;
			}
			t=t->next;
		}
	}while(flag==0);
	return food;
}

void move(snake *head,int a,int b)
{
	snake *t1;
	int x1,y1,x2,y2;
	t1=head->next;
	x1=head->x;
	y1=head->y;
	x2=x1;
	y2=y1;
	head->x=a;
	head->y=b;

	while(t1!=NULL)
	{
		x1=t1->x;
		y1=t1->y;
		t1->x=x2;
		t1->y=y2;
		x2=x1;
		y2=y1;
		t1=t1->next;
	}
}

void increase(snake *head,Food *food,int &score)
{
	score++;
	snake *temp=new snake();
	temp->x=head->x;
	temp->y=head->y;
	head->x=food->x;
	head->y=food->y;
	temp->var='#';
	temp->next=head->next;
	//head->var='#';
	head->next=temp;

	food=generateFood(head,food);

}

int cut(int x1,int y1,snake *head)
{
	int fl=1;
	snake *temp=head;
	while(temp!=NULL)
	{
		if(x1==temp->x && y1==temp->y)
		{
			fl=0;
			break;
		}
		temp=temp->next;
	}
	return fl;
	}

int gN(char *c,int &p)
{
	int num=0;
	int m=1,d;
	while(c[p]!=',')
	{
		d=c[p]-48;
		num=num+d*m;
		m=m*10;
		p++;
	}
	return num;
}

snake * load(snake *head,Food *food)
{
	char *game=(char *)calloc(1000,sizeof(char));
	ifstream g;
	g.open("game.txt",ios::in|ios::binary);


	int j=0;
	while(!g.eof())
	{
		g>>game[j++];
	}

g.close();
	int r;
	int p=0;
	 food->var=game[p];
	 p+=2;
	 r=gN(game,p);
	 p+=1;
	 food->x=r;
	 r=gN(game,p);
	 food->y=r;
	 p++;

	//working fine till here




	while(game[p]!='\0')
	{
		snake *t=new snake();
		t->var=game[p];
		p+=2;
		r=gN(game,p);
		t->x=r;
		p++;
		r=gN(game,p);
		t->y=r;
		p++;

		if(head==NULL)
		{
			head=t;
			head->next=NULL;
		}
		else
		{
			snake *temp=head;
			while(temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp->next=t;
			t->next=NULL;
		}

	}



return head;
}

void save(snake *head,Food *food)
{
	char *game=(char *)calloc(1000,sizeof(char));
	snake *t=head;
	int i=0;

/*	game[i++]=food->var;
	game[i++]=(char)food->x;
	game[i++]=(char)food->y;
	while(t!=NULL)
	{
		game[i++]=t->var;
		game[i++]=(char)t->x;
		game[i++]=(char)t->y;
		t=t->next;
	}
	game[i++]='*';*/
	int p=0;
	game[p++]=food->var;
	game[p++]=',';
	p=input(game,food->x,p);
	game[p++]=',';
	p=input(game,food->y,p);
	game[p++]=',';
	while(t!=NULL)
	{
		game[p++]=t->var;
		game[p++]=',';
		p=input(game,t->x,p);
		game[p++]=',';
		p=input(game,t->y,p);
		game[p++]=',';
		t=t->next;
	}



	ofstream g;
	g.open("game.txt",ios::out|ios::binary);
	int j=0;
	while(game[j]!='\0')
	{
		g<<game[j]<<"\t";
		j++;
	}
	g.close();



}
int main()
{


	int score=0;
	head=create(head);
	food=new Food();
	food=generateFood(head,food);
	pri(head,food,score);
	int flag=1;
	int choice;
	char c;
	int KB_CODE=75;

		while(head->x!=food->x || head->y!=food->y)
			{
				int x1,y1;

				if(kbhit())
				KB_CODE=getch();
				//	scanf("%c",&c);
				switch(KB_CODE)
				{
					case KB_UP:
						{
					x1=head->x-1;
					if(x1<1)
					x1=39;
					y1=head->y;
					if(x1==head->next->x && y1==head->next->y)
					{
						break;
					}
					else if(x1==food->x && y1==food->y)
					{
						increase(head,food,score);

						break;
					}
					else
					{
					flag=cut(x1,y1,head);
					if(flag==0)
					{
						printf("Game Over");
						break;
						}
					else
					{
							move(head,x1,y1);
							break;
					}
					}

				}
					case KB_LEFT:
						{
					x1=head->x;
					y1=head->y-1;
					if(y1<1)
					y1=39;
					if(x1==head->next->x && y1==head->next->y)
					{
						break;
					}
					else if(x1==food->x && y1==food->y)
					{
						increase(head,food,score);

						break;
					}
					else
					{
				flag=cut(x1,y1,head);
					if(flag!=1)
					{
						printf("Game Over");
						break;
						}
					move(head,x1,y1);

					break;
					}
				}
					case KB_RIGHT:
						{
					x1=head->x;
					y1=head->y+1;
					if(y1>39)
					y1=1;
					if(x1==head->next->x && y1==head->next->y)
					{
						break;
					}
					else if(x1==food->x && y1==food->y)
					{
						increase(head,food,score);

						break;
					}
					else
					{
					flag=cut(x1,y1,head);
					if(flag!=1)
					{
						printf("Game Over");
						break;
						}
					move(head,x1,y1);

					break;
					}
				}
					case KB_DOWN:
						{
					x1=head->x+1;
					y1=head->y;
					if(x1>39)
					x1=1;
					if(x1==head->next->x && y1==head->next->y)
					{
						break;
					}
					else if(x1==food->x && y1==food->y)
					{
						increase(head,food,score);

						break;
					}
					else
					{
					flag=cut(x1,y1,head);
					if(flag!=1)
					{
						printf("Game Over");
						break;
						}
					move(head,x1,y1);

					break;
					}
				}

				}
				Sleep(200);
				system("cls");
				pri(head,food,score);
				if(flag==0 || KB_CODE==KB_ESCAPE)
				{
					if(flag==0)
					{
						printf("Game Over\n");
							break;
					}
					else if(KB_CODE==KB_ESCAPE)
					{
						printf("Do You want to Save\n1.Yes\n3.Exit\n");

						scanf("%d",&choice);
						if(choice==1)
						{
							save(head,food);
							printf("\nGame Saved\n");
							break;
						}
						if(choice==3)
						{
							break;
						}
					}

				}
			}
		head=NULL;
		if(head==NULL)
		{
			printf("\nHead is now NULL\n");
		}
		food->var='z';
		food->x=0;
		food->y=0;
		printf("Reset Food: %c %d %d\n",food->var,food->x,food->y);
		head=load(head,food);
		printf("Loaded Food: %c %d %d\n",food->var,food->x,food->y);
		snake *temp=head;
		while(temp!=NULL)
		{
			cout<<temp->var<<" "<<temp->x<<" "<<temp->y<<endl;
			temp=temp->next;
		}


	return 0;
}

