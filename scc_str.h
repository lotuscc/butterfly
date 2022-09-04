

#define scc_str_MIN_LEN 32
#define scc_str_Reserved_Space 32

struct scc_str {
    struct scc_str *next;
    int idx;
    int len;
    int cap;
};

typedef struct scc_str *scc_str_node_t;
typedef scc_str_node_t *scc_str_node_ptr_t;

typedef struct scc_str *scc_str_t;
typedef scc_str_t *scc_str_ptr_t;


scc_str_t scc_str_init(const char *s);



scc_str_t scc_str_pop_front(scc_str_t str, int size);
void scc_str_pop_back(scc_str_t str, int size);

scc_str_t scc_str_push_front(scc_str_t str, const char *s);
void scc_str_push_back(scc_str_t str, const char *s);

scc_str_t scc_str_cut_front(scc_str_t str, int size);
scc_str_t scc_str_cut_back(scc_str_t str, int size);

scc_str_t scc_str_pop_front(scc_str_t str, int size);
void scc_str_pop_back(scc_str_t str, int size);

scc_str_t scc_str_push_front(scc_str_t str, const char *s);
void scc_str_push_back(scc_str_t str, const char *s);

scc_str_t scc_str_cut_front(scc_str_t str, int size);
scc_str_t scc_str_cut_back(scc_str_t str, int size);

void scc_str_node_free(scc_str_t str);
void scc_str_free(scc_str_t str);
void scc_str_clean(scc_str_t str);

void scc_str_tidy(scc_str_t str);

void scc_str_print(const scc_str_t s);
void scc_str_println(const scc_str_t s);