#include<iostream>
using namespace std;


//这里我学到了很多新的思路（尤其是冒泡排序的新方法：while来做的指标循环）
//七三加油！！




typedef struct SQList
{
	int content;
	SQList* next;
}SQList, * LINKHEAD;


LINKHEAD begin(void);
void create(LINKHEAD head);
void showtotal(LINKHEAD head);
void insert(LINKHEAD head);
void check(LINKHEAD head, SQList* seek);
void change(LINKHEAD head);
void killone(LINKHEAD head);
void reset(LINKHEAD head);
int length(LINKHEAD head);
void sort(LINKHEAD head);//这个函数的含金量很高，因为思路是全原创的，同时用了较低时间复杂度的冒泡排序：大循环的指标跳出
void ally(LINKHEAD ahead, LINKHEAD bhead, LINKHEAD chead);//思路和课本上的完全一致，效果很好，还借鉴了一点优秀判断
void reform(LINKHEAD head);//小而精的筛分，将问题简化了很多
void showtotal_straight(LINKHEAD head);


int main()
{
	//创建了三个空表
	LINKHEAD ahead = begin();
	LINKHEAD bhead = begin();
	LINKHEAD chead = begin();
	
	//为两个表做了初始化
	create(ahead);
	create(bhead);
	
	//重写两个表
	reset(ahead);
	reset(bhead);
	
	//做有序化操作
	sort(ahead);
	sort(bhead);
	
	//变成单向链表
	reform(ahead);
	reform(bhead);

	ally(ahead, bhead, chead);

	showtotal_straight(chead);

}




//构建一个有头节点的空循环链表
LINKHEAD begin(void)
{
	printf("头节点已经生成\n");
		
	SQList* p = new SQList;
	p->content = 0;//头指针内容归零
	p->next = p;//尾部指向自己
	return p;
}


//用尾插法生成n个有用的元素
void create(LINKHEAD head)
{
	cout << "要生成多少个可写入的元素？" << endl;
	int count;
	cin >> count;

	SQList* point = head;
	for (int i = 0; i < count; i++)
	{
		SQList* temp = new SQList;
		temp->content = i + 1;//内容预加载
		temp->next = head;
		point->next = temp;
		point = point->next;
	}
	cout << "生成结束" << endl;
}


//遍历循环链表的所有元素
void showtotal(LINKHEAD head)
{
	SQList* point = head;
	do
	{
		printf("%d\t", point->content);
		point = point->next;
	} while (point!=head);
}


//遍历单向链表的所有元素
void showtotal_straight(LINKHEAD head)
{
	SQList* point = head;
	while (point!= nullptr)
	{
		printf("%d\t", point->content);
		point = point->next;
	}
}



//将第 n 个有效元素变为新插入的元素，其他元素后移
void insert(LINKHEAD head)
{
	cout << "输入要变成的位置" << endl;
	int position;
	cin >> position;

	cout << "输入要插入的值" << endl;
	int content;
	cin >> content;

	SQList* insert = new SQList;
	insert->content = content;

	SQList* seek = head;//从头结点开始查找

	for (int count = 1; count < position; count++)
	{
		seek = seek->next;
		check(head, seek);
	}
	insert->next = seek->next;
	seek->next = insert;
}


//对第 n 个有效元素进行赋值
void change(LINKHEAD head)
{
	int count, content;
	cout << "输入要更改的位置" << endl;
	cin >> count;
	cout << "输入要改成的值" << endl;
	cin >> content;

	SQList* point = head;//从头节点开始查找
	for (int i = 0; i < count; i++)
	{
		point = point->next;
		check(head, point);
	}
	point->content = content;
}


//检查当前的指针会不会等于头指针
void check(LINKHEAD head, SQList* seek)
{
	if (seek == head)
	{
		cout << "操作失败，因为输入的位置超过了我们有的位置" << endl;
		exit(0);
	}
}


//删除并释放第 n 位的有效元素
void killone(LINKHEAD head)
{
	int position;
	cout << "input the position of the element that you are going to delete" << endl;
	cin >> position;

	SQList* p = head;
	for (int i = 0; i < position - 1; i++)
	{
		p = p->next;
		check(head, p);
	}
	cout << "the element is " << p->next->content << endl;
	SQList* temp = p->next;
	p->next = p->next->next;
	delete temp;
}


//对链表的每一个有效元素进行赋值
void reset(LINKHEAD head)
{
	SQList* p = head->next;
	while (p!=head)
	{
		cin >> p->content;
		p = p->next;
	}
}



//将链表中的元素进行从小到大排序
//这个算法是我自己研究原创的算法，可以较好的降低时间复杂度，避免两个无脑大循环的出现（尤其是外部的大循环）
void sort(LINKHEAD head)
{
	SQList* point = head->next;
	int count = 0;

	while (true)
	{
		bool sorted = true;//每次都认为已经排序过了
		while (point->next != head)//这个循环是一定会进入的
		{
			
			if (point->content > point->next->content)
			{
				sorted = false;//发现进入了排序循环

				int temp = point->content;
				point->content = point->next->content;
				point->next->content = temp;
			}
			point = point->next;

		}
		point = head->next;//要记得让指针归位，否则会出现循环只走一次的问题

		if (sorted) { break; }
	}
}




//计算有效长度
int length(LINKHEAD head)
{
	int count = 0;
	SQList* p = head->next;
	for (; p != head; p = p->next)
	{
		count++;
	}
	return count;
}


//将两个有序链表进行组合（不生成新的链表,在时间复杂度相同的情况下，过程的空间复杂度略胜一筹）
//这个地方的代码要好好琢磨一下，写的实在是有点完美
void ally(LINKHEAD ahead, LINKHEAD bhead,LINKHEAD chead)
{
	SQList* a = ahead;
	SQList* b = bhead;
	SQList* c = chead;

	//a b 均不是空表
	if (a->next != ahead && b->next != bhead)
	{
		a = a->next;
		b = b->next;
		//这里用来实现“当两表未尽时的排序”
		while (a != nullptr && b != nullptr)
		{
			if (a->content < b->content)
			{
				c->next = a;
				c = c->next;
				a = a->next;
			}
			else
			{
				c->next = b;
				c = c->next;
				b = b->next;
			}
		}
	}
	//这一段是学来的，真的及其优美
	//与此同时可以发现，不需要再次分析有没有空表的情况，因为用下面的判断式就可以解决空表问题
	c->next = (a == nullptr) ? b : a;


	//避免轻微的内存泄漏
	delete ahead;
	delete bhead;
}


//将循环链表变成单向链表
void reform(LINKHEAD head)
{
	SQList* point = head;
	if (point->next == head)
	{
		point->next = nullptr;
	}
	else
	{
		point = point->next;
		while (point->next != head)
		{
			point = point->next;
		}
		point->next = nullptr;
	}
}