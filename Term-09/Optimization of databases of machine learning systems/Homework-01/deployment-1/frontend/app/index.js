'use strict';

angular.module('Metanome', [
  'ngSanitize',
  'ngAnimate',
  'ngCookies',
  'ngResource',
  'ui.router',
  'ngMaterial',
  'ngDialog',
  'schemaForm',
  'angularSpinner',
  'md.data.table',
  'timer',
  'Metanome.config',
  'toaster'
])
  .config(function ($stateProvider, $urlRouterProvider, $qProvider) {
    $urlRouterProvider.otherwise('/new');
    $qProvider.errorOnUnhandledRejections(false);
  })
;
