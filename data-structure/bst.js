class Node {
	constructor(data) {
		this.data = data;
		this.left;
		this.right;
	}
}

class BinarySearchTree {
	constructor(data) {
		this.count = 1;
		this.root = new Node(data);
	}

	insert(data) {
		const node = new Node(data);

		this._insert(this.root, node);
		this.count++;
	}

	// recursion
	_insert(root, node) {
		if (node.data < root.data) {
			root.left = this._insert(root.left, node);
		}

		if (node.data > root.data) {
			root.right = this._insert(root.right, node);
		}

		return root;
	}

	find(data) {
		if (!this.root) return null;
		
		return this._find(this.root, data);
	}

	// recursion
	_find(root, data) {
		if (data < root.data) return this._find(root.left, data);
		if (data > root.data) return this._find(root.right, data);
			
		return root;
	}

	remove(data) {
		if (!root) return null;

		const node = this._remove(this.root, data);

		this.root = node;
		this.count--;
	}

	// recursion
	_remove(root, data) {
		let exchange, tmp;

		if (data < root.data) root.left = this._remove(root.left. data);
		else if (data > root.data) root.right = this._remove(root.right, data);
		else { // root.data === data
			if (!root.left) return root.right;
			else if (!root.right) return root.left;
			else {
				exchange = root.left;

				// root.left의 제일 하위 node로 갈 때 까지 반복
				while (exchange.right) exchange = exchange.right;

				// 교환
				tmp = root.data;
				root.data = exchange;
				exchange = tmp;

				root.left = this._remove(root.left, exchange.data);
			}
		}
	}
}

const tree = new Tree(10);

tree.insert(3);
tree.insert(62);
tree.insert(123);