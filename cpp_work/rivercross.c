/* 
   过河问题： 老老虎、小老虎、老狮子、小狮子、
   老熊、小熊共六个动物准备过河，
   河边有一条船，一次至多只能搭载两个动物。
   只有三个老动物和小老虎会划船。
   当小动物与其父亲不在一块时，其它在场的
   老动物会吃点该小动物。 问：这些动物如何安全过河？

   解题思路： 1) 6个动物和一条船的过河状态共有
   128种(2的7次方)。根据题目中的约束要求，
   可以剔除掉其中的无效状态，
   比如：小老虎和老狮子在一起，但老老虎却在
   对岸。过河状态可以用7个比特位表示，全0表示
   初始出发态，全1表示全部已过河状态。

   2) 在剩下的有效状态中，识别所有有效的
   状态迁移关系，构造一个有向状态图，
   图中每个节点表示一个状态。

   3) 在有向图中，从初始态节点向目标态
   节点搜索一条路径，该路径就是本题的解。 */

#include <stdio.h>
#include <stdlib.h>

#define bitn1(n)    (0x01<<(n))
#define bitn0(n)  (~(bitn1(n)))
#define setbit1(b,n)  ((b)=(b) | bitn1(n))
#define setbit0(b,n)  ((b)=(b) & bitn0(n) )
#define getbit(b,n)  (((b) & bitn1(n))>>(n))

#define bit_i(b,i)  ((b) & bitn1(i))
#define bit_i_v(b,i) (bit_i(b,i)>>(i))

#define bit0(b)  bit_i_v(b,0)
#define bit1(b)  bit_i_v(b,1)
#define bit2(b)  bit_i_v(b,2)
#define bit3(b)  bit_i_v(b,3)
#define bit4(b)  bit_i_v(b,4)
#define bit5(b)  bit_i_v(b,5)
#define bit6(b)  bit_i_v(b,6)

#define NULL_PTR    0

typedef unsigned int UINT32;
typedef unsigned char UINT8;
typedef struct {
  UINT8 *p;                     // 指向位图，位图中的bit位记录节点间的有向关系
  UINT32 n;                     // 节点数
  UINT8 *aFlag;                 // 搜索路径时，用于存节点是否被访问过
} GRAPH_S;

struct path_edge {
  UINT32 vs;
  UINT32 ve;
  UINT32 cost;
  struct path_edge *prev;
  struct path_edge *next;
  struct path_edge *parent;
};

typedef struct path_edge PATH_EDGE_S;

GRAPH_S *create_graph(int n) {
  int bitnum;
  GRAPH_S *ptr = 0;

  bitnum = n * n;
  if ((bitnum % 8) != 0)
    bitnum += 8 - bitnum % 8;
  ptr = (GRAPH_S *) malloc(sizeof(GRAPH_S));
  if (ptr == 0)
    return 0;

  ptr->n = n;
  ptr->p = 0;
  ptr->aFlag = 0;
  ptr->p = (UINT8 *) malloc(bitnum / 8);
  if (ptr->p == 0) {
    free(ptr);
    return 0;
  }
  ptr->aFlag = (UINT8 *) malloc(n);
  if (ptr->aFlag == 0) {
    free(ptr);
    return 0;
  }
  memset(ptr->p, 0, bitnum / 8);
  memset(ptr->aFlag, 0, n);
  return ptr;
}

void free_graph(GRAPH_S * ptr) {
  if (ptr == 0)
    return;

  free(ptr->p);
  free(ptr->aFlag);
  free(ptr);
  return;
}

int setarc(GRAPH_S * ptr, UINT32 i, UINT32 j, UINT8 v) {
  UINT32 pos = 0, bytepos = 0, offset = 0;
  if (ptr == 0)
    return 0;

  if (i >= ptr->n || j >= ptr->n)
    return 0;

  if (v != 0 && v != 1)
    return 0;
  pos = i * ptr->n + j;
  bytepos = pos / 8;
  offset = pos % 8;
  if (v == 1)
    setbit1(ptr->p[bytepos], offset);
  else
    setbit0(ptr->p[bytepos], offset);

  return 1;
}

