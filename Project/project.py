import sys
import random

STARTING_DISTANCE
PAR
def play():
    print ("This hole is a 230m par 5.")
    shots = 0
    dist = 230
    while dist != 0:
        print ("You are " + str(dist)+"m from the hole, after "+str(shots)+" shot /s.")
        print ("Club selection: press D for driver, I for Iron, P for Putter.")
        sys.stdout.write ("Choose club: ")
        inp = raw_input()
        inp = inp.upper()
        if inp == 'D':
            dist -= random.randint(80,120)
#   return random.randint(2,10)
           
def handleInput(rounds):
    instruction = '''This is a simple golf game in which each hole is 230m game away with par 5. You are able to choose from 3 clubs, the Driver, Iron or Putter. The Driver will hit around 100m, the Iron around 30m and the Putter around 10m. The putter is best used very close to the hole.'''
    inp = input()
    inp = inp.upper()
    if inp == 'I':
        print (instruction)
        return True
    elif inp == 'Q':    
        return False
    elif inp == 'P':
        rounds.append(play())
        return True
    else:
        print ("Invalid menu choice.")
        return True

def parStatus(entry):
    tempVal = entry - PAR
    if tempVal == 0:
        return "On par."
    elif tempVal > 0:
        return str(tempVal) + " over par."
    else:
        return str(abs(tempVal)) + " under par."    

def main():
    menu = '''(I)nstructions
(P)lay golf 
(Q)uit'''
    rounds = []
    print ("Enter your name")
    name = input()
    print ("Hello " + name +", welcome to Tropical Golf.")
    game = True
    while game:
        print (menu)
        game = handleInput(rounds)
    
    if len(rounds) > 0:
        currRound = 1
        print ("You're scores:")
        for entry in rounds:
            print ("Round " + str(currRound) + " : " + str(entry) + " shots. " + parStatus(entry))
            currRound += 1
    
    print ("\nFarewell and thanks for playing " +name+".")
if __name__ == "__main__":
    main()
