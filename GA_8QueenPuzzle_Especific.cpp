#include <bits/stdc++.h>
#define f first
#define s second
#define NumQueen 8
#define Max_Possible 28
#define NumPopulation 100
#define NumIterations 1000
#define MutationRatio (double)0.01
using namespace std;

typedef vector<int> vi;
typedef pair<vi,vi> pvi;
typedef vector<vi> vvi;

// Different from the generic version
vi Random_vector(){ // returns a random genetic chain of a individual in the population, parameterized on a permutation of a 1 to 8 vector. Each number represents the row of a queen on the i-th column
    vector<int> h(NumQueen);
    for(int i=0;i<NumQueen;i++) h[i] = 1+i;
    random_shuffle(h.begin(), h.end());
    return h;
}

// Different from the generic version
vi CrossoverOX(vi a, vi b){ // return a pair os genetic chain reproduced from 2 mother chains with a random crossover section 
    vi r(NumQueen, 0), vis = vi(NumQueen+1, 0);
    int pos1 = rand()%NumQueen, pos2 = rand()%NumQueen, i, j=0;
    if(pos1>pos2) swap(pos1, pos2);
    for(i=pos1;i<=pos2;i++){
        r[i] = a[i];
        vis[a[i]] = 1;
    }
    for(i=0;i<NumQueen;i++){
        if(!r[i]){
            while(vis[b[j]]) j++;
            vis[b[j]] = 1;
            r[i] = b[j];
        }
    }
    return r;
}

int Fitness_Calc(vi a){ // The function which we must find its maximum value. In this case it is the number of non-attacking queens on the chess board
    int resp = Max_Possible;
    for(int i=0;i<NumQueen-1;i++){
        for(int j=i+1;j<NumQueen;j++){
            if(abs(a[i]-a[j])==j-i || a[i]==a[j]) resp--;
        }
    }
    return resp;
}

int Binary_Search(vi v, int num){
    int l = 0, r = v.size()-1, m;
    while(l<r){
        m = (l+r)/2;
        if(v[m]>num) r = m;
        else l = m+1;
    }
    return l;
}

// Different from the generic version
vvi Reproduce(vvi p){ // Sets the Roulette Wheel and generates a new population by reproducing with Crossover OX randomly the population, based on each individual Fitness
    int Total = 0;
    pvi u;
    vvi new_p;
    vi sum_prob(NumPopulation);
    for(int i=0;i<NumPopulation;i++){
        Total += Fitness_Calc(p[i]);
        sum_prob[i] = Total; // accumulated sum to set the Roulette Whell
    }
    for(int i=0;i<NumPopulation;i++) new_p.push_back(CrossoverOX(p[Binary_Search(sum_prob, rand()%Total)], p[Binary_Search(sum_prob, rand()%Total)])); // Binary search on the accumulated sum to based on fitness value select the progenitors
    return new_p;
}

// Different from the generic version
vi Mutation(vi a){ // Randomly selects some positions on the genetic chain to suffer mutation. The mutation swaps 2 positions on the chain, there are 2 ways of doing that.
    int ref = RAND_MAX*MutationRatio; // MutationRatio is the probability setted to a mutation to happen
    for(int i=0;i<NumQueen;i++){
        if(rand()<=ref){
            //swap(a[i], a[(i+1)%NumQueen]); //Possibility 1 to swap with the next number
            int k = rand()%(NumQueen-1); //Possibility 2 to swap with a random other position
            swap(a[i], a[(k==i)? NumQueen-1:k]);
        }
    }
    return a;
}

vvi Mutate(vvi p){ // Runs Mutation on all individuals of the population
    for(int i=0;i<NumPopulation;i++){
        p[i] = Mutation(p[i]);
    }
    return p;
}

int Found_Maximum(vvi p){ // Finds the individual position in p that has the greatest Fitness value
    int m = 0, pos = -1;
    for(int i=0;i<NumPopulation;i++){
        if(Fitness_Calc(p[i])>m){
            pos = i;
            m = Fitness_Calc(p[i]);
        }
    }
    return pos;
}

void Genetic_Algorithm(){
    vvi Pop = vvi(NumPopulation, Random_vector());
    int Iterations=NumIterations, k;
    for(int i=0;i<NumIterations;i++){
        if(Fitness_Calc(Pop[k = Found_Maximum(Pop)])==Max_Possible){
            Iterations = i;
            break;
        }
        Pop = Reproduce(Pop);
        Pop = Mutate(Pop); 
    }
    cout << "Number of Iterations: " << Iterations << endl;
    if(Fitness_Calc(Pop[k])<Max_Possible) cout << "It wasn't possible to find the real maximum number of pairs of unattacking queens" << endl;
    cout << "Maximum found: " << Fitness_Calc(Pop[k]) << endl;
    for(int i=0;i<NumQueen;i++) cout << Pop[k][i] << ' ';
}

int main(){
    srand((unsigned) time(NULL)); // sets the rand seed to be based on time, to have a acceptable pseudo-randomness
    Genetic_Algorithm();
    return (0);
}