function(add_shape NAME)
  add_executable(${NAME} ${NAME}.cpp)

  target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR})
endfunction()

add_shape(ShapeInheritance)

add_shape(ShapeInheritanceAddedFunctionality)

add_shape(ShapeInheritanceAddedType)

add_shape(ShapeVariant)

add_shape(ShapeVariantAddedFunctionality)

add_shape(ShapeVariantAddedType)