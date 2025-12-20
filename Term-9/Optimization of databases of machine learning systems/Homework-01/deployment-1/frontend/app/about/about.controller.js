'use strict';

var app = angular.module('Metanome')

  .config(function config($stateProvider) {
    $stateProvider
      .state('about', {
        url: '/about',
        views: {
          'main@': {
            controller: 'AboutCtrl',
            templateUrl: 'app/about/about.html'
          }
        }
      })
  })

  .config(['$locationProvider', function($locationProvider) {
    $locationProvider.hashPrefix('');
  }]);

app.controller('AboutCtrl', function () {
});
