################################################################################
#    Introduction for using json files to describe a detector setup
################################################################################

1. The top level should always be a world:
    a) the world should have a "world half length" and a "name" property.

    b) the world should have a "type" property, and its value should be "module".

    c) all other valumes should be described in the "submodules" section.

2. To describe a module:
    a) required properties: "name", "type", "color", "coordinate", "rotation",
       these are general properties, all modules must have them.

    b) "type" can be primitives like "cube", "trapezoid", "sphere", "tube", etc,
       for these primitive types, it should not have "submodules" section,
       "type" can also be collections: "module", if it is a "module" type,
       then this module is treated as an assembly, it should have "submodules"
       section.

   c) a module can also have its "type" property set to the "name" property value of
      another already built module,
      in this case this module does not need a "submodules" section, it makes a copy
      of the already built module.
      e.g:
          [
              {
                  "name": "top_volume",
                  "type": "module",
                  "submodules": [
                  ]
              },
              {
                  "name": "bottom_volume",
                  "type": "top_volume",
                  "coordinate:": [
                  ]
              }
          ]
      in the above setup, "bottom_volume" does not need a "submodules" section, because
      its "type" property is set to "top_volume", in this case the program will just
      make a copy of "top_volume" and tranlate it to the specified "coordinate".
      This will make writing json files much easier

      ***NOTE:
      the "coordinate" for "bottom_volume" should be checked carefully, keep in mind that
      all transformation is in "module-local" coordinate, so suppose "top_volume" is located
      in (x0, y0, z0), if you want to place "bottom_volume" (a copy of the "top_volume") to
      (x1, y1, z1), then the "coordinate" for "bottom_volume" should be:
      (x1-x0, y1-y0, z1-z0).
