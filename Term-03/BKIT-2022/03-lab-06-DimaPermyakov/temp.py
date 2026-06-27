# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
import turtle

mitul = turtle.Turtle()
mitul.width(8)
mitul.color("#00FF00")
new = turtle.getscreen()
mitul.speed(10)

new.bgcolor("lightblue")

# Hidden Work(penup)
mitul.left(180)
mitul.penup()
mitul.forward(300)
mitul.right(90)
mitul.forward(100)
mitul.pendown()

# Printing H

# start to draw
mitul.forward(50)
mitul.right(90)
mitul.forward(50)
mitul.left(90)
mitul.forward(50)
mitul.left(90)

mitul.penup()
mitul.forward(50)
mitul.left(90)
mitul.pendown()
mitul.forward(50)
mitul.left(90)
mitul.forward(50)
mitul.right(90)
mitul.forward(50)

# printing A

mitul.penup()
mitul.left(90)
mitul.forward(15)
mitul.pendown()
mitul.left(70)
mitul.forward(110)
mitul.right(70)
mitul.right(70)
mitul.forward(110)
mitul.left(180)
mitul.forward(55)
mitul.left(70)
mitul.forward(38)
mitul.left(70)
mitul.penup()
mitul.forward(55)
mitul.left(110)

mitul.forward(100)

# printing P

mitul.left(90)
mitul.pendown()
mitul.forward(100)
mitul.right(90)
mitul.forward(50)
mitul.right(20)
mitul.forward(20)
mitul.right(70)
mitul.forward(40)
mitul.right(70)
mitul.forward(20)
mitul.right(20)
mitul.forward(50)
mitul.left(90)
mitul.forward(50)
mitul.left(90)
mitul.penup()
mitul.forward(100)

# printing P

mitul.left(90)
mitul.pendown()
mitul.forward(100)
mitul.right(90)
mitul.forward(50)
mitul.right(20)
mitul.forward(20)
mitul.right(70)
mitul.forward(40)
mitul.right(70)
mitul.forward(20)
mitul.right(20)
mitul.forward(50)
mitul.left(90)
mitul.forward(50)
mitul.left(90)
mitul.penup()
mitul.forward(100)

# printing Y

mitul.forward(20)
mitul.pendown()
mitul.left(90)
mitul.forward(50)
mitul.left(30)
mitul.forward(60)
mitul.backward(60)
mitul.right(60)
mitul.forward(60)
mitul.backward(60)
mitul.left(30)

# go Home.

mitul.penup()
mitul.home()

mitul.color("orange")
new.bgcolor("white")
# setting second row

mitul.backward(300)
mitul.right(90)
mitul.forward(60)
mitul.left(180)

# printing P


mitul.pendown()
mitul.forward(100)
mitul.right(90)
mitul.forward(50)
mitul.right(20)
mitul.forward(20)
mitul.right(70)
mitul.forward(40)
mitul.right(70)
mitul.forward(20)
mitul.right(20)
mitul.forward(50)
mitul.backward(50)
mitul.left(180)
mitul.right(20)
mitul.forward(20)
mitul.right(70)
mitul.forward(40)
mitul.right(70)
mitul.forward(20)
mitul.right(20)
mitul.forward(50)
mitul.right(90)
mitul.forward(10)

# go Home

mitul.penup()
mitul.home()

# setting up

mitul.backward(200)
mitul.right(90)
mitul.forward(10)
mitul.left(90)
mitul.pendown()
mitul.forward(20)
mitul.penup()
mitul.home()

# D

mitul.backward(150)
mitul.right(90)
mitul.forward(60)
mitul.pendown()
mitul.backward(100)
mitul.right(90)
mitul.forward(10)
mitul.backward(70)
mitul.left(180)
mitul.right(20)
mitul.forward(20)
mitul.right(70)
mitul.forward(88)
mitul.right(70)
mitul.forward(20)
mitul.right(20)
mitul.forward(70)

mitul.penup()
mitul.home()

# set up for A

mitul.backward(50)
mitul.right(90)
mitul.forward(65)
mitul.left(90)

# printing A


mitul.pendown()
mitul.left(70)
mitul.forward(110)
mitul.right(70)
mitul.right(70)
mitul.forward(110)
mitul.left(180)
mitul.forward(55)
mitul.left(70)
mitul.forward(38)
mitul.left(70)
mitul.penup()
mitul.forward(55)
mitul.left(110)

mitul.forward(100)

# printing Y


mitul.pendown()
mitul.left(90)
mitul.forward(50)
mitul.left(30)
mitul.forward(60)
mitul.backward(60)
mitul.right(60)
mitul.forward(60)
mitul.backward(60)
mitul.left(30)

# go to Home

mitul.penup()
mitul.home()

# settig pogition

mitul.right(90)
mitul.forward(215)
mitul.right(90)
mitul.forward(200)
mitul.right(90)

# color

mitul.color("blue")
new.bgcolor("black")

# printing Ido
# printing I


mitul.pendown()
mitul.forward(100)
mitul.right(90)
mitul.forward(45)
mitul.backward(90)
mitul.forward(45)
mitul.pendown()
mitul.right(90)
mitul.forward(100)
mitul.right(90)
mitul.forward(45)
mitul.backward(90)

# printing d
mitul.penup()
mitul.backward(70)
mitul.right(180)
mitul.forward(20)
mitul.left(90)
mitul.pendown()
mitul.forward(100)
mitul.right(180)
mitul.forward(45)
mitul.right(90)
mitul.forward(50)
mitul.left(20)
mitul.forward(20)
mitul.left(70)
mitul.forward(40)
mitul.left(70)
mitul.forward(20)
mitul.left(20)
mitul.forward(50)
mitul.penup()

# printing 0
mitul.forward(70)
mitul.pendown()
mitul.circle(35)

# setup
mitul.penup()
mitul.left(90)
mitul.forward(80)
mitul.left(90)
mitul.forward(7)

mitul.forward(100)

# design


# design pattern
mitul.home()
mitul.forward(200)
mitul.pendown()
mitul.color("PURPLE")
mitul.width(3)
mitul.speed(0)


def squre(length, angle):
    mitul.forward(length)
    mitul.right(angle)
    mitul.forward(length)
    mitul.right(angle)

    mitul.forward(length)
    mitul.right(angle)
    mitul.forward(length)
    mitul.right(angle)


squre(80, 90)

for i in range(36):
    mitul.right(10)
    squre(80, 90)

turtle.mainloop()
