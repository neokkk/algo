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
            left = this.arr[index * 2 + 1];

            if (index * 2 + 2 < this.arr.length) {
                right = this.arr[index * 2 + 2];
            }

            if (typeof right === 'undefined' || left < right) smallIndex = index * 2 + 1;
            else smallIndex = index * 2 + 2;

            console.log('smallIndex:', smallIndex, ':', this.arr[smallIndex]);

            if (this.arr[index] > this.arr[smallIndex]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[smallIndex];
                this.arr[smallIndex] = tmp;

                this._heapDown(smallIndex);
            }
        }
    }
}