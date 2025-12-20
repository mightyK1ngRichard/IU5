'use strict';

angular.module('Metanome')
  .factory('AlgorithmExecution', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/algorithm-execution', {}, {
        run: {
          method: 'POST'
        }
      });
    }
  ])

;
