import java.lang.Math;

public class Node { 
	int x;
	int y;	
	private Node next;	

	public Node(int x, int y) {
		this.x = x;
		this.y = y;
		this.next = null;
	}
	public Node() {
		this.next=null;
	}	
	public Node(Node node) {
		this.x=node.x;
		this.y=node.y;
		this.next=node.next;
	}
	public Node getNext() {
		return this.next;
	}
	public void setNext(Node node) {
		this.next=node;
	}
	public int distanceFrom(Node node) {
		int netX, netY;

		netX=this.x-node.x;
		netY=this.y-node.y;
		return (int) Math.sqrt(netX*netX+netY*netY);
	}
	public Queue getPossibleMoveNodes(Queue finalPath,int[][] moves,int gridSize) {

		//find all valid Nodes and enqueue it

		Queue validNodes=new Queue();

		for(int i=0;i<moves.length;i++) {
			int newX=this.x+moves[i][0],
					newY=this.y+moves[i][1];
			label:
			{
				if((newX>=0 && newX<gridSize)&&(newY>=0 && newY<gridSize)) {
					Node nodetoCheck=new Node(newX,newY);
					
					Queue path=new Queue(finalPath);
					while(!path.isEmpty()) {
						Node traversedNode=path.dequeue();
						if(nodetoCheck.isEqual(traversedNode)){
							break label;
						}
					}
					validNodes.enqueue(nodetoCheck);
				}
			}
		}
		return validNodes;
	}	
	public void print() {
		System.out.println("\n"+this.x+", "+this.y);
	}
	public boolean isEqual(Node node) {
		return (this.x==node.x && this.y==node.y);
	}
} 