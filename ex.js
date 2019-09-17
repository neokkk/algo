class Stack {
    constructor(size) {
        this.arr = [];
        this.top = -1;
        this.size = size;
    }

    push(data) {
        if (this.arr.length === this.size) return;

        this.top++;
        this.arr[this.top] = data;

        console.log(this.arr);
    }

    pop() {
        if (this.top < 0) return;

        const popped = this.arr.splice(this.top);

        console.log(this.arr);

        return popped;
    }

    peek() {
        console.log(this.arr);

        return this.arr[this.top];
    }
}

class Queue {
    constructor(size) {
        this.arr = [];
        this.size = size;
    }

    enqueue(data) {
        if (this.arr.length === this.size) return;

        this.arr.push(data);

        console.log(this.arr);
    }

    dequeue() {
        if (this.arr.length === 0) return;

        const dq = this.arr.shift();

        console.log(this.arr);

        return dq;
    }
}

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

        if (this.count === 0) this.head = node;
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
        if (this.count === 0) return;
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
        let currentNode = this.head;

        console.log(currentNode.data);

        while (currentNode.next) {
            currentNode = currentNode.next;

            console.log(currentNode.data);
        }
    }
}

class MaxHeap {
    constructor() {
        this.arr = [];
    }

    insert(data) {
        const last = this.arr.length;

        this.arr[last] = data;
        this._heapUp(last);        
    }

    _heapUp(index) {
        if (index) {
            const parentIndex = parseInt((index - 1) / 2);

            if (this.arr[index] > this.arr[parentIndex]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[parentIndex];
                this.arr[parentIndex] = tmp;

                this._heapUp(parentIndex);
            }
        }
    }

    delete() {
        if (this.arr.length < 2) return this.arr.pop();

        const del = this.arr[0];

        this.arr[0] = this.arr.pop();
        this._heapDown(0);

        return del;
    }

    _heapDown(index) {
        let left, right, largeIndex;

        if (index * 2 + 1 < this.arr.length) {
            left = this.arr[index * 2 + 1];

            if (index * 2 + 2 < this.arr.length) {
                right = this.arr[index * 2 + 2];
            }

            if (left < right) largeIndex = index * 2 + 2;
            else largeIndex = index * 2 + 1;

            if (this.arr[index] < this.arr[largeIndex]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[largeIndex];
                this.arr[largeIndex] = tmp;

                this._heapDown(largeIndex);
            }
        }
    }
}

class MinHeap {
    constructor() {
        this.arr = [];
    }

    insert(data) {
        const last = this.arr.length;

        this.arr[last] = data;
        this._heapUp(last);
    }

    _heapUp(index) {
        if (index) {
            const parentIndex = parseInt((index - 1) / 2);

            if (this.arr[index] < this.arr[parentIndex]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[parentIndex];
                this.arr[parentIndex] = tmp;

                this._heapUp(parentIndex);
            }
        }
    }

    delete() {
        if (this.arr.length < 2) return this.arr.pop();

        const del = this.arr[0];

        this.arr[0] = this.arr.pop();
        this._heapDown(0);

        console.log(this.arr);

        return del;
    }

    _heapDown(index) {
        let left, right, smallIndex;

        if (index * 2 + 1 < this.arr.length) {
            left = index * 2 + 1;

            if (index * 2 + 2 < this.arr.length) {
                right = index * 2 + 2;
            }

            if (left < right) smallIndex = index * 2 + 1;
            else smallIndex = index * 2 + 2;

            if (this.arr[index] > this.arr[smallIndex]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[smallIndex];
                this.arr[smallIndex] = tmp;

                this._heapDown(smallIndex);
            }
        }
    }
}

const mh = new MinHeap();

mh.insert(5);
mh.insert(14);
mh.insert(39);
mh.insert(1);
mh.insert(12);

while (mh.arr.length) {
    mh.delete();
}