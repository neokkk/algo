class Node {
	constructor(data) {
		this.data = data;
		this.next;
	}
}

class LinkedList {
	constructor() {
		this.head;
		this.length = 0;
	}

	insert(data) {
		const node = new Node(data);

		if (this.length === 0) {
			this.head = node;
		} else {
			let currentNode = this.head;

			while (currentNode.next) {
				currentNode = currentNode.next;
			}

			currentNode.next = node;
		}

		this.length++;
	}

	delete(data) {
		if (this.length === 0) return null;
		if (this.head.data === data) {
			this.head = this.head.next;
		} else {
			let currentNode = this.head;
	
			while (currentNode.next.data !== data) {
				currentNode = currentNode.next;
			}
	
			currentNode.next = currentNode.next.next;
		}

		this.length--;
	}

	display() {
		if (this.length === 0) return null;

		let currentNode = this.head;
		console.log(currentNode.data);

		while (currentNode.next) {
			currentNode = currentNode.next;
			console.log(currentNode.data);
		}
	}

	length() {
		console.log(this.length);
		return this.length;
	}
}

const ll = new LinkedList();

ll.insert('hello');
ll.insert('link');
ll.insert('hello');
ll.insert('data');
ll.delete('hello');
ll.delete('hello');
ll.display();
ll.length();