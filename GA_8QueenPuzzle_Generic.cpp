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

vi Random_vector(){ // returns a random genetic chain of a individual in the population, parameterized on a permutation of a 1 to 8 vector. Each number represents the row of a queen on the i-th column
    vector<int> h(NumQueen);
    for(int i=0;i<NumQueen;i++) h[i] = 1+rand()%NumQueen;
    random_shuffle(h.begin(), h.end());
    return h;
}

pvi Crossover(vi a, vi b){ // return a pair os genetic chain reproduced from 2 mother chains with a random crossover section 
    pvi r = {vi(NumQueen), vi(NumQueen)};
    int pos = rand()%(NumQueen-1), i;
    for(i=0;i<=pos;i++){
        r.f[i] = a[i];
        r.s[i] = b[i];
    }
    for(;i<NumQueen;i++){
        r.f[i] = b[i];
        r.s[i] = a[i];
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

vvi Reproduce(vvi p){ // Sets the Roulette Wheel and generates a new population by reproducing with Crossover OX randomly the population, based on each individual Fitness
    int Total = 0;
    pvi u;
    vvi new_p;
    vi sum_prob(NumPopulation);
    for(int i=0;i<NumPopulation;i++){
        Total += Fitness_Calc(p[i]);
        sum_prob[i] = Total; // accumulated sum to set the Roulette Whell
    }
    for(int i=0;i<NumPopulation/2;i++){
        u = Crossover(p[Binary_Search(sum_prob, rand()%Total)], p[Binary_Search(sum_prob, rand()%Total)]); // Binary search on the accumulated sum to based on fitness value select the progenitors
        new_p.push_back(u.f); // Crossover Generates two "sons" by the division on the genetic chain
        new_p.push_back(u.s);
    }
    return new_p;
}

vi Mutation(vi a){ // Randomly selects some positions on the genetic chain to suffer mutation.
    int ref = RAND_MAX*MutationRatio, k; // MutationRatio is the probability setted to a mutation to happen
    for(int i=0;i<NumQueen;i++){
        if(rand()<=ref){
            a[i] = (((1+(k=rand()%(NumQueen-1)))==a[i])? NumQueen:1+k); // The number on the i-th position that will mutate, will change to one of the other NumQueen-1 possibilities
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
    ios_base :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    srand((unsigned) time(NULL));
    Genetic_Algorithm();
    cout << endl;
    return (0);
}