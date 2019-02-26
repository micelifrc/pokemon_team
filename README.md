# pokemon_team
This program allows to compute the "best" pokemon team, according to certain parameters.
In order to value what is a good team, it will consider defensive coverage, and, if specified, offensive effectiveness
(i.e. how many types of pokemon are weak against you stab attacks).

In the main it is possible to restrict the search to certain regions only, and it is possible to remove some typologyes of pokemon
(like legendaries, starters or mega-evolutions).

You can also set different parameters (in the main) to give different importance to different types
(for example, if the meta is dominated by fire types, you can be willing to increase the filter_factors entry associated with fire type).

The program can be run as multithread, but it needs to be specified in the main.
