import time
from time import sleep
from tkinter import *
tk=Tk()
win=Canvas(tk, width=700, height=700)
win.pack()
#functions

#north lights STRAIGHT
red=win.create_oval(205,5,250,50, fill="black")
amber=win.create_oval(205,55,250,100, fill ="black")
green=win.create_oval(205,105,250,150, fill="black")
#NORTH LIGHTS LEFT
red=win.create_oval(155,5,200,50, fill="black")
amber=win.create_oval(155,55,200,100, fill ="black")
green=win.create_oval(155,105,200,150, fill="black")
#NORTH LIGHTS RIGHT
red=win.create_oval(255,5,300,50, fill="black")
amber=win.create_oval(255,55,300,100, fill ="black")
green=win.create_oval(255,105,300,150, fill="black")

   
#west lights STRAIGHT
red=win.create_oval(55,205,100,250, fill="black")
yellow=win.create_oval(55,255,100,300, fill="black")
green=win.create_oval(55,305,100,350, fill="black")
#west lights left
red=win.create_oval(5,205,50,250, fill="black")
yellow=win.create_oval(5,255,50,300,fill="black")
green=win.create_oval(5,305,50,350, fill="black")
#WEST LIGHTS PROTECTED RIGHT 
red=win.create_oval(105,205,150,250, fill="black")
yellow=win.create_oval(105,255,150,300, fill="black")
green=win.create_oval(105,305,150,350, fill="black")

#south lights STRAIGHT
red=win.create_oval(205,405,250,450, fill="black")
amber=win.create_oval(205,455,250,500, fill ="black")
green=win.create_oval(205,505,250,550, fill="black")
#south lights left
red=win.create_oval(155,405,200,450, fill="black")
amber=win.create_oval(155,455,200,500, fill ="black")
green=win.create_oval(155,505,200,550, fill="black")
#SOUTH LIGHTS PROTECTED RIGHT 
red=win.create_oval(255,405,300,450, fill="black")
amber=win.create_oval(255,455,300,500, fill ="black")
green=win.create_oval(255,505,300,550, fill="black")

#east lights STRAIGHT
red=win.create_oval(405,205,450,250, fill="black")
yellow=win.create_oval(405,255,450,300, fill="black")
green=win.create_oval(405,305,450,350, fill="black")
#east lights left 
red=win.create_oval(355,205,400,250, fill="black")
yellow=win.create_oval(355,255,400,300, fill="black")
green=win.create_oval(355,305,400,350, fill="black")
#EAST LIGHTS PROTECTED RIGHT
red=win.create_oval(455,205,500,250, fill="black")
yellow=win.create_oval(455,255,500,300, fill="black")
green=win.create_oval(455,305,500,350, fill="black")