int getarc(GRAPH_S * ptr, UINT32 i, UINT32 j, UINT8 * pv) {
  UINT32 pos = 0, bytepos = 0, offset = 0;
  if (ptr == 0 || pv == 0)
    return 0;

  if (i >= ptr->n || j >= ptr->n)
    return 0;

  pos = i * ptr->n + j;
  bytepos = pos / 8;
  offset = pos % 8;

  *pv = getbit(ptr->p[bytepos], offset);
  return 1;
}

// 从cur节点出发，找未访问过的下个联通节点
UINT32 next_vertex(GRAPH_S * pG, UINT32 cur, UINT32 * nextv) {
  UINT32 j;
  UINT8 v = 0;

  for (j = 0; j < pG->n; j++) {
    if (0 == getarc(pG, cur, j, &v))
      continue;
    if (v == 0)
      continue;
    if (pG->aFlag[j])
      continue;
    *nextv = j;
    return 1;
  }

  return 0;
}

UINT32 get_adj_node(GRAPH_S * pG, UINT32 ve, UINT32 * aNode) {
  UINT32 j, num = 0;
  UINT8 v = 0;

  for (j = 0; j < pG->n; j++) {
    if (0 == getarc(pG, ve, j, &v))
      continue;
    if (v == 0)
      continue;
    aNode[num] = j;
    num++;
  }

  return num;
}

UINT32 get_idle_adj_node(GRAPH_S * pG, UINT32 ve, UINT32 * aNode) {
  UINT32 j, num = 0;
  UINT8 v = 0;

  for (j = 0; j < pG->n; j++) {
    if (pG->aFlag[j] == 1)
      continue;
    if (0 == getarc(pG, ve, j, &v))
      continue;
    if (v == 0)
      continue;
    aNode[num] = j;
    num++;
  }

  return num;
}


UINT32 get_an_idle_node(GRAPH_S * pG, UINT32 * v) {
  UINT32 j;

  for (j = 0; j < pG->n; j++) {
    if (0 == pG->aFlag[j])
      break;
  }

  if (j == pG->n)
    return 0;
  *v = j;
  return 1;
}


int search_path(GRAPH_S * pG, UINT32 from, UINT32 dest, UINT32 * a,
                UINT32 * pNum) {
  UINT32 ret = 0, nextv, top;

  if (pG == 0 || a == 0 || pNum == 0)
    return 0;
  if (from >= pG->n || dest >= pG->n)
    return 0;

  a[0] = from;
  *pNum = 1;

  memset(pG->aFlag, 0, pG->n);
  pG->aFlag[from] = 1;

  while (*pNum > 0) {
    top = a[*pNum - 1];
    if (top == dest)
      return 1;
    ret = next_vertex(pG, top, &nextv);
    if (ret == 0) {
      (*pNum)--;
    } else {
      a[*pNum] = nextv;
      (*pNum)++;
      pG->aFlag[nextv] = 1;
    }
  }

  return 0;

}

void insert_edge_in_queue(PATH_EDGE_S ** pQueue, PATH_EDGE_S * pNode) {
  PATH_EDGE_S *temp;

  pNode->prev = NULL_PTR;
  pNode->next = NULL_PTR;
  if (*pQueue == NULL_PTR) {
    *pQueue = pNode;
    return;
  }

  temp = *pQueue;
  while (temp) {
    if (pNode->cost <= temp->cost) {
      if (temp->prev == NULL_PTR) {
        temp->prev = pNode;
        pNode->next = temp;
        *pQueue = pNode;
        break;
      }

      pNode->prev = temp->prev;
      pNode->next = temp;
      pNode->prev->next = pNode;
      temp->prev = pNode;
      break;
    }

    if (temp->next == NULL_PTR) {
      temp->next = pNode;
      pNode->prev = temp;
      break;
    }
    temp = temp->next;
  }

  return;
}

PATH_EDGE_S *delete_edge_from_queue(PATH_EDGE_S ** pQue) {
  PATH_EDGE_S *temp;

  if (*pQue == NULL_PTR)
    return NULL_PTR;
  temp = *pQue;

  *pQue = temp->next;
  if (*pQue != NULL_PTR) {
    (*pQue)->prev = NULL_PTR;
  }

  temp->prev = NULL_PTR;
  temp->next = NULL_PTR;
  return temp;
}

