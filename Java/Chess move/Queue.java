
public class Queue {
	Node front; // front of the queue
	Node rear; // end of the queue

	public Queue() {
		this.front=this.rear=null;
	}
	public Queue(Queue queue) {
		this.front=new Node(queue.front);
		this.rear=new Node(queue.rear);
	}
	public final boolean isEmpty()
	// returns true if the queue is empty
	{
		return (this.front == null);
	}
	public final void enqueue(Node element) {
		// adds an element to the rear of the queue
		Node newNode = new Node(element);
		newNode.setNext(null);
		
		if (this.rear == null) {
			this.front = newNode;
			this.rear = newNode;
		}
		else {
			this.rear.setNext(newNode);
			this.rear = newNode;
		}

	}
	public final Node dequeue() {
		// throws a underflow exception if the queue is empty
		// else, removes the front element and returns it
		if (isEmpty()) {
			throw new RuntimeException("Stack Underflow");
		} else {
			Node element;
			element = this.front;
			this.front = this.front.getNext();
			if(this.front==null) this.rear=null;
			return element;
		}
	}
	public void print() {
		while(!this.isEmpty()) {
			Node toPrint=this.dequeue();
			toPrint.print();
		}
	}
}