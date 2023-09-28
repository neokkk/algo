import { reverseLinkedList } from './reverseLinkedList';

class Node {
    constructor(data) {
        this.data = data;
        this.next;
    }
}

class LinkedList {
    constructor() {
        this.head;
        this.count = 0;
    }

    insert(data) {
        const node = new Node(data);

        if (!this.head) this.head = node;
        else {
            let currentNode = this.head;

            while (currentNode.next) {
                currentNode = currentNode.next;
            }

            currentNode.next = node;
        }

        this.count++;
    }

    delete(data) {
        if (!this.head) return null;
        if (this.head.data === data) this.head = this.head.next;
        else {
            let currentNode = this.head;

            while (currentNode.next.data !== data) {
                currentNode = currentNode.next;
            }

            currentNode.next = currentNode.next.next;
        }

        this.count--;
    }

    display() {
        if (!this.head) return null;

        let currentNode = this.head;

        while (currentNode.next) {
            console.log(currentNode.data);
            currentNode = currentNode.next;
        }

        console.log(currentNode.data);
    }

    length() {
        console.log(this.count);
        return this.count;
    }
}

const ll = new LinkedList();

ll.insert('hello');
ll.insert('hi');
ll.insert('linked');
ll.insert('list');
ll.delete('hi');
ll.display();
ll.length();

console.log('reverse');
console.log(reverseLinkedList(ll));