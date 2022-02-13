typedef struct
{
    pthread_t tid;
    pthread_mutex_t exec_mutex;
    size_t size;
    int num;
    int duration;
    int elapsed;
} Customer;

Customer* new_Customer()
{
    Customer* c = malloc(sizeof(Customer));
    c->num = 0;
    c->duration = 0;
    c->elapsed = 0;
    return c;
}

typedef struct
{
    Customer **queue;
    int read_idx;
    int write_idx;
    int num_queued;
    int len;
} WaitQueue;

WaitQueue new_WaitQueue(int len)
{
    WaitQueue q;
    q.read_idx = 0;
    q.write_idx = 0;
    q.num_queued = 0;
    q.len = len;
    q.queue = (Customer **)malloc(sizeof(Customer *) * len);
    return q;
}

int WQ_isFull(WaitQueue *q) {
    return q->len == q->num_queued;
}

int WQ_isEmpty(WaitQueue *q) {
    return q->num_queued == 0;
}

void WQ_push(WaitQueue *q, Customer* c)
{
    int next_write_idx = (q->write_idx + 1) % q->len;
    // printf("WRITE: Writeidx: %d, Readidx: %d, ", q->write_idx, q->read_idx);
    if (WQ_isFull(q))
    {
        // printf("WRITE: Queue full. Write blocked\n");
        return;
    }

    q->queue[q->write_idx] = c;
    q->write_idx = next_write_idx;
    q->num_queued++;
    // printf("q.len: %d, q.num_queued: %d\n", q->len, q->num_queued);
}

Customer* WQ_pop(WaitQueue *q) {
    int next_read_idx = (q->read_idx + 1) % q->len;
    // printf("READ: Writeidx: %d, Readidx: %d, ", q->write_idx, q->read_idx);
    if (WQ_isEmpty(q)) {
        printf("[   WQ   ] Queue empty. Read blocked and NULL returned.\n");
        return NULL;
    }

    Customer* c = q->queue[q->read_idx];
    q->read_idx = next_read_idx;
    q->num_queued--;
    // printf("q.len: %d, q.num_queued: %d\n", q->len, q->num_queued);
    return c;
    
}