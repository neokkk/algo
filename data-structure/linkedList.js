class Node {
    constructor(data) {
        this.data = data;
        this.next;
    }
}

class LinkedList {
    constructor(data) {
        this.count = 1;
        this.head = new Node(data);
    }

    find(data) {
        let currentNode = this.head;

        while (currentNode.data !== data) {
            currentNode = currentNode.next; // 발견 못하면 다음 노드로 넘어가기
        }

        return currentNode;
    }

    findPrev(data) {
        let currentNode = this.head;

        while (currentNode.next && currentNode.next.data !== data) {
            currentNode = currentNode.next; // 다음 노드가 존재하면서 다음 노드의 값이 아닐 경우
        }

        return currentNode;
    }

    insert(prevData, data) {
        const newNode = new Node(data);
        const currentNode = this.find(prevData);

        newNode.next = currentNode.next;
        currentNode.next = newNode;

        this.count++;
    }

    display() {
        let currentNode = this.head;

        console.log(currentNode.data);

        while (currentNode.next) {
            currentNode = currentNode.next;
            console.log(currentNode.data);
        }
    }

    remove(data) {
        const prevNode = this.findPrev(data);

        if (prevNode.next) {
            prevNode.next = prevNode.next.next;

            this.count--;
        }
    }

    length() {
        console.log(this.count);
        return this.count;
    }
}

const linkedList = new LinkedList('head');

linkedList.insert('head', 'hello');
linkedList.insert('hello', 'data');
linkedList.insert('hello', 'pass');
linkedList.remove('pass');
linkedList.display();
linkedList.length();