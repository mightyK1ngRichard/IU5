# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
from behave import Given, When, Then
from equation import calculate


@Given("equation with coef A {A} B {B} C {C}")
def given_increment(context, A: str, B: str, C: str):
    context.A = int(A)
    context.B = int(B)
    context.C = int(C)


@When("we calculate {object}")
def given_increment(context, object: str):
    context.results = calculate(context.A, context.B, context.C)


@Then("we should see root1 {root1} root2 {root2} root3 {root3} root4 {root4}")
def then_results(context, root1: str, root2: str, root3: str, root4: str):
    if root1 == "empty":
        assert (context.results == ())
    elif root2 == "empty":
        assert (context.results == (int(root1)))
    elif root3 == "empty":
        assert (context.results == (int(root1), int(root2)))
    elif root4 == "empty":
        assert (context.results == (int(root1), int(root2), int(root3)))
    else:
        assert (context.results == (int(root1), int(root2), int(root3), int(root4)))
