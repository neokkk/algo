class Node {
	constructor(data) {
		this.data = data;
		this.left;
		this.right;
	}
}

class Tree {
	constructor(data) {
		this.count = 0;
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
			return root;
		}

		if (node.data > root.data) {
			root.right = this._insert(root.right, node);
			return root;
		}

		return root;
	}

	find(data) {
		if (!this.root) return null;
		else return this._find(this.root, data);
	}

	// recursion
	_find(node, data) {
		if (node) { // node 있으면
			if (data < node.data) {
				return this._find(node.left, data);
			} else if (data > node.data) {
				return this._find(node.right, data);
			} else {
				return node;
			}
		} else { // 없으면
			return null;
		}
	}

	remove(data) {
		const node = this._remove(this.root, data);

		if (node) {
			this.root = node;
			this.count--;
		}
	}

	// recursion
	_remove(root, data) {
		let exchange, tmp;

		if (!root) return false;
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