void free_queue(PATH_EDGE_S * pQue) {
  PATH_EDGE_S *temp, *temp2;

  temp = pQue;
  while (temp) {
    temp2 = temp;
    temp = temp->next;
    free(temp2);
  }
  return;
}

PATH_EDGE_S *found_node_in_seq(PATH_EDGE_S * pSeq, UINT32 ve) {
  PATH_EDGE_S *temp, *found = NULL_PTR;

  temp = pSeq;
  while (temp) {
    if (temp->ve == ve) {
      found = temp;
      break;
    }
    temp = temp->next;
  }

  return found;
}

void get_min_path(PATH_EDGE_S * pSeq, UINT32 dest, UINT32 * aPath,
                  UINT32 * pNum) {
  PATH_EDGE_S *p, *temp;

  p = found_node_in_seq(pSeq, dest);
  if (p == NULL_PTR) {
    *pNum = 0;
    return;
  }

  temp = p;
  *pNum = 0;
  while (temp) {
    aPath[*pNum] = temp->ve;
    (*pNum)++;
    temp = temp->parent;
  }

  return;
}

int search_min_path(GRAPH_S * pG, UINT32 from, UINT32 dest, UINT32 * a,
                    UINT32 * pNum) {
  UINT32 node_num = 0, i, success = 0, aNode[64];
  PATH_EDGE_S *pPriQue, *pSeq, *pTemp, *p;

  if (pG == 0 || a == 0 || pNum == 0)
    return 0;
  if (from >= pG->n || dest >= pG->n)
    return 0;

  pPriQue = NULL_PTR;
  pSeq = NULL_PTR;

  pTemp = (PATH_EDGE_S *) malloc(sizeof(PATH_EDGE_S));
  if (pTemp == NULL_PTR) {
    printf("\r\nalloc path edge node failed");
    return 0;
  }
  pTemp->vs = from;
  pTemp->ve = from;
  pTemp->cost = 0;
  pTemp->parent = NULL_PTR;
  insert_edge_in_queue(&pPriQue, pTemp);


  while (pPriQue != NULL_PTR) {
    p = delete_edge_from_queue(&pPriQue);

    if (found_node_in_seq(pSeq, p->ve)) {
      free_queue(p);
      continue;
    }

    insert_edge_in_queue(&pSeq, p);

    if (p->ve == dest) {
      success = 1;
      break;
    }
    node_num = get_adj_node(pG, p->ve, aNode);
    // printf("\r\nnode num=%d\r\n",node_num);

    for (i = 0; i < node_num; i++) {
      pTemp = (PATH_EDGE_S *) malloc(sizeof(PATH_EDGE_S));
      if (pTemp == NULL_PTR) {
        printf("\r\nalloc path edge node failed");
        free_queue(pPriQue);
        free_queue(pSeq);
        return 0;
      }
      pTemp->vs = p->ve;
      pTemp->ve = aNode[i];
      pTemp->cost = p->cost + 1;
      pTemp->parent = p;
      insert_edge_in_queue(&pPriQue, pTemp);
    }
  }

  if (success == 0) {
    free_queue(pPriQue);
    free_queue(pSeq);
    return 0;
  }
  get_min_path(pSeq, dest, a, pNum);
  free_queue(pPriQue);
  free_queue(pSeq);
  return 1;
}



UINT32 check_state(UINT8 i) {

  /* 
     bit0: 船, bit1: 老老虎, bit2: 老狮子, bit3:老熊, bit4:
     小老虎,bit5: 小狮子, bit6: 小熊 */

  // 船所在侧必须有会划船的动物
  if (bit0(i) == 0) {
    if (bit1(i) == 1 && bit2(i) == 1 && bit3(i) == 1 && bit4(i) == 1)
      return 0;
  }

  if (bit0(i) == 1) {
    if (bit1(i) == 0 && bit2(i) == 0 && bit3(i) == 0 && bit4(i) == 0)
      return 0;
  }

  /* 小动物和对应老动物不在一块时，
     小动物不能和其它老动物在一块 */
  if (bit1(i) != bit4(i)) {
    if ((bit4(i) == bit2(i)) || (bit4(i) == bit3(i)))
      return 0;
  }

  if (bit2(i) != bit5(i)) {
    if ((bit5(i) == bit1(i)) || (bit5(i) == bit3(i)))
      return 0;
  }

  if (bit3(i) != bit6(i)) {
    if ((bit6(i) == bit1(i)) || (bit6(i) == bit2(i)))
      return 0;
  }

  return 1;
}

