# SDL engine play around

## TODO Larger Goals

- Figure out the best way to render game objects. I don't think that the object should contain any render specific code, but should contain everything the render needs (i.e. the texture or in the future sprites)
- Game objects should be stored on the heap, I'll eventually need a collection to put them all in. This has conitations on how the objects should be indexed in this container, i.e. by position.

## TODO Smaller tasks

Always pleanty of TODOs in the code to grep through, here some others that don't belong in comment form:

- Find proper structure for a cpp project's source files
- Choose a build scripting methodology, something better than my build script
- Produce a renderer class and remove all SDL from the player and main files.
- Textures should use shared_ptr so repeated textures are only once.
- Add frame rate instrumentations.

## Style Guide

Follow [el-googs style guide](https://google.github.io/styleguide/cppguide.html#Naming) and use [their linter](https://github.com/google/styleguide/tree/gh-pages/cpplint) with the lint length set to 120 `--linelength=120`.

### Var Names

snake_case, no caps

    int price_count_reader;    // No abbreviation.
    int num_errors;            // "num" is a widespread convention.

### Private data memebers

snake_case, no caps, sufix `_`

    class TableInfo {
        private:
            string table_name_;  // OK - underscore at end.
            static Pool<TableInfo>* pool_;  // OK.
    };

### Constants

snake_case, no caps, Prefix `k_`

    const int k_days_in_week = 7;
    const int k_days_in_week_ = 7; // private contant in a class

### Globals

snake_case, no caps, Prefix `g_`, shouldn't be any!

    const SDL_Window* g_window;

### Types and Functions

Camal Case, leading cap

    class UrlTableTester {}
    struct UrlTableProperties {}
    void AddTableEntry()
