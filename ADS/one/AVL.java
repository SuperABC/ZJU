import java.util.*;
public class AVL {
	static node root = null;
	@SuppressWarnings("resource")
	public static void main(String[] args){
		int n = 0;
		Scanner s = new Scanner(System.in);
		n = s.nextInt() - 1;
		root = new node(null, s.nextInt());
		node tmp = null;
		for(int i = 0; i < n; i++){
			tmp = insert(root, s.nextInt());
			node.updateBf(tmp);
			rotate(tmp);
			while(root.pre!=null)root = root.pre;
			node.updateBf(tmp);
		}
		System.out.println(root.getValue());
	}
	static node insert(node r, int val){
		if(val<r.getValue()){
			if(r.left==null){
				r.setLeft(new node(r, val));
				return r.left;
			}
			else return insert(r.left, val);
		}
		else if(val >r.getValue()){
			if(r.right==null){
				r.setRight(new node(r, val));
				return r.right;
			}
			else return insert(r.right, val);
		}
		else return r;
	}
	static void rotate(node n){
		node start = n;
		node tmp1 = null, tmp2 = null;
		while(start.pre!=null){
			if(start.needRot())break;
			start = start.pre;
		}
		if(start.pre==null&&!start.needRot())return;
		node prev = start.pre;
		int lr;
		if(prev==null)lr = 0;
		else if(prev.left==start)lr = 1;
		else if(prev.right==start)lr = 2;
		else lr = 0;
		if(start.bf>0){
			if(start.left.bf>0){
				tmp1 = start.deleteLeft();
				tmp2 = start;
				start = tmp1;
				if(lr==1)prev.left = start;
				if(lr==2)prev.right = start;
				start.pre = tmp2.pre;
				tmp1 = start.deleteRight();
				start.setRight(tmp2);
				start.right.setLeft(tmp1);
			}
			else if(start.left.bf<0){
				tmp1 = start.left.right.deleteLeft();
				tmp2 = start.left.deleteRight();
				start.left.setRight(tmp1);
				tmp1 = start.deleteLeft();
				tmp2.setLeft(tmp1);
				tmp1 = tmp2.deleteRight();
				start.setLeft(tmp1);
				tmp1 = start;
				start = tmp2;
				if(lr==1)prev.left = start;
				if(lr==2)prev.right = start;
				start.pre = tmp1.pre;
				start.setRight(tmp1);
			}
		}
		else if(start.bf<0){
			if(start.right.bf>0){
				tmp1 = start.right.left.deleteRight();
				tmp2 = start.right.deleteLeft();
				start.right.setLeft(tmp1);
				tmp1 = start.deleteRight();
				tmp2.setRight(tmp1);
				tmp1 = tmp2.deleteLeft();
				start.setRight(tmp1);
				tmp1 = start;
				start = tmp2;
				if(lr==1)prev.left = start;
				if(lr==2)prev.right = start;
				start.pre = tmp1.pre;
				start.setLeft(tmp1);
			}
			else if(start.right.bf<0){
				tmp1 = start.deleteRight();
				tmp2 = start;
				start = tmp1;
				if(lr==1)prev.left = start;
				if(lr==2)prev.right = start;
				start.pre = tmp2.pre;
				tmp1 = start.deleteLeft();
				start.setLeft(tmp2);
				start.left.setRight(tmp1);
			}
		}
	}
}
class node{
	private int value;
	int bf, height;
	node pre, left, right;
	node(node n, int i){
		value = i;
		bf = height = 0;
		pre = n;
		left = null;
		right = null;
	}
	int getValue(){
		return value;
	}
	node getPre(){
		return pre;
	}
	void setLeft(node n){
		left = n;
		if(n!=null){
			n.pre = this;
		}
		bf = (n==null?-1:n.height) - (right==null?-1:right.height);
		height = 1+Math.max(left==null?-1:left.height, right==null?-1:right.height);
	}
	node getLeft(){
		return left;
	}
	node deleteLeft(){
		if(left==null)return null;
		else{
			bf -= 1+left.height;
			height = 1+(right==null?-1:right.height);
			node tmp = left;
			left = null;
			return tmp;
		}
	}
	void setRight(node n){
		right = n;
		if(n!=null){
			n.pre = this;
		}
		bf = (n==null?-1:n.height) - (left==null?-1:left.height);
		height = 1+Math.max(left==null?-1:left.height, right==null?-1:right.height);
	}
	node getRight(){
		return right;
	}
	node deleteRight(){
		if(right==null)return null;
		else{
			bf -= 1+right.height;
			height = 1+(left==null?-1:left.height);
			node tmp = right;
			right = null;
			return tmp;
		}
	}
	boolean needRot(){
		return bf<=-2||bf>=2;
	}
	static void updateBf(node n){
		while(n!=null){
			n.bf = (n.left==null?-1:n.left.height)-(n.right==null?-1:n.right.height);
			n.height = 1+Math.max(n.left==null?-1:n.left.height, n.right==null?-1:n.right.height);
			n = n.pre;
		}
	}
}
