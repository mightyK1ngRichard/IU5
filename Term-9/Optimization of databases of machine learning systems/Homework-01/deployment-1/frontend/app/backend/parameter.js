'use strict';

angular.module('Metanome')
  .factory('Parameter', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/parameter/:algorithm/:what', {}, {
        get: {
          method: 'GET',
          params: {
            algorithm: '@algorithm',
            what: ''
          }, isArray: true
        },
        authorsDescription: {
          method: 'GET',
          params: {
            algorithm: '@algorithm',
            what: 'authors-description'
          }
        }
      });
    }
  ])

;
