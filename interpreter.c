#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct ll_node {
  char val;
  struct ll_node* next;
  struct ll_node* prev;
};

struct ll_node data;
struct ll_node* dp;

// Create a new linked list node on the heap
// and initialize it with a value of 0
// Sets both links to NULL so parenting is flexible
struct ll_node* cell_init(void) {
  struct ll_node* new = malloc(sizeof(struct ll_node));
  new->val = 'W';
  new->next = NULL;
  new->prev = NULL;
  return new;
}

// Recursivly free memory starting at cell
// Will only clear nodes that are connected to
// the given cell
void clear_mem(struct ll_node* cell) {
  if (cell == NULL) return;
  clear_mem(cell->next);
  clear_mem(cell->prev);
  free(cell);
}

// Evaluates the program provided in the buffer. This will allocate new space 
// as needed, but wont free it, so make sure to call clear_mem(dp) at some
// point in the future. This also assumes that there is a data pointer called
// dp in the global scope.
void eval_program(char* buf) {
  int input;
  for(char* ip = buf; *ip != '\0'; ip++) {
    switch (*ip) {
      case '>':
        if (dp->next == NULL) {
          dp->next = cell_init();
          dp->next->prev = dp;
        }
        dp = dp->next;
        break;

      case '<':
        if (dp->prev == NULL) {
          dp->prev = cell_init();
          dp->prev->next = dp;
        }
        dp = dp->prev;
        break;

      case '+':
        dp->val++;
        break;

      case '-':
        dp->val--;
        break;

      case '.':
        printf("%c", dp->val);
        break;

      case ',':
        input = fgetc(stdin);
        dp->val = (char)input;
        break;

      case '[':
        
        break;

      case ']':

        break;

      default:
        break;
    }
  }
}

void _print_data_backward(struct ll_node* cell) {
  if (cell == NULL) {
    printf("|");
    return;
  }
  _print_data_backward(cell->prev);
  printf("%d|", cell->val);
}

void _print_data_forward(struct ll_node* cell) {
  if (cell == NULL) {
    printf("|");
    return;
  }
  printf("|%d", cell->val);
  _print_data_forward(cell->prev);
}

// Displays all non-null nodes connected to the given
// parent cell in logical linked-list order
void print_data(struct ll_node* cell) {
  printf("\nMem: ");
  if (cell != NULL) {
    _print_data_backward(cell->prev);    
    printf("DP -> %d", cell->val);
    _print_data_forward(cell->next);
  } else {
    printf("|null memory|");
  }
  printf("\n");
}


int main(int argc, char** argv) {
  
  // Only start the REPL if given no args
  if (argc != 1) return 0;
  printf("++ BFREPL ++\n");
  char buf[256];
  dp = cell_init();

  while (1) { 
    printf("\n#");
    fgets(buf, sizeof(buf), stdin);

    // Since data and pointer is gloabal, mutation is persitant
    // The state of the data array and the pointer will be preserved
    // across multiple program calls
    eval_program(buf);
    print_data(dp);
  }

  clear_mem(dp);
  return 0;
}
