# A-Star-Algorithm-8-Tile

The A* algorithm was implemented using two different heuristics, Misplaced Tiles (MT) and Manhattan Distance (MD). These two heuristics were put to test in the 8-puzzle game to compare their efficiencies in determining the shortest path from an initial node to a goal node using several levels of difficultness. It is to note that both the heuristics’ value and depth at each node formed the equation f(n) = h(n) + g(n), where g(n) represents the cost to reach this node, or its depth in this case, and h(n) its heuristic cost, either determined by the MD or MT.

## Examples
Next, nine tests will be shown with their initial and goal states, each more difficult than the previous, to be used on both heuristics.

>### **Note that the ASCII character for the blank tile should be an underscore '_' (hex value 5f) during input stage of the initial and final states.** 

![Example Initial and Goal States](https://imgur.com/a/3rU7yMb)

![Test Results](https://imgur.com/a/bC99xBF)

## Results

The results of the test are shown above, along with the corresponding graphs below. The optional solution column is shown to confirm that the optimal solution was discovered, which was the case for all the tests. The nodes explored column shows the sum of the nodes visited and the nodes in queue during the algorithms. The iterations column represents the iterations inside the while-loop that executed until the goal state was reached, meaning how many times the algorithm switched to a new node in search of the goal node.

It is evident that the MD heuristic is significantly more efficient than the MT heuristic at reaching the goal node. In the first two tests, which required less than 10 moves to solve, the results were identical – both heuristics reaching the same goal in the same amount of iterations and nodes visited. At test #3, the MD heuristic shows to reach 24% of the nodes reached by the MT heuristic and in 22.6% of the iterations than the MT heuristic took. After this test point, the relation between both heuristics becomes almost linear and exponential, as shown below. It is to note that there were certain scenarios where one heuristic performed better than predicted, for example on Test #6, the MD heuristic performed much better than anticipated, with comparison to its previous performance at 18 moves. This represents the complexity of the board and not simply the moves away that a solution could be found. It was difficult to come up with test scenarios where the solutions where 25 or more moves away from the initial state as according to some 8-puzzle websites, the hardest puzzle is 31 moves away. For the sake of testing the worst-case scenario, the hardest 8-puzzle configuration was tested at last. The results for Test #2 show how different these two algorithms performed, with the MD heuristic discovering a total of 6822 nodes in 4357 iterations and the MT heuristic reaching a total of 219081 nodes in 172974 iterations. That is, the MD heuristic reached the same goal in 212,259 nodes less than the MT heuristic, which is a 3,211.3% efficiency in nodes reached and 3,970% in iterations performance for worst-case scenario.


