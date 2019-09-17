class Heap { // max Heap
    constructor() {
        this.arr = [];
    }

    insert(data) {
        const last = this.arr.length;

        this.arr[last] = data;
        this._heapUp(last);

        return true;
    }

    delete() {
        if (this.arr.length < 2) return this.arr.pop();

        const del = this.arr[0];

        this.arr[0] = this.arr.pop(); // 제일 하위 node와 교환
        this._heapDown(0);

        return del;
    }

    sort() {
        const sort = [];

        for (let i in this.arr) {
            sort.push(this.delete());
        }

        return sort;
    }

    /* recursion */
    _heapUp(index) {
        if (index) {
            const parent = parseInt((index - 1) / 2); // 부모 node의 index

            if (this.arr[index] > this.arr[parent]) { // 부모 node 값보다 크면 교환
                let tmp = this.arr[index];
                this.arr[index] = this.arr[parent];
                this.arr[parent] = tmp;

                this._heapUp(parent);
            }
        }
    }

    _heapDown(index) {
        let left, right, max;

        if (index * 2 + 1 < this.arr.length) { // root.left index
            left = this.arr[index * 2 + 1];

            if (index * 2 + 2 < this.arr.length - 1) { // ?
                right = this.arr[index * 2 + 2];
            }

            if (left > right) max = index * 2 + 1;
            else max = index * 2 + 2;

            if (this.arr[index] < this.arr[max]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[max];
                this.arr[max] = tmp;

                this._heapDown(max);
            }
        }
    }
}

const heap = new Heap();

heap.insert(5);
heap.insert(310);
heap.insert(120);
heap.insert(41);
console.log(heap.arr);
heap.delete();
console.log(heap.arr);