# Knight's Tour Solver

`knights-tour` is a command-line tool for solving the subset of the bipartite-graph Hamiltonian path problem consisting of finding knight's tours on rectangular boards.

This is not aimed to be a novel program, but simply a quick exercise in programming and graph theory. The algorithm uses a largely naive depth-first search, with modest speedups offered by basic graph-theoretic dead end detection. There is certainly room for improvement in detecting "dead" board-states, but to do so would require nontrivial study of the problem.

In terms of performance, the tool is a bit inconsistent on larger boards (9+ in one or more dimensions): either it finds a tour almost immediately, or it is unlikely to find one in any reasonable amount of time, due to the depth-first nature of the search; it is very possible to become 'stuck' on a branch that will never bear fruit. When this occurs, I recommend trying a different starting tile.

Performance on larger boards could be improved by allowing the search to explore varying initial sequences of steps, instead of requiring that it exhaust the possibilities on the first such sequence before proceeding to the next. Another possible improvement is the implementation of Warnsdorff's heuristic, wherein tiles with low numbers of knight-adjacencies are prioritized. However, these are out of scope; you're welcome to fork to implement them.

In practice, the largest board I have had success with is a 16x16 board, where the algorithm happened upon a solution in a mere 1031 steps, starting from the second row, third column; all smaller n x n boards have also admitted solutions, subject to the correct choice of initial tile.

## Installation

Just download the repository and use GNU `make`.

If GNU `make` is not available on your platform, your life just got a lot harder, but what you'll have to do boils down to compiling all the .cpp files into a single executable. Normally with my projects it's necessary to use the `-I ./src/` option (or equivalent) so that the `#include` directives work properly, but in this case the source directory structure is so simple that I believe it's not necessary -- I have not tested this, though.

## Usage

If you're on a Unix-like OS, once you've built `knights-tour`, execute it with `./knights-tour n m [p q]` from the terminal, where `n` and `m` are the height and width of the board, respectively, and `p` and `q` are optional arguments specifying a starting tile other than the default upper-left corner, as row and column indices (with 1-indexing, not 0-indexing).

If you're not on a Unix-like, you presumably still generated an executable during the build process you came up with. Run it from the command line as above.

## Contributing

This particular project is mostly a done deal; I'm not especially interested in extending its functionality.

## License

MIT License. See `LICENSE` file for details.

