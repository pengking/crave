
SET(CRAVE_LIB_SRC 
  ConstrainedRandom.cpp
  ConstrainedRandomInit.cpp
  EvalVisitor.cpp
  FixWidthVisitor.cpp
  GetSupportSetVisitor.cpp
  metaSMTNodeVisitor.cpp
  metaSMTNodeVisitorYices2.cpp
  ReplaceVisitor.cpp
  ToDotNodeVisitor.cpp
  CraveSettings.cpp
  Generator.cpp
  SettingType.cpp
  VariableCoverageGenerator.cpp
  ConstraintPartition.cpp
  Evaluator.cpp
  RandObjGenerator.cpp
  CraveSettings.cpp
  Evaluator.cpp
  RandObjGenerator.cpp
  SettingType.cpp
  VariableCoverageSolver.cpp
  VariableDefaultSolver.cpp
  VariableGeneratorType.cpp
  VariableSolver.cpp
  VectorGenerator.cpp
  ConstrainedRandom.cpp
  UserVectorConstraint.cpp
  UserConstraintType.cpp
  ConstraintManager.cpp
  ConstraintPartitioner.cpp
  Operators.cpp
  Distribution.cpp
  RandomBase.cpp
  VariableGeneratorMT.cpp
  ComplexityEstimationVisitor.cpp
  RandomSeedManager.cpp
)

if (CRAVE_ENABLE_EXPERIMENTAL)
  LIST(APPEND CRAVE_LIB_SRC
    experimental/Object.cpp	
    experimental/GraphVisitor.cpp	
    experimental/ConstrainedRandomGraph.cpp  
    experimental/Experimental.cpp
    experimental/ConstraintBase.cpp
    experimental/SequenceItem.cpp
    experimental/Expression.cpp
    experimental/graph/Rule.cpp
  )
endif (CRAVE_ENABLE_EXPERIMENTAL)

add_library (${PROJECT_NAME} STATIC
  ${CRAVE_LIB_SRC}
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE on)

SET(LINK_LIBRARIES
  metaSMT
  ${ALL_EXTERNAL_LIBS}
)

target_link_libraries (${PROJECT_NAME} ${LINK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
)


