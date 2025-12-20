'use strict';

angular.module('Metanome')
  .factory('Datasource', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/:type', {}, {
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