void init_state_list(UINT8 * pS, UINT8 * pNum) {
  UINT8 i, j = 0;

  for (i = 0; i < 128; i++) {
    if (check_state(i)) {
      pS[j] = i;
      j++;
    }
  }

  *pNum = j;
  return;
}

UINT32 check_2state_transition(UINT8 s1, UINT8 s2) {
  UINT8 b, bit1234 = 0, bit56 = 0;
  UINT8 i, mask = 0;

  // 船必须过河
  if (bit0(s1) == bit0(s2))
    return 0;

  // 找出和船同侧的动物
  for (i = 0; i < 7; i++) {
    if (getbit(s1, i) == bit0(s1))
      mask |= bitn1(i);
  }

  b = s1 ^ s2;                  // 找出状态变化的位
  // 与船不同侧的位不能过河(变化)
  if (b & (~mask))
    return 0;

  if (bit1(b))
    bit1234++;
  if (bit2(b))
    bit1234++;
  if (bit3(b))
    bit1234++;
  if (bit4(b))
    bit1234++;
  if (bit5(b))
    bit56++;
  if (bit6(b))
    bit56++;

  // 必须要有会划船的过河
  if (bit1234 == 0)
    return 0;

  // 过河动物最多两个
  if ((bit1234 + bit56) > 2)
    return 0;

  return 1;
}

// 构造状态迁移图
void init_transition(GRAPH_S * pG, UINT8 * pState) {
  UINT8 i, j;
  UINT32 n;

  n = pG->n;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (i == j)
        continue;
      if (check_2state_transition(pState[i], pState[j]))
        setarc(pG, i, j, 1);
    }
  }
  return;
}

// 检查状态图是否对称，检查是否存在孤立的状态
void check_graph(GRAPH_S * pG, UINT8 * aState) {
  UINT32 i, j;
  UINT8 a = 0, b = 0;
  UINT8 flag, s;

  printf("\r\n");

  flag = 0;
  for (i = 0; i < pG->n - 1; i++) {

    for (j = i + 1; j < pG->n; j++) {
      getarc(pG, i, j, &a);
      getarc(pG, j, i, &b);
      if (a != b) {
        flag = 1;
        printf("\r\nFound non symmetry");
        break;
      }
    }
  }

  if (flag == 0)
    printf("\r\nThe state transition directed graph is symmetrical");

  printf("\r\nStates which have no transion to or from any other state");
  for (i = 0; i < pG->n; i++) {
    flag = 0;
    for (j = 0; j < pG->n; j++) {
      getarc(pG, i, j, &a);
      if (a != 0) {
        flag = 1;
        break;
      }
    }

    if (flag == 0) {
      s = aState[i];
      printf("\r\nState %2d:   %6d%6d%6d%6d%6d%6d%6d",
             i,
             bit_i_v(s, 0),
             bit_i_v(s, 1),
             bit_i_v(s, 2),
             bit_i_v(s, 3), bit_i_v(s, 4), bit_i_v(s, 5), bit_i_v(s, 6));
    }
  }

  return;
}

void get_isolate_graphs(GRAPH_S * pG, UINT8 a[64][64], UINT32 * grp_num,
                        UINT32 node_num[64]) {
  UINT32 i, n, adj_node_num, aNode[64];
  PATH_EDGE_S *pQue, *pTemp, *p;

  memset(pG->aFlag, 0, pG->n);

  *grp_num = 0;

  while (get_an_idle_node(pG, &n)) {
    pQue = NULL_PTR;

    pTemp = (PATH_EDGE_S *) malloc(sizeof(PATH_EDGE_S));
    if (pTemp == NULL_PTR) {
      printf("\r\nalloc path edge node failed");
      return;
    }
    pTemp->vs = n;
    pTemp->ve = n;
    pTemp->cost = 0;
    pTemp->parent = NULL_PTR;

    insert_edge_in_queue(&pQue, pTemp);

    node_num[*grp_num] = 0;
    while (pQue != NULL_PTR) {
      p = delete_edge_from_queue(&pQue);
      a[*grp_num][node_num[*grp_num]] = p->vs;
      node_num[*grp_num]++;
      pG->aFlag[p->vs] = 1;

      adj_node_num = get_idle_adj_node(pG, p->vs, aNode);
      for (i = 0; i < adj_node_num; i++) {
        pTemp = (PATH_EDGE_S *) malloc(sizeof(PATH_EDGE_S));
        if (pTemp == NULL_PTR) {
          printf("\r\nalloc path edge node failed");
          free_queue(pQue);
          return;
        }
        pTemp->vs = aNode[i];
        pTemp->ve = aNode[i];
        pTemp->cost = 0;
        pTemp->parent = NULL_PTR;
        insert_edge_in_queue(&pQue, pTemp);
      }

      free_queue(p);
    }
    (*grp_num)++;
  }

  return;
}

