import random
import sys
import time
def initialize(chromosomelen):
    population = []   
    for i in range(1000):
        chromosome = []
        for j in range(chromosomelen):           
            chromosome.append(random.choice([0,1,2,3]))
        population.append(chromosome)
    return population

def fitness(maze, current, chromosomelen):
    score = chromosomelen - ((maze.goal.i - current.i) + (maze.goal.j - current.j))

    return score

def selection(population, popuscore):
    offspring = []
    sumscore = 0
    for i in popuscore:
        sumscore += i
    prob = []
    for i in popuscore:
        prob.append(i/sumscore)
    for i in population:
        r = random.random()
        #print(r)
        temp = 0
        for j in range(len(population)):
            temp += prob[j]
            if temp > r :
                offspring.append(population[j])
                break
    
    return offspring



        
def crossover(population):
    offspring = []
    for i in range(0, len(population), 2):
        parentone = population[i]
        parenttwo = population[i+1]
        r = random.randint(0,len(parentone))
        childone = parentone[0: r] + parenttwo[r: len(parenttwo)]
        childtwo = parenttwo[0: r] + parenttwo[r: len(parentone)]
        offspring.append(childone)
        offspring.append(childtwo)
    #print("crossover: ", len(offspring))
    return offspring
    


def mutation(population):
    #print("--------------")  
    for i in population:
        r = random.random()
        #print( r )
        if r > 0.4:
            d = random.randint(0,len(i)-1)
            i[d] = random.choice([0,1,2,3])
  
        #print(i)
    #print("--------------")  
    #print ("mutation: ", len(population))

    return population


def search(maze, render):
    start = maze.start
    goal = maze.goal

    chromosomelen = (maze.goal.i - maze.start.i) + (maze.goal.j - maze.start.j) + 10
    print ("chromosome_length:{0}".format(chromosomelen))
    generation = 1000000
    wall = 0
    # Keep track of cells left to explore
    open_cells = [start]

    population = initialize(chromosomelen)
    print(population)
    
    final = 0
    while generation != 0:
        popuscore = []    
        if final == 1: 
            break
        for chromo in population:
            #print(chromo)
            flag = 1                   
            for gene in range(len(chromo)): # each chromosome's route
                # Move to new cell
                #print(len(open_cells))
                current = open_cells.pop()
                
                # Don't go to already explored cells
                if current is not goal:
                    #current.explored = True
                    neighbors = maze.valid_ganeighbors(current)
                    for i, neighbor in neighbors:
                        if chromo[gene] == i and neighbor.explored == False:
                            if (chromo[gene] == 0 and chromo[gene-1] != 1) or (chromo[gene] == 1 and chromo[gene-1] != 0) or (chromo[gene] == 2 and chromo[gene-1] != 3) or (chromo[gene] == 3 and chromo[gene-1] != 2):
                                open_cells.append(neighbor)
                                #print("open_cells: ", len(open_cells))
                                #neighbor.parent = current
                                flag = 0  
                                break
                            else:
                                flag = 1 
                        else:
                            flag = 1       
                #print("flag: ", flag)
                else:
                    flag = 0

                
                if flag == 1:
                    if render:
                        maze.draw(current)
                    popuscore.append(fitness(maze, current, chromosomelen))
                    open_cells.append(start)
                    break
                else: 
                    if render:
                        maze.draw(current)
                    if current is goal:
                        final = 1 
                        print("final", chromo)
                        print('Solution found!')
                        #maze.trace_final_path()
                        tempopen_cells = [start]
                        for t in range(len(chromo)): 
                            if tempopen_cells:                          
                                tempcurrent = tempopen_cells.pop()
                                if tempcurrent is goal:
                                    #print('Solution found!')
                                    maze.trace_final_path()
                                if tempcurrent.explored == False:
                                    tempcurrent.explored = True
                                    neighbors = maze.valid_ganeighbors(tempcurrent)
                                    for x, neighbor in neighbors:
                                        if chromo[t] == x and neighbor.explored == False:
                                            tempopen_cells.append(neighbor)
                                            neighbor.parent = tempcurrent
                        break
                if final == 1: 
                   break
            if final == 1: 
                break        
        print (popuscore)
        print (len(popuscore))
        
        population = selection(population, popuscore) 
        population = crossover(population)
        population = mutation(population)
        generation -= 1           