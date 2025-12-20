'use strict';

angular.module('Metanome')
  .factory('Results', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/result-store/:method/:type/:sort/:ascending/:from/:to', {}, {
        get: {
          method: 'GET',
          params: {
            type: '@type',
            sort: '@sort',
            from: '@from',
            to: '@to',
            method: 'get-from-to',
            ascending: 'true'
          }, isArray: true
        }
      });
    }
  ])

;
