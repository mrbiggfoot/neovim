# neovim + fuzzy completion
This is a [neovim](https://github.com/neovim/neovim) fork that enables fuzzy
search on completion candidates by the virtue of slightly modified
[fzy](https://github.com/jhawthorn/fzy). All you need to do is
`set completeopt+=fuzzy` and trigger completion popup somehow (I personally use
[mucomplete](https://github.com/lifepillar/vim-mucomplete) plugin for that).

## Installation
Please see the "Install from source" instructions on the
[neovim](https://github.com/neovim/neovim) page. Just install this neovim fork
from the source as you would install neovim. No extra setup is required, `fzy`
algorithm is already baked in.

Some `#define`s for fine tuning:
* `src/nvim/tags_cache.hpp`
```c++
// Ignore tag names with length less than this.
#define MIN_TAG_NAME_LENTH 4
```
* `src/nvim/match.hpp`
```c++
// Min length of the pattern to trigger custom matches with. Used for
// optimization to reduce the number of candidates in fuzzy search.
#define MIN_CUSTOM_PATTERN_LENGTH 0

// Max number of threads for match score calculation.
#define MAX_NUM_MATCH_THREADS 4
```

## Caveats
- Works only for ASCII characters. This is a limitation of
  [fzy](https://github.com/jhawthorn/fzy). Please let me know if there's a
  better C/C++ fuzzy matching algorithm that is open source.
- Uses some extra memory for tags caching. Proportional to the tags files size,
  though should be less than 1/10th of the total tags files size in most cases.
  This memory is allocated only at the time of the very first fuzzy completion.
  The tags cache is rebuilt automatically if a tag file modification time stamp
  is found to be different from the cached one.
- Probably not buildable on Windows. It's just because I don't have a Windows
  environment to test it on, but PRs to fix this are welcome.

## Tags cache
Regular tags files are used to build the tags cache. However, if `b:compl_tags`
is set, the tags cache is built based on the tags from the file pointed to by
`b:compl_tags`. This is needed to implement a possibility of narrowing down
the list of candidates by doing search only in the tags relevant to the buffer.

## FAQ
### How is it different from using deoplete/nvim-completion-manager/etc?
All the async completion plugins that I've seen so far are slow. They cannot
work reliably on huge amount of completion candidates. Usually most of the
completion candidates come from tags, and at least at the moment, `deoplete`
and `NCM` don't have full-fledged fuzzy search support for tag files. They
utilize binary search, which can't be used for fuzzy matching. In fact I'm
quite skeptical about the possibility of implementing a performant fuzzy search
in pure Python.

Using a language server instead of tags has its own drawbacks: last time I
checked, building ASTs by `clang` ate up a lot of memory (I'm talking
gigabytes!) and slowed down my system to crawl. Also, there's obviously a
delay needed for the compilation to complete, during which you are not getting
completion candidates.

Sync plugins like e.g. `AutoComplPop`, `VimCompletesMe` or `mucomplete` don't
support fuzzy search. Maybe there is a potential to do it properly in this
kind of plugins by calling a fast external function from a compiled library
to match/sort candidates, but that would be a one-off solution specific to the
plugin. The solution via enabling fuzzy search at neovim level should make all
the aforementioned sync plugins use it automatically.

### Is any other neovim functionality affected?
No. Only if you use `fuzzy` option in `completeopt` you should see the new
behavior, otherwise it should behave like vanilla neovim.

### Will it be merged into neovim at some point?
Probably no. At least, I have no plans of doing it because my view on software
development is quite different from the one of the neovim maintainers'. Though
feel free to use my changes as a base if you have enough motivation to bring
it to neovim.

### How will it be maintained?
I will try to integrate at least all the major stable releases of neovim.
Perhaps I'll sync with upstream more often if some critical bugs get fixed
there. My commits will always stay on top of the latest rebase point. Also, all
significant `fzy` algorithm improvements will be brought in.

### Will you make the same functionality for vim?
[Yes.](https://github.com/mrbiggfoot/vim)

## Thanks
- [Bram Moolenaar](https://github.com/brammool)
- [Thiago de Arruda](https://github.com/tarruda)
- [John Hawthorn](https://github.com/jhawthorn)
