class Heap {
	constructor() {
		this.arr = [];
	}

	insert(data) {
		const last = this.arr.length - 1;

		this.arr[last] = data;

		this._heapUp(last);
	}

	_heapUp(index) {
		let parent = parseInt((index - 1) / 2);

		if (this.arr[index] > this.arr[parent]) {
			let tmp = this.arr[index];
			this.arr[index] = this.arr[parent];
			this.arr[parent] = tmp;

			this._heapUp(parent);
		}
	}

	delete() {
		if (this.arr.length === 0) return null;

		const del = this.arr[0];

		this.arr[0] = this.arr.pop();
		this._heapDown(0);

		return del;
	}

	_heapDown(index) {
		let left, right, max;

		if (index * 2 + 1 < this.arr.length) {
			left = index * 2 + 1;

			if (index * 2 + 2 < this.arr.length - 1) {
				right = index * 2 + 2;
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