void print_isolate_graphs(GRAPH_S * pG) {
  UINT8 a[64][64];
  UINT32 i, j, grp_num = 0;
  UINT32 node_num[64];

  get_isolate_graphs(pG, a, &grp_num, node_num);

  printf("\r\n");
  for (i = 0; i < grp_num; i++) {
    printf("\r\nsub graph %i:   ", i);
    for (j = 0; j < node_num[i]; j++) {
      printf("%d, ", a[i][j]);
    }
  }
  return;
}

void print_cross_river_steps(UINT8 * aState, UINT8 state_num, UINT32 * aPath,
                             UINT32 vertex_num) {
  UINT32 i, j;
  UINT8 s, prev, next;
  char *str[] = { "boat", "Tiger", "Lion", "Bear", "tiger", "lion", "bear" };

  printf("\r\ncross river step number: %d\r\n", vertex_num - 1);

  // 输出该路径上的状态列表
  printf("\r\n boat Tiger Lion Bear tiger lion bear ");
  printf("\r\n-------------------------------------------");
  for (i = 0; i < vertex_num; i++) {
    s = aState[aPath[i]];
    printf("\r\n%6d%6d%6d%6d%6d%6d%6d",
           bit_i_v(s, 0), bit_i_v(s, 1), bit_i_v(s, 2), bit_i_v(s, 3),
           bit_i_v(s, 4), bit_i_v(s, 5), bit_i_v(s, 6));
  }

  printf("\r\n-------------------------------------------\r\n");
  printf("Steps:");
  prev = aState[aPath[0]];
  for (i = 1; i < vertex_num; i++) {
    next = aState[aPath[i]];
    s = prev ^ next;
    if (bit0(next) == 1)
      printf("\r\n >>:");
    else
      printf("\r\n <<:");

    for (j = 1; j <= 6; j++) {
      if (bit_i_v(s, j))
        printf("%-5s", str[j]);
    }
    prev = next;
  }
  return;
}
int main(void) {
  GRAPH_S *pG = 0;
  UINT8 aState[128];
  UINT32 aPath[64], aPath2[64];
  UINT8 state_num = 0;
  UINT32 vertex_num = 0, i, j;
  UINT8 s;

  // 找出所有有效的状态
  init_state_list(aState, &state_num);

  // 构造一个状态图，图中的节点为状态，弧表示状态迁移关系
  pG = create_graph(state_num);
  if (pG == 0)
    printf("\r\ncreate graph failed ");

  init_transition(pG, aState);


  printf("\r\n1.Info of the state transition graph ");
  printf("\r\nstate number:%d ", state_num);
  check_graph(pG, aState);
  print_isolate_graphs(pG);

  // 在图中找一条从初始态到终止态的路径
  if (0 == search_path(pG, 0, state_num - 1, aPath, &vertex_num)) {
    printf("\r\nsearch path failed.");
  }
  printf("\r\n\r\n2.simple search method ");
  print_cross_river_steps(aState, state_num, aPath, vertex_num);

  if (0 == search_min_path(pG, 0, state_num - 1, aPath, &vertex_num)) {
    printf("\r\nsearch min path failed.");
  }
  for (i = 0; i < vertex_num; i++) {
    aPath2[vertex_num - 1 - i] = aPath[i];
  }
  printf("\r\n\r\n3.min path search method ");
  print_cross_river_steps(aState, state_num, aPath2, vertex_num);

  free_graph(pG);
  return 1;
}