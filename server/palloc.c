#include <palloc.h>
/*

typedef struct test_s test;


struct test_s{
    int val;
    test *next;
};

*/


pool_t* pool_init(size_t size){

    pool_t  *p;

    p = malloc(size);
    if (p == NULL) {
        return NULL;
    }

    p->last = (u_char *) p + sizeof(pool_t) + sizeof(data_t);
    p->end = (u_char *) p + size;
    

    size = size - sizeof(pool_t);
    p->size = size;

    p->current = p;
    p->next = NULL;
    return p;
}

void* pool_alloc(size_t size, pool_t *pool){
    u_char *m;
    pool_t *p, *np;
    p = pool->current;


    if(p){
        m = p->last;
        if ((size_t) (p->end - m) > size) {
            p->last = m + size;

            return m;
        }
    }
    //p = pool;
    np = pool_init(default_size);
    while (1){
        p->current = np;
        if (p->next){
            p = p->next;
        }else{
            break;
        }
    }
    p->next = np;
    pool_alloc(size, pool);

}


void* pool_free(){

    return NULL;
}

pool_t* pool_destroy(pool_t *pool, pool_t *target){
    pool_t *p, *prev, *c;
    p = pool;
    if (pool == target){
        p = p->next;
        free(pool);
        return p;
    }

    if (p->current == target){
        while(p && p!=target){
            c = p;
            p = p->next;
        }
    }

    p = pool;

    while(1){
        prev = p;

        if (p->current == target){
            p->current = c;
        }

        p = p->next;
        if (!p){
            break;
            printf("no pool found");
        }
        if(p == target){
            prev->next = p->next;
            free(p);
            break;
        }
    }

    return pool;
}

/*
int main(void){
    pool_t *pool_ptr = pool_init(default_size);
    test *test_ptr, *temp_ptr;

    test_ptr = pool_alloc(sizeof(test), pool_ptr);
    test_ptr->val = 0;

    temp_ptr = test_ptr;
    int i = 1;
    do{
        temp_ptr->next = pool_alloc(sizeof(test), pool_ptr);
        if (!temp_ptr->next){
            break;
        }
        temp_ptr->next->val = i;
        temp_ptr = temp_ptr->next;
        i++;
    }while(i < 1000);
    temp_ptr = test_ptr;
    while (temp_ptr){
        printf("%d\n",temp_ptr->val);
        temp_ptr = temp_ptr->next;
    }
    return 0;
}
*/