class LinkedListNode {
	constructor(data) {
		this.data = data;
		this.next = null;
	}
}

class LinkedList {
	constructor(head = null) {
		this.head = head;
	}

	clear() {
		this.head = null;
	}

	getLast() {
		let e;
		for (e = this.head;e && e.next;e = e.next);

		return e;
	}

	add(node) {
		let last = this.getLast();
		if (last)
			last.next = node;
		else
			this.head = node;
	}
	
	size() {
		let i = 0;
		for (let e = this.head;e;e = e.next, i++);

		return i;
	}

	toArray() {
		let arr = new Array(this.size());

		for (let e = this.head, i = 0;e;e = e.next, i++)
			arr[i] = e;

		return arr;
	}
}
