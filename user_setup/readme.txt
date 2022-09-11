################################################################################
#    Introduction for using json files to describe a detector setup
################################################################################

1. The top level should always be a world
    a) the world should have a "world half length", "name"
    b) the world should have a "type", and its value should be "module"
    c) all other valumes should be described in the "submodules" section

2. To describe a module:
    a) required properties: "name", "type", "color", "coordinate", "rotation"
       these are general properties, all modules must have them
    b) "type" can be primitives like "cube", "trapezoid", "sphere", "tube", etc,
       for these primitive types, it should not have "submodules" section
       "type" can also be collections: "module", if it is a "module" type,
       then this module is treated as an assembly, it should have "submodules"
       section

