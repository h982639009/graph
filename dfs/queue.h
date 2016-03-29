
//循环队列，队满，队空条件
//队空:front==rear
//队满:(rear+1)%size=front;
struct MyQueue{
	int *queue;//队列，采用动态数组实现,这样实现有什么不好的地方，怎么实现可以让用户动态定义队列存储元素的数据类型？？？
	int size;
	int front;
	int rear;
};
int createQueue(struct MyQueue **q,int size);
int insert(struct MyQueue *q,int e);
int delete(struct MyQueue *q,int *e);
int getCount(struct MyQueue *q);
int isEmpty(struct MyQueue *q);