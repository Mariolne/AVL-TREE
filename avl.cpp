#include"iostream"
using namespace std;

struct tree{
    int val, h;
    tree*l, *r;
    tree() : val(0), h(0), l(nullptr), r(nullptr) {}
    tree(int x) : val(x), h(1), l(nullptr), r(nullptr) {}
    tree(int x, tree* ll, tree* rr) : val(x), h(1), l(ll), r(rr) {}
};

int get_h(tree* p){
    return p ? p -> h : 0;
}

void update_h(tree* p){
    if(p){
        p -> h = max(get_h(p -> l), get_h(p -> r)) + 1;
    }
}

int get_bf(tree* p){
    return p ? get_h(p -> l) - get_h(p -> r) : 0;
}

void LL_rotate(tree*& t){
    tree* y = t;
    tree* x = y -> l;
    tree* z = x -> r;

    x -> r = y;
    y -> l = z;

    update_h(y);
    update_h(x);

    t = x;
}

void RR_rotate(tree*& t){
    tree* y = t;
    tree* x = t -> r;
    tree* z = x -> l;
    
    x -> l = y;
    y -> r = z;

    update_h(y);
    update_h(x);

    t = x;
}

void LR_rotate(tree*& t){
    RR_rotate(t -> l);
    LL_rotate(t);
}

void RL_rotate(tree*& t){
    LL_rotate(t -> r);
    RR_rotate(t);
}   

void insert_avl(tree*& t, int x){
    if(!t){
        t = new tree(x);
        return;
    }

    if(x < t -> val) insert_avl(t -> l, x);
    else insert_avl(t -> r, x);

    update_h(t);
    int bf = get_bf(t);

    if(bf > 1 && get_bf(t -> l) >= 0) LL_rotate(t);
    else if(bf < -1 && get_bf(t -> r) <= 0) RR_rotate(t);
    else if(bf > 1 && get_bf(t -> l) < 0) LR_rotate(t);
    else if(bf < -1 && get_bf(t -> r) > 0) RL_rotate(t);

}

tree* min_node(tree* node){
    tree* p = node;
    while(p -> l)
        p = p -> l;

    return p;
}

void delete_avl(tree*& t, int x){
    if(!t) return;
    
    if(x < t -> val) delete_avl(t -> l, x);
    else if(x > t -> val) delete_avl(t -> r, x);
    else{
        if(!(t -> l) || !(t -> r)){
            tree* tmp = t -> l ? t -> l : t -> r;
            if(!tmp){
                delete t;
                t = nullptr;
            }

            else {
                tree* p = t;
                t = tmp;
                delete p;
            }
        }
        else{
            tree* tmp = min_node(t -> r);
            t -> val = tmp -> val;
            delete_avl(t -> r, tmp -> val);
        }
    }

    if(!t) return;

    update_h(t);
    int bf = get_bf(t);

    if(bf > 1 && get_bf(t -> l) >= 0) LL_rotate(t);
    else if(bf < -1 && get_bf(t -> r) <= 0) RR_rotate(t);
    else if(bf > 1 && get_bf(t -> l) < 0) LR_rotate(t);
    else if(bf < -1 && get_bf(t -> r) > 0) RL_rotate(t);
    
}

void print_tree(tree* t) {
    if (!t) return;
    cout << t->val;

    if (t->l || t->r) {
        cout << '(';
        print_tree(t->l);
        cout << ',';
        print_tree(t->r);
        cout << ')';
    }
}

tree* find_node(tree* t, int x){
    if(!t) return nullptr;

    if(x < t -> val) return find_node(t -> l, x);
    else if(x > t -> val) return find_node(t -> r, x);
    else return t;
}

void destroy_tree(tree* t) {
    if (!t) return;

    destroy_tree(t->l);
    destroy_tree(t->r);

    delete t;
}

int main(){
    tree* root = nullptr;
    int op, x;

    while(1){

        cout << "1. 插入\n";
        cout << "2. 删除\n";
        cout << "3. 查找\n";
        cout << "4. 打印树\n";
        cout << "5. 重置\n";
        cout << "6. 退出\n";

        cin >> op;

        if (op == 6) break;

        if(op == 1){
            cout << "输入-1停止操作\n";
            while(cin >> x && x != -1){
                insert_avl(root, x);
            }
        }

        else if(op == 2){
            cout << "输入-1停止操作\n";
            while(cin >> x && x != -1){
                delete_avl(root, x);
            }
        }

        else if(op == 3){
            cout << "输入-1停止操作\n";
            while(cin >> x && x != -1){
                tree* res = find_node(root, x);

                if (res) cout << x << "\n";
                else cout << x << "不存在\n";
            }
        }

        else if(op == 4){
            print_tree(root);
        }

        else if(op == 5){
            destroy_tree(root);
            root = nullptr;
        }
    }

    destroy_tree(root);

    return 0;
}