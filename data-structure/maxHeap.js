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

            if (typeof right === 'undefined' || left > right) largeIndex = index * 2 + 1;
            else largeIndex = index * 2 + 2;

            if (this.arr[index] < this.arr[largeIndex]) {
                let tmp = this.arr[index];;
                this.arr[index] = this.arr[largeIndex];
                this.arr[largeIndex] = tmp;

                this._heapDown(largeIndex);
            }
        }
    }

    sort() {
        const sorted = [];

        while (this.arr.length) {
            sorted.push(this.delete());
        }

        return sorted;
    }
}

const mh = new MaxHeap();

mh.insert(5);
mh.insert(7);
mh.insert(1);
mh.insert(13);
mh.insert(3);
mh.insert(8);

console.log(mh.sort());