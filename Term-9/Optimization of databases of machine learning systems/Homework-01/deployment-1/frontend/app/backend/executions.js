'use strict';

angular.module('Metanome')
  .factory('Executions', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/executions', {}, {
        getAll: {
          method: 'GET',
          isArray: true
        }
      });
    }
  ])

;
