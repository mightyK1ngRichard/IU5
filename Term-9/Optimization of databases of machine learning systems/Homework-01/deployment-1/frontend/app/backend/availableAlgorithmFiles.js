'use strict';

angular.module('Metanome')
  .factory('AvailableAlgorithmFiles', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/algorithms/available-algorithm-files', {}, {
        get: {
          method: 'GET',
          params: {
            type: '@type'
          },
          isArray: true
        }
      });
    }
  ])

;
