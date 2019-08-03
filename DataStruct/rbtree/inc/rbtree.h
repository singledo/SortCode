#ifndef _rbtree_h
#define _rbtree_h
#include "com.h"

/* struct declaration start */
enum rb_color
{
    RED = 0,
    BLACK 
};
typedef enum rb_color tColor;


struct rb_node
{
    struct rb_node *pa;
    struct rb_node *l;
    struct rb_node *r;
    enum   rb_color color;
    ull    key;
    void   *data;
};
typedef struct rb_node tRB_node;

typedef void (*compare_func)(ull key1, ull key2);
typedef tRB_node* (*create_func)(ull key, void *data, tColor color);
typedef void (*free_func)(tRB_node *del);

struct tree
{
    struct rb_node *root;
    compare_func  compare;
    create_func   creat;
    free_func     free;
};
typedef struct tree tTree;


/* struct declaration end */

/* function declararion start */

bool key_compare (ull key1, ull key2);
void rbtree_init(tTree *tree);
tRB_node* rbtree_create_node(ull key, void *data, tColor color);
void rbtree_free(tRB_node *del);
void rbtree_set_sub_l(tRB_node *dest, tRB_node *left);
void rbtree_set_sub_r(tRB_node *dest, tRB_node *right);
void rbtree_set_parent(tRB_node *dest, tRB_node *pa);
tRB_node* rbtree_lookup(tTree *tree, ull key);
bool rbtree_insert(tTree *tree, ull key, void *data, tColor color);
void rbtree_set_color(tRB_node *dest, tColor color);

void rbtree_left_rotate (tTree *tree, tRB_node *node);
void rbtree_right_rotate (tTree *tree, tRB_node *node);
void rbtree_insert_fix (tTree *tree, tRB_node *node);

bool rbtree_del(tTree *tree, ull key, tRB_node **dest_node);
void rbtree_del_fix (tTree *tree, tRB_node *node);

/* function declararion end */

#endif
