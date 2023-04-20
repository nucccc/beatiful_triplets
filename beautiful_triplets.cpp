/*
 * Complete the 'beautifulTriplets' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER d
 *  2. INTEGER_ARRAY arr
 */
 
constexpr int TUPLE_LEN = 3;

template <int SIZE>
class RingBuffer {
public:
    RingBuffer<SIZE>() : index{-1}, len{0} {}
    
    void push(int num) {
        ++this->index;
        ++this->len;
        this->len = std::min(this->len, static_cast<int>(this->buffer.size()));
        if(this->index >= this->buffer.size()) {
            index = 0;
        }
        this->buffer[index] = num;        
    }
    
    inline void addAtCurrIndex(int num) {
        this->buffer[index] += num;
    }
    
    inline void clear() {
        this->index = -1;
        this->len = 0;
    }
    
    inline int size() const {
        return this->len;
    }
    
    inline int multBuffer() const {
        int result = 1;
        for(int elem : this->buffer) result *= elem;
        return result;
    }
    
    inline bool full() const { return this->len == this->buffer.size(); }
    
private:
    /*  the current index i'm inserting stuff at */
    int index;
    /*  len is the actual size of the buffer */
    int len;
    /*  buffer is the array actually containing elements */
    std::array<int, SIZE> buffer;
};

class BeatifulTriplets {
public:
    BeatifulTriplets(
        int d,
        const std::vector<int> & arr
    ) : d{d}, arr{arr} {
        this->triplets_counter = std::vector< RingBuffer<TUPLE_LEN> >(this->d);
        this->last_val_at_mod = std::vector< int >(this->d, -2 * d);
    }
    
    int solve() {
        int mod, prev, result = 0;
        
        mod = this->arr.front() % this->d;
        prev = this->arr.front();
        this->insertNewVal( this->arr.front(), mod );
        
        for(int i = 1; i < this->arr.size(); ++i) {
            
            if(prev != this->arr[i]) {
                if(this->triplets_counter[mod].full()) 
                    result += this->triplets_counter[mod].multBuffer();
                
                mod = this->arr[i] % this->d;
                this->insertNewVal( this->arr[i], mod );
                prev = this->arr[i];
            } else {
                this->triplets_counter[mod].addAtCurrIndex(1);
            }
        }
        
        /*  in the end by default i ensure to execute the check */
        if(this->triplets_counter[mod].full())
            result += this->triplets_counter[mod].multBuffer();
        
        return result;
    }
    
    void insertNewVal(int val, int mod) {
        if(val > this->last_val_at_mod[mod] + d) this->triplets_counter[mod].clear();
        this->last_val_at_mod[mod] = val;
        this->triplets_counter[mod].push(1);        
    }
private:
    int d;
    const std::vector<int> & arr;
    std::vector< RingBuffer<TUPLE_LEN> > triplets_counter;
    std::vector<int> last_val_at_mod;
};

int beautifulTriplets(int d, vector<int> arr) {
    BeatifulTriplets solver(d, arr);
    
    return solver.solve();
    /*int mod, div;
    int prev_num;
    int result = 0;
    std::vector< std::vector< std::pair<int, int> > > support;
    
    //initializing support
    support.reserve(d);
    for(int i = 0; i < d; ++i) support.emplace_back( std::vector<std::pair<int, int>>() );
    
    prev_num = arr[0];
    
    mod = prev_num % d;
    div = prev_num / d;
    
    support[mod].emplace_back( std::make_pair(div, 1) );
    
    for(int i = 1; i < static_cast<int>(arr.size()); ++i) {
        if (arr[i] == prev_num) {
            support[mod].back().second += 1;
        } else {
            //i shall check if i should augment result;
            if(support[mod].size() >= TUPLE_LEN) {
                bool tuple_complete = true;
                for(int j = 0; j < TUPLE_LEN - 1 && tuple_complete ; ++j) {
                    if( support[mod][ support[mod].size() - 1 - j ].first - support[mod][ support[mod].size() - 2 - j ].first != 1 ) tuple_complete = false;
                }
                if(tuple_complete) {
                    int n_triplets = 1;
                    std::vector<int> tuple;
                    for(int j = 0; j < TUPLE_LEN ; ++j) {
                        tuple.push_back(support[mod][ support[mod].size() - 1 - j ].first * d + mod);
                        n_triplets *= support[mod][ support[mod].size() - 1 - j ].second;
                    }
                    result += n_triplets;
                    for(int elem : tuple) std::cout << elem << " ";
                    std::cout << endl;
                }
            }
            
            prev_num = arr[i];
    
            mod = prev_num % d;
            div = prev_num / d;
            
            support[mod].emplace_back( std::make_pair(div, 1) );
        }
    }
    
    if(support[mod].size() >= TUPLE_LEN) {
        bool tuple_complete = true;
        for(int j = 0; j < TUPLE_LEN - 1 && tuple_complete ; ++j) {
            if( support[mod][ support[mod].size() - 1 - j ].first - support[mod][ support[mod].size() - 2 - j ].first != 1 ) tuple_complete = false;
        }
        if(tuple_complete) {
            int n_triplets = 1;
            std::vector<int> tuple;
            for(int j = 0; j < TUPLE_LEN ; ++j) {
                tuple.push_back(support[mod][ support[mod].size() - 1 - j ].first * d + mod);
                n_triplets *= support[mod][ support[mod].size() - 1 - j ].second;
            }
            result += n_triplets;
            for(int elem : tuple) std::cout << elem << " ";
            std::cout << endl;
        }
    }
    
    return result;*/
}
