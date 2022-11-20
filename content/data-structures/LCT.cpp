/**
 * Author: Hanfei Chen
 * Description: Vertex set and path composite
 */
struct F {
	num a, b;
	friend F compose(const F& a, const F& b) {
		return F{a.a * b.a, a.a * b.b + a.b};
	}
	num eval(num x) const {
		return a * x + b;
	}
};

/// start-hash
struct node {
	static node* null;

	node* p;
	node* c[2];
	bool flip;
	
	F val;
	F sum;
	F revsum;

	bool r() {
		return !(p && p->c[d()] == this);
	}
	int d() {
		assert(p);
		return p->c[1] == this;
	}

	void do_flip() {
		flip = !flip;
		swap(c[0], c[1]);
		swap(sum, revsum);
	}

	void propagate() {
		if (flip) {
			flip = false;
			for (int i = 0; i < 2; i++) {
				c[i]->do_flip();
			}
		}
	}
	void propagate_all() {
		assert(p != null);
		if (!r()) p->propagate_all();
		propagate();
	}

	void update() {
		sum = compose(c[1]->sum, compose(val, c[0]->sum));
		revsum = compose(c[0]->revsum, compose(val, c[1]->revsum));
	}

	void rot() {
		assert(p);
		assert(!p->flip);
		assert(!flip);
		int x = d();
		node* pa = p;
		node* ch = c[!x];
		if (!pa->r()) pa->p->c[pa->d()] = this;
		p = pa->p;
		c[!x] = pa;
		pa->p = this;
		pa->c[x] = ch;
		ch->p = pa;
		pa->update();
		update();
	}

	void splay() {
		propagate_all();
		while (!r()) {
			if (!p->r()) {
				if (d() == p->d()) {
					p->rot();
				} else {
					rot();
				}
			}
			rot();
		}
	}

	void expose() {
		splay();
		while (p) {
			p->splay();
			p->c[1] = this;
			rot();
		}
		c[1] = null;
		update();
		assert(r());
	}

	void make_root() {
		expose();
		do_flip();
	}

	void link(node* n) {
		make_root();
		p = n;
	}

	void cut() {
		expose();
		assert(c[0] != null);
		c[0]->p = NULL;
		c[0] = null;
		update();
	}
};
/// end-hash
node* node::null = new node();

int main() {
	int N, Q;
	cin >> N >> Q;
	vector<node> nodes(N);
	node::null->val = node::null->sum = node::null->revsum = F{num(1), num(0)};
	for (int i = 0; i < N; i++) {
		nodes[i].c[0] = nodes[i].c[1] = node::null;
		int a, b;
		cin >> a >> b;
		nodes[i].val = F{num(a), num(b)};
		nodes[i].update();
	}
	for (int e = 0; e < N-1; e++) {
		int u, v;
		cin >> u >> v;
		nodes[u].link(&nodes[v]);
	}
	for (int q = 0; q < Q; q++) {
		int t;
		cin >> t;
		if (t == 0) {
			int u, v, w, x;
			cin >> u >> v >> w >> x;
			nodes[u].make_root();
			nodes[v].cut();
			nodes[w].link(&nodes[x]);
		} else if (t == 1) {
			int p, a, b;
			cin >> p >> a >> b;
			nodes[p].splay();
			nodes[p].val = F{num(a), num(b)};
			nodes[p].update();
		} else if (t == 2) {
			int u, v, x;
			cin >> u >> v >> x;
			nodes[u].make_root();
			nodes[v].expose();
			cout << int(nodes[v].sum.eval(x)) << '\n';
		} else assert(false);
	}
}