class trafficLights:
    def state1():
        #<NLR | ELR | SLR | WLR> 
        #<RRR | GRG | RRR | GRG>

        win.delete("yellowNR")
        win.delete("redER")
        win.delete("yellowWL")
        win.delete("redE")
        
        #north and south STRAIGHT red 
        redN=win.create_oval(205,5,250,50, fill="red", tags="redN") 
        redS=win.create_oval(205,405,250,450, fill="red",tags="redS")
        #north and south LEFT red
        redNL=win.create_oval(155,5,200,50, fill="red", tags="redNL") 
        redSL=win.create_oval(155,405,200,450, fill="red",tags="redSL")
        #east and west STRAIGHT green
        greenE=win.create_oval(405,305,450,350, fill="green",tags="greenE")
        greenW=win.create_oval(55,305,100,350, fill="green", tags="greenW")

        #EAST AND WEST RIGHT GREEN
        greenER=win.create_oval(455,305,500,350, fill="green",tags="greenER")
        greenWR=win.create_oval(105,305,150,350, fill="green",tags="greenWR")

        #NORTH AND SOUTH PR RED
        redNR=win.create_oval(255,5,300,50,  fill="red",tags="redNR")
        redSR= win.create_oval(255,405,300,450, fill="red",tags="redSR")
        
        #east and west LEFT red
        redEL=win.create_oval(355,205,400,250, fill="red",tags="redEL")
        redWL=win.create_oval(5,205,50,250, fill="red",tags="redWL")

        tk.update()
        sleep(10)

      
    def state2():
        #<NLR | ELR | SLR | WLR> 
        #<RRR | YRY | RRR |YRY> 

        #DELETE EAST AND WEST STRAIGHT GREENS 
        win.delete("greenE")
        win.delete("greenW")
        win.delete("greenER")
        win.delete("greenWR")
        
        #east and west STRAIGHT yellow 
        yellowE=win.create_oval(405,255,450,300, fill="orange",tags="yellowE")
        yellowW=win.create_oval(55,255,100,300, fill="orange",tags="yellowW")

        yellowER=win.create_oval(455,255,500,300, fill="orange",tags="yellowER")
        yellowWR=win.create_oval(105,255,150,300, fill="orange",tags="yellowWR")
        
        tk.update()
        sleep(5)


    def state3():
        #<NLR | ELR | SLR | WLR> 
        #<RRG | RGR | RRG | RGR> 

        #delete east and west straight yellows & EAST AND WEST REDS 
        win.delete("yellowE")
        win.delete("yellowW")
        win.delete("yellowER")
        win.delete("yellowWR")
        win.delete("redNR")
        win.delete("redSR")
        win.delete("redEL")
        win.delete("redWL")

        #MAKE EAST AND WEST LEFTS GREEN
        greenEL=win.create_oval(355,305,400,350, fill="green",tags="greenEL")
        greenWL=win.create_oval(5,305,50,350, fill="green", tags="greenWL")

        #make east and west straights red
        redE=win.create_oval(405,205,450,250, fill="red", tags="redE") 
        redW= win.create_oval(55,205,100,250, fill="red", tags="redW") 


        redER= win.create_oval(455,205,500,250, fill="red",tags="redER")
        redWR=win.create_oval( 105,205,150,250, fill="red",tags="redWR")

        greenNR=win.create_oval(255,105,300,150, fill="green",tags="greenNR")
        greenSR=win.create_oval(255,505,300,550, fill="green",tags="greenSR")

        
        tk.update()
        sleep(10)
        
    def state4():
        #<NLR | ELR | SLR | WLR> 
        #<RRY | RGR | RRG | RYR> 

        #delete west green LEFT 
        win.delete("greenWL")
        win.delete("greenNR")

        #make west left yellow
        yellowWL=win.create_oval(5,255,50,300, fill="orange",tags="yellowWL")
        yellowNR=win.create_oval( 255,55,300,100,fill="orange",tags="yellowNR")
 
        tk.update()
        sleep(5)

    def state5():
        #<NLR | ELR | SLR | WLR> 
        #<RRR | GGG | RRG | RRR>
        #delete west left yellow & EAST RED 
        win.delete("yellowWL")
        win.delete("yellowNR")
        win.delete("redE")
        win.delete("redER")

        #make east straight green & west left red
        greenER= win.create_oval(455,305,500,350, fill="green",tags="greenER")
        greenE=win.create_oval(405,305,450,350, fill="green",tags="greenE")
        redWL=win.create_oval(5,205,50,250, fill="red",tags="redWL")

        redNR=win.create_oval(255,5,300,50,  fill="red",tags="redNR")

        tk.update()
        sleep(10)

    def state6():
        #<NLR | ELR | SLR | WLR> 
        #<RRR | YYY | RRG | RRR>

        #remove east straight and east left greens
        win.delete("greenE")
        win.delete("greenEL")
        win.delete("greenER")

        #make east straight and east left yellow
        yellowE=win.create_oval(405,255,450,300, fill="orange",tags="yellowE")
        yellowEL=win.create_oval(355,255,400,300, fill="orange",tags="yellowEL")
        yellowER=win.create_oval( 455,255,500,300, fill="orange",tags="yellowER")
        
        tk.update()
        sleep(5)

    def state7():
        #<GRG | RRR | GRG | RRR>

        win.delete("yellowE")
        win.delete("yellowEL")
        win.delete("yellowER")
        win.delete("redNR")
        win.delete("redN")
        win.delete("redS")

        #MAKE BOTH EAST STRAIGHT AND EAST LEFT RED
        redE=win.create_oval(405,205,450,250, fill="red", tags="redE") 
        redEL=win.create_oval(355,205,400,250, fill="red", tags="redEL")
        redER= win.create_oval(455,205,500,250, fill="red",tags="redER")
        
        #MAKE NORTH AND SOUTH STRAIGHT GREEN
        greenN=win.create_oval(205,105,250,150,fill="green",tags="greenN")
        greenS= win.create_oval( 205,505,250,550, fill="green",tags="greenS")
        greenNR=win.create_oval(255,105,300,150, fill="green",tags="greenNR")

        tk.update()
        sleep(10)

    def state8():
        #<NLR | ELR | SLR | WLR> 
        #<YRY | RRR | GRG | RRR>
        
        win.delete("greenN")
        win.delete("greenNR")
        yellowN= win.create_oval(205,55,250,100,fill="yellow",tags="yellowN")
        yellowNR= win.create_oval( 255,55,300,100,fill="orange",tags="yellowNR")
        tk.update()
        sleep(5)

    def state9():
        #<NLR | ELR | SLR | WLR> 
        #<RRR | RRR | GGG | RRG>

        win.delete("yellowN")
        win.delete("redSL")
        win.delete("yellowNR")
        win.delete("redWR")

        greenWR= win.create_oval(105,305,150,350, fill="green",tags="greenWR")
        redNR=win.create_oval(255,5,300,50,  fill="red",tags="redNR")
        greenSL=win.create_oval(155,505,200,550, fill="green", tags="greenSL")
        redN= win.create_oval(205,5,250,50, fill="red", tags="redN") 

        
        tk.update()
        sleep(10)

    def state10():
        #<NLR | ELR | SLR | WLR> 
        #<RRR | RRR | YGY | RRG>

        win.delete("greenSR")
        win.delete("greenS")
        yellowSR= win.create_oval(255,455,300,500, fill="orange",tags="yellowSR")
        yellowS= win.create_oval(205,455,250,500,fill="yellow",tags="yellowS")
        
        tk.update()
        sleep(5)
        
    def state11():
        #<NLR | ELR | SLR | WLR> 
        #<RGR | RRG | RGR | RRG>

        
        win.delete("yellowS")
        win.delete("yellowSR")
        win.delete("redNL")
        win.delete("redER")

        greenER= win.create_oval(455,305,500,350, fill="green",tags="greenER")
        #greenNR= win.create_oval(255,105,300,150, fill="green",tags="greenNR")
        greenNL= win.create_oval(155,105,200,150,fill="green",tags="greenNL") 
        redS= win.create_oval(205,405,250,450, fill="red",tags="redS")
        redSR = win.create_oval(255,405,300,450, fill="red",tags="redSR")
                                  
        tk.update()
        sleep(10)

    def state12():
        #<NLR | ELR | SLR | WLR> 
        #<RGG | RRG | RYY | RRY>

        win.delete("greenSL")
        win.delete("greenWR")

        yellowWR= win.create_oval(105,255,150,300, fill="orange",tags="yellowWR")
        yellowSL= win.create_oval(155,455,200,500, fill="yellow",tags="yellowSL")
        
        tk.update()
        sleep(5)

    def state13():
        #<NLR | ELR | SLR | WLR> 
        #<GGG | RRG | RRR | RRR>

        win.delete("redN")
        win.delete("redNR")
        win.delete("yellowWR")
        win.delete("yellowSL")
        win.delete("yellowSR")

        redWR= win.create_oval( 105,205,150,250, fill="red",tags="redWR")
        redSR= win.create_oval(255,405,300,450, fill="red",tags="redSR")
        redSL=win.create_oval(155,405,200,450, fill="red",tags="redSL")
        greenN=win.create_oval(205,105,250,150,fill="green",tags="greenN")
        greenNR= win.create_oval(255,105,300,150, fill="green",tags="greenNR")
        
        tk.update()
        sleep(10)

    def state14():
        #<NLR | ELR | SLR | WLR> 
        #<YYG | RRY | RRR| RRR>

        win.delete("greenER")
        win.delete("greenN")
        win.delete("greenNL")

        yellowER= win.create_oval(455,255,500,300, fill="orange",tags="yellowER")
        yellowN= win.create_oval(205,55,250,100,fill="yellow",tags="yellowN")
        yellowNL= win.create_oval(155,55,200,100,fill="yellow",tags="yellowNL")
        
        tk.update()
        sleep(5)

    def state15():
        #<NLR | ELR | SLR | WLR> 
        #<RRG | RRR | RRR| GGG>

        win.delete("yellowER")
        win.delete("yellowN")
        win.delete("yellowNL")
        win.delete("redW")
        win.delete("redWL")
        win.delete("redWR")
        win.delete("redNR")
                                  
        greenWR= win.create_oval(105,305,150,350, fill="green",tags="greenWR")
        redER= win.create_oval(455,205,500,250, fill="red",tags="redER")
        redN=win.create_oval(205,5,250,50, fill="red", tags="redN")
        redNL=win.create_oval(155,5,200,50, fill="red", tags="redNL")
        greenW= win.create_oval(55,305,100,350, fill="green", tags="greenW")
        greenWL= win.create_oval(5,305,50,350, fill="green", tags="greenWL")
        
        tk.update()
        sleep(10)

    def state16():
        #<NLR | ELR | SLR | WLR> 
        #<RRY | RRR | RRR | GYG>

        win.delete("greenWL")
        win.delete("greenNR")

        yellowNR= win.create_oval( 255,55,300,100,fill="orange",tags="yellowNR")
        yellowWL= win.create_oval(5,255,50,300, fill="yellow", tags="yellowWL")
        tk.update()
        sleep(5)

lights = trafficLights

for x in range(200):
    lights.state1()
    lights.state2()
    lights.state3()
    lights.state4()
    lights.state5()
    lights.state6()
    lights.state7()
    lights.state8()
    lights.state9()
    lights.state10()
    lights.state11()
    lights.state12()
    lights.state13()
    lights.state14()
    lights.state15()
    lights.state16()
    
#root.mainloop()

tk.mainloop()


	
