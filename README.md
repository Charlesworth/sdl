### TODO
- Figure out the best way to render game objects. I don't think that the object should contain any render specific code, but should contain everything the render needs (i.e. the texture or in the future sprites)
- Game objects should be stored on the heap, I'll eventually need a collection to put them all in. This has conitations on how the objects should be indexed in this container, i.e. by position.

### Style Guide
Follow [el-googs style guide](https://google.github.io/styleguide/cppguide.html#Naming) and use [their linter](https://github.com/google/styleguide/tree/gh-pages/cpplint) with the lint length set to 120 `--linelength=120` 

#### Var Names
snake_case, no caps

    int price_count_reader;    // No abbreviation.
    int num_errors;            // "num" is a widespread convention.

#### Private data memebers
snake_case, no caps, sufix `_`

    class TableInfo {
        private:
            string table_name_;  // OK - underscore at end.
            static Pool<TableInfo>* pool_;  // OK.
    };

#### Constants
snake_case, no caps, Prefix `k_`

    const int k_days_in_week = 7;
    const int k_days_in_week_ = 7; // private contant in a class

#### Types and Functions
Camal Case, leading cap

    class UrlTableTester {}
    struct UrlTableProperties {}
    void AddTableEntry()
