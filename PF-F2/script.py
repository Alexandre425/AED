import sys

if __name__ == "__main__":
  printed = 0
  if len(sys.argv) != 3:
    print("Wrong usage\n")
  solutions = open(sys.argv[1]).read().split("\n\n")
  prof = open(sys.argv[2]).read().split("\n\n")

  for i in range(min(len(prof), len(solutions))-1):
    resCost = solutions[i].split("\n")[0].split(" ")
    orgCost = prof[i].split(" ")
    #print(resCost)
    #print(orgCost)
    if resCost[4] != orgCost[4]:
      if printed == 0:
        print("In files {} and {}".format(sys.argv[1], sys.argv[2]))
        printed = 1
      print("Solution {} doesnt match".format(i+1))
      print("result:\t\t{}\noriginal:\t{}".format(solutions[i].split("\n")[0], prof[i]))
