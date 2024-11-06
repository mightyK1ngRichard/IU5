Feature: Testing the Equation
  Scenario: Test calculate 4 roots
    Given equation with coef A 1 B -10 C 9
    When we calculate roots
    Then we should see root1 -3 root2 -1 root3 1 root4 3

  Scenario: Test calculate 3 roots
    Given equation with coef A -4 B 16 C 0
    When we calculate roots
    Then we should see root1 -2 root2 0 root3 2 root4 empty

  Scenario: Test calculate 0 roots
    Given equation with coef A 431 B -123 C 665
    When we calculate roots
    Then we should see root1 empty root2 empty root3 empty root4 empty