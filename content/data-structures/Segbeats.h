/**
 * Author: Hanfei Chen
 * Description: segment tree beats abstracted
 */

#pragma once

/// start-hash
template <class N> struct segbeats {
	vector<N> seg;
	int s;
	segbeats() {}
	template <class T> segbeats(const vector<T>& a) {
		int n = int(a.size());
		s = 1 << (n <= 1 ? 0 : 32 - __builtin_clz(n-1));
		seg.resize(2*s);
		for (int i = 0; i < n; i++) {
			seg[s+i] = a[i];
		}
		for (int i = s-1; i >= 1; i--) {
			upd_node(i);
		}
	}
	void propagate(int i) {
		seg[i].propagate(seg[2*i], seg[2*i+1]);
	}
	void upd_node(int i) {
		seg[i] = N::merge(seg[2*i], seg[2*i+1]);
	}
	template <class F, class... Args> void upd(int i, int l, int r, int ql, int qr, F f, Args&&... args) {
		if (r <= ql || qr <= l) return;
		if (ql <= l && r <= qr && (seg[i].*f)(forward<Args>(args)...)) return;
		propagate(i);
		int m = (l+r)/2;
		upd(2*i, l, m, ql, qr, f, forward<Args>(args)...);
		upd(2*i+1, m, r, ql, qr, f, forward<Args>(args)...);
		upd_node(i);
	}
	template <class F, class G, class H> auto query(int i, int l, int r, int ql, int qr, F f, G g, H h) {
		if (r <= ql || qr <= l) return h;
		if (ql <= l && r <= qr) {
			return (seg[i].*f)();
		}
		propagate(i);
		int m = (l+r)/2;
		return g(query(2*i, l, m, ql, qr, f, g, h), query(2*i+1, m, r, ql, qr, f, g, h));
	}
	template <class F, class... Args> void upd(int l, int r, F f, Args&&... args) {
		assert(l <= r);
		upd(1, 0, s, l, r, f, forward<Args>(args)...);
	}
	template <class F, class G, class H> auto query(int l, int r, F f, G g, H h) {
		assert(l <= r);
		return query(1, 0, s, l, r, f, g, h);
	}
};
/// end-hash

// range affine range sum
// https://judge.yosupo.jp/submission/114707
/// start-hash
struct D {
	num a, b, c;
	int s;
	D(num v = 0, int len = 1) : a(1), b(0), c(v), s(len) {}
	bool affine(pair<num, num> z) {
		a *= z.first;
		b = b * z.first + z.second;
		c *= z.first;
		c += z.second * s;
		return true;
	}
	void propagate(D& x, D& y) {
		x.affine(make_pair(a, b));
		y.affine(make_pair(a, b));
		a = 1, b = 0;
	}
	static D merge(const D& x, const D& y) {
		return D(x.c + y.c, x.s + y.s);
	}
	num getsum() {
		return c;
	}
};
/// end-hash

// copied from https://judge.yosupo.jp/submission/8028
// setmin, setmax, add, sum
/// start-hash
struct D{
	const static int w[2];
	struct MaxData{
		ll a,b,c;
		MaxData(ll v):a(v),b(-INF),c(1){}
		ll ch(ll v){
			assert(v>b);
			ll dif=min(v-a,ll(0));
			a+=dif;
			return c*dif;
		}
		void updb(ll v){
			assert(v<a);
			setmax(b,v);
		}
		void add(ll v){
			a+=v;
			b+=v;
		}
		static MaxData merge(const MaxData&x,const MaxData&y){
			MaxData res(max(x.a,y.a));
			res.c=0;
			for(auto z:{x,y}){
				setmax(res.b,z.a<res.a?z.a:z.b);
				if(res.a==z.a)res.c+=z.c;
			}
			return res;
		}
	} d[2];
	ll sum,len,lzc[2],lza;
	D(ll v=0):d{MaxData(v),MaxData(-v)},sum(v),len(1),lzc{INF,INF},lza(0){}
	bool allsame(){
		return d[0].a==-d[1].a;
	}
	// 0->setmin, 1->setmax
	bool change(int k,ll v){
		v*=w[k];
		if(allsame()){
			return add(min(v-d[k].a,ll(0))*w[k]);
		}
		if(v>d[k].b){
			setmin(lzc[k],v);
			sum+=d[k].ch(v)*w[k];
			d[k^1].updb(-v);
			return true;
		}
		return false;
	}
	bool add(ll v){
		lza+=v;
		for (int k=0; k<2; k++) lzc[k]+=v*w[k];
		sum+=len*v;
		for (int k=0; k<2; k++) d[k].add(v*w[k]);
		return true;
	}
	void propagate(D&x,D&y){
		auto sub=[&](D&z){
			z.add(lza);
			for (int k=0; k<2; k++) {
				bool res=z.change(k,w[k]*lzc[k]);
				assert(res);
			}
		};
		sub(x);
		sub(y);
		for (int k=0; k<2; k++) lzc[k]=INF;
		lza=0;
	}
	ll gets(){
		return sum;
	}
	static D merge(const D&x,const D&y){
		D res;
		for (int k=0 ;k<2 ;k++) res.d[k]=MaxData::merge(x.d[k],y.d[k]);
		res.sum=x.sum+y.sum;
		res.len=x.len+y.len;
		return res;
	}
};
const int D::w[2]{1,-1};
/// end-hash
