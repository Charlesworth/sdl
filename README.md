### TODO
- Figure out the best way to render game objects. I don't think that the object should contain any render specific code, but should contain everything the render needs (i.e. the texture or in the future sprites)
- Game objects should be stored on the heap, I'll eventually need a collection to put them all in. This has conitations on how the objects should be indexed in this container, i.e. by position.