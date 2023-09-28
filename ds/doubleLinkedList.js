class Node {
    constructor(data) {
        this.data = data;
        this.prev;
        this.next;
    }
}

class DoubleLinkedList {
    constructor(data) {
        this.count = 1;
        this.head = new Node(data);
    }

    find(data) {
        let currentNode = this.head;

        while (currentNode.data !== data) {
            currentNode = currentNode.next;
        }

        return currentNode;
    }

    insert(prevData, data) {
        const newNode = new Node(data);
        const currentNode = this.find(prevData);

        newNode.next = currentNode.next;
        newNode.prev = currentNode;

        this.count++;
    }

    display() {
        let currentNode = this.head;

        while (currentNode.next) {
            console.log(currentNode.data);
            currentNode = currentNode.next;
        }
    }

    remove(data) {
        let currentNode = this.head;

        if (!currentNode) return false;

        while (currentNode.data !== data & currentNode.next) {
            currentNode = currentNode.next;
        }

        currentNode.prev = currentNode.next;
        this.count--;
    }

    length() {
        return this.count;
    }
}

const doubleLinkedList = new DoubleLinkedList('head');

doubleLinkedList.insert('head', 'hello');
doubleLinkedList.insert('hello', 'double');
doubleLinkedList.display();