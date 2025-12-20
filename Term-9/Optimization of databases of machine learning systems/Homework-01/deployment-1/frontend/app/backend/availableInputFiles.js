'use strict';

angular.module('Metanome')
  .factory('AvailableInputFiles', ['$resource', 'ENV_VARS',
    function ($resource, ENV_VARS) {
      return $resource(ENV_VARS.API + '/api/file-inputs/:operation', {}, {
        get: {
          method: 'GET',
          params: {
            operation: 'available-input-files'
            },
          isArray: true
        },
        getDirectory: {
          method: 'POST',
          params: {
            operation: 'get-directory-files'
          },
          isArray: true
        }
      });
    }
  ])

;
