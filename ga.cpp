#include <vector>
#include <tuple>
#include <random>

using  std::vector;
using  std::pair;

std::random_device rd{};
std::mt19937 randgen(rd);

using chromosome_t = pair<double ,vector<char> > ;

vector<chromosome_t> ga(int max_iterations = 10) {
    vector<chromosome_t> population = init_population();
    int iteration = 0;
    while(iteration < max_iterations) {
        for (auto &e:population) e = fitness(e);
        auto parents = selection(population);
        //auto elite = get_elite(population);
        auto offspring = crossover(parents);
        offspring = mutation(offspring);
        //population = merge_with_elite(offspring,elite);
        population = offspring;
        iteration++;
    }
    return population;
}

vector<chromosome_t> selection(vector<chromosome_t> &pop) {
    vector<chromosome_t> new_pop;
    std::uniform_int_distribution rand_dist(0,(int)pop.size()-1);
    #pragma omp parallel for
    for (int i = 0; i < pop.size(); i++) {
        chromosome_t specimen[2] = {pop.at(rand_dist(randgen)),pop.at(rand_dist(randgen))};
        new_pop.push_back((specimen[0].first > specimen[1].first)?specimen[0]:specimen[1]);
    }
    return new_pop;
}



chromosome_t fitness(chromosome_t &chromosome) {
    chromosome_t ret = chromosome;
    ret.first = 0;
    for (auto i : chromosome.second) ret.first += i;
    return ret;
}

chromosome_t get_random_chromosome(int chr_size = 16) {
    chromosome_t ret = {0.0,{}};
    std::uniform_int_distribution rand_01(0,1);
    for (int i = 0; i < chr_size; i++) {
        ret.second[i] = rand_01(randgen);
    }
    return ret;
}

vector<chromosome_t> init_population(int pop_size = 50, int chr_size = 16) {
    vector<chromosome_t> population;
    for (int i = 0; i < pop_size; i++) {
        population.push_back( get_random_chromosome(chr_size));
    }
    return population;
}
