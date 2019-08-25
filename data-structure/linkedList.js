class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedList {
    constructor(data) {
        this.head = new Node('head');
    }

    find(item) {
        let currentNode = this.head;

        while (currentNode.data !== item) {
            currentNode = currentNode.next; // 발견 못하면 다음 노드로 넘어가기
        }

        return currentNode;
    }

    findPrev(item) {
        let currentNode = this.head;

        while (currentNode.next !== null && currentNode.next.data !== item) {
            currentNode = currentNode.next; // 다음 노드가 존재하면서 다음 노드의 값이 아닐 경우
        }

        return currentNode;
    }

    insert(newElement, item) {
        const newNode = new Node(newElement);
        const currentNode = this.find(item);

        newNode.next = currentNode.next;
        currentNode.next = newNode;
    }

    display() {
        let currentNode = this.head;

        while (currentNode.next !== null) {
            console.log(currentNode.next.data);
            currentNode = currentNode.next;
        }
    }

    remove(item) {
        const prevNode = this.findPrev(item);

        if (prevNode.next !== null) {
            prevNode.next = prevNode.next.next;
        }
    }
}

const linkedList = new LinkedList();

linkedList.insert('hello', 'head');
linkedList.insert('data', 'hello');
linkedList.display();