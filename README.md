# ga-demo
Genetic Algorithm demo

This repo contains example genetic algorithm implementation in c++.


## Basic schematic of Genetic Algorithm

```c++
vector<chromosome_t> genetic_algorithm() {
    vector<chromosome_t> population = init_population();
    population = calculate_fitness(population);
    while(!termination_condition(population)) {
        auto parents = selection(population);
        auto elite = get_elite(population);
        auto offspring = crossover(parents);
        offspring = mutation(offspring);
        population = merge_with_elite(offspring,elite);
        population = calculate_fitness(population);
    }
    return population;
}
```
