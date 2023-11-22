import os

def revert():
    files = os.listdir("..")
    for file in files:
        if(file.split("_")[0] == "original"):
            os.system("mv ../"+file+" ../"+file.split("_")[1])

if __name__ == "__main__":
    revert()

#Example --> mv ../original_adder.cpp ../adder.cpp