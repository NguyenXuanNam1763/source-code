#include<iostream>
#include<graphics.h>
#include<windows.h>
using namespace std;
struct node
{
	int x;
	int y;
	node *next;
	node *priv;
};
struct queue
{
	node *head;
	node *tail;
};
struct stack
{
	node *top;
};
struct goal
{
	int x;
	int y;
};
struct td
{
	int x;
	int y;
};
struct snake
{
	td td[500];
	int n;
};
void design(snake &snake)	//thiet ke con ran ban dau
{
	snake.n=10;
	int k=10;
	for(int i=0;i<10;i++)
	{
		snake.td[i].x=k;
		snake.td[i].y=10;
		k--;
	}
}
void inits(stack &s)	//khoi tao ngan xep stack
{
	s.top=NULL;
}
void push(stack &s,node *p)	// them 1 node vao stack
{
	if(s.top==NULL)
		s.top=p;
	else
	{
		p->next=s.top;
		s.top=p;
	}
}
void init(queue &q)		//khoi tao hang doi queue
{
	q.head=q.tail=NULL;
}
void initgraph()	//khoi tao do hoa
{
	initwindow(500,500);
}
node *createnode(int x,int y)		//tao 1 node chua toa do x,y
{
	node *p=new node;
	p->x=x;
	p->y=y;
	p->next=NULL;
	p->priv=NULL;
	return p;
}
void  addtail(queue &q,node *p)		//then 1 node vao cuoi hang doi
{
	if(q.head==NULL)
		q.head=q.tail=p;
	else
	{
		q.tail->next=p;
		q.tail=p;
	}
}
node *pup(queue &q)			//lay 1 node ra khoi hang doi
{
	node *p=q.head;
	q.head=q.head->next;
	return p;
}
void addtoopen(queue &q,int x,int y,node *p,int open[500][500],int close[500][500])	//them 1 node vao danh sach hang doi
{
	if(open[x][y]==0 && close[x][y]==0)
	{
		open[x][y]=1;
		node *a=createnode(x,y);
		a->priv=p;
		addtail(q,a);
	}
}
void genmove(queue &q,node *p,int open[500][500],int close[500][500])	//phat trien 4 huong cua 1 diem x,y
{
	if(p->x<450)
		addtoopen(q,p->x+1,p->y,p,open,close);
	if(p->y<450)
		addtoopen(q,p->x,p->y+1,p,open,close);
	if(p->x>0)
		addtoopen(q,p->x-1,p->y,p,open,close);
	if(p->y>0)
		addtoopen(q,p->x,p->y-1,p,open,close);
}
node *pups(stack &s)	//lay node ra khoi stack
{
	node *p=s.top;
	s.top=s.top->next;
	return p;
}
void display(snake snake,int goalx,int goaly)	//hien thi con ran va food
{
	cleardevice();
	int mau=1+rand()%14;
	putpixel(goalx,goaly,mau);
	putpixel(goalx,goaly-1,mau);
	putpixel(goalx+1,goaly,mau);
	putpixel(goalx,goaly+1,mau);
	putpixel(goalx-1,goaly,mau);
	line(10,10,480,10);
	line(10,10,10,480);
	line(480,10,480,480);
	line(10,480,480,480);
	for(int i=0;i<snake.n;i++)
	{
		if(i==0)
		{
			putpixel(snake.td[i].x,snake.td[i].y,mau);
			putpixel(snake.td[i].x,snake.td[i].y+1,mau);
			putpixel(snake.td[i].x+1,snake.td[i].y,mau);
			putpixel(snake.td[i].x,snake.td[i].y+1,mau);
			putpixel(snake.td[i].x-1,snake.td[i].y,mau);
		}
		else
		{
			putpixel(snake.td[i].x,snake.td[i].y,mau);
		}
	}
	delay(10);
}
void change(snake &snake,int x,int y,int goalx,int goaly)	//thay doi toa do cua dac dot ran
{
	for(int i=snake.n;i>=1;i--)
	{
		snake.td[i].x=snake.td[i-1].x;
		snake.td[i].y=snake.td[i-1].y;
	}
	snake.td[0].x=x;
	snake.td[0].y=y;
}
void move(stack &s,snake &snake,int goalx,int goaly)	//di chuyen con ran theo top stack
{
	int i=0;
	while(s.top!=NULL)
	{
		node *p=pups(s);
		
		if(p->x==goalx &&p->y==goaly)
		{
			snake.n++;
			//PlaySound("earFood.wav",NULL,SND_ASYNC);
			PlaySound("beep.wav",NULL,SND_ASYNC);
		}
		change(snake,p->x,p->y,goalx,goaly);
		display(snake,goalx,goaly);
		//cout<<"\nn="<<snake.n;
	}
}
void getsolution(stack &s,node *p)	//lay vi tri father cua queue dua vao stack
{
	while(p!=NULL)
	{
		node *a=createnode(p->x,p->y);
		push(s,a);
		p=p->priv;
	}
	//pups(s);
}
void handling(int x,int y,int goalx,int goaly,snake &snake)		//xu ly tim kiem duong di cua ran
{
	int open[500][500]={0};
	int close[500][500]={0};
	for(int i=0;i<snake.n;i++)
	{
		close[snake.td[i].x][snake.td[i].y]=1;
	}
	queue q;
	//display(snake);
	stack s;
	init(q);
	inits(s);
	node *p=createnode(x,y);
	addtail(q,p);
	while(true)
	{
		p=pup(q);
		//putpixel(p->x,p->y,14);
		//delay(10);
		if(p->x==goalx && p->y==goaly)
		{
			getsolution(s,p);
			move(s,snake,goalx,goaly);
			break;
		}
		genmove(q,p,open,close);
	}
}
void designgr()
{
	line(10,10,480,10);
	line(10,10,10,480);
	line(480,10,480,480);
	line(10,480,480,480);
	outtextxy(200,150,"Start");
	outtextxy(180,200,"Information");
	outtextxy(200,250,"Exit");
}
main()
{
	PlaySound("music.wav",NULL,SND_ASYNC);
	initgraph();
	designgr();
	int x,y;
	while(true)
	{
		delay(10);
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN,x,y);
			//cout<<"x="<<x<<"	y="<<y;
		}
		if((x>180 && x<220) && (y>130 &&y<180))
		{
			snake snake;
			design(snake);
			int startx=10;
			int starty=10;
			int goalx=1+rand()%450;
			int goaly=1+rand()%450;
			while(true)
			{
				//cleardevice();
				handling(startx,starty,goalx,goaly,snake);
				startx=goalx;
				starty=goaly;
				goalx=1+rand()%450;
				goaly=1+rand()%450;
			}
		}
		if((x>180 && x<266) && (y>190 && y<220))
		{
			cleardevice();
			line(10,10,480,10);
			line(10,10,10,480);
			line(480,10,480,480);
			line(10,480,480,480);
			outtextxy(200,150,"DEMO Snake AI");
			outtextxy(180,180,"Sinhvien: Nguyen Xuan Nam-1781310159");
			outtextxy(200,200,"Giang Vien Ho Tro:");
			outtextxy(200,220,"Cu Viet Dung");
			outtextxy(300,300,"Back <-");
		}
		if((x>290 && x<330)&&(y>290 && y<320))
		{
			cleardevice();
			designgr();
		}
		if((x>190 && x<240)&&( y>250 && y<260))
			exit(0);
	}	
	getch();
	closegraph();
}
