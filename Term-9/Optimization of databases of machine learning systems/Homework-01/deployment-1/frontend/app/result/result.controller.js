'use strict';

var app = angular.module('Metanome')

  .config(function config($stateProvider) {
    $stateProvider
      .state('result', {
        url: '/result/:resultId?cached&count&load&file&extended&ind&od&ucc&cucc&fd&md$cfd&mvd&basicStat&dc',
        views: {
          'main@': {
            controller: 'ResultCtrl',
            templateUrl: 'app/result/result.html'
          }
        }
      })
  });

app.controller('ResultCtrl', function ($scope, $log, Executions, Results, $q, usSpinnerService,
                                       $timeout, $stateParams, LoadResults, CountResults, Execution, File,
                                       ngDialog, $http, ENV_VARS) {

  // ** VARIABLE DEFINITIONS **
  // **************************

  $scope.id = $stateParams.resultId;
  $scope.extended = ($stateParams.extended === 'true');
  $scope.cached = ($stateParams.cached === 'true');
  $scope.file = ($stateParams.file === 'true');
  $scope.count = ($stateParams.count === 'true');
  $scope.fd = ($stateParams.fd === 'true');
  $scope.cid = ($stateParams.cid === 'true');
  $scope.md = ($stateParams.md === 'true');
  $scope.cfd = ($stateParams.cfd === 'true');
  $scope.ind = ($stateParams.ind === 'true');
  $scope.ucc = ($stateParams.ucc === 'true');
  $scope.cucc = ($stateParams.cucc === 'true');
  $scope.od = ($stateParams.od === 'true');
  $scope.mvd = ($stateParams.mvd === 'true');
  $scope.basicStat = ($stateParams.basicStat === 'true');
  $scope.dc = ($stateParams.dc === 'true');
  $scope.load = ($stateParams.load === 'true');

  $scope.basicStatisticColumnNames = [];

  $scope.paginationValues = [10, 20, 30, 40, 50];

  var defaultCacheSize = 50;

  $scope.uniqueColumnCombination = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Unique Column Combination',
      sort: 'Column Combination',
      from: 0,
      to: defaultCacheSize
    }
  };

  $scope.functionalDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Functional Dependency',
      sort: 'Determinant',
      from: 0,
      to: defaultCacheSize
    }
  };
  
  $scope.conditionalInclusionDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Conditional Inclusion Dependency',
      sort: 'Determinant',
      from: 0,
      to: defaultCacheSize
    }
  };

  $scope.matchingDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Matching Dependency',
      sort: 'Determinant',
      from: 0,
      to: defaultCacheSize
    }
  };

  $scope.conditionalFunctionalDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Conditional Functional Dependency',
      sort: 'Determinant',
      from: 0,
      to: defaultCacheSize
    }
  };

  $scope.basicStatistic = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Basic Statistic',
      sort: 'Column Combination',
      from: 0,
      to: defaultCacheSize
    }
  };

  $scope.denialConstraint = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Denial Constraint',
      sort: 'Predicates',
      from: 0,
      to: defaultCacheSize
    }
  };

  $scope.inclusionDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Inclusion Dependency',
      sort: 'Dependant',
      from: '0',
      to: defaultCacheSize
    }
  };

  $scope.conditionalUniqueColumnCombination = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Conditional Unique Column Combination',
      sort: 'Dependant',
      from: '0',
      to: defaultCacheSize
    }
  };

  $scope.orderDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Order Dependency',
      sort: 'LHS',
      from: '0',
      to: defaultCacheSize
    }
  };

  $scope.multivaluedDependency = {
    count: 0,
    data: [],
    query: {
      order: '',
      limit: 10,
      page: 1
    },
    selected: [],
    params: {
      type: 'Multivalued Dependency',
      sort: 'Determinant',
      from: '0',
      to: defaultCacheSize
    }
  };

  // ** FUNCTION DEFINITIONS **
  // **************************

  /**
   * Removes duplicates from the given array.
   * @param arr the array
   * @returns {Array} the array without duplicates
   */
  function removeDuplicates(arr){
    var retArray = [];
    for (var a = arr.length - 1; a >= 0; a--) {
      for (var b = arr.length - 1; b >= 0; b--) {
        if(arr[a] === arr[b] && a !== b){
          delete arr[b];
        }
      }
      if(arr[a] !== undefined) {
        retArray.push(arr[a]);
      }
    }
    return retArray;
  }


  // ** Getting the result from the backend **

  /**
   * Loads the result for unique column combinations from the backend.
   */
  function loadUniqueColumnCombination() {
    Results.get($scope.uniqueColumnCombination.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var combinations = [];
        result.result.columnCombination.columnIdentifiers.forEach(function (combination) {
          combinations.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        rows.push({
          columnCombination: '[' + combinations.join(',\n ') + ']',
          columnRatio: result.columnRatio,
          occurrenceRatio: result.occurrenceRatio,
          uniquenessRatio: result.uniquenessRatio,
          randomness: result.randomness
        })
      });
      $scope.uniqueColumnCombination.data = $scope.uniqueColumnCombination.data.concat(rows)
    })
  }

  /**
   * Loads the result for conditional unique column combinations from the backend.
   */
  function loadConditionalUniqueColumnCombination() {
    Results.get($scope.conditionalUniqueColumnCombination.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var combinations = [];
        result.result.columnCombination.columnIdentifiers.forEach(function (combination) {
          combinations.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        rows.push({
          columnCombination: '[' + combinations.join(',\n ') + ']',
          condition: result.result.condition.columnIdentifier.tableIdentifier + '.' + result.result.condition.columnIdentifier.columnIdentifier + (result.result.condition.negated ? ' != ' : ' = ') + result.result.condition.columnValue,
          coverage: result.result.condition.coverage,
          columnRatio: result.columnRatio,
          occurrenceRatio: result.occurrenceRatio,
          uniquenessRatio: result.uniquenessRatio
        })
      });
      $scope.conditionalUniqueColumnCombination.data = $scope.conditionalUniqueColumnCombination.data.concat(rows)
    })
  }

  /**
   * Loads the result for functional dependencies from the backend.
   */
  function loadFunctionalDependency() {
    Results.get($scope.functionalDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var determinant = [];
        result.result.determinant.columnIdentifiers.forEach(function (combination) {
          if (combination.tableIdentifier && combination.columnIdentifier) {
            determinant.push(combination.tableIdentifier + '.' + combination.columnIdentifier);
          } else {
            determinant.push('');
          }
        });
        var extendedDependant = [];
        if (result.extendedDependant) {
          result.extendedDependant.columnIdentifiers.forEach(function (combination) {
            if (combination.tableIdentifier && combination.columnIdentifier) {
              extendedDependant.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
            } else {
              determinant.push('');
            }
          })
        }
        var dependant = '';
        if (result.dependant.tableIdentifier && result.dependant.columnIdentifier) {
          dependant = result.dependant.tableIdentifier + '.' + result.dependant.columnIdentifier;
        }

        rows.push({
          determinant: '[' + determinant.join(',\n ') + ']',
          dependant: dependant,
          extendedDependant: '[' + extendedDependant.join(',\n ') + ']',
          determinantColumnRatio: result.determinantColumnRatio,
          dependantColumnRatio: result.dependantColumnRatio,
          determinantOccurrenceRatio: result.determinantOccurrenceRatio,
          dependantOccurrenceRatio: result.dependantOccurrenceRatio,
          generalCoverage: result.generalCoverage,
          determinantUniquenessRatio: result.determinantUniquenessRatio,
          dependantUniquenessRatio: result.dependantUniquenessRatio,
          pollution: result.pollution,
          pollutionColumn: result.pollutionColumn,
          informationGainCell: result.informationGainCells,
          informationGainByte: result.informationGainBytes
        })
      });
      $scope.functionalDependency.data = $scope.functionalDependency.data.concat(rows)
    })
  }
  
  /**
   * Loads the result for conditional inclusion dependencies from the backend.
   */
  function loadConditionalInclusionDependency() {
    Results.get($scope.conditionalInclusionDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var determinant = [];
        result.result.determinant.columnIdentifiers.forEach(function (combination) {
          if (combination.tableIdentifier && combination.columnIdentifier) {
            determinant.push(combination.tableIdentifier + '.' + combination.columnIdentifier);
          } else {
            determinant.push('');
          }
        });
        var extendedDependant = [];
        if (result.extendedDependant) {
          result.extendedDependant.columnIdentifiers.forEach(function (combination) {
            if (combination.tableIdentifier && combination.columnIdentifier) {
              extendedDependant.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
            } else {
              determinant.push('');
            }
          })
        }
        var dependant = '';
        if (result.dependant.tableIdentifier && result.dependant.columnIdentifier) {
          dependant = result.dependant.tableIdentifier + '.' + result.dependant.columnIdentifier;
        }

        rows.push({
          determinant: '[' + determinant.join(',\n ') + ']',
          dependant: dependant,
          extendedDependant: '[' + extendedDependant.join(',\n ') + ']'
        })
      });
      $scope.conditionalInclusionDependency.data = $scope.conditionalInclusionDependency.data.concat(rows)
    })
  }

  /**
   * Loads the result for matching dependencies from the backend.
   */
  function loadMatchingDependency() {
    Results.get($scope.matchingDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var determinant = [];
        result.result.determinant.matchingIdentifiers.forEach(function (combination) {
          var leftIdentifier = '';
          if(combination.left) {
            leftIdentifier = combination.left.tableIdentifier + '.' + combination.left.columnIdentifier;
          }
          var rightIdentifier = '';
          if(combination.right) {
            rightIdentifier = combination.right.tableIdentifier + '.' + combination.right.columnIdentifier;
          }
          var identifier;
          if(leftIdentifier === rightIdentifier) {
            identifier = leftIdentifier;
          } else {
            identifier = leftIdentifier + ',' + rightIdentifier;
          }
          if (combination.similarityMeasure && combination.threshold) {
            determinant.push(identifier + '(' + combination.similarityMeasure + '@' + combination.threshold + ')');
          } else {
            determinant.push('');
          }
        });
        var dependant = '';
        if (result.result.dependant.similarityMeasure && result.result.dependant.threshold) {
          var leftIdentifier = '';
          if(result.result.dependant.left) {
            leftIdentifier = result.result.dependant.left.tableIdentifier + '.' + result.result.dependant.left.columnIdentifier;
          }
          var rightIdentifier = '';
          if(result.result.dependant.right) {
            rightIdentifier = result.result.dependant.right.tableIdentifier + '.' + result.result.dependant.right.columnIdentifier;
          }
          var identifier;
          if(leftIdentifier === rightIdentifier) {
            identifier = leftIdentifier;
          } else {
            identifier = leftIdentifier + ',' + rightIdentifier;
          }
          dependant = identifier + '(' + result.result.dependant.similarityMeasure + '@' + result.result.dependant.threshold + ')';
        }

        rows.push({
          determinant: '[' + determinant.join(',\n ') + ']',
          dependant: dependant,
          support: result.result.support
        })
      });
      $scope.matchingDependency.data = $scope.matchingDependency.data.concat(rows)
    })
  }

  /**
   * Loads the result for conditional functional dependencies from the backend.
   */
  function loadConditionalFunctionalDependency() {
    Results.get($scope.conditionalFunctionalDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var determinant = [];
        result.result.determinant.columnIdentifiers.forEach(function (combination) {
          if (combination.tableIdentifier && combination.columnIdentifier) {
            determinant.push(combination.tableIdentifier + '.' + combination.columnIdentifier);
          } else {
            determinant.push('');
          }
        });
        var extendedDependant = [];
        if (result.extendedDependant) {
          result.extendedDependant.columnIdentifiers.forEach(function (combination) {
            if (combination.tableIdentifier && combination.columnIdentifier) {
              extendedDependant.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
            } else {
              determinant.push('');
            }
          })
        }
        var dependant = '';
        if (result.dependant.tableIdentifier && result.dependant.columnIdentifier) {
          dependant = result.dependant.tableIdentifier + '.' + result.dependant.columnIdentifier;
        }

        rows.push({
          determinant: '[' + determinant.join(',\n ') + ']',
          dependant: dependant,
          extendedDependant: '[' + extendedDependant.join(',\n ') + ']',
          tableau: result.patternTableau
        })
      });
      $scope.conditionalFunctionalDependency.data = $scope.conditionalFunctionalDependency.data.concat(rows)
    })
  }

  /**
   * Loads the result for basic statistics from the backend.
   */
  function loadBasicStatistic() {
    Results.get($scope.basicStatistic.params, function (res) {
      // getting all column names
      var columnNames = [];
      res.forEach(function (result) {
        for (var columnName in result.statisticMap) {
          columnNames.push(columnName)
        }
      });
      // remove duplicates in column names
      columnNames = removeDuplicates(columnNames);
      columnNames.forEach(function (name) {
        $scope.basicStatisticColumnNames.push({
          'name': name,
          'order': name.replace(/\s/g, '_')
        })
      });

      var rows = [];
      res.forEach(function (result) {
        var combinations = [];
        result.result.columnCombination.columnIdentifiers.forEach(function (combination) {
          combinations.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        var entry = {
          columnCombination: '[' + combinations.join(',\n ') + ']',
          columnRatio: result.columnRatio,
          occurrenceRatio: result.occurrenceRatio,
          uniquenessRatio: result.uniquenessRatio
        };
        $scope.basicStatisticColumnNames.forEach(function(column) {
          if (column.name in result.result.statisticMap) {
            entry[column.order] = result.result.statisticMap[column.name].value;
          } else {
            entry[column.order] = '-';
          }
        });
        rows.push(entry)
      });
      $scope.basicStatistic.data = $scope.basicStatistic.data.concat(rows)
    })
  }

  var predicateOperators = {
    "EQUAL":"=",
    "UNEQUAL":"≠",
    "GREATER":">",
    "LESS":"<",
    "GREATER_EQUAL":"≥",
    "LESS_EQUAL":"≤",
  }

  /**
   * Loads the result for basic statistics from the backend.
   */
  function loadDenialConstraint() {
    Results.get($scope.denialConstraint.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var combinations = [];
        var tableNames = [];
        result.result.predicates.forEach(function (predicate) {
          var operator = predicateOperators[predicate.op] || predicate.op;
          if(predicate.type === "de.metanome.algorithm_integration.PredicateConstant") {
            tableNames[predicate.index1] = predicate.column1.tableIdentifier;
            combinations.push('t' + predicate.index1 + '.' + predicate.column1.columnIdentifier +
             operator + predicate.constant);
          } else if (predicate.type === "de.metanome.algorithm_integration.PredicateVariable") {
            tableNames[predicate.index1] = predicate.column1.tableIdentifier;
            tableNames[predicate.index2] = predicate.column2.tableIdentifier;
            combinations.push('t' + predicate.index1 + '.' + predicate.column1.columnIdentifier +
             operator + 't' + predicate.index2 + '.' + predicate.column2.columnIdentifier);
          }
        });
        var tuples = [];
        for (var index in tableNames) {
          if (tableNames.hasOwnProperty(index)) {
            tuples.push('t' + index + '∈' + tableNames[index]);
          }
        }

        var entry = {
          predicates: '∀' + tuples.join(',') + ':\n¬[' + combinations.join('∧\n ') + ']',
          size: combinations.length,
        };
        rows.push(entry);
      });
      $scope.denialConstraint.data = $scope.denialConstraint.data.concat(rows)
    })
  }

  /**
   * Loads the result for inclusion dependencies from the backend.
   */
  function loadInclusionDependency() {
    Results.get($scope.inclusionDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var combinations = [];
        result.result.dependant.columnIdentifiers.forEach(function (combination) {
          combinations.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        var referenced = [];
        result.result.referenced.columnIdentifiers.forEach(function (combination) {
          referenced.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        rows.push({
          dependant: '[' + combinations.join(',\n ') + ']',
          referenced: '[' + referenced.join(',\n ') + ']',
          dependantColumnRatio: result.dependantColumnRatio,
          referencedColumnRatio: result.referencedColumnRatio,
          dependantOccurrenceRatio: result.dependantOccurrenceRatio,
          referencedOccurrenceRatio: result.referencedOccurrenceRatio,
          generalCoverage: result.generalCoverage,
          dependantUniquenessRatio: result.dependantUniquenessRatio,
          referencedUniquenessRatio: result.referencedUniquenessRatio
        })
      });
      $scope.inclusionDependency.data = $scope.inclusionDependency.data.concat(rows)
    })
  }

  /**
   * Loads the result for order dependencies from the backend.
   */
  function loadOrderDependency() {
    Results.get($scope.orderDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var combinations = [];
        result.result.lhs.columnIdentifiers.forEach(function (combination) {
          combinations.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        var referenced = [];
        result.result.rhs.columnIdentifiers.forEach(function (combination) {
          referenced.push(combination.tableIdentifier + '.' + combination.columnIdentifier)
        });
        var ordertype = 'Lexicographical';
        if (result.orderType === 'POINTWISE') {
          ordertype = 'Pointwise'
        }
        var comparisonOperator = '<';
        if (result.comparisonOperator === 'SMALLER_EQUAL') {
          comparisonOperator = '<='
        }

        rows.push({
          LHS: '[' + combinations.join(',\n ') + ']',
          RHS: '[' + referenced.join(',\n ') + ']',
          ComparisonOperator: comparisonOperator,
          OrderType: ordertype,
          LHSColumnRatio: result.lhsColumnRatio,
          RHSColumnRatio: result.rhsColumnRatio,
          GeneralCoverage: result.generalCoverage,
          LHSOccurrenceRatio: result.lhsOccurrenceRatio,
          RHSOccurrenceRatio: result.rhsOccurrenceRatio,
          LHSUniquenessRatio: result.lhsUniquenessRatio,
          RHSUniquenessRatio: result.rhsUniquenessRatio
        })
      });
      $scope.orderDependency.data = $scope.orderDependency.data.concat(rows)
    })
  }


  /**
   * Loads the result for multivalued dependencies from the backend.
   */
  function loadMultivaluedDependency() {
    Results.get($scope.multivaluedDependency.params, function (res) {
      var rows = [];
      res.forEach(function (result) {
        var determinants = [];
        result.result.determinant.columnIdentifiers.forEach(function (determinant) {
          determinants.push(determinant.tableIdentifier + '.' + determinant.columnIdentifier)
        });
        var dependants = [];
        result.result.dependant.columnIdentifiers.forEach(function (dependant) {
          dependants.push(dependant.tableIdentifier + '.' + dependant.columnIdentifier)
        });
        rows.push({
          determinant: '[' + determinants.join(',\n ') + ']',
          dependant: '[' + dependants.join(',\n ') + ']',
          determinantColumnRatio: result.determinantColumnRatio,
          dependantColumnRatio: result.dependantColumnRatio,
          determinantOccurrenceRatio: result.determinantOccurrenceRatio,
          dependantOccurrenceRatio: result.dependantOccurrenceRatio,
          generalCoverage: result.generalCoverage,
          determinantUniquenessRatio: result.determinantUniquenessRatio,
          dependantUniquenessRatio: result.dependantUniquenessRatio,
          pollution: result.pollution,
          pollutionColumn: result.pollutionColumn,
          informationGainCell: result.informationGainCells,
          informationGainByte: result.informationGainBytes
        })
      });
      $scope.multivaluedDependency.data = $scope.multivaluedDependency.data.concat(rows)
    })
  }

  /**
   * Loads the results depending on the requested result types.
   */
  function init() {
    if ($scope.ucc || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.uniqueColumnCombination.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.uniqueColumnCombination.count = count;
            if (!$scope.count) {
              loadUniqueColumnCombination()
            }
          }
        });
    }
    if ($scope.fd || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.functionalDependency.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.functionalDependency.count = count;
            if (!$scope.count) {
              loadFunctionalDependency()
            }
          }
        });
    }
    if ($scope.cid || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.conditionalInclusionDependency.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.conditionalInclusionDependency.count = count;
            if (!$scope.count) {
              loadConditionalInclusionDependency()
            }
          }
        });
    }
    if ($scope.md || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.matchingDependency.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.matchingDependency.count = count;
            if (!$scope.count) {
              loadMatchingDependency()
            }
          }
        });
    }
    if ($scope.cfd || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.conditionalFunctionalDependency.params.type).
      then(function (response) {
        var count = response.data;
        if (count > 0) {
          $scope.conditionalFunctionalDependency.count = count;
          if (!$scope.count) {
            loadConditionalFunctionalDependency()
          }
        }
      });
    }
    if ($scope.basicStat || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.basicStatistic.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.basicStatistic.count = count;
            if (!$scope.count) {
              loadBasicStatistic()
            }
          }
        });
    }
    if ($scope.dc || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.denialConstraint.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.denialConstraint.count = count;
            if (!$scope.count) {
              loadDenialConstraint()
            }
          }
        });
    }
    if ($scope.ind || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.inclusionDependency.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.inclusionDependency.count = count;
            if (!$scope.count) {
              loadInclusionDependency()
            }
          }
        });
    }
    if ($scope.cucc || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.conditionalUniqueColumnCombination.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.conditionalUniqueColumnCombination.count = count;
            if (!$scope.count) {
              loadConditionalUniqueColumnCombination()
            }
          }
        });
    }
    if ($scope.od || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.orderDependency.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.orderDependency.count = count;
            if (!$scope.count) {
              loadOrderDependency()
            }
          }
        })
    }
    if ($scope.mvd || $scope.file) {
      $http.get(ENV_VARS.API + '/api/result-store/count/' + $scope.multivaluedDependency.params.type).
        then(function (response) {
          var count = response.data;
          if (count > 0) {
            $scope.multivaluedDependency.count = count;
            if (!$scope.count) {
              loadMultivaluedDependency()
            }
          }
        })
      }
  }

  /**
   * Loads the file with a specific id from the backend.
   */
  function loadDetailsForFile() {
    File.get({id: $scope.id}, function (result) {
      $scope.file = result;
      $scope.file.shortFileName = $scope.file.fileName.replace(/^.*[\\\/]/, '');
    })
  }

  /**
   * Formats the given number. The number should contain two digits.
   * @param number the number
   * @returns {string} a string containig two digits
   */
  function twoDigits(number) {
    return (number < 10 ? '0' + number : '' + number)
  }

  /**
   * Load the execution with a specific id from the backend.
   */
  function loadDetailsForExecution() {
    Execution.get({id: $scope.id}, function (result) {
      $scope.execution = result;
      var duration = result.end - result.begin; // milliseconds

      var days = Math.floor(duration / (1000 * 60 * 60 * 24));
      var hours = twoDigits(Math.floor(duration / (1000 * 60 * 60)));
      var minutes = twoDigits(Math.floor((duration / (1000 * 60)) % 60));
      var seconds = twoDigits(Math.floor((duration / 1000) % 60));
      var milliseconds = Math.floor(duration % 1000);

      if (seconds === '00') {
        $scope.duration = milliseconds + ' ms';
      } else if (days === 0) {
        $scope.duration = hours + ':' + minutes + ':' + seconds + ' (hh:mm:ss) and ' + milliseconds + ' ms';
      } else {
        $scope.duration = days + ' day(s) and ' + hours + ':' + minutes + ':' + seconds + ' (hh:mm:ss) and ' + milliseconds + ' ms';
      }
    })
  }

  /**
   * Open the visualizations for functional dependencies.
   */
  function openFDVisualization() {
    $scope.openVisualizationType = 'FD';
    ngDialog.open({
      template: '/assets/visualization.html',
      scope: $scope
    })
  }

  /**
   * Open the visualizations for unique column combinations
   */
  function openUCCVisualization() {
    $scope.openVisualizationType = 'UCC';
    ngDialog.open({
      template: '/assets/visualization.html',
      scope: $scope
    })
  }

  // ** Getting the result from the backend **

  /**
   * Updates the result for functional dependency according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeFD(page, limit) {
    var deferred = $q.defer();
    if ($scope.functionalDependency.params.to < $scope.functionalDependency.count) {
      $scope.functionalDependency.params.from += $scope.functionalDependency.params.to + 1;
      $scope.functionalDependency.params.to += Math.max(limit, $scope.functionalDependency.count);
      loadFunctionalDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }
  
  /**
   * Updates the result for conditional inclusion dependency according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeCID(page, limit) {
    var deferred = $q.defer();
    if ($scope.conditionalInclusionDependency.params.to < $scope.conditionalInclusionDependency.count) {
      $scope.conditionalInclusionDependency.params.from += $scope.conditionalInclusionDependency.params.to + 1;
      $scope.conditionalInclusionDependency.params.to += Math.max(limit, $scope.conditionalInclusionDependency.count);
      loadConditionalInclusionDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for matching dependency according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeMD(page, limit) {
    var deferred = $q.defer();
    if ($scope.matchingDependency.params.to < $scope.matchingDependency.count) {
      $scope.matchingDependency.params.from += $scope.matchingDependency.params.to + 1;
      $scope.matchingDependency.params.to += Math.max(limit, $scope.matchingDependency.count);
      loadMatchingDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for conditional functional dependency according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeCFD(page, limit) {
    var deferred = $q.defer();
    if ($scope.conditionalFunctionalDependency.params.to < $scope.conditionalFunctionalDependency.count) {
      $scope.conditionalFunctionalDependency.params.from += $scope.conditionalFunctionalDependency.params.to + 1;
      $scope.conditionalFunctionalDependency.params.to += Math.max(limit, $scope.conditionalFunctionalDependency.count);
      loadFunctionalDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for unique column combinations according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeUCC(page, limit) {
    var deferred = $q.defer();
    if ($scope.uniqueColumnCombination.params.to < $scope.uniqueColumnCombination.count) {
      $scope.uniqueColumnCombination.params.from += $scope.uniqueColumnCombination.params.to + 1;
      $scope.uniqueColumnCombination.params.to += Math.max(limit, $scope.uniqueColumnCombination.count);
      loadUniqueColumnCombination();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for basic statistics according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeBS(page, limit) {
    var deferred = $q.defer();
    if ($scope.basicStatistic.params.to < $scope.basicStatistic.count) {
      $scope.basicStatistic.params.from += $scope.basicStatistic.params.to + 1;
      $scope.basicStatistic.params.to += Math.max(limit, $scope.basicStatistic.count);
      loadBasicStatistic();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for denial constraints according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeDC(page, limit) {
    var deferred = $q.defer();
    if ($scope.denialConstraint.params.to < $scope.denialConstraint.count) {
      $scope.denialConstraint.params.from += $scope.denialConstraint.params.to + 1;
      $scope.denialConstraint.params.to += Math.max(limit, $scope.denialConstraint.count);
      loadDenialConstraint();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for inclusion dependencies according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeIND(page, limit) {
    var deferred = $q.defer();
    if ($scope.inclusionDependency.params.to < $scope.inclusionDependency.count) {
      $scope.inclusionDependency.params.from += $scope.inclusionDependency.params.to + 1;
      $scope.inclusionDependency.params.to += Math.max(limit, $scope.inclusionDependency.count);
      loadInclusionDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for conditional unique column combinations according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeCUCC(page, limit) {
    var deferred = $q.defer();
    if ($scope.conditionalUniqueColumnCombination.params.to < $scope.conditionalUniqueColumnCombination.count) {
      $scope.conditionalUniqueColumnCombination.params.from += $scope.conditionalUniqueColumnCombination.params.to + 1;
      $scope.conditionalUniqueColumnCombination.params.to += Math.max(limit, $scope.conditionalUniqueColumnCombination.count);
      loadConditionalUniqueColumnCombination();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for order dependencies according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeOD(page, limit) {
    var deferred = $q.defer();
    if ($scope.orderDependency.params.to < $scope.orderDependency.count) {
      $scope.orderDependency.params.from += $scope.orderDependency.params.to + 1;
      $scope.orderDependency.params.to += Math.max(limit, $scope.orderDependency.count);
      loadOrderDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }

  /**
   * Updates the result for multivalued dependencies according to the selected limit and page.
   * @param page the current page
   * @param limit the current limit
   * @returns {*}
   */
  function onPageChangeMVD(page, limit) {
    var deferred = $q.defer();
    if ($scope.multivaluedDependency.params.to < $scope.multivaluedDependency.count) {
      $scope.multivaluedDependency.params.from += $scope.multivaluedDependency.params.to + 1;
      $scope.multivaluedDependency.params.to += Math.max(limit, $scope.multivaluedDependency.count);
      loadMultivaluedDependency();
      $timeout(function () {
        deferred.resolve();
      }, 500);
    } else {
      deferred.resolve()
    }
    return deferred.promise;
  }


  /**
   * Starts the spinner
   */
  function startSpin() {
    $timeout(function() {
      usSpinnerService.spin('spinner-2');
    }, 10);
  }

  /**
   * Stops the spinner
   */
  function stopSpin() {
    $timeout(function() {
      usSpinnerService.stop('spinner-2');
    }, 10);
  }

  /**
   * Open a dialog which shows an error message.
   * @param message the message
   */
  function openError(message) {
    $scope.errorMessage = message;
    ngDialog.open({
      /*jshint multistr: true */
      template: '\
                <h3 style="color: #F44336">ERROR</h3>\
                <p>{{errorMessage}}</p>\
                <div class="ngdialog-buttons">\
                    <button type="button" class="ngdialog-button ngdialog-button-secondary" ng-click="closeThisDialog(0)">Ok</button>\
                </div>',
      plain: true,
      scope: $scope
    })
  }

  // ** EXPORT FUNCTIONS **
  // **********************

  $scope.openFDVisualization = openFDVisualization;
  $scope.openUCCVisualization = openUCCVisualization;
  $scope.onPageChangeCID = onPageChangeCID;
  $scope.onPageChangeBS = onPageChangeBS;
  $scope.onPageChangeUCC = onPageChangeUCC;
  $scope.onPageChangeFD = onPageChangeFD;
  $scope.onPageChangeMD = onPageChangeMD;
  $scope.onPageChangeCFD = onPageChangeCFD;
  $scope.onPageChangeIND = onPageChangeIND;
  $scope.onPageChangeCUCC = onPageChangeCUCC;
  $scope.onPageChangeOD = onPageChangeOD;
  $scope.onPageChangeMVD = onPageChangeMVD;
  $scope.onPageChangeDC = onPageChangeDC;

  // ** FUNCTION CALLS **
  // ********************

  // load extended results
  if ($scope.extended) {
    startSpin();
    $scope.loading = true;
    LoadResults.load({id: $scope.id, notDetailed: false}, function () {
      init();
      loadDetailsForExecution();
      $scope.loading = false;
      stopSpin();
    }, function (errorMessage) {
      $scope.loading = false;
      stopSpin();
      openError('Could not load extended results: ' + errorMessage.data);
    });
    // load all results for a file
  } else if ($scope.file) {
    startSpin();
    $scope.loading = true;
    loadDetailsForFile();
    LoadResults.file({id: $scope.id, notDetailed: true}, function () {
      init();
      $scope.loading = false;
      stopSpin();
    }, function (errorMessage) {
      $scope.loading = false;
      stopSpin();
      openError('Results could not be loaded: ' + errorMessage.data);
    });
    // load result (coming from history)
  } else if ($scope.load) {
    startSpin();
    $scope.loading = true;
    LoadResults.load({id: $scope.id, notDetailed: true}, function () {
      init();
      loadDetailsForExecution();
      $scope.loading = false;
      stopSpin();
    }, function (errorMessage) {
      $scope.loading = false;
      stopSpin();
      openError('Results could not be loaded: ' + errorMessage.data);
    });
    // load results
  } else {
    $scope.loading = false;
    init();
    loadDetailsForExecution();
  }

});
