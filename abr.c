#define _GNU_SOURCE
#include "abr.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

btree * createNode( int key, type_t content , btree * fg , btree * fd )
{
  btree * n =( btree *) malloc (sizeof(btree)) ;
  n->key = key;
  n->content = content ;
  n->fg = fg ;
  n->fd = fd;

  return n;
}

// int isBalanced(btree* t)
// {
//   int lh;
//   int rh;
//   if(!t)
//     return 1;
//   // lh = height(t->fg);
//   // rh = height(t->fd);
//   return abs(lh - rh) <= 1 && isBalanced(t->fg) && isBalanced(t->fd);
// }


int isBSTUtil(btree * t, int min, int max)
{
  if(t == NULL)
    return 1;
  if(t->key < min || t->key > max)
    return 0;
  return isBSTUtil(t->fg,min,t->key) &&  isBSTUtil(t->fd,t->key,max);
}

int isBST(btree * t)
{
  return(isBSTUtil(t, INT_MIN, INT_MAX)); 
}

btree* insert(btree *tree, int key, int new){
  if(tree!=NULL){
    if ((key >= tree->key) && (tree->fd == NULL)){
      tree->fd = createNode(key, new, NULL, NULL);
    }
    else if ((key < tree->key) && (tree->fg == NULL)){
      tree->fg = createNode(key, new, NULL, NULL);
    }
    else{
      if (key < tree->key){
        insert(tree->fg, key, new);
      }
      else{
        insert(tree->fd, key, new);
      }
    }
  }
  else{
    tree=createNode(key, new, NULL, NULL);
  }
  return(tree);
}

void deleteTree(btree*tree){
	if(tree->fg==NULL && tree->fd==NULL){
		free(tree);
	}
	else{
    if(tree->fg!=NULL){
      deleteTree(tree->fg);
    }
		else{
		  deleteTree(tree->fd);
    }
	}
}

void print_order(btree* tree){
	if (tree != NULL){
		print_order(tree->fg);
		printf("%d ", tree->key);
		print_order(tree->fd);
	}
}

void print_root_fg_fd(btree* tree){
  if (tree!=NULL){
    printf("%d ", tree->key);
    print_root_fg_fd(tree->fg);
    print_root_fg_fd(tree->fd);
  }
}

btree* search(btree*tree, int key){
	if (tree!=NULL){
		if (key == tree->key){
			return tree;
		}
		else if (key > tree->key){
			return (search(tree->fd, key));
		}
		else if (key < tree->key){
			return (search(tree->fg, key));
		}
	}
	return NULL;
}

btree* minBST(btree* tree){
  btree* tmp=tree;
  while (tmp->fg!=NULL){
    tmp=tmp->fg;
  }
  return tmp;
  deleteTree(tmp);
}

btree* maxBST(btree* tree){
  btree* tmp=tree;
  while (tmp->fd!=NULL){
    tmp=tmp->fd;
  }
  return tmp;
  deleteTree(tmp);
}

btree* delete(btree *tree, int key){
	// printf("on est dans %d\n", tree->key);
	if(tree == NULL){
		return tree;
	}
	if(tree->key < key){
		tree->fd = delete(tree->fd, key);
	}
	else if(tree->key > key){
		tree->fg = delete(tree->fg, key);
	}
	else{
		if(tree->fd == NULL){
			btree* t = tree->fg; 
			free(tree);
			return t; 
		}
		else if(tree->fg == NULL){
			btree* t = tree->fd; 
			free(tree);
			return t;
		}
		else{
			btree* min = tree->fg; 
			while(min->fd != NULL){
				min = min->fd;
			}
			tree->key = min->key;
			tree->fg = delete(tree->fg, min->key);
		}
	}
	return tree;
}


int height(btree* t){
  int height=0;
  btree* tmp=t;
  while(tmp->fg!=NULL){
    tmp=tmp->fg;
    height++;
  }
  if (tmp->fd!=NULL){
    height++;
  }
  return height;
  deleteTree(tmp);
}

btree* rotationLeft(btree *t){
  btree* tmp=t->fd;
  t->fd=t->fd->fg;
  tmp->fg=t;
  return tmp;
  free(tmp);
}
btree* rotationRight(btree *t){
  btree* tmp=t->fg;
  t->fg=t->fg->fd;
  tmp->fd=t;
  return tmp;
  free(tmp);
}